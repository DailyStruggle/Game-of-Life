// Game of Life infinite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <set>

class GameOfLife {
	public:
        struct Coord_T {
            int64_t x, y;
            inline bool operator==(const Coord_T& o) const { return x == o.x && y == o.y; }
            inline bool operator<(const Coord_T& o) const { return x < o.x || (x == o.x && y < o.y); }
            inline bool operator>(const Coord_T& o) const { return x > o.x || (x == o.x && y > o.y); }
            inline bool operator!=(const Coord_T& o) const { return x != o.x || y != o.y; }
            inline bool operator<=(const Coord_T& o) const { return x < o.x || (x == o.x && y <= o.y); }
            inline bool operator>=(const Coord_T& o) const { return x > o.x || (x == o.x && y >= o.y); }
        };

        std::set<Coord_T> data;

        void Tick();
        void Tick(uint64_t numTicks);
        
        void ReadFile(std::string fileName);
        void WriteFile(std::string fileName);
};