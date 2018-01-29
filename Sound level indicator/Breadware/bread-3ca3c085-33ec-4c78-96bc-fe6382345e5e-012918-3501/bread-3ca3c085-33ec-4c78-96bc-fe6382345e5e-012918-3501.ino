
#include "bread.h"
#include "Bread_App.h"
#include "App_DeviceConstants.h"

static const Bread_App bread_app = Bread_App(
  PROJECT_ID, USERNAME,
  DEVICE_ID, DEVICE_NAME,
  PROCESSOR_TYPE
);




#include "App_Slider.h"
#include "App_Textbox.h"
#include "App_Button.h"
#include "App_Indicator.h"
#include "App_Sound.h"
#include "App_Notification.h"
#include "App_DeviceConstants.h"







void setup() {
    
    Serial.begin(9600);

    bool success = bread_init();
    if (success) {
        uart_print_char_array("Bread initialized successfully");
    } else {
        uart_print_char_array("Failed to initialize bread");
    }
    bread_app.setup();

    
}

void loop() {
  bread_app.check();
  //put your main code here
int x=mic1.read();
delay(1000);
x=mic1.read();
if(x>80)
    led1.setRGB(255,0,0);
else  if(x>75)
    led1.setRGB(200,0,0);
else if(x>60)
    led1.setRGB(190,100,0);
else if(x>50)
    led1.setRGB(100,190,0);
else if(x>40)
    led1.setRGB(0,190,0);
else if(x>35)
    led1.setRGB(0,190,100);
else if(x>30)
    led1.setRGB(0,100,190);
else if(x>25)
    led1.setRGB(0,0,200);
else 
    led1.setRGB(126,127,127);
}
