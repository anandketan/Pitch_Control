# Arduino MPU-9250 - Gyroscope Motion Processing

The MPU-9250 is a 9-axis Motion Tracking device that combines a 3-axis gyroscope, 3-axis accelerometer, 3-axis magnetometer and a Digital Motion Processor. 
With its dedicated I2C sensor bus, the MPU-9250 directly provides complete 9-axis DoF output. In this project, the gyroscope function is explored in controlling pitch by
altering elevator deflection angle.

Procedure for using MPU-9250 - refer "arduino_pitch.cpp" - 3 DoF gyrosocpe: <br>
1. Fix address, reset calibrate, reset threshold from previous iterations.
2. Set up clock souorce, scale and range of functioning.
3. Read input for elevator as 8-bit values loaded into fast registers.
4. Change angle of deflection to alter pitch suitably.

## References
Pitch controller design: https://www.researchgate.net/figure/The-pitch-controller-synthesis_fig1_275533475  <br>
Arduino MPU-9250 manual: https://invensense.tdk.com/products/motion-tracking/9-axis/mpu-9250/  <br>
PID tuning methods: https://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID



