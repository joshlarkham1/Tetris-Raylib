#include "game.h"
#include "grid.h"
#include <random>

// input vars
const double DAS = 0.18;	// delay auto shift
const double ARR = 0.04;	// auto repeat rate

double leftHoldTime = 0;
double rightHoldTime = 0;
double downHoldTime = 0;


Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;

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
		return;
	}

	double t = GetTime();
	if (IsKeyPressed(KEY_LEFT)) 
	{
		MoveBlockLeft();
		leftHoldTime = t;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		if (t - leftHoldTime >= DAS)
		{
			static double lastRepeat = 0;
			if (t - lastRepeat >= ARR)
			{
				MoveBlockLeft();
				lastRepeat = t;
			}
		}
	}
	else
	{
		leftHoldTime = 0;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		MoveBlockRight();
		rightHoldTime = t;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		if (t - rightHoldTime >= DAS)
		{
			static double lastRepeat = 0;
			if (t - lastRepeat >= ARR)
			{
				MoveBlockRight();
				lastRepeat = t;
			}
		}
	}
	else
	{
		rightHoldTime = 0;
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		MoveBlockDown();
		downHoldTime = t;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		static double lastDrop = 0;
		if (t - lastDrop >= ARR)
		{
			bool moved = MoveBlockDown();
			if (moved)
			{
				UpdateScore(0, 1);
			}
			lastDrop = t;
		}
	}
	else
	{
		downHoldTime = 0;
	}
	if (IsKeyPressed(KEY_UP))
		RotateBlock();
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

	Block testBlock = nextBlock;
	if (!BlockFitsTest(testBlock))
	{
		gameOver = true;
		return;
	}

	currentBlock = nextBlock;
	nextBlock = GetRandomBlock();
	int rowsCleared = grid.ClearFullRows();
	UpdateScore(rowsCleared, 0);
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
	score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		score += 40;
		break;
	case 2:
		score += 100;
		break;
	case 3:
		score += 300;
		break;
	case 4:
		score += 1200;
		break;
	default:
		break;
	}
	score += moveDownPoints;
}

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw(11 ,11);
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 310); // I BLOCK
		break;
	case 4:
		nextBlock.Draw(255, 280); // O BLOCK
		break;
	default:
		nextBlock.Draw(270, 270);
		break;
	}
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

bool Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
			return false;
		}
		return true;
	}
	return false;
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