#include "bread.h"

bool bread_init() {
    uart_start(9600);
    bool failed = false;
    // [{'alias': u'button1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa274710310>, 'file': 'button', 'map': {'PIN': '62', 'pin': '62'}}, {'alias': u'a', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa274710f50>, 'file': 'led_ws2812', 'map': {'pin': '69', 'PIN': '69'}}, {'alias': u'b', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa274710050>, 'file': 'led_ws2812', 'map': {'pin': '67', 'PIN': '67'}}, {'alias': u'c', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa274710c90>, 'file': 'led_ws2812', 'map': {'pin': '7', 'PIN': '7'}}]
    if (!button1.init()) {
      uart_print_char_array("\n\nFAILed to initialise button1\n\n");
      failed = true;
    }
    if (!a.init()) {
      uart_print_char_array("\n\nFAILed to initialise a\n\n");
      failed = true;
    }
    if (!b.init()) {
      uart_print_char_array("\n\nFAILed to initialise b\n\n");
      failed = true;
    }
    if (!c.init()) {
      uart_print_char_array("\n\nFAILed to initialise c\n\n");
      failed = true;
    }

    return !failed;
      
}
