#include <iostream>
#include <ctime>
#include <string>

#include "Pool.h"
#include "Player.h"
#include "../common/Board.h"
#include "Command.h"
#include "../common/Console_Setup.h"
#include "Move.h"

int main()
{
#ifdef _WIN32
    SetupConsole();
#endif
    srand((unsigned int) time(NULL)); //letter randomize

    //english alphabet 
    std::string englishAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<char> alphabet(englishAlphabet.begin(), englishAlphabet.end());

    Pool my_pool(alphabet);
    Board my_board("test.txt");
    Player player1(my_pool, "Alfredo");

    for (;;) {
        my_board.show();
        std::cout << "\n";
        player1.showHand();
        player1.showScore();
        std::string input;
        std::cout << "\nMove: ";
        std::getline(std::cin, input);
        Command command(input);
        if (!command.isMove()) {
            player1.exchange(1, my_pool);
            std::cout << "exchanging from pool...\n";
        }
        else {
            Move move(command, my_board);
            if (!move.hasProblems(player1)) move.execute(player1, my_board, my_pool);
            else std::cout << "move has problems.\n";
        }
        std::cout << "press enter.\n";
        std::cin.ignore(10000,'\n');
        //refresh pool to debug
        for (int i = 0; i < 7;++i) {
            player1.exchange(i, my_pool);
        }
        clearConsole();
    }
}