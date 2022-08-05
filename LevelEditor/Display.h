#pragma once

constexpr char kCursor = '_';

constexpr char kTopRightBorder = (char)187;
constexpr char kTopLeftBorder = (char)201;
constexpr char kBottomRightBorder = (char)188;
constexpr char kBottomLeftBorder = (char)200;
constexpr char kHorizontalBorder = (char)205;
constexpr char kVerticalBorder = (char)186;

int GetIndexFromXY(int x, int y, int width);
void DisplayMenu();
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
void DisplayLegend();