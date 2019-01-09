#include <iostream>
#include <random>

#include "gameoflife.h"

Node::Node(Status life)
    : life(life)
{
}

Status Node::GetStatus()
{
    return life;
}

void Node::Die()
{
    life = Status::Dead;
}

void Node::BeBorn()
{
    life = Status::Alive;
}

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
            board.push_back(Node(Status::Dead));
        }
        else
        {
            board.push_back(Node(Status::Alive));
        }
    }
}

Node GameOfLife::GetNode(int x, int y)
{
    return board[x + y * boardX];
}

void GameOfLife::SetNode(int x, int y, Node node)
{
    newBoard[x + y * boardX] = node;
}

Status GameOfLife::GetNodeStatus(int x, int y)
{
    return GetNode(x, y).GetStatus();
}

int GameOfLife::GetNeighbors(int x, int y)
{
    int aliveNeighbors = 0;

    // Row above
    if (x > 1 && y > 1)
    {
        if (GetNode(x - 1, y - 1).GetStatus() == Status::Alive)
        {
            aliveNeighbors++;
        }
    }

    if (y > 1)
    {
        if (GetNode(x, y - 1).GetStatus() == Status::Alive)
        {
            aliveNeighbors++;
        }
    }

    if (x < boardX - 1 && y > 1)
    {
        if (GetNode(x + 1, y - 1).GetStatus() == Status::Alive)
        {
            aliveNeighbors++;
        }
    }

    // Same row
    if (x > 1)
    {
        if (GetNode(x - 1, y).GetStatus() == Status::Alive)
        {
            aliveNeighbors++;
        }
    }

    if (x < boardX - 1)
    {
        if (GetNode(x + 1, y).GetStatus() == Status::Alive)
        {
            aliveNeighbors++;
        }
    }

    // Row below
    if (x > 1 && y < boardY - 1)
    {
        if (GetNode(x - 1, y + 1).GetStatus() == Status::Alive)
        {
            aliveNeighbors++;
        }
    }

    if (y < boardY - 1)
    {
        if (GetNode(x, y + 1).GetStatus() == Status::Alive)
        {
            aliveNeighbors++;
        }
    }

    if (x < boardX - 1 && y < boardY - 1)
    {
        if (GetNode(x + 1, y + 1).GetStatus() == Status::Alive)
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
            if (GetNode(x, y).GetStatus() == Status::Alive && (aliveNeighbors == 2 || aliveNeighbors == 3))
            {
            }
            // Rule 4.: Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
            else if (GetNode(x, y).GetStatus() == Status::Dead && aliveNeighbors == 3)
            {
                Node node = GetNode(x, y);
                node.BeBorn();
                SetNode(x, y, node);
            }
            // Rule 1.: Any live cell with fewer than two live neighbors dies, as if by underpopulation.
            // Rule 3.: Any live cell with more than three live neighbors dies, as if by overpopulation.
            else if (GetNode(x, y).GetStatus() == Status::Alive && (aliveNeighbors < LowerNeighborBoundary || aliveNeighbors > UpperNeighborBoundary))
            {
                Node node = GetNode(x, y);
                node.Die();
                SetNode(x, y, node);
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
            if (GetNode(x, y).GetStatus() == Status::Alive)
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