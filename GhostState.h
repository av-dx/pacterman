#pragma once

class Ghost;

class GhostState
{
public:
    virtual GhostStateID stateID() {}
    virtual ~GhostState() {}
    virtual void enter(Ghost &g) {}
    virtual GhostState *update(Ghost &g, Player &p, Map &m) {}
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
    GhostStateID stateID();
    void enter(Ghost &g);
    GhostState *update(Ghost &g, Player &p, Map &m);
};

class GhostRetreatingState : public GhostState
{
private:
    Direction gDir;
    Direction gbackDir;
    Direction optimalDir;
    Vector2D spawner;
    Vector2D step;
    Vector2D side;
    Vector2D dest;

    int distFromSpawnerX, distFromSpawnerY;
    ObjectID destBlock, side1Block, side2Block;

public:
    GhostStateID stateID();
    void enter(Ghost &g);
    GhostState *update(Ghost &g, Player &p, Map &m);
};

class GhostVulnerableState : public GhostState
{
private:
    Direction gDir;
    Direction gbackDir;
    Direction optimalDir;
    Vector2D spawner;
    Vector2D step;
    Vector2D side;
    Vector2D dest;

    int timer;
    int distFromPlayerX, distFromPlayerY;
    ObjectID destBlock, side1Block, side2Block;

public:
    GhostStateID stateID();
    void enter(Ghost &g);
    GhostState *update(Ghost &g, Player &p, Map &m);
};