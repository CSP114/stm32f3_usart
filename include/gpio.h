#ifndef GPIO_INCLUDED
#define GPIO_INCLUDED

void pb13_init(void);

void pb13_write(int state);

void pc13_init(void);

int pc13_read(void);

#endif
