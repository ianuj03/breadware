#ifndef BREAD_APP_H
#define BREAD_APP_H

#include "hal.h"
#include "Arduino.h"

/*
 * App module includes
 */


enum APP_MODE {
  APP_MODE_NONE = 0,
  APP_MODE_DATA,
  APP_MODE_EXECUTION
};

static const String COMMAND_SEPARATOR = "&&&";
static const String INTERNAL_SEPARATOR = ">";

// Check these values for correctness/limits if space becomes an issue
#define DATA_STACK_SIZE 20
#define CMD_STACK_SIZE 10
#define MAX_NUM_SENSORS 20


class Bread_App
{
	public:

	// functions
		Bread_App();
		Bread_App(String proj_id, String u_name, String dev_id, String dev_name, String processor_type);

		void setup();
    void check();
		void update();
		void write(String command);

		unsigned int getSensorPeriod();

		int parseByStringSeparator(String in_string, String separator);
		int isValid(int command_end);

	// fields
		int app_mode;
		int is_connected;

		String to_device_data_stack[CMD_STACK_SIZE];
		int to_device_data_pointer;

    void debug(String str);
	private:
	// functions
		void readHandler(String command);
		void deviceDetailHandler(); // This is a legacy function that will be removed when the app is updated
		void deviceModeHandler(String arg_string);
		void deviceIDHandler(String arg_string);
		void projectIDHandler(String arg_string);
		void usernameHandler(String arg_string);
		void deviceNameHandler(String arg_string);
		void heartbeatHandler();
		void sensorDetectHandler(String arg_string);
		void sensorLogPeriodHandler(String arg_string);
		void dataToDeviceHandler(String arg_string);

	// fields
		String incoming_stack[DATA_STACK_SIZE];
		int incoming_stack_pointer; // points to the top of the incoming_stack
    unsigned int last_sensor_log;

		String project_id;
		String username;
		String device_id;
		String device_name;
		String processor;

		// For data logging
		String sensor_array[MAX_NUM_SENSORS];
		unsigned int sensor_period = 1000; // 1 second default. Min of 100, Max of 60,000
		String sensor_value_array[MAX_NUM_SENSORS];
		int num_sensors;

		String app_module_array[MAX_NUM_SENSORS];
		int num_app_modules;

		unsigned long last_heartbeat;
		unsigned long HEARTBEAT_LIMIT = 3000;

    unsigned long last_app_update;
    unsigned long APP_UPDATE_PERIOD = 10;
};

#endif