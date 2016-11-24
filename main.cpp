#include "grid.h"
#include "main.h"

int main(int argc, char const *argv[]) {
    Inputs inputs = handleInputs(argc, argv);

    Grid grid = Grid(inputs.threshold, inputs.seed);
    grid.initiate(inputs.gridSize);
    grid.populate(inputs.percEmpty, inputs.nRaces);
    grid.simulate(inputs.maxIter, inputs.plotInterval, inputs.sleep);

    return 0;
}
