#include "App_Indicator.h"

App_Indicator::App_Indicator() {}

App_Indicator::App_Indicator(Bread_App* bread_app, int pos)
{
	app = bread_app;
	position = pos;
}

void App_Indicator::write(String color)
{
  if (app->is_connected == 1) {
		String to_app = "TA>M" + String(position) + ">" + color;
    Serial3.print(to_app + "&&&");
  }
}