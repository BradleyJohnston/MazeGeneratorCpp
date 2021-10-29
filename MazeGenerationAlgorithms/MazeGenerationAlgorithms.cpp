// MazeGenerationAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include "MazeContainer.cpp"

using namespace std;


// Maze Generation Algorithms
void RecursiveBacktracker(Maze_Container & maze);

int main()
{
    Maze_Container maze;

    int size;
    int ratio;

    cout << "Enter scale of image: ";
    cin >> size;

    cout << "Enter white to black ratio: ";
    cin >> ratio;

    maze.setHeight(9 * size);

    maze.setWidth(16 * size);
    maze.setWhiteRatio(ratio);
    maze.initializeMaze();
    
    RecursiveBacktracker(maze);

    maze.writeMazeAsImage("./backtracker_maze.png");

    return 0;
}


void RecursiveBacktracker(Maze_Container & maze)
{
    unsigned int height = maze.getHeight();
    unsigned int width = maze.getWidth();

    stack<Pair> backtracker;
    Pair pairBuffer;
    Pair neighbor;

    /*
    
    #include <random>

    int number = rand() % 6;

    */

    pairBuffer.x = 0;
    pairBuffer.y = 0;

    backtracker.push(pairBuffer);
    unsigned long iterations = 0;
    while (!backtracker.empty())
    {
        iterations++;

        //if (iterations % 10 == 0)
        //{
        //    cout << "Iterations: " << iterations << " size: " << backtracker.size() << endl;
        //    cout << backtracker.top().x << backtracker.top().y << endl;
        //    backtracker = stack<Pair>();
        //    break;
        //}

        pairBuffer = backtracker.top();
        backtracker.pop();


        // Choose one of the neighbors
        neighbor = maze.getRandomUnvisitedNeighbors(pairBuffer.x, pairBuffer.y);


        if (neighbor.x != pairBuffer.x || neighbor.y != pairBuffer.y)
        {
            // Push current cell to stack
            backtracker.push(pairBuffer);

            // Remove the wall between the current cell and the chose cell
            if (neighbor.y == pairBuffer.y)
            {
                if (neighbor.x > pairBuffer.x)
                {
                    maze.openSouthPath(pairBuffer.x, pairBuffer.y);
                    maze.openNorthPath(neighbor.x, neighbor.y);
                }
                else
                {
                    maze.openNorthPath(pairBuffer.x, pairBuffer.y);
                    maze.openSouthPath(neighbor.x, neighbor.y);
                }
            }
            else
            {
                if (neighbor.y > pairBuffer.y)
                {
                    maze.openEastPath(pairBuffer.x, pairBuffer.y);
                    maze.openWestPath(neighbor.x, neighbor.y);
                }
                else
                {
                    maze.openWestPath(pairBuffer.x, pairBuffer.y);
                    maze.openEastPath(neighbor.x, neighbor.y);
                }
            }
            // Mark neighbor cell as visited and push it to the stack.
            backtracker.push(neighbor);
        }
    }

    cout << "Ran " << iterations << " iterations" << endl;

    return;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
