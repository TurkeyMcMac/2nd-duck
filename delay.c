
#include "delay.h"

#include <time.h>

void delay(unsigned int time) {
	clock_t end = clock() + time;
	while (clock() <= end);
}

