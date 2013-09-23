#ifndef LEVELIMPORTER_H
#define LEVELIMPORTER_H

#include <string>
#include <iostream>
#include "LodePNG.h"
using namespace std;
class LevelImporter
{
public:
	
	~LevelImporter(void);

	//Enter name of level without the .png file ending
	static int** LoadLevel(string p_levelName);
private:
	LevelImporter(void);
};

#endif