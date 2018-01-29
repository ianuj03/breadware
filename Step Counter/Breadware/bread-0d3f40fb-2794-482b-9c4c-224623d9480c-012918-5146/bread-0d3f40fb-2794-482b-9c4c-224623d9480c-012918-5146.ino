
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
//int y;
//#include<String.h>
int step =0,step1=0,y;
//char a[];
App_Textbox count = App_Textbox(&bread_app,0);




void setup() {
    
    Serial.begin(9600);

    bool success = bread_init();
    if (success) {
        uart_print_char_array("Bread initialized successfully");
    } else {
        uart_print_char_array("Failed to initialize bread");
    }
    bread_app.setup();

    //put your setup code here
Serial.begin(9600);
}

void loop() {
  bread_app.check();
  //put your main code here
    y=acc1.read_y();
    if(y>7){
        //Serial.println(++count);
        while(!(acc1.read_x()<-8||acc1.read_y()<0));
        Serial.print("\nForward step: ");
        Serial.println(++step);
        //count.write(String(step));
    }
    /*else if(y<-7){
            while(acc1.read_x()<-12||acc1.read_y()<0);
            Serial.print("\nBackward step: ");
            Serial.println(++step1);
    }*/
   /* Serial.println(acc1.read_x());
    Serial.println(acc1.read_y());
    Serial.println(acc1.read_z());
    delay(1000);*/
}
