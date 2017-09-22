//
//  main.c
//  CSE-6010 Assignment1
//
//  Created by Karl Gemayel on 8/17/17.
//  Copyright © 2017 Karl Gemayel. All rights reserved.
//
//  Student name: YOUR_NAME_HERE
//  Student username: YOUR_GT_USERNAME

#include <stdio.h>
#include <stdlib.h>     // for rand, srand
#include <time.h>       // for time, clock
#include <string.h>     // for strncmp

// Use these variables for simplicity of code
#define RED 'R'
#define GREEN 'G'
#define VACANT ' '

// Function Prototypes: generic
void usage(const char *programName);

// Function Prototypes: matrix specific
char**      malloc_matrix   (int n1, int n2);
void        free_matrix     (int n1, int n2, char **a);
void        init_matrix     (int n1, int n2, char **a);
int         simulate        (int n1, int n2, char **a, double f);
void        print_matrix    (int n1, int n2, char **a);



// Main function
int main(int argc, const char * argv[]) {

    // Start by reading the input from the command line prompt.
    // Note: when no additional arguments are passed through the
    // the command prompt, argc equals 1, and argv[0] is the 
    // name of our executable file.

    // In this case, the program takes in 3 addition arguments:
    // (1) number of rows, (2) number of columns, (3) number of
    // times to run 'simulate', and (4) value of f
    if (argc != 5) {
        usage(argv[0]);
        return 1;
    }

    int n1 = (int) strtol(argv[1], NULL, 10);                   // number of rows
    int n2 = (int) strtol(argv[2], NULL, 10);                   // number of columns
    int numSimulations = (int) strtol(argv[3], NULL, 10);       // number of times to run 'simulate'
    double f = strtod(argv[4], NULL);                           // the satisfiability fraction

    // This is used for testing
    n1=5;
    n2=5;
    numSimulations=10;
    f=0.4;
    // TODO: Your code here.
    // This part should actually run the simulate function over and over
    // and print the final result.

    return 0;
}

/**
 * Print out the usage message.
 *
 * @param programName the name of the executable file.
 */
void usage(const char *programName) {
    printf("usage: %s  n1 n2 s f\n", programName);
    printf("where:\n");
    printf("    n1      : number of rows\n");
    printf("    n2      : number of columns\n");
    printf("    s       : number of simulation iterations\n");
    printf("    f       : minimum fraction for satisfiability\n");
    printf("\nExample: %s 10 10 100 0.3\n", programName);
}

/****** Matrix Specific Functions ******\
 *                                     *
 * These functions define what matrix  *
 * operations can be performed.        *
 *                                     *
\***************************************/


/**
 * Allocate memory for a 2D matrix
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @return a pointer to the matrix
 */
char **malloc_matrix(int n1, int n2) {
    
    if (!(n1>=1 && n2>=1)) {
        printf("Invalid input");
    }
    
    char **mat = NULL;       // pointer to the matrix
    char *arr;
    
    arr=(char*)malloc(n1 * n2 * sizeof(char));
    
    mat=&arr;

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    // - update the 'mat' variable

    return mat;
}


/**
 * Free the space allocated for the matrix.
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void free_matrix(int n1, int n2, char **a) {
    
    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
}


/**
 * Initialize the matrix.
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void init_matrix(int n1, int n2, char **a) {
    
    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
}

/**
 * Print the matrix to standard output
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void print_matrix(int n1, int n2, char **a) {
    
    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
}


/**
 * Simulate one time-step using matrix 'a', where f determines
 * the minimum number of desired neighbors similar to the occupant.
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 * @param f the fraction indicating the minimum number of desired similar neighbours
 * @return the number of citizens that moved or left the game in this time-step; -1 if
 * function failed.
 */
int simulate(int n1, int n2, char **a, double f) {
    
    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs
    // - update the return value based on success/failure
    
    return 1;
}














