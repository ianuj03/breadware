
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
int x,y,z,count=0;
double t;
//int flag=10;




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
Serial.println(time_ms());
x=acc1.read_x();
y=acc1.read_y();
z=acc1.read_z();
t=time_ms();
pinMode(13,OUTPUT);
digitalWrite(13,0);
}

void loop() {
  bread_app.check();
  if(abs(x - acc1.read_x())>1||abs(y - acc1.read_y())>1||abs(z - acc1.read_z())>1)
{
    delay(500);
    count++;
}
if(count>14)
{
    Serial.println("\n\n\n\tKindly check the machine.\n");
    digitalWrite(13,1);
    delay(10000);
    count=0;
}
else if((abs(t - time_ms())/1000)>14&&count<14)
{
    count=0;
    t=time_ms();
   // flag=0;
}

}
