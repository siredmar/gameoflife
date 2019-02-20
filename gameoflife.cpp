#include <iostream>
#include <random>

#include "gameoflife.h"

GameOfLife::GameOfLife(int x, int y, double percentage)
    : boardX(x)
    , boardY(y)
    , percentage(percentage)
    , iteration(0)
{
    std::mt19937 rng;
    for (int i = 0; i < x * y; i++)
    {
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1000);
        if (dist6(rng) > 1000 * percentage)
        {
            board.push_back(0);
        }
        else
        {
            board.push_back(1);
        }
    }
}

int GameOfLife::GetNode(int x, int y)
{
    return board[x + y * boardX];
}

void GameOfLife::SetNode(int x, int y, int status)
{
    newBoard[x + y * boardX] = status;
}

int GameOfLife::GetNeighbors(int x, int y)
{
    int aliveNeighbors = 0;

    // Row above
    if (x > 1 && y > 1)
    {
        if (GetNode(x - 1, y - 1) == 1)
        {
            aliveNeighbors++;
        }
    }

    if (y > 1)
    {
        if (GetNode(x, y - 1) == 1)
        {
            aliveNeighbors++;
        }
    }

    if (x < boardX - 1 && y > 1)
    {
        if (GetNode(x + 1, y - 1) == 1)
        {
            aliveNeighbors++;
        }
    }

    // Same row
    if (x > 1)
    {
        if (GetNode(x - 1, y) == 1)
        {
            aliveNeighbors++;
        }
    }

    if (x < boardX - 1)
    {
        if (GetNode(x + 1, y) == 1)
        {
            aliveNeighbors++;
        }
    }

    // Row below
    if (x > 1 && y < boardY - 1)
    {
        if (GetNode(x - 1, y + 1) == 1)
        {
            aliveNeighbors++;
        }
    }

    if (y < boardY - 1)
    {
        if (GetNode(x, y + 1) == 1)
        {
            aliveNeighbors++;
        }
    }

    if (x < boardX - 1 && y < boardY - 1)
    {
        if (GetNode(x + 1, y + 1) == 1)
        {
            aliveNeighbors++;
        }
    }
    return aliveNeighbors;
}

void GameOfLife::Step()
{
    int aliveNeighbors = 0;
    newBoard = board;
    for (int x = 0; x < boardX; x++)
    {
        for (int y = 0; y < boardY; y++)
        {
            aliveNeighbors = GetNeighbors(x, y);
            // Rule 2.: Any live cell with two or three live neighbors lives on to the next generation.
            if (GetNode(x, y) == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3))
            {
            }
            // Rule 4.: Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
            else if (GetNode(x, y) == 0 && aliveNeighbors == 3)
            {
                SetNode(x, y, 1);
            }
            // Rule 1.: Any live cell with fewer than two live neighbors dies, as if by underpopulation.
            // Rule 3.: Any live cell with more than three live neighbors dies, as if by overpopulation.
            else if (GetNode(x, y) == 1 && (aliveNeighbors < LowerNeighborBoundary || aliveNeighbors > UpperNeighborBoundary))
            {
                SetNode(x, y, 0);
            }
            aliveNeighbors = 0;
        }
    }
    board = newBoard;
}

void GameOfLife::Output()
{
    for (int y = 0; y < boardY; y++)
    {
        for (int x = 0; x < boardX; x++)
        {
            if (GetNode(x, y) == 1)
            {
                std::cout << "0";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Iteration: " << iteration++ << std::endl;
}