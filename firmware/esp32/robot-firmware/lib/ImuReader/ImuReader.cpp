#include "ImuReader.h"

bool ImuReader::begin() {
  Wire.begin(21, 22);
  Wire.setClock(400000);

  int status9250 = mpu9250_.begin();
  if (status9250 < 0) {
    Serial.println("MPU9250 initialization unsuccessful");
    return false;
  }
  mpu9250_.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  mpu9250_.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  mpu9250_.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  mpu9250_.setSrd(19);

  mpu6050_.initialize();
  if (!mpu6050_.testConnection()) {
    Serial.println("MPU6050 connection failed");
    return false;
  }

  mpu6050_.setXAccelOffset(0);
  mpu6050_.setYAccelOffset(0);
  mpu6050_.setZAccelOffset(0);
  mpu6050_.setXGyroOffset(0);
  mpu6050_.setYGyroOffset(0);
  mpu6050_.setZGyroOffset(0);

  return true;
}

bool ImuReader::update9250() {
  mpu9250_.readSensor();
  mpu9250Sample_.accelX_mss = mpu9250_.getAccelX_mss();
  mpu9250Sample_.accelY_mss = mpu9250_.getAccelY_mss();
  mpu9250Sample_.accelZ_mss = mpu9250_.getAccelZ_mss();
  mpu9250Sample_.gyroX_rads = mpu9250_.getGyroX_rads();
  mpu9250Sample_.gyroY_rads = mpu9250_.getGyroY_rads();
  mpu9250Sample_.gyroZ_rads = mpu9250_.getGyroZ_rads();
  mpu9250Sample_.magX_uT = mpu9250_.getMagX_uT();
  mpu9250Sample_.magY_uT = mpu9250_.getMagY_uT();
  mpu9250Sample_.magZ_uT = mpu9250_.getMagZ_uT();
  mpu9250Sample_.temperature_C = mpu9250_.getTemperature_C();
  return true;
}

bool ImuReader::update6050() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu6050_.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  mpu6050Sample_.accelX_g = ax / kAccelSensitivity_2g;
  mpu6050Sample_.accelY_g = ay / kAccelSensitivity_2g;
  mpu6050Sample_.accelZ_g = az / kAccelSensitivity_2g;
  mpu6050Sample_.gyroX_dps = gx / kGyroSensitivity_250dps;
  mpu6050Sample_.gyroY_dps = gy / kGyroSensitivity_250dps;
  mpu6050Sample_.gyroZ_dps = gz / kGyroSensitivity_250dps;

  return true;
}