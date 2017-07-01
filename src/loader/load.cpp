#include <stdlib.h>
#include <string.h>
#include "load.h"

//#define WINDOWS
//#define DEBUG

#ifdef DEBUG
	#include <stdio.h>
#endif

#ifdef WINDOWS
	#define EXPORT_DLL extern "C" __declspec(dllexport)
#else
	#define EXPORT_DLL
#endif

EXPORT_DLL void DatFile::read(char key[], char res[]) {

	#ifdef DEBUG
		printf("Loader module, reading string...\n");
	#endif

	char line[256];
	char readKey[5]; //4 chars to name stuff is hardcoded in dat file
	
	while (fgets(line, sizeof(line), file)) {

		strncpy(readKey, line, 4);
		readKey[4] = (char) 0;

		if (!strcmp(readKey, key))
		{
			strcpy(res, line+5);
			res[strcspn(res, "\n")] = (char) 0;
			break;
		}	
	}

	rewind(file);

	#ifdef DEBUG
		printf("...read into buffer: %s\n", res);
	#endif
}

EXPORT_DLL float DatFile::read(char key[]) {

	#ifdef DEBUG
		printf("Loader module, reading float...\n");
	#endif

	char line[256];
	char readKey[5]; //4 chars to name stuff is hardcoded in dat file
	char res[32];

	while (fgets(line, sizeof(line), file)) {

		strncpy(readKey, line, 4);
		readKey[4] = (char) 0;

		if (!strcmp(readKey, key))
		{
			strcpy(res, line+5);
			break;
		}	
	}

	rewind(file);

	#ifdef DEBUG
		printf("...returning %f\n", atof(res));
	#endif

	return atof(res);
}