#include "BLE.h"

String bluetoothModuleSetup(String bleName) {
  int i;
  String dev_id;
  String device_name;
  char temp_character;

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  delay(10);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);

  delay(250);
  Serial.println("------------");

  // Put into config mode
  Serial3.write("$$$");
  Serial.println("$$$");
  delay(500);
  while (Serial3.available() > 0) {
    Serial.write(Serial3.read());
    Serial.print(" ");
  }
  Serial.println("------------");

  ////  --------------- BEGIN Receive Device ID ----------------  ////
  Serial.print("D");
  Serial3.write("D\r");  //String return from RN4871: "BTA=D88039F1DB62", want: "D88039F1DB62"
  delay(500);

  if (Serial3.available())
  {
    for (i = 0; i < 4; i++) {
      Serial.write(Serial3.read());
      Serial.print(" ");
    } i = 0;

    for (i = 0; i < 12; i++) {
      temp_character = Serial3.read();
      dev_id.concat(temp_character);
    }
    dev_id.trim();
    Serial.println(dev_id);  //This is the unique device ID

    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }


    Serial3.write("GN\r");
    delay(50);
    while (Serial3.available() > 0) {
      device_name.concat(Serial3.readString());
    }
    Serial.println("DeviceID: " + dev_id);
    Serial.println("DeviceName: " + device_name);
  }


  ////  --------------- END Receive Device ID ----------------  ////
  // Set the device name
  if (!device_name.startsWith("BRD") || device_name.startsWith("BRD_")) {
    Serial3.write("SN,BRD");
    Serial3.print(dev_id);
    Serial3.write("\r");
    Serial.println("SN");

    delay(50);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }

    // Set the BLE mode to transparent UART
    Serial3.write("SS,40\r");
    Serial.println("SS");
    delay(100);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }



    // Reset the characteristics and services
    Serial3.write("PZ\r");
    Serial.println("PZ");
    delay(100);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }


    // Reboot the BLE
    Serial3.write("R,1\r");
    Serial.println("R");
    delay(500);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }

    // Create a private service
    Serial3.write("PS,49535343FE7D4AE58FA99FAFD205E455\r");
    Serial.println("PS");
    delay(100);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }

    // Create a write, notify, and write without response characteristics
    Serial3.write("PC,495353431E4D4BD9BA6123C647249616,18,50\r");
    Serial.println("PC");
    delay(100);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }

    // Reboot the BLE
    Serial3.write("R,1\r");
    Serial.println("R");
    delay(500);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }

    delay(500);
  } else {

    // Set the BLE mode to transparent UART
    Serial3.write("SS,40\r");
    Serial.println("SS");
    delay(100);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }
        // Reboot the BLE
    Serial3.write("R,1\r");
    Serial.println("R");
    delay(500);
    while (Serial3.available() > 0) {
      Serial.write(Serial3.read());
    }

    delay(500);
  }

  // Exit config mode
  Serial.println("---");
  Serial3.write("---\r");
  delay(20);
  while (Serial3.available() > 0) {
    Serial.write(Serial3.read());
  }
  delay(20);
  return dev_id;
}
