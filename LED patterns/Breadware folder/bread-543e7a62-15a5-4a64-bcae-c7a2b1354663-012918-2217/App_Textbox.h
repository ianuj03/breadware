#ifndef APP_TEXTBOX_H
#define APP_TEXTBOX_H

#include "hal.h"
#include "Bread_App.h"

class App_Textbox
{
	public:

	// functions
	App_Textbox();
	App_Textbox(Bread_App* bread_app, int pos);
	void write(String text);

	// fields
	int position;
	Bread_App* app;
};

#endif