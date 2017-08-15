#include "delay.h"

#include <stdio.h>

void delay (int millis) {
#ifdef WIN32
	#include <windows.h>
	Sleep(millis);
#else
	#include <unistd.h>
	usleep(millis * 1000);
#endif
}
