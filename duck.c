
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PHRASES_LOCATION strcat(getenv("HOME"), "/phrases.txt")
#define MAX_PHRASE_NUM 100
#define MAX_READ_PHRASE_LEN 200

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
	if (!strcmp(argv[1], "echo")) {
		sayFromText(argv[2], argv[3]);
	} else if (!strcmp(argv[1], "rand")) {
		char phrase[MAX_READ_PHRASE_LEN];
		memset(phrase, 0, MAX_READ_PHRASE_LEN);
		sayFromText(argv[2], randomPhrase(phrase));
	}
	return 0;
}
