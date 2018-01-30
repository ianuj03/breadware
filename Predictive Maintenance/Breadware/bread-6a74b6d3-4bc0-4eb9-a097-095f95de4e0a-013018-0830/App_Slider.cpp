#include "App_Slider.h"

App_Slider::App_Slider() {}

App_Slider::App_Slider(Bread_App* bread_app, int pos)
{
	app = bread_app;
	position = pos;
}

bool App_Slider::read()
{
	int found_match = 0;
	bool return_val = previous_state;
	for (int i=0; i<app->to_device_data_pointer; i++) {
		// if already found match then have to collapse the stack by 1.
		if (found_match == 1) {
			app->to_device_data_stack[i-1] = app->to_device_data_stack[i];
			continue;
		}
		String cmd = app->to_device_data_stack[i];
		int end_of_cmd = app->parseByStringSeparator(cmd,INTERNAL_SEPARATOR);

		// if this is a button command
		if (app->isValid(end_of_cmd)) { // ">" is in slider commands
			int cmd_pos = (cmd.substring(1,end_of_cmd)).toInt();
			if (cmd_pos == position) {
				found_match = 1;
				return_val = (bool) cmd.substring(end_of_cmd+1).toInt();
				previous_state = return_val;
				app->to_device_data_pointer--;
			}
		}
	}
	return return_val;
}