#pragma once

class GhostState;
class GhostHuntingState;
class GhostRetreatingState;

class Ghost : public Entity
{
private:
    Direction dir;
    float speed;
    int animFrame;
    char sprite[1][2];
    GhostState *state;

public:
    Ghost(Vector2D p);
    void update(Player &p, Map &m);
    void setDir(Direction d);
    GhostStateID getState();
    void setState(GhostStateID);
    Direction getDir();
};