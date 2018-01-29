#include "bread.h"

bool bread_init() {
    uart_start(9600);
    bool failed = false;
    // [{'alias': u'mic1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa27483b750>, 'file': 'mic_max4466', 'map': {'PIN': '68', 'pin': '68'}}, {'alias': u'led1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa27483ba90>, 'file': 'led_ws2812', 'map': {'pin': '69', 'PIN': '69'}}]
    if (!mic1.init()) {
      uart_print_char_array("\n\nFAILed to initialise mic1\n\n");
      failed = true;
    }
    if (!led1.init()) {
      uart_print_char_array("\n\nFAILed to initialise led1\n\n");
      failed = true;
    }

    return !failed;
      
}
