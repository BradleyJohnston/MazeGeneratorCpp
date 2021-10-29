#ifndef MAZE_CONTROLLER
#define MAZE_CONTROLLER

#include <random>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/cuda.inl.hpp>

using namespace std;


/****************************************************
 * MAZE CONTAINER
 * 
 * Maze Container will contain a 2 dimensional array
 * of char to store the information. Each char consists
 * of 8 bits that we will use for the important data
 * From Least Significant Bit to Most Significant Bit
 * 1) Is North path open
 * 2) Is East path open
 * 3) Is South path open
 * 4) Is West path open
 * 5) Has this cell been visited
 ****************************************************/
namespace Maze
{

	class Pair
	{
	public:
		unsigned int x;
		unsigned int y;
	};

	class Maze_Container
	{
	private:
		unsigned int height;
		unsigned int width;
		unsigned int whiteRatio;

		char** maze;
	public:
		void setHeight(unsigned int height);
		void setWidth(unsigned int width);
		void setWhiteRatio(unsigned int whiteRatio);
		unsigned int getHeight();
		unsigned int getWidth();
		unsigned int getWhiteRatio();

		void openNorthPath(unsigned int row, unsigned int col);
		void openEastPath(unsigned int row, unsigned int col);
		void openSouthPath(unsigned int row, unsigned int col);
		void openWestPath(unsigned int row, unsigned int col);

		void closeNorthPath(unsigned int row, unsigned int col);
		void closeEastPath(unsigned int row, unsigned int col);
		void closeSouthPath(unsigned int row, unsigned int col);
		void closeWestPath(unsigned int row, unsigned int col);

		bool isNorthPath(unsigned int row, unsigned int col);
		bool isEastPath(unsigned int row, unsigned int col);
		bool isSouthPath(unsigned int row, unsigned int col);
		bool isWestPath(unsigned int row, unsigned int col);

		void visitCell(unsigned int row, unsigned int col);

		void initializeMaze();
		void unvisit();
		void reset();

		bool isCellVisited(unsigned int row, unsigned int col);
		Pair getRandomUnvisitedNeighbors(unsigned int row, unsigned int col);

		Maze_Container();
		Maze_Container(unsigned int height, unsigned int width);
		~Maze_Container();

		// OpenCV focused methods
		void writeMazeAsImage(string filename);
		cv::Mat convertMazeToImage();

		void display();
	};
}

#endif