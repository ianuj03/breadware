
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


int x=1;
int pattern1(){
        a.setRGB(0,0,255);
        delay(500);
        if(button1.is_pressed()){
        a.off();
        return 0;
        }
        a.off();
        b.setRGB(0,0,255);
        delay(500);
        if(button1.is_pressed()){
        b.off();
        return 0;
        }
        b.off();
        if(button1.is_pressed())
        return 0;
        c.setRGB(0,0,255);
        delay(500);
        if(button1.is_pressed()){
        c.off();
        return 0;
        }
        c.off();
        if(button1.is_pressed())
        return 0;
    return 1;
}
int pattern2(){
        a.setRGB(0,0,255);
        delay(500);
        if(button1.is_pressed()){
            a.off();
            return 0;
        }
        a.setRGB(0,255,0);
        delay(500);
        if(button1.is_pressed()){
            a.off();
            return 0;
        }
        a.setRGB(255,0,0);
        delay(500);
        a.off();
        if(button1.is_pressed())
        return 0;
        
        b.setRGB(0,0,255);
        delay(500);
        if(button1.is_pressed()){
            b.off();
            return 0;
        }
        b.setRGB(0,255,0);
        delay(500);
        if(button1.is_pressed()){
            b.off();
            return 0;
        }
        b.setRGB(255,0,0);
        delay(500);
        if(button1.is_pressed()){
        b.off();
        return 0;
        }
        b.off();
        if(button1.is_pressed())
        return 0;
        
        c.setRGB(0,0,255);
        delay(500);
        if(button1.is_pressed()){
            c.off();
            return 0;
        }
        c.setRGB(0,255,0);
        delay(500);
        if(button1.is_pressed()){
            c.off();
            return 0;
        }
        c.setRGB(255,0,0);
        delay(500);
        if(button1.is_pressed()){
        c.off();
        return 0;
        }
        c.off();
        if(button1.is_pressed())
        return 0;
    return 1;
}
/*int pattern3(){
    for(int i=0;i<3;i++){
        led[0].setRGB(255,0,0);
        delay(500);
        led[1].setRGB(0,255,0);
        delay(500);
        led
    }
}*/
void led_off(){
        a.off();
        b.off();
        c.off();
}




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
PATTERN1:
    led_off();
    for(int i=0;i<2;i++){
        x=pattern1();
        if(x==0||button1.is_pressed()){
            led_off();
            goto PATTERN2;
        }
    }
PATTERN2:
    led_off();
    for(int i=0;i<2;i++){
        x=pattern2();
        if(x==0||button1.is_pressed()){
            led_off();
            goto PATTERN1;
        }
    }/*
PATTERN3:
    for(int i=0;i<2;i++){
        x=pattern1();
        if(x==0||button1.is_pressed()){
            led_off();
            goto PATTERN1;
        }
    }*/
}
