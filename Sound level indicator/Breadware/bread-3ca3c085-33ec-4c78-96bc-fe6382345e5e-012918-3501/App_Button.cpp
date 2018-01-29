#include "App_Button.h"

App_Button::App_Button() {}

App_Button::App_Button(Bread_App* bread_app, int pos)
{
  app = bread_app;
	position = pos;
}

bool App_Button::read()
{
	int found_match = 0;
	bool return_val = 0;
	for (int i=0; i<app->to_device_data_pointer; i++) {

		// if already found match then have to collapse the stack by 1.
		if (found_match) {
			app->to_device_data_stack[i-1] = app->to_device_data_stack[i];
			continue;
		}
		String cmd = this->app->to_device_data_stack[i];
		int end_of_cmd = this->app->parseByStringSeparator(cmd, INTERNAL_SEPARATOR);

		// if this is a button command
		if (~(this->app->isValid(end_of_cmd))) { // no ">" in button commands
			int cmd_pos = (cmd.substring(1)).toInt();
			if (cmd_pos == position) {
				found_match = 1;
				return_val = 1;
				app->to_device_data_pointer--;
			}
		}
	}
	return return_val;
}