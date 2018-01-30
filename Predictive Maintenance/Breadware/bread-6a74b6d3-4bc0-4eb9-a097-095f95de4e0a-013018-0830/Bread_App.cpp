#include "Bread_App.h"
#include "bread.h"
#include "BLE.h"

unsigned int num_sensor_keys = 6;
String BREAD_APP_allDataSensorKeys[6] = {"ACL_X", "ACL_Y", "ACL_Z", "GYR_X", "GYR_Y", "GYR_Z"};
String BREAD_APP_getSensorReading(String dataKey) {
    String val = "";
    if (dataKey == "ACL_X") {
        val = String(acc1.read_x());
    }
    if (dataKey == "ACL_Y") {
        val = String(acc1.read_y());
    }
    if (dataKey == "ACL_Z") {
        val = String(acc1.read_z());
    }
    if (dataKey == "GYR_X") {
        val = String(g1.read_x());
    }
    if (dataKey == "GYR_Y") {
        val = String(g1.read_y());
    }
    if (dataKey == "GYR_Z") {
        val = String(g1.read_z());
    }
    return val;
}



//*************CONSTRUCTORS and SETUP*****************************************//

Bread_App::Bread_App() {}

Bread_App::Bread_App(String proj_id, String u_name, String dev_id, String dev_name, String processor_type)
{
	processor = processor_type;
	project_id = proj_id;
	username = u_name;
	device_id = dev_id;
	device_name = dev_name;
}


/*
 * Initialize the Bread App connection interfaces
 *
 */
void Bread_App::setup()
{
  Serial3.begin(115200);
  delay(50);
  Serial3.setTimeout(20);

  device_id = bluetoothModuleSetup(this->device_name);
  Serial.println("Got device id: " + device_id);
}


/*
 * Write a debug statement to serial.
 *
 * @param str : The formatted string to write
 */
void Bread_App::debug(String str) {
  Serial.println(str);
}

/*
 * App sync ticker
 *
 * Checks to see if we need to sync up with the app and update if we do.
 */
void Bread_App::check() {
  if (millis()-last_app_update > APP_UPDATE_PERIOD) {
    last_app_update = millis();
    this->update();
  }
}

/*
 * High level update routines for the Bread application.
 *
 * Execution Overview
 * ===================
 *
 * * Check if new data has been sent from the application.
 * * If available, parse and process the app command.
 * * Send the current "Data Mode" sensor values to the application.
 */
void Bread_App::update()
{
	// (if available) read incoming app data
  int data_available = Serial3.available();

	if (data_available) {
    this->debug("Got data available from update: " + data_available);
		// get the new byte:
		String incoming = Serial3.readString();

    this->debug("Got incoming string: " + incoming);

    //  TODO(samdolan): Maintain legacy app. Remove when app updated
		if (incoming == "DI") {
			deviceDetailHandler();
		}

		incoming_stack_pointer = 0;
		while (incoming.length() > 0) {

      // parse out the first command
			int end_of_command = parseByStringSeparator(incoming,COMMAND_SEPARATOR);

			if (isValid(end_of_command)) {
				String incoming_command = incoming.substring(0,end_of_command);
        this->debug("Got incoming command: " + incoming_command);

        // the remainder of the incoming string
				incoming = incoming.substring(end_of_command+COMMAND_SEPARATOR.length());

        // add the command to the incoming command stack
				incoming_stack[incoming_stack_pointer++] = incoming_command;
			} else {
				incoming = "";
			}
		}
		while (incoming_stack_pointer > 0) {
			readHandler(incoming_stack[--incoming_stack_pointer]);
		}
	}

  unsigned int ms_since_last_heartbeat = millis() - last_heartbeat;

	if (ms_since_last_heartbeat > HEARTBEAT_LIMIT) {
    // heartbeat not being set correctly (don't see it from the app). Figure out what's going on and add this change the val back to 0
		is_connected = 0;
    //this->debug("NOT connected with via last heartbeat. Ms since last heartbeat = " + String(ms_since_last_heartbeat) + " LIMIT: " + String(HEARTBEAT_LIMIT));
    //this->setup();
	}

  // Log sensor data to the app if we have an active connection
	if (is_connected && num_sensor_keys > 0) {
    this->debug("We are connected sending sensor values");

			String sensor_value_string = "";


			for (int i=0; i< num_sensor_keys; i++) {
				sensor_value_string += BREAD_APP_getSensorReading(BREAD_APP_allDataSensorKeys[i]);
        if (i+1 < num_sensor_keys) {
          sensor_value_string += ",";
        }
			}
      Serial.println("Sending sensor values: " + sensor_value_string);
			String log_command = "SL>" + sensor_value_string;
			write(log_command);
	}

  // This updates the app with what sensors are connected
  sensorDetectHandler("GET");
}


/*
 * Read incoming message commands
 */
