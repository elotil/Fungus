#include <iostream>
#include <queue>
#include "Controller.h"
#include "Hypha.h"
#include "Spore.h"

//#define BOARD_SIZE 100
//#define INIT_AS 100
//#define SEARCH_RADIUS 2
//#define BLOCK_RADIUS 1
//#define SEED_RADIUS 2

int main() {
    Controller control;
    std::queue<Spore> seedQ;
    std::queue<Hypha> myceliumQ;

    int BOARD_SIZE, INIT_AS, SEARCH_RADIUS, BLOCK_RADIUS, SEED_RADIUS;
    std::cout << "Board size: ";
    std::cin >> BOARD_SIZE;
    std::cout << "Initial spores: ";
    std::cin >> INIT_AS;
    std::cout << "Search radius: ";
    std::cin >> SEARCH_RADIUS;
    std::cout << "Block radius: ";
    std::cin >> BLOCK_RADIUS;
    std::cout << "Seed radius: ";
    std::cin >> SEED_RADIUS;

    control.initBoard(BOARD_SIZE);
    for (int i = 0; i < INIT_AS; i++) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        Spore s(x, y);
        seedQ.push(s);
    }


    while (!seedQ.empty()) {
        Spore s = seedQ.front();
        seedQ.pop();
        location_t l = control.searchForNutrients(s.getLocation(), SEARCH_RADIUS);
        if (l.x >= 0) {
            s.germinate();
            Hypha h = control.createHypha(s.getLocation(), l, BLOCK_RADIUS);
            myceliumQ.push(h);
            seedQ.push(s);
        }
        while (!myceliumQ.empty()) {
            Hypha h = myceliumQ.front();
            myceliumQ.pop();
            location_t l = control.searchForNutrients(h.getLocation(), SEARCH_RADIUS);
            if (l.x >= 0) {
                Hypha h2 = control.createHypha(h.getLocation(), l, BLOCK_RADIUS);
                myceliumQ.push(h2);
            } else {
                Spore s2 = control.createRandSeed(h.getLocation(), SEED_RADIUS);
                seedQ.push(s2);
            }
        }
    }

    std::string str;
    std::cout << "Finished." << std::endl;
    std::cout << "Print fungus maze? [Y/N]: ";
    std::cin >> str;
    if (str[0] == 'Y' || str[0] == 'y') {
        control.printBoard();
    }
    std::cout << "Print blocks? [Y/N]: ";
    std::cin >> str;
    if (str[0] == 'Y' || str[0] == 'y') {
        control.printBlocks();
    }
    std::cout << "Save maze to file? [Y/N]: ";
    std::cin >> str;
    if (str[0] == 'Y' || str[0] == 'y') {
        str = control.printToFile(INIT_AS, SEARCH_RADIUS, BLOCK_RADIUS);
        if (str != "")
            std::cout << "Maze has been saved to " << str << std::endl;
    }
    control.closeBoard();

    return 0;
}
