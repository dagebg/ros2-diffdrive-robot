// #include <Arduino.h>
// #include <Wire.h>
// #include "WifiDebug.h"
// #include "SECRETS.h"
// #include "ImuReader.h"

// ImuReader imu;

// void setup() {
//   wifiDebugBegin(ESP_WIFI_SSID, ESP_WIFI_PASSWORD);
//   delay(500);
//   if (!imu.begin()) {
//     wifiDebugPrintln("IMU initialization failed");
//     while (true) {
//       delay(1000);
//     }
//   }
//   wifiDebugPrintln("Robot firmware ready.");
// }

// void loop() {
//   wifiDebugLoop();

//   static unsigned long lastPrint = 0;
//   if (millis() - lastPrint >= 1000) {
//     lastPrint = millis();

//     imu.update9250();
//     Mpu9250Sample s9250 = imu.getMpu9250();

//     imu.update6050();
//     Mpu6050Sample s6050 = imu.getMpu6050();

//     char buf[160];
//     snprintf(buf, sizeof(buf),
//       "[9250] Accel: %.3f %.3f %.3f | Gyro: %.3f %.3f %.3f",
//       s9250.accelX_mss, s9250.accelY_mss, s9250.accelZ_mss,
//       s9250.gyroX_rads, s9250.gyroY_rads, s9250.gyroZ_rads);
//     wifiDebugPrintln(String(buf));

//     snprintf(buf, sizeof(buf),
//       "[6050] Accel(g): %.3f %.3f %.3f | Gyro(dps): %.3f %.3f %.3f",
//       s6050.accelX_g, s6050.accelY_g, s6050.accelZ_g,
//       s6050.gyroX_dps, s6050.gyroY_dps, s6050.gyroZ_dps);
//     wifiDebugPrintln(String(buf));
//   }
// }


