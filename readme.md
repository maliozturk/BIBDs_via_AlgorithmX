## Efficient algorithm for finding block designs for given parameters (v, k)
My purpose of writing this code was generating Balanced Incomplete Block Designs (BIBD)s for given parameters (v, k, λ) using Donald Knuth's Algorithm X.
Current version of code is only working for λ == 1 and shall be improved to generate designs for λ>1 aswell. Still, making this code work on c++ was an accomplishment for me.

## Usage:
Assuming that you have a g++ compiler ready (with paths) on your operating system.
+ Open terminal/cmd
+ Cd in to the src file.
+ After changing parameters v,k in main(), you can just simply g++ main.cpp Combinations.cpp IncidenceMatrix.cpp -std=c++17
+ To see results, simply type ./a.out

##
<h5>Number of BIBDs found for certain (v,k,1) by this algorithm:</h5>
1. (7,3,1): 30
2. (8,3,1): 0, because there isn't any (8,3,1)-BIBD.
3. (13,4,1): 1.108.000
4. (15,3,1): more than 3.6GB size txt file (100.000.000+)

##
<h5>Resources:</h6>
<a href='https://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/0011047.pdf'>Donald Knuth's Algorithm X</a>