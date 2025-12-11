#pragma once
#include <raylib.h>
#include <array>
#include <vector>

class Grid
{
public:
	Grid();
	int numRows;
	int numCols;
	void Initialize();
	void Print();
	void Draw();
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows();
	std::array<std::array<int, 10>, 20> grid;

private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int cellSize;
	std::vector<Color> colors;
};


