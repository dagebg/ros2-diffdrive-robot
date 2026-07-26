#ifndef IMU_READER_H
#define IMU_READER_H

#include <Arduino.h>
#include <Wire.h>
#include "MPU9250.h"
#include "I2Cdev.h"
#include "MPU6050.h"

struct Mpu9250Sample {
  float accelX_mss, accelY_mss, accelZ_mss;
  float gyroX_rads, gyroY_rads, gyroZ_rads;
  float magX_uT, magY_uT, magZ_uT;
  float temperature_C;
};

struct Mpu6050Sample {
  float accelX_g, accelY_g, accelZ_g;
  float gyroX_dps, gyroY_dps, gyroZ_dps;
};

class ImuReader {
public:
  bool begin();
  bool update9250();
  bool update6050();

  Mpu9250Sample getMpu9250() const { return mpu9250Sample_; }
  Mpu6050Sample getMpu6050() const { return mpu6050Sample_; }

private:
  static constexpr float kAccelSensitivity_2g = 16384.0f;
  static constexpr float kGyroSensitivity_250dps = 131.0f;

  MPU9250 mpu9250_{Wire, 0x69};
  MPU6050 mpu6050_{0x68};

  Mpu9250Sample mpu9250Sample_{};
  Mpu6050Sample mpu6050Sample_{};
};

#endif