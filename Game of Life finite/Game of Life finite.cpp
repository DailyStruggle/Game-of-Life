// Game of Life finite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum eDirs {
    north = 0,
    east = 1,
    south = 2,
    west = 3,
    northeast = 4,
    northwest = 5,
    southeast = 6,
    southwest = 7,
};

struct Node {
    int x;
    int y;
    bool val = false;
    bool val2 = false;
    Node* dir[8];
};


void initList(std::vector<std::vector<Node>>& List) {
    int r = List.size();
    int c = List[0].size();
    
    List[0][0].dir[north] = nullptr;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            List[i][j].x = j;
            List[i][j].y = i;
            if (i == 0) {
                List[i][j].dir[north] = &List[r-1][j];
            }
            else {
                List[i][j].dir[north] = &List[i - 1][j];
            }
            if (j == 0) {
                List[i][j].dir[west] = &List[i][c-1];
            }
            else {
                List[i][j].dir[west] = &List[i][j - 1];
            }
            if (i == r-1) {
                List[i][j].dir[south] = &List[0][j];
            }
            else {
                List[i][j].dir[south] = &List[i + 1][j];
            }
            if (j == c-1) {
                List[i][j].dir[east] = &List[i][0];
            }
            else {
                List[i][j].dir[east] = &List[i][j + 1];
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            List[i][j].dir[northeast] = List[i][j].dir[north]->dir[east];
            List[i][j].dir[northwest] = List[i][j].dir[north]->dir[west];
            List[i][j].dir[southeast] = List[i][j].dir[south]->dir[east];
            List[i][j].dir[southwest] = List[i][j].dir[south]->dir[west];
        }
    }
}

void Tick(std::vector<std::vector<Node>>& List, bool swapState) {
    int r = List.size();
    int c = List[0].size();

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            Node* node = &List[i][j];
            int vals = 0;
            if (swapState) {
                for (int i = 0; i < 8; i++) {
                    vals += node->dir[i]->val2;
                }

                switch (vals) {
                    case 2:
                        node->val = node->val2;
                        break;
                    case 3:
                        node->val = true;
                        break;
                    default:
                        node->val = false;
                        break;
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    vals += node->dir[i]->val;
                }

                switch (vals) {
                    case 2:
                        node->val2 = node->val;
                        break;
                    case 3:
                        node->val2 = true;
                        break;
                    default:
                        node->val2 = false;
                        break;
                }
            }
        }
    }
}

int main()
{
    int r = 5;
    int c = 6;
    
    std::ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        std::ofstream inFileSet("input.txt");
        if (inFileSet.is_open()) {
            for (int i = 0; i < 5; i++) {
                std::string line = "";
                for (int j = 0; j < c; j++) {
                    line += "0";
                }
                line += "\n";
                inFileSet << line;
            }
        }
        inFileSet.close();
        inFile.open("input.txt");
    }
    
    std::vector<std::vector<Node>> List;
    List.resize(r);
    for (int i = 0; i < r; i++) {
        List[i].resize(c);
    }
    initList(List);
    
    for (int i = 0; i < r; i++) {
        std::string line;
        std::getline(inFile, line);
        for (int j = 0; j < c; j++) {
            List[i][j].val = (line[j] == '1');
            List[i][j].val2 = List[i][j].val;
        }
    }
    
    
    int ticks = 20;

    bool swapState = false;

    for (int i = 0; i < ticks; i++) {
        Tick(List, swapState);
        swapState = !swapState;
    }

    if (swapState) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                List[i][j].val = List[i][j].val2;
            }
        }
    }
    
    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < r; i++) {
            std::string outLine;

            for (int j = 0; j < c; j++) {
                outLine += List[i][j].val ? "1" : "0";

            }

            outLine += "\n";

            outFile << outLine;
        }
        outFile.close();
    }
}