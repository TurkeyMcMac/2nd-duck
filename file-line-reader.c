
#include "file-line-reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t rflarr (char **arr, FILE *file, const int maxLines, const int maxLength) {
	for (size_t i = 0; i < maxLines; ++i) {
		arr[i] = malloc(maxLength);
		if (!fgets(arr[i], maxLength, file)) return i;
		else arr[i][strlen(arr[i]) - 1] = 0;
	}
}

