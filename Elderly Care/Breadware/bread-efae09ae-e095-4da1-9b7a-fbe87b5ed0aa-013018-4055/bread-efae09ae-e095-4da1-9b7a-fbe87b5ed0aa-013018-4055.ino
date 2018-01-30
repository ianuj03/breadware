
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
float x,y,z;




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
x=g1.read_x();
y=g1.read_y();
z=g1.read_z();
}

void loop() {
  bread_app.check();
  if(abs(x - g1.read_x())>100||abs(y - g1.read_y())>100||abs(z - g1.read_z())>100){
    delay(4000);
    if(abs(acc1.read_z())>7){
        Serial.println("\n\n\t Seems like something is not right with Dadi.");
        delay(5000);
    }
}

}
