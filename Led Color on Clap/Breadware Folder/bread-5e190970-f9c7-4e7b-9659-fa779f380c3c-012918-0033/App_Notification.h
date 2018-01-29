#ifndef BREAD_APP_NOTIFICATION_H
#define BREAD_APP_NOTIFICATION_H

#include "Bread_App.h"

class App_Notification
{
	public:

  static const unsigned long COOLDOWN_TIME_SEC_DEFAULT = 30;
  signed long last_notification = 0;

	// functions
  App_Notification();
	App_Notification(Bread_App* bread_app, int pos);

	App_Notification(Bread_App* bread_app, int pos, String notification_type);
	void write();
	void write(String notification_message, unsigned long cooldown_sec=COOLDOWN_TIME_SEC_DEFAULT);

	// fields
	String notification;
	int position;
  Bread_App *app;
};

#endif