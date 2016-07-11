#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include <vector>

#include "block.h"

namespace Snake {

class Player
{
public:

    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Player(point init_position = point(0, 0));
    int step();
    void setDirection(Direction dir);
    void render() const;
    void increaseTail();
    const Block& head() const;
private:
    std::vector<Block> _tail;
    Block* _head;
    Direction _direction;
};

} // namespace Snake

#endif // SNAKE_PLAYER_H
