#include "vld.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "Display.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEscape = 27;
constexpr int kBackspace = 8;

void GetLevelDimensions(int& width, int& height);
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height);
void SaveLevel(char* pLevel, int width, int height);
void DisplayLegend();
void RunEditor(char* pLevel, int width, int height);

int main()
{
	char* pLevel = nullptr;
	int levelWidth;
	int levelHeight;
	bool done = false;

	while (!done)
	{
		system("cls");
		cout << "Please select one of the following options:" << endl;
		cout << "1. Load Level" << endl;
		cout << "2. New Level" << endl;
		cout << "3. Quit" << endl;

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

void DisplayLegend()
{
	cout << "Arrows to move cursor" << endl;
	cout << "ESC to finish editing" << endl;
	cout << "+ | - for walls" << endl;
	cout << "@ for player start" << endl;
	cout << "r g b for key" << endl;
	cout << "R G B for door" << endl;
	cout << "* for star" << endl;
	cout << "$ for money" << endl;
	cout << "v for vertical moving enemy" << endl;
	cout << "h for horizontal moving enemy" << endl;
	cout << "e for non-moving enemy" << endl;
	cout << "X for end" << endl;
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

void GetLevelDimensions(int& width, int& height)
{
	cout << "Enter the width of your level: ";
	cin >> width;

	cout << "Enter the height of your level: ";
	cin >> height;
}