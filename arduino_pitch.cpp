//MPU-9250 SiP 9-axis Motion Processing Unit
//Combines two chips: the MPU-6500, which contains a 3-axis gyroscope with a 3-axis accelerometer
//And the AK-8963, containing a 3-axis digital compass

//*********************************************************

//Pitch Control using the MPU-9250 to alter deflector angle

#include "Arduino.h"
#include <Wire.h>
#include <math.h>
#include <MPU9250.h>

bool MPU9250::begin(mpu9250_dps_t scale, mpu9250_range_t range, int mpua)
{
    mpuAddress = mpua;   //Set address

    Wire.begin();

    dg.XAxis = 0;   //Reset calibrate values
    dg.YAxis = 0;
    dg.ZAxis = 0;
    useCalibrate = false;

    tg.XAxis = 0;    //Reset threshold values
    tg.YAxis = 0;
    tg.ZAxis = 0;
    actualThreshold = 0;

    if (fastRegister8(MPU9250_REG_AM_I) != 0x68)   //MPU-9250 rapid check register 
    {
	return false;
    }

    setClockSource(MPU9250_CLOCK_PLL_XGYRO);    //Set clock source

    setScale(scale);   //Set scale and range
    setRange(range);

    setSleepEnabled(false);

    return true;
}

void MPU9250::setScale(mpu9250_dps_t scale)
{
    uint8_t value;

    switch (scale)
    {
	case MPU9250_SCALE_250DPS:
	    dpsPerDigit = .007633f;
	    break;
	case MPU9250_SCALE_500DPS:
	    dpsPerDigit = .015267f;
	    break;
	case MPU9250_SCALE_1000DPS:
	    dpsPerDigit = .030487f;
	    break;
	case MPU9250_SCALE_2000DPS:
	    dpsPerDigit = .060975f;
	    break;
	default:
	    break;
    }

    value = readRegister8(MPU9250_REG_GYRO_CONFIG);   //Initialize transfer of pitch data
    value &= 0b11100111;
    value |= (scale << 3);
    writeRegister8(MPU9250_REG_GYRO_CONFIG, value);
}

mpu9250_dps_t MPU9250::getScale(void)
{
    uint8_t value;
    value = readRegister8(MPU9250_REG_GYRO_CONFIG);   //Read deflector inputs
    value &= 0b00011000;
    value >>= 3;
    return (mpu9250_dps_t)value;
}

void MPU9250::setRange(mpu9250_range_t range)
{
    uint8_t value;

    switch (range)
    {
	case MPU9250_RANGE_2G:
	    rangePerDigit = .000061f;
	    break;
	case MPU9250_RANGE_4G:
	    rangePerDigit = .000122f;
	    break;
	case MPU9250_RANGE_8G:
	    rangePerDigit = .000244f;
	    break;
	case MPU9250_RANGE_16G:
	    rangePerDigit = .0004882f;
	    break;
	default:
	    break;
    }

    value = readRegister8(MPU9250_REG_ACCEL_CONFIG);
    value &= 0b11100111;
    value |= (range << 3);
    writeRegister8(MPU9250_REG_ACCEL_CONFIG, value);
}

mpu9250_range_t MPU9250::getRange(void)   //Read 8-bits from deflector register
{
    uint8_t value;
    value = readRegister8(MPU9250_REG_ACCEL_CONFIG);
    value &= 0b00011000;
    value >>= 3;
    return (mpu9250_range_t)value;
}

void MPU9250::setDHPFMode(mpu9250_dhpf_t dhpf)
{
    uint8_t value;
    value = readRegister8(MPU9250_REG_ACCEL_CONFIG);
    value &= 0b11111000;
    value |= dhpf;
    writeRegister8(MPU9250_REG_ACCEL_CONFIG, value);
}

void MPU9250::setDLPFMode(mpu9250_dlpf_t dlpf)
{
    uint8_t value;
    value = readRegister8(MPU9250_REG_CONFIG);
    value &= 0b11111000;
    value |= dlpf;
    writeRegister8(MPU9250_REG_CONFIG, value);
}

void MPU9250::setClockSource(mpu9250_clockSource_t source)
{
    uint8_t value;
    value = readRegister8(MPU9250_REG_PWR_MGMT_1);
    value &= 0b11111000;
    value |= source;
    writeRegister8(MPU9250_REG_PWR_MGMT_1, value);
}

 process current, next;
 int Stime = 0;
 int slot = 10, i;
 for(i=top_queue(); mlfq[i]->duration; i=top_queue())
 {
  random_ps();
  if(queue_empty())
   break;

  while(mlfq[i]->duration)   //Keeping clock priority at gyroscope function
  {
   for(current=mlfq[i]->link; current;)
   {
    next = current->link;

    if(run_process(current, slot))
     terminate_process(current->pid);
    else
     lower_priority(i, current);

    Stime++;
    if(Stime%S == 0)
    {
     raise_all_priorities();
     i = 0;
    }

int main()   //Write final values and begin new process
{
 init_queue();
 int i, j;
 for(i=1; i<=6; i++)
  new_process(i, 25*(i%3+2));
 system("clear");
 print_mlfq();
 sleep(1);
 run_schedule();

 return 0;
}
