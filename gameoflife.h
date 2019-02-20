#pragma once
#include <string>
#include <vector>


class GameOfLife
{
public:
    GameOfLife(int x, int y, double percentage);
    int GetNeighbors(int x, int y);
    void Step();
    int GetNode(int x, int y);
    void SetNode(int x, int y, int status);
    void Output();

private:
    int iteration;
    const int LowerNeighborBoundary = 2;
    const int UpperNeighborBoundary = 3;
    int boardX;
    int boardY;
    std::vector<int> board;
    std::vector<int> newBoard;
    double percentage;
};