void Bread_App::readHandler(String command)
{
  this->debug("readHandler. Got command: " + command);

	if (command == "HI") {
		heartbeatHandler();
	}

  // TODO(dprice) This is to maintin the legacy app. Remove when updated
	if (command == "DD") {
		deviceDetailHandler();
	}

	else {
		int end_of_label = parseByStringSeparator(command,INTERNAL_SEPARATOR);
		if (isValid(end_of_label)) {
			String label = command.substring(0, end_of_label);
			String arguments_string = command.substring(end_of_label+INTERNAL_SEPARATOR.length());
			if (label == "MD") {
				deviceModeHandler(arguments_string);
			}
			if (label == "DID") {
				deviceIDHandler(arguments_string);
			}
			if (label == "PID") {
				projectIDHandler(arguments_string);
			}
			if (label == "UN") {
				usernameHandler(arguments_string);
			}
			if (label == "DN") {
				deviceNameHandler(arguments_string);
			}
			if (label == "SD") {
				sensorDetectHandler(arguments_string);
			}
			if (label == "SLP") {
				sensorLogPeriodHandler(arguments_string);
			}
			if (label == "TD") {
				dataToDeviceHandler(arguments_string);
			}
		}
	}
}

// TODO(dprice): This is the legacy handler. Remove when new app is updated.
void Bread_App::deviceDetailHandler()
{
  String to_app = "DD {\"device_id\": \" " + device_id + "\",\"project_id\": \"" + project_id + "\",\"username\": \"" + username + "\",\"sensor_data\": []}&&&";

  this->debug("got deviceDetailHandler. Sending: " + to_app);
	write(to_app);
}

void Bread_App::deviceModeHandler(String arg_string)
{
  Serial.println("DEVICE MODE HANDLER: " + arg_string);

	int end_of_getset = parseByStringSeparator(arg_string,INTERNAL_SEPARATOR);
	if (isValid(end_of_getset)) {
		String mode_string = arg_string.substring(end_of_getset+INTERNAL_SEPARATOR.length());

    Serial.println("Valid device mode. arg_string: " + arg_string + \
        " mode_string: " + mode_string);

    if (arg_string.startsWith("SET")) {
        if (mode_string == "NONE") {
          app_mode = APP_MODE_NONE;
        }
        if (mode_string == "DATA") {
          app_mode = APP_MODE_DATA;
        }
        if (mode_string == "EXEC") {
          app_mode = APP_MODE_EXECUTION;
        }
        write("MD>" + mode_string);
    }
  }
}

void Bread_App::deviceIDHandler(String direction)
{
	if (direction == "GET") {
	  write("DID>" + this->device_id);
	}
}

void Bread_App::projectIDHandler(String direction)
{
	if (direction == "GET") {
		write("PID>" + this->project_id);
	}
}

void Bread_App::usernameHandler(String direction)
{
	if (direction == "GET") {
		String return_command = "UN>" + username;
		write(return_command);
	}
}

void Bread_App::deviceNameHandler(String arg_string)
{
	if (arg_string == "GET") {
		String return_command = "DN>BRD" + device_name;
		write(return_command);
	}
	else {
		int end_of_getset = parseByStringSeparator(arg_string,INTERNAL_SEPARATOR);
		if (isValid(end_of_getset)) {
			arg_string = arg_string.substring(0, end_of_getset);
			if (arg_string == "SET") {
				String name_string = arg_string.substring(end_of_getset+INTERNAL_SEPARATOR.length());
				device_name = name_string;
				String return_command = "DN>BRD" + device_name;
				write(return_command);
			}
		}
	}
}

void Bread_App::heartbeatHandler()
{
	last_heartbeat = millis();
  Serial.println("LAST HEARTBEAT: " + String(last_heartbeat));
	is_connected = 1;
}

void Bread_App::sensorDetectHandler(String arg_string)
{
  /*if (!num_sensor_keys) {
    write("SD>NONE");
    return;
  }*/
	if (arg_string == "GET") {
		String sensor_string = "";
		for (int i=0; i<num_sensor_keys; i++) {
        sensor_string += BREAD_APP_allDataSensorKeys[i];
         if(i != num_sensor_keys-1) {
             sensor_string  += ",";
         }
		}
		String return_command = "SD>" + sensor_string;
		write(return_command);
	}
}

void Bread_App::sensorLogPeriodHandler(String arg_string)
{
  this->debug("Got sensorLogPeriodHandler w/arg_string: " + arg_string);

	if (arg_string  == "GET") {
		String return_command = "SLP>" + String(sensor_period);
		write(return_command);
	} else {
		int end_of_getset = parseByStringSeparator(arg_string,INTERNAL_SEPARATOR);
		if (isValid(end_of_getset)) {
			String command = arg_string.substring(0,end_of_getset);
			if (command == "SET") {
				String new_sensor_period = arg_string.substring(end_of_getset+INTERNAL_SEPARATOR.length());
				sensor_period = new_sensor_period.toInt();
				String return_command = "SLP>" + String(sensor_period);
				write(return_command);
			}
		}
	}
}

void Bread_App::dataToDeviceHandler(String arg_string)
{
  this->debug("dataToDeviceHandler go arg_string: " + arg_string);

	to_device_data_stack[to_device_data_pointer] = arg_string;
	to_device_data_pointer++;
}

void Bread_App::write(String command)
{
  command = command + "&&&";
  this->debug("writing command to outgoing serial: " + command);
  Serial3.print(command);
}

//*************INTERFACE FUNCTIONS TO THE DEVICE*****************************************//

unsigned int Bread_App::getSensorPeriod() {
  return sensor_period;
}

int Bread_App::parseByStringSeparator(String in_string, String separator)
{
	return in_string.indexOf(separator);
}

int Bread_App::isValid(int command_end)
{
	return command_end != -1;
}