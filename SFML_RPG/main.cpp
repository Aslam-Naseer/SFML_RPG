#include "stdafx.h"
#include "Game.h"

int main()
{
    std::cout << "Program starting..." << std::endl;

    try {

        Game game;
        game.run();

        std::cout << "Game loop finished normally" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 3;
    }
}