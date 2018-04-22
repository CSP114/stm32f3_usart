#include "stm32f3xx.h"
#include "gpio.h"

void pb13_init(void){
    RCC->AHBENR |= (0x1 << 18);//Enable PORTB
    GPIOB->MODER &= ~(0x3 << (2*13));// Clear MODER13
    GPIOB->MODER |= (0x1 << (2*13));// Set MODER13 as General purpose output mode
}

void pb13_write(int state){
    *((uint32_t*)&GPIOB->BSRRL) = (state) ? (0x1 << 13) : (0x1 << (16 + 13));
}

void pc13_init(void){
    RCC->AHBENR |= (0x1 << 19);//Enable PORTC
    GPIOC->MODER &= ~(0x3 << (2*13));// Clear MODER13
    GPIOC->MODER |= (0x0 << (2*13));// Set MODER13 as input 
}

int pc13_read(void){
    return (GPIOC->IDR & (0x1 << 13)) ? 1 : 0;
}
