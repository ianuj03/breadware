#include "App_Notification.h"

App_Notification::App_Notification() {}

App_Notification::App_Notification(Bread_App* bread_app, int pos)
{
	position = pos;
  app = bread_app;
	notification = "";
}

App_Notification::App_Notification(Bread_App* bread_app, int pos, String notification_type)
{
	position = pos;
	app = bread_app;
	notification = notification_type;
}

void App_Notification::write()
{
  this->write(notification);
}

void App_Notification::write(String notification_message, unsigned long cooldown_sec)
{
  if ((last_notification == 0 ||
        millis() - last_notification > cooldown_sec * 1000) &&
      app->is_connected == 1) {
    last_notification = millis();
		String to_app = "TA>M" + String(position) + ">" + notification_message;
    Serial3.print(to_app + "&&&");
  }
}