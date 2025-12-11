#include "game.h"
#include "grid.h"
#include <random>

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
}

Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}

	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return  { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
	}
	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	
	case KEY_DOWN:
		MoveBlockDown();
		break;
	
	case KEY_UP:
		RotateBlock();
		break;
	}
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles)
	{
		if (item.row >= grid.numRows || item.column < 0 || item.column >= grid.numCols)
		{
			return false;
		}
		if (item.row >= 0 && grid.grid[item.row][item.column] != 0)
		{
			return false;
		}
	}
	return true;
}

bool Game::BlockFitsTest(Block& block)
{
	std::vector<Position> tiles = block.GetCellPositions();

	for (Position item : tiles)
	{
		if (item.column < 0 || item.column >= grid.numCols)
		{
			return false;
		}
		if (item.row >= grid.numRows)
		{
			return false;
		}
		if (item.row >= 0 && grid.grid[item.row][item.column] != 0)
		{
			return false;
		}
	}
	return true;
}


void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles)
	{
		if (!grid.IsCellOutside(item.row, item.column))
		{
			grid.grid[item.row][item.column] = currentBlock.id;
		}
	}

	grid.ClearFullRows();

	Block testBlock = nextBlock;
	if (!BlockFitsTest(testBlock))
	{
		gameOver = true;
		return;
	}

	currentBlock = nextBlock;
	nextBlock = GetRandomBlock();
}


bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw();
}

void Game::MoveBlockLeft()
{
	if (!gameOver)
	{
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRight()
{
	if (!gameOver)
	{
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::RotateBlock()
{
	if (!gameOver)
	{
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Unrotate();
		}
	}
}