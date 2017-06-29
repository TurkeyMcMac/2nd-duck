
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void delay(unsigned int time) {
	clock_t end = clock() + time;
	while (clock() <= end);
}


char *sayInto(char *target, char *message) {
	static bool mouthOpen = false;
	mouthOpen = !mouthOpen;
	char *duckPicture = mouthOpen ? "7^< -{%s}" : "7^= -{%s}";
	sprintf(target, duckPicture, message);
	return target;
}

void sayOverTime(unsigned int wait, char *message) {
	int length = strlen(message);
	char *thingToSay = malloc(length);
	for (int i = 0; i <= length; ++i){
		strncpy(thingToSay, message, i);
		thingToSay[i] = 0;
		char *str = malloc(i + 8);
		printf("%s\r", sayInto(str, thingToSay));
		fflush(stdout);
		free(str);
		delay(wait);
	}
	free(thingToSay);
	printf("\n");
}

void sayFromText(char *wait, char *message) {
	sayOverTime(strtol(wait, 0, 10) * 1000, message);
}

int main(int argc, char *argv[]) {
	sayFromText(argv[1], argv[2]);
	return 0;
}
