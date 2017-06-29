#include <stdlib.h>
#include <string.h>
#include "load.h"

//#define WINDOWS

#ifdef WINDOWS
	#define EXPORT_DLL extern "C" __declspec(dllexport)
#else
	#define EXPORT_DLL
#endif

EXPORT_DLL void DatFile::read(char key[], char res[]) {

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
}

EXPORT_DLL float DatFile::read(char key[]) {

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
	return atof(res);
}