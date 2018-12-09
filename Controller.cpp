#include <utility>
#include <map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Controller.h"
#include "Hypha.h"
#include "Spore.h"

void Controller::initBoard(int s) {
    size = s;
    blockBoard = (bool**) malloc(size * sizeof(bool*));
    fungusBoard = (bool**) malloc(size * sizeof(bool*));
    for (int i = 0; i < size; i++) {
        blockBoard[i] = (bool*) calloc(size, sizeof(bool));
        fungusBoard[i] = (bool*) calloc(size, sizeof(bool));
    }
    rs = time(NULL);
    srand(rs);
}

location_t Controller::searchForNutrients(location_t loc, int radius) {
    //std::cout << "searching for nutrients within " << radius << " of " << loc.x << "," << loc.y << std::endl;
    int nFound = 0;
    std::map<int, location_t> locs;
    for (int i = loc.x - radius; i <= loc.x + radius; i++) {
        if (i < 0 || i >= size) continue;
        for (int j = loc.y - radius; j <= loc.y + radius; j++) {
            if (j < 0 || j >= size) continue;
            if (!blockBoard[i][j]) {
                location_t l;
                l.x = i;
                l.y = j;
                locs[nFound] = l;
                nFound++;
                //std::cout << "nutrient found at " << l.x << "," << l.y << std::endl;
            }
        }
    }
    if (nFound <= 0) {
        location_t l;
        l.x = -1;
        l.y = -1;
        return l;
        //std::cout << "no nutrients found near " << loc.x << "," << loc.y << std::endl;
    }
    int i = rand() % nFound;
    //std::cout << "returning nutrient at " << locs[i].x << "," << locs[i].y << std::endl;
    return locs[i];
}

Hypha Controller::createHypha(location_t src, location_t dst, int radius) {
    //std::cout << "create hypha from " << src.x << "," << src.y << " to " << dst.x << "," << dst.y << std::endl;
    std::map<int, location_t> locs;
    int nLocs = 0;

    // mark locations between src & dst
    location_t cur = src;
    fungusBoard[cur.x][cur.y] = true;
    blockBoard[cur.x][cur.y] = true;
    locs[nLocs] = cur;
    nLocs++;
    while (cur != dst) {
        int xDif = dst.x - cur.x;
        int yDif = dst.y - cur.y;
        int xMov = 0, yMov = 0;
        if ((int)abs(xDif) == (int)abs(yDif)) {
            xMov = xDif / abs(xDif);
            yMov = yDif / abs(yDif);
        } else if ((int)abs(xDif) > (int)abs(yDif)) {
            xMov = xDif / abs(xDif);
            yMov = 0;
        } else {
            xMov = 0;
            yMov = yDif / abs(yDif);
        }
        cur.x = cur.x + xMov;
        cur.y = cur.y + yMov;
        fungusBoard[cur.x][cur.y] = true;
        blockBoard[cur.x][cur.y] = true;
        locs[nLocs] = cur;
        //std::cout << "dst: " << dst.x << "," << dst.y << std::endl;
        //std::cout << "cur: " << cur.x << "," << cur.y << std::endl;
        nLocs++;
    }

    // mark locations within radius of all locs marked in previous step
    for (int n = 0; n < nLocs; n++) {
        for (int i = locs[n].x - radius; i <= locs[n].x + radius; i++) {
            if (i < 0 || i >= size) continue;
            for (int j = locs[n].y - radius; j <= locs[n].y + radius; j++) {
                if (j < 0 || j >= size) continue;
                blockBoard[i][j] = true;
            }
        }
    }

    // actually create the hypha lol
    Hypha h(src, dst);
    //std::cout << "created hypha from " << src.x << "," << src.y << " to " << dst.x << "," << dst.y << std::endl;
    return h;
}

Spore Controller::createRandSeed(location_t src, int radius) {
    //std::cout << "creating random seed near " << src.x << "," << src.y << std::endl;
    int xOff = rand() % (2 * radius + 1) - radius;
    int yOff = rand() % (2 * radius + 1) - radius;
    int nx = src.x + xOff;
    if (nx < 0) nx = 0;
    if (nx >= size) nx = size - 1;
    int ny = src.y + yOff;
    if (ny < 0) ny = 0;
    if (ny >= size) ny = size - 1;
    Spore s(nx, ny);
    //std::cout << "created rand seed at " << nx << "," << ny << std::endl;
    return s;
}

bool** Controller::getBoard() {
    return fungusBoard;
}

void Controller::closeBoard() {
    //std::cout << "closing board...." << std::endl;
    for (int i = 0; i < size; i++) {
        free(blockBoard[i]);
        free(fungusBoard[i]);
    }
    free(blockBoard);
    free(fungusBoard);
}

void Controller::printBoard() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fungusBoard[i][j]) {
                std::cout << "x";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Controller::printBlocks() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (blockBoard[i][j]) {
                std::cout << "x";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

std::string Controller::printToFile(int initS, int searchR, int blockR) {
    // build file name
    std::stringstream filename;
    filename << "Output/";
    filename << size << "_" << initS << "_" << searchR << "_" << blockR << "_";
    filename << rs << ".pbm";
    std::cout << filename.str() << std::endl;

    // build file
    std::ofstream file(filename.str());
    if (file.is_open()) {
        file << "P1\n";
        file << size << " " << size << "\n";
        int linespace = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (fungusBoard[i][j]) {
                    file << 1 << " ";
                } else {
                    file << 0 << " ";
                }
                linespace += 2;
                if (linespace > 60) {
                    file << "\n";
                    linespace = 0;
                }
            }
        }
    } else {
        std::cout << "Unable to write to file." << std::endl;
        return "";
    }
    file.close();
    return filename.str();
}
