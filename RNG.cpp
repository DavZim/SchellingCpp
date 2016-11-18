//
// Created by root on 16.11.16.
//
#include "RNG.h"

RNG::RNG(int seed) {
    setseed(seed);
    printseed();
}
void RNG::setseed(int newSeed){
    seed = newSeed;
    re.seed(seed);
}
void RNG::printseed() {
    std::cout << "Current seed is: " << seed << "\n";
}
RNG::~RNG() {
}

//////
// Integer
//////
std::vector<int> RNG::runif(int minNum, int maxNum, int n) {
    std::vector<int> vec (n);

    for (int i = 0; i < n; ++i){
        vec[i] = dui(re, distUnifInt::param_type{minNum, maxNum});
    }
    return vec;
}
int RNG::runif(int minNum, int maxNum) {
    return dui(re, distUnifInt::param_type{minNum, maxNum});
}

//////
// Double
//////
std::vector<double> RNG::runif(double minNum, double maxNum, int n) {
    std::vector<double> vec (n);

    for (int i = 0; i < n; ++i){
        vec[i] = dud(re, distUnifDbl::param_type{minNum, maxNum});
    }
    return vec;
}
double RNG::runif(double minNum, double maxNum) {
    return dud(re, distUnifDbl::param_type{minNum, maxNum});
}

