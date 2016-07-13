#include <ncurses.h>
#include <vector>
#include <random>

#include "player.h"

using namespace std;

namespace Snake
{
    typedef vector<vector<Snake::Block>> Board;
}

void init_curses();
void init_board(Snake::Board& board, const int &cols, const int &rows);
void render_board(const Snake::Board& board);
void addEatable(Snake::Board& board, Snake::point& eatablePoint);

int main(int argc, char *argv[])
{
    init_curses();

    char input;
    Snake::Board board;
    bool playerLost = false;
    int cols, rows;
    unsigned int score = 0;
    getmaxyx(stdscr, rows, cols);
    Snake::Player me(Snake::point(cols/2, rows/2));
    Snake::point eatable(-1, -1);

    init_board(board, cols, rows);
    do {
        clear();
        render_board(board);
        me.render();
        refresh();
        input = getch();
        switch(input) {
        case 'a':
            me.setDirection(Snake::Player::LEFT);
        break;
        case 'd':
            me.setDirection(Snake::Player::RIGHT);
        break;
        case 'w':
            me.setDirection(Snake::Player::UP);
        break;
        case 's':
            me.setDirection(Snake::Player::DOWN);
        break;
        case 'c':
            me.increaseTail();
        break;
        }
        if(me.step() != 0) {
            playerLost = true;
        }
        const Snake::point& player_pos = me.head().getPosition();
        Snake::Block& current_block = board[player_pos.second][player_pos.first];
        switch(current_block.getType()) {
        case Snake::Block::SOLID:
            playerLost = true;
        break;
        case Snake::Block::EATABLE:
            current_block.changeType(Snake::Block::EMPTY);
            me.increaseTail();
            eatable = Snake::point(-1, -1);
            ++score;
        break;
        default:
        break;
        }
        addEatable(board, eatable);

    } while(input != 'q' && !playerLost);

    endwin();
    printf("Game Over, your score was: %d\n", score);

    return 0;
}

void init_curses()
{
    initscr();                  /* Start curses mode 		*/
    raw();                      /* Line buffering disabled	*/
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    noecho();
    timeout(400/6);
    curs_set(0);
}

void init_board(Snake::Board& board, const int& cols, const int& rows)
{
    board.reserve(rows);
    for(int i = 0; i < rows; ++i) {
        board.push_back(vector<Snake::Block>());
    }
    for(int i = 0; i < cols; ++i) {
        board[0].push_back(Snake::Block(Snake::Block::SOLID, Snake::point(i, 0)));
        board[rows - 1].push_back(Snake::Block(Snake::Block::SOLID, Snake::point(i, rows-1)));
    }
    for(int row = 1; row < rows-1; ++row) {
        for(int col = 0; col < cols; ++col) {
            Snake::Block::TYPE block_type;
            if(col == 0 || col == cols -1) {
                block_type = Snake::Block::SOLID;
            }
            else {
                block_type = Snake::Block::EMPTY;
            }
            board[row].push_back(Snake::Block(block_type, Snake::point(col, row)));
        }
    }
}

void render_board(const Snake::Board& board)
{
    for(const auto& row : board)
    {
        for(const auto& block : row)
        {
            block.render();
        }
    }
}
bool isValid(const Snake::point& p)
{
    return p.first >= 0 && p.second >=0;
}

void addEatable(Snake::Board& board, Snake::point& eatablePoint)
{
    std::random_device rand_device;
    std::mt19937 gen(rand_device());
    std::uniform_int_distribution<> row(1, board.size()-2);
    std::uniform_int_distribution<> col(1, board[0].size()-2);

    if(!isValid(eatablePoint)){
        eatablePoint.first = col(gen);
        eatablePoint.second = row(gen);
        board[eatablePoint.second][eatablePoint.first].changeType(Snake::Block::EATABLE);
    }
}
