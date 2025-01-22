#include <array>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <ios>
#include <limits>
#include <ostream>
#include <iostream>
#include <random>

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Tile
{
public:
    // Constructs a tile with a value in range [0,15]
    Tile(int value)
        : m_value{value}
    {
        assert(value >= 0 && value < 16);
    }

    Tile()
        : m_value{0}
    {
    }

    int getNum() const 
    {
        return m_value;
    }
    
    // const indicates that this member function won't modify any of the class's member variables 
    bool isEmpty() const 
    {
        return m_value == 0;
    }

    friend std::ostream& operator<< (std::ostream& out, const Tile& tile);
    
    private:
        int m_value;

};

std::ostream& operator << (std::ostream& out, const Tile& tile)
{
    if (tile.isEmpty()){
        out << "    ";
        return out;
    }
    if (tile.m_value < 10){
        out << "  " << tile.m_value << " ";
    } else {
        out << " " << tile.m_value << " ";
    }

    return out;
}


class Board
{
    using BoardArray = std::array<std::array<Tile, 4>, 4>;
    public:
        Board()
            : m_board {{
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 0}
            }}
        {
        }
    const Tile& operator()(int row, int col) const
    {
        assert(row >= 0 && row < 4 && col >= 0 && col < 4);
        return m_board[row][col];
    }

    friend std::ostream& operator<< (std::ostream& out, const Board& tile);

    private:
        BoardArray m_board {};
};

std::ostream& operator<< (std::ostream& out, const Board& board){
    for (int i {0}; i < g_consoleLines; i++)
        out << '\n';

    for (size_t row {0}; row < 4; row++){
        for (size_t col {0}; col < 4; col ++) {
            out << board(row, col);
        }
        out << '\n';
    }
    return out;
}

namespace  Input 
{
    char getCommand(){
        while (true){
            char cmd {};
            std::cin >> cmd;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (cmd) 
            {
                case 'w':
                case 'a':
                case 's':
                case 'd':
                case 'q':
                    return cmd;
            }
        }
    }
}

class Direction 
{
   public: 
        enum Type
        {
            up,
            down,
            left, 
            right
        };

        Direction(char cmd)
        {
            switch (cmd) {
                case 'w':
                    m_x = 0;
                    m_y = -1;
                    m_type = Type::up;
                    break;
                case 's':
                    m_x = 0; 
                    m_y = 1;
                    m_type = Type::down;
                    break;
                case 'a':
                    m_x = -1;
                    m_y = 0;
                    m_type = Type::left;
                    break;
                case 'd':
                    m_x = 1;
                    m_y = 0;
                    m_type = Type::right;
                    break;
            }
        }

        Direction(int x, int y)
                : m_x {x}, m_y {y}
        {}

        Direction operator-() const
        {
            return Direction(-m_x, -m_y); 
        }

        constexpr std::string_view getDirectionName(const Direction::Type direction) const;
        friend std::ostream& operator<< (std::ostream& out, Direction direction);

        static Direction generateRandomDirection()
        {
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0,3);
            int rand = dist(rd);

            switch (rand) {
                case 0:
                    return Direction('w');
                case 1:
                    return Direction('s');
                case 2:
                    return Direction('a');
                case 3:
                    return Direction('d');
                default:
                    return Direction('w');
            }
        }

        private:
            int m_x {};
            int m_y {};
            Type m_type;

};

constexpr std::string_view getDirectionName(const Direction::Type direction)
{
    switch (direction) 
    {
        case Direction::Type::up: return "up";
        case Direction::Type::down: return "down";
        case Direction::Type::left: return "left";
        case Direction::Type::right: return "right";
    }
}

std::ostream& operator<< (std::ostream& out, Direction direction){
    out << getDirectionName(direction.m_type);
    return out;
}


int main()
{   
    Board board{};
    std::cout << board;
    
    for (int i {0}; i < 4; i++){
        std::cout << "Generating random direction... " << Direction::generateRandomDirection() << '\n';
    }

    std::cout << "Use w,a,s,d to move piece and q to quit \n";
    while (true){
        char cmd {Input::getCommand()};
        Direction dir {cmd};

        std::cout << "You entered direction: " << dir << '\n';

        if (cmd == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }
    }
    return 0;
}