
#ifndef SPEAKAGE_H_
#define SPEAKAGE_H_

void delay(unsigned int time);

char *sayInto(char *target, char *message);

void sayOverTime(unsigned int wait, char *message);

void sayFromText(char *wait, char *message);

char *randomPhrase(char *randomize);

#endif
