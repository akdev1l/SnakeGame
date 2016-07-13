#include "player.h"
#include "block.h"

namespace Snake {

Player::Player(point init_position)
    : tail_{Block(Block::PLAYER, init_position)}
    , head_(&tail_.front())
    , direction_(RIGHT)
{
}
int Player::step()
{
    point offset;
    switch(direction_) {
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
    point new_pos = head_->getPosition();
    new_pos += offset;
    for(const Block& el : tail_) {
        if(new_pos == el.getPosition()) {
            return -1; //player crashed against its tail
        }
    }
    /* This moves the tail to follow the head */
    for(auto it = tail_.rbegin(); it != tail_.rend() - 1; ++it) {
        auto previous = it + 1;
        it->setPosition(previous->getPosition());
    }
    head_->move(offset);
    return 0;
}
void Player::setDirection(Direction dir)
{
    auto isOpposite =
            [](const Direction& direction, const Direction& dir)
            {
                return direction + dir == 0;
            };

    if(!isOpposite(direction_, dir)){
        direction_ = dir;
    }
}
void Player::render() const
{
    for(const Block& block : tail_)
    {
        block.render();
    }
}
void Player::increaseTail()
{
    tail_.push_back(Block(Block::PLAYER, head_->getPosition()));
    head_ = &tail_.front();
}

const Block& Player::head() const
{
    return *head_;
}
} // namespace Snake
