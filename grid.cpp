#include <algorithm>
#include "grid.h"

Grid::Grid(double threshold, int seed) {
    happinessThreshold = threshold;
    allHappy = false;
    rng.setseed(seed);
    nMoves = 0;
}

Grid::~Grid() {
}

void Grid::initiate(unsigned int gridSize){
    this->gridSize = gridSize;
    std::cout << "Creating a grid of size " << gridSize << "x" << gridSize << "\n";

    // 1. create the grid
    GridEl* lastEl;
    GridEl* el;
    GridEl* upperEl = nullptr;
    unsigned int row = 0, col = 0;

    // first iteration
    el = new GridEl(row, col, 0, nullptr, nullptr, nullptr, nullptr);
    head = el;
    lastEl = el;
    ++col;

    while (col < gridSize) {
        // iterate left to right and link vertically
        el = new GridEl(row, col, 0, nullptr, nullptr, nullptr, nullptr);
        el->W = lastEl;
        lastEl->E = el;
        lastEl = el;
        ++col;
    }
    upperEl = lastEl;
    ++row;
    
    // loop the body
    while(row < gridSize) {
        col = 0;
        if (row % 2 != 0) {
            el = new GridEl(row, gridSize - col - 1, 0, nullptr, nullptr, nullptr, nullptr);

            // even row (starts at 0...), iterate right to left
            el->E = nullptr; // right is nothing
            el->N = upperEl;
            upperEl->S = el;
            lastEl = el;
            upperEl = upperEl->W; // move to the left
            ++col;

            while (col < gridSize) {
                el = new GridEl(row, gridSize - col - 1, 0, nullptr, nullptr, nullptr, nullptr);
                el->E = lastEl;
                lastEl->W = el;
                el->N = upperEl;
                upperEl->S = el;
                upperEl = upperEl->W;
                lastEl = el;
                ++col;
            }
        } else {
            el = new GridEl(row, col, 0, nullptr, nullptr, nullptr, nullptr);

            // uneven rows (starts at 0...), iterate left to right
            el->W = nullptr; // left is nothing
            el->N = upperEl;
            upperEl->S = el;
            lastEl = el;
            upperEl = upperEl->E;
            col++;

            while (col < gridSize) {
                el = new GridEl(row, col, 0, nullptr, nullptr, nullptr, nullptr);
                el->W = lastEl;
                lastEl->E = el;
                el->N = upperEl;
                upperEl->S = el;
                upperEl = upperEl->E;
                lastEl = el;
                ++col;
            }
        }
        ++row;
        upperEl = el;
    }
}

void Grid::countElements(){
    unsigned int n = 0;
    GridEl* el = head;

    while (el != nullptr) {
        el = next(el);
        ++n;
    }
    std::cout << "Total number of elements: " << n << "\n";
}

Grid::GridEl* Grid::next(Grid::GridEl* reference) {
    unsigned int row = reference->row;
    GridEl* returnReference;

    // if the row is even, move left to right, else move right to left,
    // if the next is empty (end), move down)
    // if down is empty, return nullptr! (finish)
    if (row % 2 != 0) {
        // even row, right to left
        if (reference->W != nullptr) { // not left = empty!
            returnReference = reference->W;
        } else { // right = empty
            if (reference->S != nullptr) {
                returnReference = reference->S;
            } else {
                returnReference = nullptr;
            }
        }
    } else {
        // uneven row, left to right
        if (reference->E != nullptr) { // not right = empty!
            returnReference = reference->E;
        } else { // right = empty
            if (reference->S != nullptr) {
                returnReference = reference->S;
            } else {
                returnReference = nullptr;
            }
        }
    }
    return returnReference;
}

