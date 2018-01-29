#ifndef BREAD_APP_INDICATOR_H
#define BREAD_APP_INDICATOR_H

#include "Bread_App.h"

class App_Indicator
{
	public:

	// functions
	App_Indicator();
	App_Indicator(Bread_App* bread_app, int pos);

	void write(String color);

	// fields
	int position;
	Bread_App* app;
};

#endif