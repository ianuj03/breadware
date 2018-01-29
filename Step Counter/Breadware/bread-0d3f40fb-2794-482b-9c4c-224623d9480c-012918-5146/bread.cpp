#include "bread.h"

bool bread_init() {
    uart_start(9600);
    bool failed = false;
    // [{'alias': u'acc1', 'type': <autogen.breadware.hardware_module_mapper.DataSensor object at 0x7fa274809090>, 'file': 'accel_mma8652', 'map': {}}]
    if (!acc1.init()) {
      uart_print_char_array("\n\nFAILed to initialise acc1\n\n");
      failed = true;
    }

    return !failed;
      
}
