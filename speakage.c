
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

char *sayInto(char *target, char *message, bool mouthOpen) {
	char *duckPicture = mouthOpen ? "7^< -{%s}" : "7^= -{%s}";
	sprintf(target, duckPicture, message);
	return target;
}

void sayOverTime(size_t wait, char *message) {
	long unsigned length = strlen(message) + 1;
	char *thingToSay = malloc(length);
	char *said = malloc(length + 7);
	bool mouthOpen = false;
	for (int i = 0; i < length; ++i, mouthOpen = !mouthOpen) {
		strncpy(thingToSay, message, i);
		thingToSay[i] = 0;
		printf("%s\r", sayInto(said, thingToSay, mouthOpen));
		fflush(stdout);
		delay(wait);
	}
	free(said);
	free(thingToSay);
	printf("\n");
}

void sayFromText(char *wait, char *message) {
	sayOverTime(strtol(wait, 0, 10), message);
}

char *randomPhrase() {
	char *phrasesLocation = PHRASES_LOCATION;
	FILE *phrases = fopen(phrasesLocation, "r");
	if (!phrases) {
		char *notFound = malloc(250);
		sprintf(notFound, "Phrase list file '%s' not found.", phrasesLocation);
		return notFound;
	}
	char *phraseList[MAX_PHRASE_NUM];
	size_t phrasesFound = rflarr(phraseList, phrases, MAX_PHRASE_NUM, MAX_READ_PHRASE_LEN);
	fclose(phrases);
	srand(time(NULL));
	size_t indexPicked = rand() % phrasesFound;
	char *pickedStr = phraseList[indexPicked];
	for (size_t i = 0; i < phrasesFound; ++i) {
		if (i != indexPicked) free(phraseList[i]);
	}
	return pickedStr;
}

