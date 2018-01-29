#ifndef BREAD_APP_SLIDER_H
#define BREAD_APP_SLIDER_H

#include "Bread_App.h"

class App_Slider
{
	public:

	// functions
	App_Slider();
	App_Slider(Bread_App* app, int pos);
	bool read();

	// fields
	bool previous_state;
	int position;
	Bread_App* app;
};

#endif