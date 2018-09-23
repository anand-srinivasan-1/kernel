#include <arch.h>

#include "serial.h"

void arch_init() {
    serial_init();
    serial_print("hello world\n");
}
