
#include <stdio.h>

#ifndef SPEAKAGE_H_
#define SPEAKAGE_H_

char *sayInto(char *target, char *message);

void sayOverTime(size_t wait, char *message);

void sayFromText(char *wait, char *message);

char *randomPhrase(char *randomize);

#endif
