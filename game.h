#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	void Draw();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void HandleInput();
	Grid grid;
	bool gameOver;

private:
	bool BlockFits();
	bool BlockFitsTest(Block& block);
	void LockBlock();
	void RotateBlock();
	bool IsBlockOutside();
	void Reset();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};