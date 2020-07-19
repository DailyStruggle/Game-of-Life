// Game of Life infinite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game of Life infinite.h"
#include <map>

void GameOfLife::Tick() {
    std::set<Coord_T> res;
    std::map<Coord_T, bool> scheduledCoords;
    for (Coord_T coord : this->data) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                Coord_T thisCoord{ thisCoord.x = coord.x+i, thisCoord.y = coord.y+j };
                scheduledCoords[thisCoord] = (this->data.find(thisCoord) != this->data.end());
            }
        }
    }

    for (std::map<Coord_T, bool>::iterator iter = scheduledCoords.begin(); iter != scheduledCoords.end(); iter++) {
        int numAdjacent = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                Coord_T thisCoord{ thisCoord.x = iter->first.x + i, thisCoord.y = iter->first.y + j };
                if (this->data.find(thisCoord) != this->data.end()) numAdjacent++;
            }
        }


        switch (numAdjacent) {
        case 3:
            res.insert(iter->first);
            break;
        case 4:
            if (this->data.find(iter->first) != this->data.end()) 
                res.insert(iter->first);
            break;
        }
    }
    this->data = res;
}

void GameOfLife::Tick(uint64_t numTicks) {
    for (int i = 0; i < numTicks; i++) {
        this->Tick();
    }
}

void GameOfLife::ReadFile(std::string fileName) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cout << "input file '" << fileName << "' does not exist. Creating it now.\n";
        std::ofstream inFileSet(fileName);
        if (inFileSet.is_open()) {
            for (int i = 0; i < 6; i++) {
                std::string line = "";
                for (int j = 0; j < 6; j++) {
                    line += "0";
                }
                line += "\n";
                inFileSet << line;
            }
        }
        inFileSet.close();
        inFile.open(fileName);
    }

    std::cout << "reading input file '" << fileName << "'\n";
    std::string str;
    uint64_t y_coord = 0;
    while (getline(inFile, str)) {
        uint64_t x_coord = 0;
        for (char c : str) {
            if (c == '1') {
                Coord_T thisCoord { thisCoord.x = x_coord, thisCoord.y = y_coord };
                this->data.insert(thisCoord);
            }
            x_coord++;
        }
        y_coord++;
    }
}

void GameOfLife::WriteFile(std::string fileName) {
    std::cout << "writing result to '" << fileName << "'\n";
    if (this->data.empty()) return;
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        int64_t x_min = INT64_MAX;
        int64_t y_min = INT64_MAX;
        int64_t x_max = INT64_MIN;
        int64_t y_max = INT64_MIN;
        x_min = (*(this->data.begin())).x;
        x_max = (*(this->data.rbegin())).x;
        
        for (Coord_T coord : this->data) {
            int64_t y = coord.y;
            if (y > y_max) 
                y_max = y;
            if (y < y_min) 
                y_min = y;
        }

        outFile << "output shifted by: " << x_min << ", " << y_min << "\n";

        for (int i = y_min; i <= y_max; i++) {
            std::string line = "";
            for (int j = x_min; j <= x_max; j++) {
                Coord_T thisCoord{ thisCoord.x = j, thisCoord.y = i };
                line += ( this->data.find(thisCoord)!=(this->data.end()) ) ? "1" : "0";
            }
            line += "\n";
            outFile << line;
        }
        outFile.close();
    }
    else {
        std::cout << "unable to open output file '" << fileName << "'\n";
    }
}

int main()
{
    std::string inFile = "input.txt";
    std::string outFile = "output.txt";
    int numTicks = 20;

    GameOfLife game;

    game.ReadFile(inFile);
    game.Tick(numTicks);
    game.WriteFile(outFile);
}