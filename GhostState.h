#pragma once

class Ghost;

class GhostState
{
public:
    virtual ~GhostState() {}
    virtual void enter(Ghost &g) {}
    virtual void update(Ghost &g, Player &p, Map &m) {}
};

class GhostHuntingState : public GhostState
{
private:
    Direction gDir;
    Direction gbackDir;
    Direction optimalDir;
    Vector2D step;
    Vector2D side;
    Vector2D dest;

    int distFromPlayerX, distFromPlayerY;
    ObjectID destBlock, side1Block, side2Block;

public:
    void enter(Ghost &g);
    void update(Ghost &g, Player &p, Map &m);
};