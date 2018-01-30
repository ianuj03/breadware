#include "bread.h"

bool bread_init() {
    uart_start(9600);
    bool failed = false;
    // [{'alias': u'acc1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa274710c90>, 'file': 'accel_mma8652', 'map': {}}, {'alias': u'g1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa274710f50>, 'file': 'gyro_l3gd20', 'map': {}}]
    if (!acc1.init()) {
      uart_print_char_array("\n\nFAILed to initialise acc1\n\n");
      failed = true;
    }
    if (!g1.init()) {
      uart_print_char_array("\n\nFAILed to initialise g1\n\n");
      failed = true;
    }

    return !failed;
      
}
