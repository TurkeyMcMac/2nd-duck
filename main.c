
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
		case 'e':
			if (!(argc >= 4)) goto help;
			sayFromText(argv[2], argv[3]);
			break;
		case 'p':
			puts(PHRASES_LOCATION);
			break;
		case 'r':
			if (!(argc >= 3)) goto help;
			char phrase[MAX_READ_PHRASE_LEN];
			memset(phrase, 0, MAX_READ_PHRASE_LEN);
			sayFromText(argv[2], randomPhrase(phrase));
			break;
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
