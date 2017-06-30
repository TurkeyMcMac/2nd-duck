
#include "delay.h"

#include <stdio.h>
#include <time.h>

void delay(size_t time) {
	clock_t end = clock() + time;
	while (clock() <= end);
}

