#ifndef GRID_H
#define GRID_H

#include <ostream>
#include <vector>
#include "RNG.h"
#include <iostream>
#include <unistd.h>

class Grid {
public:
    Grid(double threshold = 0.5, int seed = (int) time(0));
    ~Grid();
    struct GridEl {
        unsigned int row;
        unsigned int col;
        GridEl* N;
        GridEl* E;
        GridEl* S; 
        GridEl* W;
        unsigned int race;
        bool happy, movable;
        GridEl(unsigned int r, unsigned int c, unsigned int racevalue, GridEl* former, GridEl* next, GridEl* lower, GridEl* upper) :
            row(r), col(c), race(racevalue), W(former), S(lower), N(upper), E(next), happy(false), movable(true) {}
    };

    void initiate(unsigned int gridSize);
    void populate(double percentEmpty, unsigned int nRaces);
    void drawPlot();
    void simulate(unsigned int nMax, int plotAfter, int sleep = 10000);
    void updateHappiness();
    void move();
    void countElements();
    GridEl* next(GridEl* reference);

private:
    double happinessThreshold;
    unsigned int n, gridSize, nRaces;
    GridEl* head;
    bool allHappy;
    int moves;
    std::vector<GridEl*> emptyPlaces;
    RNG rng;// = RNG (12);
    double findRatio(GridEl* reference);
    std::vector<char> raceChars {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                                 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
};
#endif