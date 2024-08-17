Author: Filippos Rafail Papadakis

## How to RUN
* Compilation

          gcc -fopenmp GameOfLife.c -O3

* Threads change from the definition at the start of the code text.

* The program to run needs:

        ./a.out {glidfile} {generations} {outputfile}

Where 
* glidfile : the input file (eg glid1.txt)

* generations: the genes that we want to run

* outputfile: the file that we want to save the results.
##### If there isn't an output file then it prints the results to the stdout(not suggested).
