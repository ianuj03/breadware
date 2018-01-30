#ifndef BREAD_APP_BUTTON_H
#define BREAD_APP_BUTTON_H

#include "hal.h"
#include "Bread_App.h"

class App_Button
{
	public:

	// functions
	App_Button();
  App_Button(Bread_App* mobile_app, int pos);
	bool read();

  private:

	// fields
	int position;
	Bread_App* app;
};

#endif