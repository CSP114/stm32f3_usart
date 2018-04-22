#include "delay.h"
#include "gpio.h"
#include "stm32f3xx.h"                  // Device header


void usart_init(void){
    //Set PA2 as USART2_TX Set PA3 as USART3_TX
    RCC->AHBENR |= (0x1 << 17);//Enable PORTA
    GPIOA->MODER &= ~(0x3 << (2*3));// Clear MODER3
    GPIOA->MODER |= (0x2 << (2*3));// Set MODER3 as Alternate mode
    GPIOA->MODER &= ~(0x3 << (2*2));// Clear MODER2
    GPIOA->MODER |= (0x2 << (2*2));// Set MODER2 as Alternate mode
    
    GPIOA->AFR[0] &= ~(0xf << (4*3));// Clear MODER3
    GPIOA->AFR[0] |= (0x7 << (4*3));// Set MODER3 as Alternate mode
    GPIOA->AFR[0] &= ~(0xf << (4*2));// Clear MODER2
    GPIOA->AFR[0] |= (0x7 << (4*2));// Set MODER2 as Alternate mode
    
    RCC->APB1ENR |= (0x1 << 17);//enable USART2
    
    SystemCoreClockUpdate();
    
    USART2->BRR = 0x0341;//Pck=8Mhz freqin=9600bps 
	USART2->CR1 = (0x1<<0)//UE =1
                |(0x1<<3)//TEN =1
                |(0x1<<2);//REN =1
}

void usart2_putc(char c){
    while(!(USART2->ISR & (0x1 << 7)));
    USART2->TDR = c;
}

int main(){
    int state = 0;
    pb13_init();
    pc13_init();
    usart_init();
    while(1) {
        state = !state;
        pb13_write(state);
        usart2_putc('c');
        usart2_putc('\n');
        delay_ms(500);
    }
}
