#include "vld.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "Display.h"
#include "Edit.h"

using namespace std;

int main()
{
	char* pLevel = nullptr;
	int levelWidth;
	int levelHeight;
	bool done = false;

	while (!done)
	{
		system("cls");
		DisplayMenu();

		int input;
		cin >> input;

		if (input == 1)
		{
			// Load Level
			cout << "Enter Level name: ";
			string levelName;
			cin >> levelName;

			levelName.insert(0, "../");

			ifstream levelFile;
			levelFile.open(levelName);

			if (!levelFile)
			{
				cout << "Opening file failed!" << endl;
			}
			else
			{
				constexpr int tempSize = 25;
				char temp[tempSize];

				levelFile.getline(temp, tempSize, '\n');
				levelWidth = atoi(temp);

				levelFile.getline(temp, tempSize, '\n');
				levelHeight = atoi(temp);

				pLevel = new char[levelWidth * levelHeight];
				levelFile.read(pLevel, levelWidth * levelHeight);
				levelFile.close();

				RunEditor(pLevel, levelWidth, levelHeight);

				delete[] pLevel;
				pLevel = nullptr;

			}

		}
		else if (input == 2)
		{
			// New Level
			GetLevelDimensions(levelWidth, levelHeight);

			pLevel = new char[levelWidth * levelHeight];

			for (int i = 0; i < levelWidth * levelHeight; i++)
			{
				pLevel[i] = ' ';
			}

			RunEditor(pLevel, levelWidth, levelHeight);

			delete[] pLevel;
			pLevel = nullptr;
		}
		else
		{
			done = true;
		}

	}

}