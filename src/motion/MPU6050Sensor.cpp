#include "MPU6050Sensor.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR

MPU6050Sensor::MPU6050Sensor(ScanI2C::DeviceAddress address) 
: MotionSensor::MotionSensor(ScanI2C::DeviceType::MPU6050, address)
{}

bool MPU6050Sensor::init() {
    if (sensor.begin(deviceAddress())) 
    {
        // setup motion detection
        sensor.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
        sensor.setMotionDetectionThreshold(1);
        sensor.setMotionDetectionDuration(20);
        sensor.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
        sensor.setInterruptPinPolarity(true);
        LOG_DEBUG("MPU6050Sensor::init ok\n");
        return true;
    } 
    LOG_DEBUG("MPU6050Sensor::init failed\n");
    return false;
}

int32_t MPU6050Sensor::runOnce()
{
    if (sensor.getMotionInterruptStatus()) {
        wakeScreen();
    } 
    return MOTION_SENSOR_CHECK_INTERVAL_MS;
}

#endif