void Grid::populate(double percentEmpty, unsigned int nRaces) {
    // gridSize
    if (nRaces > 26) {
        std::cout << "Too many races, currently maximal 26 allowed! I cropped them to 26\n";
        nRaces = 26;
    }
    this->nRaces = nRaces;

    GridEl* reference = head;

    while (reference != nullptr) {
        double rnd = rng.runif(0.0, 1.0);
        if (rnd < percentEmpty) {
            // then empty
            reference->race = 0;
            emptyPlaces.push_back(reference);
        } else {
            unsigned int race = (unsigned int) rng.runif(1, (int) nRaces);
            reference->race = race;
        }
        reference = next(reference);
    }
    //std::reverse(emptyPlaces.begin(), emptyPlaces.end());
}
void Grid::drawPlot() {
    GridEl* firstEl = head;
    GridEl* reference = head;
    std::string num;

    while (firstEl != nullptr) {
        while (reference != nullptr) {
            num = raceChars[reference->race];
            std::cout << num << "|";
            reference = reference->E;
        }
        std::cout << "\n";
        firstEl = firstEl->S;
        reference = firstEl;
    }
}
void Grid::updateHappiness() {
    GridEl* reference = head;
    allHappy = true;

    while (reference != nullptr) {
        reference->happy = findRatio(reference) >= happinessThreshold;
        if (!reference->happy && reference->race != 0) {
            allHappy = false;
        }

        reference->movable = true;
        reference = next(reference);
    }
}
double Grid::findRatio(Grid::GridEl* reference){
    double totalNeighbors = 0;
    double sameNeighbors = 0;

    // North
    if (reference->N != nullptr) {
        if (reference->N->race != 0) {
            ++totalNeighbors;
            if (reference->N->race == reference->race) {
                ++sameNeighbors;
            }
        }
        // North East
        if (reference->N->E != nullptr) {
            if (reference->N->E->race != 0) {
                ++totalNeighbors;
                if (reference->N->E->race == reference->race) {
                    ++sameNeighbors;
                }
            }
        }
        // North West
        if (reference->N->W != nullptr) {
            if (reference->N->W->race != 0) {
                ++totalNeighbors;
                if (reference->N->W->race == reference->race) {
                    ++sameNeighbors;
                }
            }
        }
    }
    // West
    if (reference->W != nullptr) {
        if (reference->W->race != 0) {
            ++totalNeighbors;
            if (reference->W->race == reference->race) {
                ++sameNeighbors;
            }
        }
    }
    // East
    if (reference->E != nullptr) {
        if (reference->E->race != 0) {
            ++totalNeighbors;
            if (reference->E->race == reference->race) {
                ++sameNeighbors;
            }
        }
    }
    // South
    if (reference->S != nullptr) {
        if (reference->S->race != 0) {
            ++totalNeighbors;
            if (reference->S->race == reference->race) {
                ++sameNeighbors;
            }
        }
        // South East
        if (reference->S->E != nullptr) {
            if (reference->S->E->race != 0) {
                ++totalNeighbors;
                if (reference->S->E->race == reference->race) {
                    ++sameNeighbors;
                }
            }
        }
        // South West
        if (reference->S->W != nullptr) {
            if (reference->S->W->race != 0) {
                ++totalNeighbors;
                if (reference->S->W->race == reference->race) {
                    ++sameNeighbors;
                }
            }
        }
    }
    return sameNeighbors / totalNeighbors;
}
void Grid::move() {
    moves = 0;
    GridEl* reference = head;
    int rndHouse;
    int nEmpty = (int) emptyPlaces.size() - 1;

    if (nEmpty > 0) {
        while (reference != nullptr) {
            if (!reference->happy && reference->movable && reference->race != 0) {
                // move to random
                reference->movable = false;
                rndHouse = rng.runif(0, nEmpty);
                //std::cout << "r: " << rndHouse << "\n";
                emptyPlaces[rndHouse]->movable = false;
                emptyPlaces[rndHouse]->race = reference->race;
                reference->race = 0;
                emptyPlaces[rndHouse] = reference;
                //std::cout << "moving to house #" << rndHouse << " in the range of [0, " << (int) emptyPlaces.size() - 1 << "] !\n";
                ++moves;
            }
            reference = next(reference);
        }
    }
    nMoves += moves;
}

void Grid::simulate(unsigned int nMax, int plotAfter, int sleep) {
    unsigned int nSim = 0;
    while (!allHappy && nSim <= nMax) {

        if (nSim % plotAfter == 0) {
            std::cout << "\033[2J\033[1;1H"; // clear the screen
            std::cout << "---- Grid after " << nSim << " Iterations, with " << moves << " moves in this round and a total of " << nMoves << " moves. ---- \n";
        }
        updateHappiness();
        move();

        // clears the screen
        if (nSim % plotAfter == 0) {
            drawPlot();
            usleep(sleep);
        }
        ++n;
        ++nSim;

    }
    if (nSim > nMax) {
        std::cout << "Aborted after " << nSim - 1 << " rounds!\n";
    }

    std::cout << "\033[2J\033[1;1H";
    std::cout << "---- Grid after " << nSim << " Iterations, with " << moves << " moves in this round and a total of " << nMoves << " moves. ----\n";
    drawPlot();
}
