#include "grid.h"

static void show_usage()
{
    std::cerr << "Usage Options:\n"
              << "  -h,--help\t\tShow this help message\n"
              << "  -s,--seed\t\tSet seed, defaults to current time\n"
              << "  -g,--gridSize\t\tSpecify the length of a simulation grid, defaults to 10 (i.e., 10x10)\n"
              << "  -p,--percEmpty\tSpecify the percentage of empty grids, defaults to 0.2\n"
              << "  -t,--threhhold\tSpecify the threshold above which agents are happy, defaults to 0.5\n"
              << "  -n,--nRaces\t\tSpecify the number of races [2,26], defaults to 3\n"
              << "  -m,--maxIter\t\tSpecify the maximum number of iterations, defaults to 10,000\n"
              << "  -pi,--plotInterval\tSpecify the intervals in which the plots should be updated, defaults to 100\n"
              << "  -d,--displayTime\tSpecify the display time for plots [in microseconds], defaults to 10,000\n";
}
struct Inputs {
    unsigned int gridSize;
    double percEmpty;
    unsigned int nRaces;
    unsigned int maxIter;
    unsigned int plotInterval;
    unsigned int sleep;
    unsigned int seed;
    double threshold;
};
Inputs handleInputs(int argc, char const *argv[]) {
    Inputs inputs;
    int tmp;
    double tmpDbl;

    // default values
    inputs.gridSize = 10;
    inputs.percEmpty = 0.2;
    inputs.threshold = 0.5;
    inputs.nRaces  = 3;
    inputs.maxIter = 10000;
    inputs.plotInterval = 100;
    inputs.sleep = 10000;
    inputs.seed = (unsigned int) time(0);

    // check the inputs and update "inputs"
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage();
            std::exit(1);
        } else if ((arg == "-g") || (arg == "--gridSize")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmp = std::stoi(argv[++i]);
                if (tmp < 0) {
                    tmp = -tmp;
                    std::cout << "gridSize is smaller than 0, taking the absolute value of: " << tmp << "\n";
                }
                inputs.gridSize = (unsigned int) tmp;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--gridSize option requires one argument.\n";
                std::exit(1);
            }
        } else if ((arg == "-p") || (arg == "--percEmpty")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmpDbl = std::stod(argv[++i]);
                if (tmpDbl < 0) {
                    tmpDbl = -tmpDbl;
                    std::cout << "percEmpty is smaller than 0, taking the absolute value of: " << tmpDbl << "\n";
                }
                inputs.percEmpty = tmpDbl;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--percEmpty option requires one argument.\n";
                std::exit(1);
            }
        } else if ((arg == "-t") || (arg == "--threshold")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmpDbl = std::stod(argv[++i]);
                if (tmpDbl < 0) {
                    tmpDbl = -tmpDbl;
                    std::cout << "threshold is smaller than 0, taking the absolute value of: " << tmpDbl << "\n";
                }
                inputs.threshold = tmpDbl;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--threshold option requires one argument.\n";
                std::exit(1);
            }
        } else if ((arg == "-n") || (arg == "--nRaces")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmp = std::stoi(argv[++i]);
                if (tmp < 0) {
                    tmp = -tmp;
                    std::cout << "nRaces is smaller than 0, taking the absolute value of: " << tmp << "\n";
                }
                inputs.nRaces = (unsigned int) tmp;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--nRaces option requires one argument.\n";
                std::exit(1);
            }
        } else if ((arg == "-m") || (arg == "--maxIter")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmp = std::stoi(argv[++i]);
                if (tmp < 0) {
                    tmp = -tmp;
                    std::cout << "maxIter is smaller than 0, taking the absolute value of: " << tmp << "\n";
                }
                inputs.maxIter = (unsigned int) tmp;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--maxIter option requires one argument.\n";
                std::exit(1);
            }
        } else if ((arg == "-pi") || (arg == "--plotInterval")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmp = std::stoi(argv[++i]);
                if (tmp < 0) {
                    tmp = -tmp;
                    std::cout << "plotInterval is smaller than 0, taking the absolute value of: " << tmp << "\n";
                }
                inputs.plotInterval = (unsigned int) tmp;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--plotInterval option requires one argument.\n";
                std::exit(1);
            }
        } else if ((arg == "-d") || (arg == "--displayTime")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmp = std::stoi(argv[++i]);
                if (tmp < 0) {
                    tmp = -tmp;
                    std::cout << "display is smaller than 0, taking the absolute value of: " << tmp << "\n";
                }
                inputs.sleep = (unsigned int) tmp;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--displayTime option requires one argument.\n";
                std::exit(1);
            }
        } else if ((arg == "-s") || (arg == "--seed")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                tmp = std::stoi(argv[++i]);
                if (tmp < 0) {
                    tmp = -tmp;
                    std::cout << "seed is smaller than 0, taking the absolute value of: " << tmp << "\n";
                }
                inputs.seed = (unsigned int) tmp;
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--seed option requires one argument.\n";
                std::exit(1);
            }
        } else {
            std::cout << "Unknown option \"" << arg << "\", known options include:\n";
            show_usage();
            std::exit(1);
        }
    }
    return inputs;
}


int main(int argc, char const *argv[]) {

    Inputs inputs = handleInputs(argc, argv);

    Grid grid = Grid(inputs.threshold, inputs.seed);
    grid.initiate(inputs.gridSize);
    grid.populate(inputs.percEmpty, inputs.nRaces);
    grid.simulate(inputs.maxIter, inputs.plotInterval, inputs.sleep);

    return 0;
}
