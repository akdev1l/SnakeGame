#include "block.h"

#include <iostream>
#include <ncurses.h>

namespace Snake {

Block::Block(const TYPE& block_type, point position)
    :
      _position(position),
      _symbol(block_type),
      _type(block_type)
{

}

void Block::render() const
{
    mvaddch(_position.second, _position.first, _symbol);
}

Block::TYPE Block::getType() const
{
    return _type;
}

void Block::changeType(Block::TYPE new_type)
{
    _symbol = new_type;
    _type = new_type;
}

Block::~Block()
{

}

void Block::move(point offset)
{
    _position += offset;
}

point Block::getPosition() const
{
    return _position;
}

void Block::setPosition(const point& new_pos)
{
    _position = new_pos;
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
