#include <stdio.h>

class DatFile {
public:
	inline DatFile(char fileName[]) { file = fopen(fileName, "r"); }
	inline ~DatFile() { fclose(file); }
	void read(char key[], char res[]);
	float read(char key[]);
private:
	FILE* file;
};