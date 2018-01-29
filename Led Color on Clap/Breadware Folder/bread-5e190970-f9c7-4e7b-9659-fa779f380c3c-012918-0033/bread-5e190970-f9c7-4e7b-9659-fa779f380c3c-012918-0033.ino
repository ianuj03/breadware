
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


//put your global code here
int x;




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
x=mic1.read();
if(x>50){
    delay(400);
    x=mic1.read();
    if(x>50){
        delay(400);
        x=mic1.read();
        if(x>50)
            led1.setRGB(0,0,255);
        else
            led1.setRGB(0,255,0);
    }
    else
        led1.setRGB(255,0,0);
    delay(3000);
    led1.off();
}
}
