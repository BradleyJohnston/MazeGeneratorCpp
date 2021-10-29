#include "MazeContainer.h"

using namespace Maze;

void Maze::Maze_Container::setHeight(unsigned int height)
{
	this->height = height;
}

void Maze::Maze_Container::setWidth(unsigned int width)
{
	this->width = width;
}

void Maze::Maze_Container::setWhiteRatio(unsigned int whiteRatio)
{
	this->whiteRatio = whiteRatio;
}

unsigned int Maze::Maze_Container::getHeight()
{
	return this->height;
}

unsigned int Maze::Maze_Container::getWidth()
{
	return this->width;
}

unsigned int Maze::Maze_Container::getWhiteRatio()
{
	return this->whiteRatio;
}

void Maze::Maze_Container::openNorthPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] | 0b10000000;
}

void Maze::Maze_Container::openEastPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] | 0b01000000;
}

void Maze::Maze_Container::openSouthPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] | 0b00100000;
}

void Maze::Maze_Container::openWestPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] | 0b00010000;
}

void Maze::Maze_Container::closeNorthPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] & ~0b10000000;
}

void Maze::Maze_Container::closeEastPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] & ~0b01000000;
}

void Maze::Maze_Container::closeSouthPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] & ~0b00100000;
}

void Maze::Maze_Container::closeWestPath(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] & ~0b00010000;
}

bool Maze::Maze_Container::isNorthPath(unsigned int row, unsigned int col)
{
	return this->maze[row][col] & 0b10000000;
}

bool Maze::Maze_Container::isEastPath(unsigned int row, unsigned int col)
{
	return this->maze[row][col] & 0b01000000;
}

bool Maze::Maze_Container::isSouthPath(unsigned int row, unsigned int col)
{
	return this->maze[row][col] & 0b00100000;
}

bool Maze::Maze_Container::isWestPath(unsigned int row, unsigned int col)
{
	return this->maze[row][col] & 0b00010000;
}

void Maze::Maze_Container::visitCell(unsigned int row, unsigned int col)
{
	this->maze[row][col] = this->maze[row][col] | 0b00001000;
}

void Maze::Maze_Container::initializeMaze()
{
	this->maze = new char* [this->height];
	for (unsigned int i = 0; i < this->height; i++)
	{
		this->maze[i] = new char[this->width];
		for (unsigned int j = 0; j < width; j++)
		{
			this->maze[i][j] = (char)0;
		}
	}
}

void Maze::Maze_Container::unvisit()
{
	for (unsigned int i = 0; i < this->height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			this->maze[i][j] = this->maze[i][j] & ~0b00001000;
		}
	}
}

void Maze::Maze_Container::reset()
{
	for (unsigned int i = 0; i < this->height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < 5; k++)
			{
				this->maze[i][j] = (char)0;
			}
		}
	}
}

bool Maze::Maze_Container::isCellVisited(unsigned int row, unsigned int col)
{
	return this->maze[row][col] != '\0';
}

Pair Maze::Maze_Container::getRandomUnvisitedNeighbors(unsigned int row, unsigned int col)
{
	int count = 0;
	Pair returnValue;

	// North
	if (row != 0)
	{
		count += !this->isCellVisited(row - 1, col) ? 1 : 0;
	}

	// East
	if (col != this->width - 1)
	{
		count += !this->isCellVisited(row, col + 1) ? 1 : 0;
	}

	// South
	if (row != this->height - 1)
	{
		count += !this->isCellVisited(row + 1, col) ? 1 : 0;
	}

	// West
	if (col != 0)
	{
		count += !this->isCellVisited(row, col - 1) ? 1 : 0;
	}

	if (count == 0)
	{
		returnValue.x = row;
		returnValue.y = col;
		return returnValue;
	}

	
	int randomNeighbor = rand() % count;

	// North
	if (row != 0)
	{
		randomNeighbor -= !this->isCellVisited(row - 1, col) ? 1 : 0;
		if (randomNeighbor < 0)
		{
			returnValue.x = row - 1;
			returnValue.y = col;

			return returnValue;
		}
	}

	// East
	if (col != this->width - 1)
	{
		randomNeighbor -= !this->isCellVisited(row, col + 1) ? 1 : 0;
		if (randomNeighbor < 0)
		{
			returnValue.x = row;
			returnValue.y = col + 1;

			return returnValue;
		}
	}

	// South
	if (row != this->height - 1)
	{
		randomNeighbor -= !this->isCellVisited(row + 1, col) ? 1 : 0;
		if (randomNeighbor < 0)
		{
			returnValue.x = row + 1;
			returnValue.y = col;

			return returnValue;
		}
	}

	// West
	if (col != 0)
	{
		randomNeighbor -= !this->isCellVisited(row, col - 1) ? 1 : 0;
		if (randomNeighbor < 0)
		{
			returnValue.x = row;
			returnValue.y = col - 1;

			return returnValue;
		}
	}

	returnValue.x = row;
	returnValue.y = col;

	return returnValue;
}

Maze::Maze_Container::Maze_Container()
{
	this->width = 0;
	this->height = 0;
	initializeMaze();
}

Maze::Maze_Container::Maze_Container(unsigned int height, unsigned int width)
{
	this->width = width;
	this->height = height;
	initializeMaze();
}

Maze::Maze_Container::~Maze_Container()
{
	for (int i = 0; i < this->height; i++)
	{
		delete[] this->maze[i];
	}
	delete[] this->maze;
}

void Maze::Maze_Container::writeMazeAsImage(string filename)
{
	cv::imwrite(filename, this->convertMazeToImage());
}

cv::Mat Maze::Maze_Container::convertMazeToImage()
{
	int imgHeight = (this->height * (this->whiteRatio + 1)) + 2;
	int imgWidth = (this->width * (this->whiteRatio + 1)) + 2;

	cv::Mat image = cv::Mat::zeros(imgHeight, imgWidth, CV_8UC3);

	cv::Vec3b white = cv::Vec3b(255, 255, 255);


	for (unsigned int i = 0; i < this->height; i++)
	{
		for (unsigned int j = 0; j < this->width; j++)
		{
			// Fill white square
			for (unsigned int x = 0; x < this->whiteRatio; x++)
			{
				for (unsigned int y = 0; y < this->whiteRatio; y++)
				{
					image.at<cv::Vec3b>((i * (this->whiteRatio + 1)) + 1 + y, (j * (this->whiteRatio + 1)) + 1 + x) = white;
				}
			}

			// Fill East wall
			if (this->isEastPath(i, j))
			{
				for (unsigned int x = 0; x < this->whiteRatio; x++)
				{
					image.at<cv::Vec3b>((i * (this->whiteRatio + 1)) + 1 + x, (j * (this->whiteRatio + 1)) + 1 + this->whiteRatio) = white;
				}
			}

			// Fill South wall
			if (this->isSouthPath(i, j))
			{
				for (unsigned int x = 0; x < this->whiteRatio; x++)
				{
					image.at<cv::Vec3b>((i * (this->whiteRatio + 1) + 1 + this->whiteRatio), (j * (this->whiteRatio + 1)) + 1 + x) = white;
				}
			}
		}
	}

	return image;
}

void Maze::Maze_Container::display()
{
	for (int x = 0; x < this->height; x++)
	{
		for (int y = 0; y < this->width; y++)
		{
			cout << this->maze[x][y] << ",";
		}
		cout << endl;
	}
}

