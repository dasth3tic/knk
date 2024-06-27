#pragma once

#include "../freertosinc.h"
#include <Print.h>
#include <stdarg.h>
#include <string>

/**
 * A Printable that can be switched to squirt its bytes to a different sink.
 * This class is mostly useful to allow debug printing to be redirected away from Serial
 * to some other transport if we switch Serial usage (on the fly) to some other purpose.
 */
class RedirectablePrint : public Print
{
    Print *dest;

    /// Used to allow multiple logDebug messages to appear on a single log line
    bool isContinuationMessage = false;

#ifdef HAS_FREE_RTOS
    SemaphoreHandle_t inDebugPrint = nullptr;
    StaticSemaphore_t _MutexStorageSpace;
#else
    volatile bool inDebugPrint = false;
#endif
  protected:
    /**
     * If true we are talking to a smart host and all messages (including log messages) must be framed as protobufs.
     */
    bool usingProtobufs = false;

  public:
    explicit RedirectablePrint(Print *_dest) : dest(_dest) {}

    /**
     * Set a new destination
     */
    void rpInit();
    void setDestination(Print *dest);

    virtual size_t write(uint8_t c);

    /**
     * Debug logging print message
     *
     * If the provide format string ends with a newline we assume it is the final print of a single
     * log message.  Otherwise we assume more prints will come before the log message ends.  This
     * allows you to call logDebug a few times to build up a single log message line if you wish.
     */
    size_t log(const char *logLevel, const char *format, ...) __attribute__((format(printf, 3, 4)));

    /** like printf but va_list based */
    size_t vprintf(const char *format, va_list arg);

    void hexDump(const char *logLevel, unsigned char *buf, uint16_t len);

    std::string mt_sprintf(const std::string fmt_str, ...);

  private:
    void log_to_serial(const char *logLevel, const char *format, va_list arg);
    void log_to_syslog(const char *logLevel, const char *format, va_list arg);
    void log_to_ble(const char *logLevel, const char *format, va_list arg);
};

class NoopPrint : public Print
{
  public:
    virtual size_t write(uint8_t c) { return 1; }
};

/**
 * A printer that doesn't go anywhere
 */
extern NoopPrint noopPrint;