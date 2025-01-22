#include "board.h"
#include <iostream>
namespace Input {
    char getCommand()
    {
        while (true) {
            char cmd{};
            std::cin >> cmd;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (cmd) {
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

int main()
{
    Board board{};
    board.randomize();
    std::cout << board;

    std::cout << "Use w,a,s,d to move piece and q to quit \n";
    while (true) {
        char cmd{ Input::getCommand() };

        if (cmd == 'q') {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        Direction dir{ getDirectionFromChar(cmd) };
        std::cout << "You entered direction: " << dir << '\n';
        board.moveTile(dir);
        std::cout << board;
    }
    return 0;
}