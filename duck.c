
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "settings.h"

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
	for (int i = 0; i <= length; ++i) {
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

char *randomPhrase(char *randomize) {
	FILE *phrases = fopen(PHRASES_LOCATION, "r");
	if (!phrases) {
		fprintf(stderr, "Phrase list file '%s' not found.\n", PHRASES_LOCATION);
		return randomize;
	}
	char phraseList[MAX_PHRASE_NUM][MAX_READ_PHRASE_LEN];
	int i = 0;
	for (i = 0; i < MAX_PHRASE_NUM; ++i)
		if (!fgets(phraseList[i], MAX_READ_PHRASE_LEN, phrases)) break;
	fclose(phrases);
	srand(time(NULL));
	char *pickedStr = phraseList[rand() % i];
	randomize = strncpy(randomize, pickedStr, strlen(pickedStr) - 1);
	return randomize;
}

int main(int argc, char *argv[]) {
	char opt,
	     optMaybe;
	bool hasOpt = false;
	while ((optMaybe = getopt(argc, argv, "ehpr")) != -1) {
		if (hasOpt) {
			puts("Multiple options are unnecessary.");
			return -1;
		}
		opt = optMaybe;
		hasOpt = true;
	}
	switch (opt) {
		case 'e': {
			if (!(argc >= 4)) goto help;
			int waitIndex;
			int messageIndex;
			const char *optArg = "-e";
			if (!strcmp(argv[1], optArg)) {
				waitIndex = 2;
				messageIndex = 3;
			} else if (!strcmp(argv[2], optArg)) {
				waitIndex = 1;
				messageIndex = 3;
			} else {
				waitIndex = 1;
				messageIndex = 2;
			}
			sayFromText(argv[waitIndex], argv[messageIndex]);
			break;
		}
		case 'p':
			puts(PHRASES_LOCATION);
			break;
		case 'r': {
			if (!(argc >= 3)) goto help;
			int waitIndex = !strcmp(argv[1], "-r") ? 2 : 1;
			char phrase[MAX_READ_PHRASE_LEN];
			memset(phrase, 0, MAX_READ_PHRASE_LEN);
			sayFromText(argv[waitIndex], randomPhrase(phrase));
			break;
		}
		default: help:
			puts("Placeholder help information.");
			break;
	}
	return 0;
}
