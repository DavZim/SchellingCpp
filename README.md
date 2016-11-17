#SchellingCpp

A C++ implementation of the Schelling agent-based model to model urban migration. Details about the model can be found for example here: http://nifty.stanford.edu/2014/mccown-schelling-model-segregation/

The program is written in an Ubuntu environment and should be launched using the terminal. 

## Usage:
To launch the program, you need to use `make` in the folder to compile the code (no outside dependencies are necessary) and then launch the code by typing `./schelling.out`. Possible arguments for the program are listed using `./schelling.out -h`, which include:

```
Usage Options:
  -h,--help           Show this help message
  -s,--seed           Set seed, defaults to current time
  -g,--gridSize       Specify the length of a simulation grid, defaults to 10 (i.e., 10x10)
  -p,--percEmpty      Specify the percentage of empty grids, defaults to 0.2
  -t,--threhhold      Specify the threshold above which agents are happy, defaults to 0.5
  -n,--nRaces         Specify the number of races [2,26], defaults to 3
  -m,--maxIter        Specify the maximum number of iterations, defaults to 10,000
  -pi,--plotInterval  Specify the intervals in which the plots should be updated, defaults to 100
  -d,--displayTime    Specify the display time for plots [in microseconds], defaults to 10,000
```

## Example:
`./schelling.out -g 60 -n 15 -d 1000 -s 101 -m 100000` results in a final grid of


