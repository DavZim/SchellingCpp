//
// Created by root on 16.11.16.
//

#include <iostream>
#include <random>
#include <vector>

#ifndef SCHELLING_RNG_H
#define SCHELLING_RNG_H

class RNG {
public:
    RNG(int seed = (int) time(0));
    ~RNG();
    void setseed(int newSeed);
    void printseed();
    int runif(int minNum, int maxNum);
    double runif(double minNum, double maxNum);
    std::vector<int> runif(int minNum, int maxNum, int n);
    std::vector<double> runif(double minNum, double maxNum, int n);

private:
    int seed;
    std::mt19937 gen;
    std::mt19937 re {};
    using distUnifInt = std::uniform_int_distribution<int>;
    using distUnifDbl = std::uniform_real_distribution<double>;

    distUnifInt dui {};
    distUnifDbl dud {};
};

#endif //SCHELLING_RNG_H