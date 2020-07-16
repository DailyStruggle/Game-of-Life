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
    west = 3
};


struct Node {
    int x;
    int y;
    bool val = false;
    bool val2 = false;
    Node* dir[4];
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
}

void Tick(std::vector<std::vector<Node>>& List, bool swapState) {
    int r = List.size();
    int c = List[0].size();

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            Node* node = &List[i][j];
            int vals = 0;
            if (swapState) {
                vals += (*(node->dir[north])).val2;
                vals += (*(node->dir[east])).val2;
                vals += (*(node->dir[south])).val2;
                vals += (*(node->dir[west])).val2;
                vals += (*(node->dir[north]->dir[east])).val2;
                vals += (*(node->dir[north]->dir[west])).val2;
                vals += (*(node->dir[south]->dir[east])).val2;
                vals += (*(node->dir[south]->dir[west])).val2;

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
                vals += (*(node->dir[north])).val;
                vals += (*(node->dir[east])).val;
                vals += (*(node->dir[south])).val;
                vals += (*(node->dir[west])).val;
                vals += (*(node->dir[north]->dir[east])).val;
                vals += (*(node->dir[north]->dir[west])).val;
                vals += (*(node->dir[south]->dir[east])).val;
                vals += (*(node->dir[south]->dir[west])).val;

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
                inFileSet << "000000\n";
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

        /*
        for (int i = 0; i < r; i++) {
            std::cout << "\n";
            for (int j = 0; j < c; j++) {
                if(swapState) std::cout << List[i][j].val2;
                else          std::cout << List[i][j].val;
            }
        }
        std::cout << "\n\n";
        */
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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
