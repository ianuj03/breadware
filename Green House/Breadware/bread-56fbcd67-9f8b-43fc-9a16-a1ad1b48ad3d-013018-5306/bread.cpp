#include "bread.h"

bool bread_init() {
    uart_start(9600);
    bool failed = false;
    // [{'alias': u'temp1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa2746fd090>, 'file': 'temp_lm75bd', 'map': {}}, {'alias': u'humidity1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa2746fdf10>, 'file': 'humid_hdc1080', 'map': {'STAR': 'VOID'}}, {'alias': u'ldr1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa2746fd950>, 'file': 'bright_tsl2561', 'map': {}}, {'alias': u'speaker1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa2746fd8d0>, 'file': 'speaker', 'map': {'PIN': '65', 'pin': '65'}}, {'alias': u'led1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa2746fd650>, 'file': 'led_ws2812', 'map': {'pin': '66', 'PIN': '66'}}, {'alias': u'button1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa2746fdf50>, 'file': 'button', 'map': {'PIN': '62', 'pin': '62'}}]
    if (!temp1.init()) {
      uart_print_char_array("\n\nFAILed to initialise temp1\n\n");
      failed = true;
    }
    if (!humidity1.init()) {
      uart_print_char_array("\n\nFAILed to initialise humidity1\n\n");
      failed = true;
    }
    if (!ldr1.init()) {
      uart_print_char_array("\n\nFAILed to initialise ldr1\n\n");
      failed = true;
    }
    if (!speaker1.init()) {
      uart_print_char_array("\n\nFAILed to initialise speaker1\n\n");
      failed = true;
    }
    if (!led1.init()) {
      uart_print_char_array("\n\nFAILed to initialise led1\n\n");
      failed = true;
    }
    if (!button1.init()) {
      uart_print_char_array("\n\nFAILed to initialise button1\n\n");
      failed = true;
    }

    return !failed;
      
}
