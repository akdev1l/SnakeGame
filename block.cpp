#include "block.h"

#include <iostream>
#include <ncurses.h>

namespace Snake {

Block::Block(const TYPE& block_type, point position)
    :
      position_(position),
      symbol_(block_type),
      type_(block_type)
{

}

void Block::render() const
{
    mvaddch(position_.second, position_.first, symbol_);
}

Block::TYPE Block::getType() const
{
    return type_;
}

void Block::changeType(Block::TYPE new_type)
{
    symbol_ = new_type;
    type_ = new_type;
}

Block::~Block()
{

}

void Block::move(point offset)
{
    position_ += offset;
}

point Block::getPosition() const
{
    return position_;
}

void Block::setPosition(const point& new_pos)
{
    position_ = new_pos;
}

point& operator+=(point& lhs, const point& rhs)
{
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}
const point operator-(point&& lhs, const point& rhs)
{
    point result;
    result.first = lhs.first - rhs.first;
    result.second = lhs.second - rhs.second;
    return result;
}
} // namespace Snake
