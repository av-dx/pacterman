#pragma once

class GhostState;
class GhostHuntingState;
class GhostRetreatingState;

class Ghost : public Entity
{
private:
    Direction dir;
    int animFrame;
    char sprite[1][2];
    GhostState *state;

public:
    float speed;
    Ghost(Vector2D p);
    void update(Player &p, Map &m);
    int move(Map &m, Direction d);
    GhostStateID getState();
    void setState(GhostStateID);
    Direction getDir();
    void setDir(Direction d);
};