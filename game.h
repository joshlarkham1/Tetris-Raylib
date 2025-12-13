#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	void Draw();
	bool MoveBlockDown();
	void HandleInput();
	void Reset();
	bool gameOver;
	int score;
	Music music;

private:
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();
	bool BlockFits();
	bool BlockFitsTest(Block& block);
	void LockBlock();
	void RotateBlock();
	bool IsBlockOutside();
	void UpdateScore(int linesCleared, int moveDownPoints);
	Grid grid;
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Sound rotateSound;
	Sound clearSound;
	Sound gameOverSound;
	Sound tetrisSound;
	Sound moveSound;
	Sound contactSound;
};