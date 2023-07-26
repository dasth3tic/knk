#include "RTC.h"
#include "configuration.h"
#include "detect/ScanI2C.h"
#include "main.h"
#include <sys/time.h>
#include <time.h>

static RTCQuality currentQuality = RTCQualityNone;

RTCQuality getRTCQuality()
{
    return currentQuality;
}

// stuff that really should be in in the instance instead...
static uint32_t
    timeStartMsec; // Once we have a GPS lock, this is where we hold the initial msec clock that corresponds to that time
static uint64_t zeroOffsetSecs; // GPS based time in secs since 1970 - only updated once on initial lock

/**
 * Reads the current date and time from the RTC module and updates the system time.
 * @return True if the RTC was successfully read and the system time was updated, false otherwise.
 */
void readFromRTC()
{
    struct timeval tv; /* btw settimeofday() is helpful here too*/
#ifdef RV3028_RTC
    if (rtc_found.address == RV3028_RTC) {
        uint32_t now = millis();
        Melopero_RV3028 rtc;
#ifdef I2C_SDA1
        rtc.initI2C(rtc_found.port == ScanI2C::I2CPort::WIRE1 ? Wire1 : Wire);
#else
        rtc.initI2C();
#endif
        tm t;
        t.tm_year = rtc.getYear() - 1900;
        t.tm_mon = rtc.getMonth() - 1;
        t.tm_mday = rtc.getDate();
        t.tm_hour = rtc.getHour();
        t.tm_min = rtc.getMinute();
        t.tm_sec = rtc.getSecond();
        tv.tv_sec = mktime(&t);
        tv.tv_usec = 0;
        LOG_DEBUG("Read RTC time from RV3028 as %ld\n", tv.tv_sec);
        timeStartMsec = now;
        zeroOffsetSecs = tv.tv_sec;
        if (currentQuality == RTCQualityNone) {
            currentQuality = RTCQualityDevice;
        }
    }
#elif defined(PCF8563_RTC)
    if (rtc_found.address == PCF8563_RTC) {
        uint32_t now = millis();
        PCF8563_Class rtc;

#ifdef I2C_SDA1
        rtc.begin(rtc_found.port == ScanI2C::I2CPort::WIRE1 ? Wire1 : Wire);
#else
        rtc.begin();
#endif

        auto tc = rtc.getDateTime();
        tm t;
        t.tm_year = tc.year - 1900;
        t.tm_mon = tc.month - 1;
        t.tm_mday = tc.day;
        t.tm_hour = tc.hour;
        t.tm_min = tc.minute;
        t.tm_sec = tc.second;
        tv.tv_sec = mktime(&t);
        tv.tv_usec = 0;
        LOG_DEBUG("Read RTC time from PCF8563 as %ld\n", tv.tv_sec);
        timeStartMsec = now;
        zeroOffsetSecs = tv.tv_sec;
        if (currentQuality == RTCQualityNone) {
            currentQuality = RTCQualityDevice;
        }
    }
#else
    if (!gettimeofday(&tv, NULL)) {
        uint32_t now = millis();
        LOG_DEBUG("Read RTC time as %ld\n", tv.tv_sec);
        timeStartMsec = now;
        zeroOffsetSecs = tv.tv_sec;
    }
#endif
}

/**
 * Sets the RTC (Real-Time Clock) if the provided time is of higher quality than the current RTC time.
 * 
 * @param q The quality of the provided time.
 * @param tv A pointer to a timeval struct containing the time to potentially set the RTC to.
 * @return True if the RTC was set, false otherwise.
 * 
 * If we haven't yet set our RTC this boot, set it from a GPS derived time
 */
