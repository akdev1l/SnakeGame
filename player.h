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
        UP = -1,
        DOWN = 1,
        LEFT = -2,
        RIGHT = 2
    };

    Player(point init_position = point(0, 0));
    int step();
    void setDirection(Direction dir);
    void render() const;
    void increaseTail();
    const Block& head() const;
private:
    std::vector<Block> tail_;
    Block* head_;
    Direction direction_;
};

} // namespace Snake

#endif // SNAKE_PLAYER_H
