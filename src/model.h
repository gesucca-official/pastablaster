//element definition sucks
//array dimension need to be defined somewhere

#include <stdio.h>
#include <vector>

class Element {
public:
	void setImg(char img[]) {
		snprintf(pathToImg, 25, "%s", img);
	}
	void getImg(char* outStr) {
		for(int i=0; i < 25; ++i)
			outStr[i] = pathToImg[i];
	}
private:
	char pathToImg[25];
};


class DuelModel {
public:
	void addElement(Element el) {
		e.push_back(el);
	}
	std::vector<Element> getElements() {
		return e;
	};
private:
	std::vector<Element> e;
};


