
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file-line-reader.h"
#include "settings.h"
#include "speakage.h"

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
			puts(
"Usage: duck [option] wait [phrase]\n\
  options:\n\
    -e wait phrase  Echo the specified phrase, waiting the specified\n\
                    time between saying each character.\n\
    -r wait         Say a phrase picked randomly from the phrase file,\n\
                    waiting the specified time between saying each\n\
		    character.\n\
    -p              Print the path of the file containing phrases.");
			break;
	}
	return 0;
}
