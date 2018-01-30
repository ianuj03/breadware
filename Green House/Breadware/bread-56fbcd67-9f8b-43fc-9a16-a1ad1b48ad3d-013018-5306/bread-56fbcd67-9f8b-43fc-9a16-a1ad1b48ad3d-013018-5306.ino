
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
  //for Indo Tomato plants
while(!(temp1.read()>74&&temp1.read()<86)&&ldr1.read()>100&&(humidity1.read()>79&&humidity1.read()<91)){         //75-85 temp 80-90 humidity
            speaker1.write(520);
            delay(300);
            speaker1.write(0);
            if(button1.is_pressed())
                break;
    }
while(!(temp1.read()>60&&temp1.read()<75)&&ldr1.read()<100&&(humidity1.read()>64&&humidity1.read()<76)){     //60-75 temp 65-75 humidity
            speaker1.write(520);
            delay(300);
            speaker1.write(0);
            if(button1.is_pressed())
                break;
}
}
