
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

void sayInstantly(char *message) {
	char *str = malloc(strlen(message) + 8);
	puts(sayInto(str, message));
	free(str);
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

int main(int argc, char *argv[]) {
	if (argv[1] == "-i" || argv[1] == "--instant") sayInstantly(argv[2]);
	else sayOverTime(strtol(argv[1], 0, 10) * 1000, argv[2]);

	return 0;
}
