#ifndef HAL_H
#define HAL_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

typedef int bool;
#define true 1
#define false 0

/**
 * Establishes a serial connection to a host computer via USB with 20 ms timeout
 *
 * @param baud_rate The Baud Rate for the connection
 */
void uart_start(uint16_t baud_rate);

/**
 * Read a byte from the serial buffer
 */
uint8_t uart_read_byte();

/**
 * Write a byte to the serial buffer
 *
 * @param write_byte The byte value to write to the buffer
 */
void uart_write_byte(uint8_t write_byte);

/**
 * Write a character array to the serial buffer
 *
 * @param write_array The character array to write to the buffer
 */
void uart_print_char_array(char* write_array);

/**
 * Write a float to the serial buffer
 *
 * @param write_float The float to write to the buffer
 */
void uart_print_float(float write_float);

/**
 * Write an integer to the serial buffer
 *
 * @param write_int The integer to write to the buffer
 */
void uart_print_int(int write_int);

//char* uart_read();
//void uart_write(char* write_array); // Function overloading
//void uart_write(float write_float);
//void uart_write(int write_int);

/* I2C functions */

//# Ideally wrapped up into BreadInit()
//# I want to be passing i2c instances to drivers with the layout information
//# Since it's possible to create your own i2c instance with bit-banging
//# And i2c implemenations for different microcontrollers will be different
//# Then we'll have things like i2c.read() and i2c.write()
/**
 * Currently a wrapper for Arduino's implementation which requires instantiation of a C++ class
 */
void i2c_start();

/**
 * Configures the microcontroller to support I2C communication.
 *
 * @param i2c_address The 8-bit (7-bits shifted left) address of the slave to request
 * data from
 *
 * @param reg The single-byte register value / command / query sent to the slave with the request
 */
uint8_t i2c_read_byte(uint8_t i2c_address, uint8_t reg);

/**
 * Read 1 byte of information from a slave device (specified by its address) on the i2c bus.
 *
 * @param i2c_address The 8-bit (7-bits shifted left) address of the slave to request
 * data from
 *
 * @param reg The single-byte register value / command / query sent to the slave with the request
 *
 * @param *buffer The buffer pointer to write the query into.
 * This most likely should be same same length as the length paramater.
 *
 * @param length The length of the buffer.
 */

void i2c_read_length(uint8_t i2c_address, uint8_t reg, uint8_t *buffer, uint8_t length);

/**
 * Send a single byte on the default i2c bus.
 *
 * @param i2c_address The 8-bit (7-bits shifted left) address of the slave to send data to
 * @param reg The first byte of the transmission to specify a register / command to the slave
 * @param write_btye The single-byte payload of the write operation following the register value
 *
 */
void i2c_write_byte(uint8_t i2c_address, uint8_t reg, uint8_t write_byte);

/**
 * Write 1 bye of information to a slave device (specified by its address) on the i2c bus.
 *
 * @param i2c_address The 8-bit (7-bits shifted left) address of the slave to request data from
 * @param reg A single register / command byte sent to the slave with the request
 * @param read_delay_ms The number of milliseconds to wait after sending the request before collecting the response
 *
 */
uint8_t i2c_read_byte_with_delay(uint8_t i2c_address, uint8_t reg, uint16_t read_delay_ms);

/**
 * Read 2 bytes from the i2c bus with a delay between requesting it and reading it
 *
 * @param i2c_address The 8-bit (7-bits shifted left) address of the slave to request data from
 * @param reg A single register / command byte sent to the slave with the request
 * @param read_delay_ms The number of milliseconds to wait after sending the request before collecting the response
 *
 */
uint16_t i2c_read_2_bytes_with_delay(uint8_t i2c_address, uint8_t reg, uint16_t read_delay_ms);


/**
 * Read a 16-bit word from the default i2c bus.
 *
 * @param i2c_address The 8-bit (7-bits shifted left) address of the slave to request data from
 *
 * @param reg A single-byte register value / command / query to accompany the read request
 */
uint16_t i2c_read_2_bytes(uint8_t i2c_address, uint8_t reg);

/**
 * Read 2 bytes of information from a slave device (specified by its address) on the i2c bus.
 *
 * @param i2c_address The 8-bit (7-bits shifted left) address of the slave to write to
 * @param reg A single-bye register value / command / query before the payload
 * @param write_int A 16-bit data payload to the slave
 */
void i2c_write_2_bytes(uint8_t i2c_address, uint8_t reg, uint16_t write_int);

//char* i2c_read(uint8_t i2c_address, uint8_t reg, uint8_t bytes);
//void i2c_write(uint8_t i2c_address, uint8_t reg, char* write_array);

/* GPIO functions */

/**
 * Write a boolean logic level (transistor-transitor logic level for the microcontroller)
 * to a specified pin
 *
 * @param pin The pin number
 * @param state A boolean (true or false) to represent high or low voltage respectively
 */
void gpio_write(uint8_t pin, bool state);

/**
 * Read the boolean logic level (transistor-transistor logic level for the microcontroller)
 * of a specified pin
 *
 * @param pin The pin number
 */
bool gpio_read(uint8_t pin);

//# This should be different for each board to return a float of TRUE voltage.
/**
 * Read the analog voltage level of a pin. Full-scale range is microcontroller-dependent, but
 * output is an integer from 0 to 1023.
 * This implementation is already scheduled for deprecation
 *
 * @param pin The pin number
 */
int gpio_analog_read(uint8_t pin);

/**
 * Reads the analog voltage level of a pin - output is an integer from 0 to 1023 which maps linearly to 0V - 5V.
 *
 * @param pin The pin number
 */
void gpio_set_output(uint8_t pin);

/**
 * Configure a pin to allow read operations rather than write operations.
 *
 * @param pin The pin number
 */
void gpio_set_input(uint8_t pin);

/**
 * Set the digital logic level of a pin to follow a constant-frequency square wave
 *
 * @param pin The pin number
 * @param frequency_hz The frequency of the waveform, in hertz
 * @param duration The duration of the waveform in milliseconds
 */
void gpio_pwm(uint8_t pin, int frequency_hz, int duration);

/**
 * Get the number of microseconds that a pin stays in the specified state after entering it.
 * If the pin is already in the specified state, will wait until the pin transitions out then in again.
 *
 * @param pin The pin number
 * @param is_high 0 for low logic state, anything else for high logic state
 *
 */
uint16_t gpio_pulse_in(uint8_t pin, int is_high);

/* timing functions */

/**
 * Pause synchronous logic execution for a while
 *
 * @param ms_delay Number of milliseconds to do nothing but wait
 */
void delay_for_ms(uint16_t ms_delay);

/**
 * Look up the number of milliseconds since we started running our program
 * At 32 bits, the counter overflows (resets to zero) in 49 days 17 hours ~3 minutes
 */
unsigned long time_ms(void);

long unsigned int get_micros();

#endif /* HAL_H */

