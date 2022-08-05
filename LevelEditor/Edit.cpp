#include <conio.h>
#include <iostream>
#include <fstream>
#include "Edit.h"
#include "Display.h"

using namespace std;

void GetLevelDimensions(int& width, int& height)
{
	cout << "Enter the width of your level: ";
	cin >> width;

	cout << "Enter the height of your level: ";
	cin >> height;
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height)
{
	int newCursorX = cursorX;
	int newCursorY = cursorY;

	int intInput = _getch();

	if (intInput == kArrowInput)
	{
		int arrowInput = _getch();
		switch (arrowInput)
		{
		case kLeftArrow:
			newCursorX--;
			break;
		case kRightArrow:
			newCursorX++;
			break;
		case kUpArrow:
			newCursorY--;
			break;
		case kDownArrow:
			newCursorY++;
			break;
		}

		if (newCursorX < 0)
			newCursorX = 0;
		else if (newCursorX == width)
			newCursorX = width - 1;
		if (newCursorY < 0)
			newCursorY = 0;
		else if (newCursorY == height)
			newCursorY = height - 1;

		cursorX = newCursorX;
		cursorY = newCursorY;
	}
	else
	{
		if (intInput == kEscape)
		{
			return true;
		}
		else if (intInput == kBackspace)
		{
			// ignore
		}
		else
		{
			int index = GetIndexFromXY(newCursorX, newCursorY, width);
			pLevel[index] = (char)intInput;
		}
	}
	return false;
}

void SaveLevel(char* pLevel, int width, int height)
{
	cout << "Pick a name for your level file (eg: Level1.txt): ";
	string levelName;
	cin >> levelName;

	levelName.insert(0, "../");

	ofstream levelFile;
	levelFile.open(levelName);
	if (!levelFile)
	{
		cout << "Opening file failed!" << endl;
	}
	else
	{
		levelFile << width << endl;
		levelFile << height << endl;
		levelFile.write(pLevel, width * height);
		if (!levelFile)
		{
			cout << "Write failed!" << endl;
		}
		levelFile.close();
	}
}

void RunEditor(char* pLevel, int width, int height)
{
	int cursorX = 0;
	int cursorY = 0;
	bool doneEditing = false;
	while (!doneEditing)
	{
		system("cls");
		DisplayLevel(pLevel, width, height, cursorX, cursorY);
		DisplayLegend();
		doneEditing = EditLevel(pLevel, cursorX, cursorY, width, height);
	}

	system("cls");
	DisplayLevel(pLevel, width, height, -1, -1);

	SaveLevel(pLevel, width, height);
}