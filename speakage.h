
#include <stdbool.h>
#include <stdio.h>

#ifndef SPEAKAGE_H_
#define SPEAKAGE_H_

char *sayInto(char *target, char *message, bool mouthOpen);

void sayOverTime(size_t wait, char *message);

void sayFromText(char *wait, char *message);

char *randomPhrase();

#endif
