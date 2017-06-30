
#include "speakage.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "delay.h"
#include "file-line-reader.h"
#include "settings.h"

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
	char **phraseList = malloc(MAX_PHRASE_NUM * sizeof (char *));
	size_t phrasesFound = rflarr(phraseList, phrases, MAX_PHRASE_NUM, MAX_READ_PHRASE_LEN);
	fclose(phrases);
	srand(time(NULL));
	char *pickedStr = phraseList[rand() % phrasesFound];
	randomize = strcpy(randomize, pickedStr);
	free(*phraseList);
	free(phraseList);
	return randomize;
}