bool perhapsSetRTC(RTCQuality q, const struct timeval *tv)
{
    static uint32_t lastSetMsec = 0;
    uint32_t now = millis();

    bool shouldSet;
    if (q > currentQuality) {
        currentQuality = q;
        shouldSet = true;
        LOG_DEBUG("Upgrading time to RTC %ld secs (quality %d)\n", tv->tv_sec, q);
    } else if (q == RTCQualityGPS && (now - lastSetMsec) > (12 * 60 * 60 * 1000UL)) {
        // Every 12 hrs we will slam in a new GPS time, to correct for local RTC clock drift
        shouldSet = true;
        LOG_DEBUG("Reapplying external time to correct clock drift %ld secs\n", tv->tv_sec);
    } else
        shouldSet = false;

    if (shouldSet) {
        lastSetMsec = now;

        // This delta value works on all platforms
        timeStartMsec = now;
        zeroOffsetSecs = tv->tv_sec;

        // If this platform has a setable RTC, set it
#ifdef RV3028_RTC
        if (rtc_found.address == RV3028_RTC) {
            Melopero_RV3028 rtc;
#ifdef I2C_SDA1
            rtc.initI2C(rtc_found.port == ScanI2C::I2CPort::WIRE1 ? Wire1 : Wire);
#else
            rtc.initI2C();
#endif
            tm *t = localtime(&tv->tv_sec);
            rtc.setTime(t->tm_year + 1900, t->tm_mon + 1, t->tm_wday, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
            LOG_DEBUG("RV3028_RTC setTime %02d-%02d-%02d %02d:%02d:%02d %ld\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                      t->tm_hour, t->tm_min, t->tm_sec, tv->tv_sec);
        }
#elif defined(PCF8563_RTC)
        if (rtc_found.address == PCF8563_RTC) {
            PCF8563_Class rtc;

#ifdef I2C_SDA1
            rtc.begin(rtc_found.port == ScanI2C::I2CPort::WIRE1 ? Wire1 : Wire);
#else
            rtc.begin();
#endif
            tm *t = localtime(&tv->tv_sec);
            rtc.setDateTime(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
            LOG_DEBUG("PCF8563_RTC setDateTime %02d-%02d-%02d %02d:%02d:%02d %ld\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                      t->tm_hour, t->tm_min, t->tm_sec, tv->tv_sec);
        }
#elif defined(ARCH_ESP32)
        settimeofday(tv, NULL);
#endif

        // nrf52 doesn't have a readable RTC (yet - software not written)
#ifdef HAS_RTC
        readFromRTC();
#endif

        return true;
    } else {
        return false;
    }
}

/**
 * Sets the RTC time if the provided time is of higher quality than the current RTC time.
 * 
 * @param q The quality of the provided time.
 * @param t The time to potentially set the RTC to.
 * @return True if the RTC was set to the provided time, false otherwise.
 */
bool perhapsSetRTC(RTCQuality q, struct tm &t)
{
    /* Convert to unix time
    The Unix epoch (or Unix time or POSIX time or Unix timestamp) is the number of seconds that have elapsed since January 1, 1970
    (midnight UTC/GMT), not counting leap seconds (in ISO 8601: 1970-01-01T00:00:00Z).
    */
    time_t res = mktime(&t);
    struct timeval tv;
    tv.tv_sec = res;
    tv.tv_usec = 0; // time.centisecond() * (10 / 1000);

    // LOG_DEBUG("Got time from GPS month=%d, year=%d, unixtime=%ld\n", t.tm_mon, t.tm_year, tv.tv_sec);
    if (t.tm_year < 0 || t.tm_year >= 300) {
        // LOG_DEBUG("Ignoring invalid GPS month=%d, year=%d, unixtime=%ld\n", t.tm_mon, t.tm_year, tv.tv_sec);
        return false;
    } else {
        return perhapsSetRTC(q, &tv);
    }
}

/**
 * Returns the current time in seconds since the Unix epoch (January 1, 1970).
 *
 * @return The current time in seconds since the Unix epoch.
 */
uint32_t getTime()
{
    return (((uint32_t)millis() - timeStartMsec) / 1000) + zeroOffsetSecs;
}

/**
 * Returns the current time from the RTC if the quality of the time is at least minQuality.
 *
 * @param minQuality The minimum quality of the RTC time required for it to be considered valid.
 * @return The current time from the RTC if it meets the minimum quality requirement, or 0 if the time is not valid.
 */
uint32_t getValidTime(RTCQuality minQuality)
{
    return (currentQuality >= minQuality) ? getTime() : 0;
}
