#include "player.h"
#include "block.h"

namespace Snake {

Player::Player(point init_position)
    : _tail{Block(Block::PLAYER, init_position)}
    , _head(&_tail.front())
    , _direction(RIGHT)
{
}
int Player::step()
{
    point offset;
    switch(_direction) {
    case UP:
        offset = point(0, -1);
    break;
    case DOWN:
        offset = point(0, 1);
    break;
    case LEFT:
        offset = point(-1, 0);
    break;
    case RIGHT:
        offset = point(1, 0);
    break;
    }
    point new_pos = _head->getPosition();
    new_pos += offset;
    for(const Block& el : _tail) {
        if(new_pos == el.getPosition()) {
            return -1; //crashed
        }
    }
    for(auto it = _tail.rbegin(); it != _tail.rend() - 1; ++it) {
        auto previous = it + 1;
        it->setPosition(previous->getPosition());
    }
    _head->move(offset);
    return 0;
}
void Player::setDirection(Direction dir)
{
    auto isOpposite =
            [](const Direction& direction, const Direction& dir)
            {
                return (direction == UP && dir == DOWN)
                    || (direction == DOWN && dir == UP)
                    || (direction == LEFT && dir == RIGHT)
                    || (direction == RIGHT && dir == LEFT);
            };

    if(!isOpposite(_direction, dir)){
        _direction = dir;
    }
}
void Player::render() const
{
    for(const Block& block : _tail)
    {
        block.render();
    }
}
void Player::increaseTail()
{
    _tail.push_back(Block(Block::PLAYER));
    _head = &_tail.front();
}

const Block& Player::head() const
{
    return *_head;
}
} // namespace Snake
