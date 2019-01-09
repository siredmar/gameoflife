#pragma once
#include <string>
#include <vector>

enum class Status
{
    Dead = 0,
    Alive = 1,
};

class Node
{
public:
    Node(Status life);
    Status GetStatus();
    void Die();
    void BeBorn();

private:
    Status life;
};

class GameOfLife
{
public:
    GameOfLife(int x, int y, double percentage);
    Status GetNodeStatus(int x, int y);
    int GetNeighbors(int x, int y);
    void Step();
    Node GetNode(int x, int y);
    void SetNode(int x, int y, Node node);
    void Output();
    int iteration;

private:
    const int LowerNeighborBoundary = 2;
    const int UpperNeighborBoundary = 3;
    int boardX;
    int boardY;
    std::vector<Node> board;
    std::vector<Node> newBoard;
    double percentage;
};