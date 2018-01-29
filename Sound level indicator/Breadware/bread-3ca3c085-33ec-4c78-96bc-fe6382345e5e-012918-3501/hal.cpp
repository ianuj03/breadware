#include "hal.h"

#include "Arduino.h"
#include <Wire.h>

/******************/
/* UART functions */
/******************/
void uart_start(uint16_t baud_rate)
{
	Serial.begin(baud_rate);
	
	uint16_t timeout_ms = 20;
	Serial.setTimeout(timeout_ms);
}

uint8_t uart_read_byte()
{
	Serial.read();
}

void uart_write_byte(uint8_t write_byte) 
{
	Serial.write(write_byte);
}

void uart_print_char_array(char* write_array)
{
	Serial.print(write_array);
}

void uart_print_float(float write_float)
{
	Serial.print(write_float);
}

void uart_print_int(int write_int)
{
	Serial.print(write_int);
}


/*char* uart_read()
{
	String read_string = Serial.readString();
	uint16_t num_bytes = read_string.length();
	static char read_array[num_bytes];
	read_string.toCharArray(read_array,num_bytes);
	return read_array;
}

void uart_write(char* write_array)
{
	Serial.write(write_array);
}

void uart_write(float write_float);
{
	Serial.write(write_array);
}

void uart_write(int write_int);
{
	Serial.write(write_array);
}*/


/******************/
/*  I2C functions */
/******************/
void i2c_start()
{
	Wire.begin();
}

uint8_t i2c_read_byte_with_delay(uint8_t i2c_address, uint8_t reg, uint16_t read_delay_ms) {
  Wire.beginTransmission(i2c_address);
	Wire.write(reg);
	Wire.endTransmission();
  
  if (read_delay_ms != 0) {
    delay(read_delay_ms);
  }

  Wire.requestFrom((uint8_t) i2c_address,(uint8_t) 1);

  const int TIMEOUT = 3; // 3ms timeout
  int ms_ticks = 0; 
  while(!Wire.available()) {
    ms_ticks++;
    if (ms_ticks >= TIMEOUT) {
      break;
    }
  }
  
  uint8_t value = Wire.read();
  Wire.endTransmission();

  return value;
}

uint8_t i2c_read_byte(uint8_t i2c_address, uint8_t reg)
{
  return i2c_read_byte_with_delay(i2c_address, reg, 0);
}

void i2c_read_length(uint8_t i2c_address, uint8_t address, uint8_t *buffer, uint8_t length)
{
  uint8_t i;
  Wire.beginTransmission(i2c_address);
  Wire.write(address);
  Wire.endTransmission(false);

  Wire.requestFrom(i2c_address, length);

  const int TIMEOUT = 3; // 3ms timeout
  int ms_ticks = 0; 
  for(i=0; i < length; i++)
  {
    ms_ticks = 0;
    while(!Wire.available()) {
      ms_ticks++;
      if (ms_ticks >= TIMEOUT) {
        break;
      }
    }
    buffer[i] = Wire.read();
  }
  // TODO: Should this throw a big warning if the buffer sizes are off?
}



void i2c_write_byte(uint8_t i2c_address, uint8_t reg, uint8_t write_byte)
{
	Wire.beginTransmission(i2c_address);
	Wire.write((byte)reg);
	Wire.write(write_byte);
	Wire.endTransmission();
}

uint16_t i2c_read_2_bytes_with_delay(uint8_t i2c_address, uint8_t reg, uint16_t read_delay_ms) {

	Wire.beginTransmission(i2c_address);
	Wire.write(reg);
	Wire.endTransmission();
  if (read_delay_ms != 0) {
    delay(read_delay_ms);
  }
  
  Wire.requestFrom((uint8_t) i2c_address,(uint8_t) 2);

  const int TIMEOUT = 3; // 3ms timeout
  int ms_ticks = 0; 
  while(!Wire.available()) {
    ms_ticks++;
    if (ms_ticks >= TIMEOUT) {
      break;
    }
  }
  
  uint16_t value = Wire.read();
  value <<= 8;
  value |= Wire.read();  
  return value;  
}

uint16_t i2c_read_2_bytes(uint8_t i2c_address, uint8_t reg) {
  return i2c_read_2_bytes_with_delay(i2c_address, reg, 0);
}


void i2c_write_2_bytes(uint8_t i2c_address, uint8_t reg, uint16_t write_int)
{
	Wire.beginTransmission(i2c_address);
    Wire.write(reg);
    Wire.write(write_int >> 8);
    Wire.write(write_int & 0xFF);
    Wire.endTransmission();
}

/******************/
/*  GPIO Functions */
/******************/
void gpio_write(uint8_t pin, bool state) 
{
	int output = 1;
	pinMode(pin,output);
	digitalWrite(pin,state);
}

bool gpio_read(uint8_t pin) 
{
	bool state = digitalRead(pin);
	return state;
}

int gpio_analog_read(uint8_t pin)
{
	return analogRead(pin);
}

void gpio_set_output(uint8_t pin)
{
	int output = 1;
	pinMode(pin,output);
}

void gpio_set_input(uint8_t pin)
{
  int input = 0;
  pinMode(pin,input);
}

void gpio_pwm(uint8_t pin, int frequency_hz, int duration)
{
  tone(pin,frequency_hz,duration);
}

uint16_t gpio_pulse_in(uint8_t pin, int is_high)
{
  return pulseIn(pin, is_high ? HIGH : LOW);
}


/*********************/
/*  TIMING functions */
/*********************/
void delay_for_ms(uint16_t ms_delay)
{
	delay(ms_delay);
}

// overflows in 50 days
unsigned long time_ms( void )
{
	return millis();
}

long unsigned int get_micros()
{
	return micros();
}

