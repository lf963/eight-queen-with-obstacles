# Eight-queen-with-obstacles
This aim of this project is to solve a problem based on traditional [eight queens puzzle](https://en.wikipedia.org/wiki/Eight_queens_puzzle). In addition, there may be some obstacles on board so that two queens can share same row, column or diagonal line. We use [DFS](https://en.wikipedia.org/wiki/Depth-first_search), [BFS](https://en.wikipedia.org/wiki/Breadth-first_search) and [SA](https://en.wikipedia.org/wiki/Simulated_annealing) to solve this porblem.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites
You need C++11 compiler because this project is done in C++11.

## Running the tests
The file ```input.txt``` is our input file and its format is:
```
1. First line: instruction of which algorithm to use: BFS, DFS or SA

2. Second line: strictly positive 32-bit integer n, the width and height of the square board

3. Third line: strictly positive 32-bit integer p, the number of queens

4. Next n lines: the n x n board, one file line per board row (to show you where the obstacles are). It will have a 0 where there is nothing, and a 2 where there is an obstacle.
```

We have to output our result as ```output.txt``` whose format is:
```
1. First line: OK or FAIL, indicating whether a solution was found or not. If FAIL, any following lines are ignored.

2. Next n lines: the n x n board, one line in the file per board row, including the queens and obstacles. It will have a 0 where there is nothing, a 1 where you placed a queen, and a 2 where there is an obstacle.
```