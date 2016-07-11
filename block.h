#ifndef SNAKE_BLOCK_H
#define SNAKE_BLOCK_H

#include <utility>

namespace Snake {

typedef std::pair<unsigned int, unsigned int> point;

class Block
{
public:
    enum TYPE : char {
        SOLID = '#',
        EATABLE = '&',
        EMPTY = ' ',
        PLAYER = '@'
    };

    Block(const TYPE& block_type, point position = point(0, 0));
    virtual ~Block();
    void render() const;
    TYPE getType() const;
    void changeType(TYPE new_type);
    void move(point offset);
    point getPosition() const;
    void setPosition(const point& new_pos);

private:
    point position_;
    char symbol_;
    TYPE type_;
};

point& operator+=(point& lhs, const point& rhs);
const point operator-(point&& lhs, const point& rhs);

} // namespace Snake

#endif // SNAKE_BLOCK_H
