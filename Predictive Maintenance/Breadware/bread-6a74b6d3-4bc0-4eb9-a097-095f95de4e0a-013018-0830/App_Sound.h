#ifndef BREAD_APP_SOUND_H
#define BREAD_APP_SOUND_H
#include "Arduino.h"
#include "Bread_App.h"

class App_Sound
{
	public:

	// functions
	App_Sound();
	App_Sound(Bread_App* app, int pos);
	App_Sound(Bread_App* app, int pos, String sound_type);
	void write();
	void write(String sound_clip);

  private:

	// fields
	String sound;
	int position;
	Bread_App* app;
};

#endif