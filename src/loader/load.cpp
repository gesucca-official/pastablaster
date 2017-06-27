#include "load.h"
#include <string.h>

void DatFile::read(char key[], char res[]) {

	char line[256];
	char readKey[5]; //4 chars to name stuff is hardcoded in dat file
	
	while (fgets(line, sizeof(line), file)) {

		strncpy(readKey, line, 4);
		readKey[4] = (char) 0;

		if (!strcmp(readKey, key))
		{
			strcpy(res, line+5);
			res[strcspn(res, "\n")] = (char) 0;
		}	
	}

	rewind(file);
}