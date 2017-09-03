
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "file-line-reader.h"
#include "settings.h"
#include "speakage.h"

int main(int argc, char *argv[]) {
	int exitStatus = 0;
	char opt,
	     optMaybe;
	bool hasOpt = false;
	while ((optMaybe = getopt(argc, argv, "ehpr")) != -1) {
		if (hasOpt) {
			puts("Multiple options are unnecessary.");
			exitStatus = -3;
			goto help;
		}
		opt = optMaybe;
		hasOpt = true;
	}
	switch (opt) {
		case 'e':
			if (argc < 4) {
				exitStatus = -1;
				goto help;
			}
			sayFromText(argv[2], argv[3]);
			break;
		case 'h':
			goto help;
		case 'p':
			puts(PHRASES_LOCATION);
			break;
		case 'r':
			if (argc < 3) {
				exitStatus = -2;
				goto help;
			}
			srand(time(NULL));
			sayFromText(argv[2], randomPhrase());
			break;
		default: 
			exitStatus = -4;
		help:
			puts(
"Usage: duck [option] [wait] [phrase]\n\
  options:\n\
    -e wait phrase  Echo the specified phrase, waiting the specified\n\
                    time between saying each character.\n\
    -h              Display this help information.\n\
    -p              Print the path of the file containing phrases.\n\
    -r wait         Say a phrase picked randomly from the phrase file,\n\
                    waiting the specified time between saying each\n\
		    character.");
			break;
	}
	return exitStatus;
}
