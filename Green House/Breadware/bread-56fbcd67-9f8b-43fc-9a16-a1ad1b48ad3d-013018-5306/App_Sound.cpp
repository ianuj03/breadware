#include "App_Sound.h"

App_Sound::App_Sound() {}

App_Sound::App_Sound(Bread_App* bread_app, int pos)
{
  app = bread_app;
	position = pos;
	sound = "";
}

App_Sound::App_Sound(Bread_App* bread_app, int pos, String sound_type)
{
	position = pos;
	app = bread_app;
	sound = sound_type;
}

void App_Sound::write()
{
	this->write(this->sound);
}

/*
 * Send the sound clip over serial to the connected application.
 */
void App_Sound::write(String sound_clip)
{
  if (app->is_connected == 1) {
		String to_app = "TA>M" + String(position) + ">" + sound_clip;
    Serial3.print(to_app + "&&&");
  }
}