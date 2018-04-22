#include "delay.h"
#include "gpio.h"

int main(){
    pb13_init();
    pc13_init();
    while(1) {
        pb13_write(pc13_read());
    }
}
