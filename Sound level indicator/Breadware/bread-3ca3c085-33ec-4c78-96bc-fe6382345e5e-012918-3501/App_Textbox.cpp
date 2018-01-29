#include "App_Textbox.h"

App_Textbox::App_Textbox() {}

App_Textbox::App_Textbox(Bread_App* bread_app, int pos)
{
	app = bread_app;
	position = pos;
}

void App_Textbox::write(String text)
{
	if (app->is_connected == 1) {
		String to_app = "TA>M" + String(position) + ">" + text;
		app->write(to_app + "&&&");
	}
}