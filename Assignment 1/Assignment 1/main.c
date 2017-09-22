//
//  main.c
//  CSE-6010 Assignment1
//
//  Created by Karl Gemayel on 8/17/17.
//  Copyright © 2017 Karl Gemayel. All rights reserved.
//
//  Student name: XIAOYU YANG
//  Student username: xyang368


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
int         num_unSatisifed (int n1, int n2, char **a, double f);

// Main function
int main(int argc, const char * argv[]) {
    srand(time(NULL));
    // Start by reading the input from the command line prompt.
    // Note: when no additional arguments are passed through the
    // the command prompt, argc equals 1, and argv[0] is the
    // name of our executable file.
    
    // In this case, the program takes in 4 addition arguments:
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
    
    
    //TODO: Your code here.
    
    char** matPointer = malloc_matrix(n1,n2);
    
    init_matrix(n1, n2, matPointer);
    
    //iteration
    int numTotalMoving = 1;
    int* numMoving = malloc(sizeof(int));
    
    if(numMoving == NULL) {
        printf("Error: not enough memory");
        return -1;
    }
    
    for (int i = 0; i < numSimulations; i++) {
        int numOfUns = num_unSatisifed(n1, n2, matPointer, f);
        if (numOfUns != 0) {
            numTotalMoving = simulate(n1, n2, matPointer, f);
            //printf("numIteration %d, numTotalMoving %d, numUnsatisified %d \n", i, numTotalMoving, numOfUns);
            //print_matrix(n1, n2, matPointer);
        }
        
        else {
            numTotalMoving = simulate(n1, n2, matPointer, f);
            //printf("numIteration %d, numTotalMoving %d, numUnsatisified %d \n", i, numTotalMoving, numOfUns);
            break;
        }
    }
    
    print_matrix(n1, n2, matPointer);
    
    free_matrix(n1, n2, matPointer);
    
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
    char** mat = NULL;
    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    // - update the 'mat' variable
    mat = (char**) malloc((n1+1)*sizeof(char*));
    
    for (int i = 0; i < n1+2; i++) {
        mat[i] = (char*) malloc((n2+1)*sizeof(char));
    }
    
    if (mat == NULL) {
        printf("Error: No memory to create matrix");
        return NULL;
    }
    
    else {
        return mat;
    }
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
    if (a == NULL) {
        printf("Error: No memory for matrix");
    }
    free(a);
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
    
    if (n1 < 1 || n2 < 1 || a == NULL) {
        printf("Error: Invalid input");
    }
    
    //Init boundary conditions
    for (int i = 0; i < n1+2; i++) {
        *(*(a+i)) = ' ';
        *(*(a+i)+n1+1) = ' ';
        
    }
    
    for (int j = 0; j < n2+2; j++) {
        *(*(a)+j) = ' ';
        *(*(a+n2+1)+j) = ' ';
    }
    


    for (int i = 1; i < n1 + 1; i++)
    {
        for (int j = 1; j < n2 + 1; j++) {
            int m = rand() % (n1*n2);
            if (m < 0.4*n1*n2) {
                *(*(a+i)+j) = 'R';
            }
            
            else if (0.4*n1*n2 < m < 0.8*n1*n2) {
                *(*(a+i)+j) = 'G';
            }
            
            else {
                *(*(a+i)+j) = ' ';
            }
        }
    }
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
    for (int i=1; i<n1+1; i++)
    {
        for(int j=1; j<n2+1; j++)
        {
            printf("%c ", *(*(a+i)+j));
        }
        printf("\n");
    }
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


//calculate the number of neightbor who is R
int calNeighborR (int i, int j, char **a) {
    int satRNum = ((*(*(a+i-1)+j-1)=='R') + (*(*(a+i-1)+j)=='R') + (*(*(a+i-1)+j+1)=='R') + (*(*(a+i)+j-1)=='R') + (*(*(a+i)+j+1)=='R') + (*(*(a+i+1)+j-1)=='R') + (*(*(a+i+1)+j)=='R') + (*(*(a+i-1)+j+1)=='R'));
    return satRNum;
}

//calculate the number of neightbor who is G
int calNeighborG (int i, int j, char **a) {
    int satGNum = ((*(*(a+i-1)+j-1)=='G') + (*(*(a+i-1)+j)=='G') + (*(*(a+i-1)+j+1)=='G') + (*(*(a+i)+j-1)=='G') + (*(*(a+i)+j+1)=='G') + (*(*(a+i+1)+j-1)=='G') + (*(*(a+i+1)+j)=='G') + (*(*(a+i-1)+j+1)=='G'));
    return satGNum;
}

//Check whether the location which type is G meet the preference requirement
_Bool prefGCheck (double numG, double numR, double f) {
    if (numG+numR < 1) {
        return 1;}
    
    else if (numG/(numG+numR) >= f ) {
        return 1;}
    
    else {
        return 0;}
}

//Check whether the location which type is R meet the preference requirement
_Bool prefRCheck (double numG, double numR, double f) {
    if (numG + numR < 1) {
        return 1;
    }
    
    else if (numR/(numG+numR) >= f) {
        return 1;}
    
    else {
        return 0;}
}

//Return the number of unsatisfied agent
int num_unSatisifed (int n1, int n2, char **a, double f) {
    char** unsatLoc = malloc(n1*n2*sizeof(char*));
    
    if (unsatLoc == NULL) {
        printf("error: No enough memary");
        return -1;
    }
    
    int m = 0;  //number of vacant places
    int n = 0;  //number of unsatisfied places
    for (int i = 1; i < n1+1; i++) {
        for (int j = 1; j < n2+1; j++) {
            
            int satGNum = calNeighborG(i, j, a);
            int satRNum = calNeighborR(i, j, a);
            
            int sumNum = satGNum + satRNum;
            
            if (*(*(a+i)+j) == ' ') {
                m++;
            }
            
            if (*(*(a+i)+j) == 'R' && ((double)satRNum/(double)sumNum) < f){
                n++;
            }
            
            if (*(*(a+i)+j) == 'G' && ((double)satGNum/(double)sumNum) < f){
                n++;
            }
        }
    }
    return n;
}



int simulate(int n1, int n2, char **a, double f) {
    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs
    // - update the return value based on success/failure
    
    if  (n1 < 1 || n2 < 1 || a == NULL || f<0) {
        printf("Error:Invalide Input");
        return -1;
    }
    
    //scan for the locations that don't satisfy the preference requirement
    
    char** unsatLoc = malloc(n1*n2*sizeof(char*));
    
    if (unsatLoc == NULL) {
        printf("error: No enough memery");
        return -1;
    }
    
    int numTransfer = 0;
    int numMoveout = 0;
    
    int m = 0;  //number of vacant places
    int n = 0;  //number of unsatisfied places
    
    for (int i = 1; i < n1+1; i++) {
        for (int j = 1; j < n2+1; j++) {
            
            int satGNum = calNeighborG(i, j, a);
            int satRNum = calNeighborR(i, j, a);
            
            int sumNum = satGNum + satRNum;
            
            if (*(*(a+i)+j) == ' ') {
                m++;
                }
            
            if (*(*(a+i)+j) == 'R' && ((double)satRNum/(double)sumNum) < f){
                *(unsatLoc+n) = *(a+i)+j;
                n++;
            }
            
            if (*(*(a+i)+j) == 'G' && ((double)satGNum/(double)sumNum) < f){
                *(unsatLoc+n) = *(a+i)+j;
                n++;
            }
            }
        }
    
    
    //Start the simulation process
    
    for (int i = 0; i < n; i++) {
    
        // initialize the start point randomly
        char typeofTarget = **(unsatLoc+i);
        int transfer = 0;
        int starti = rand() % n1 + 1;
        int startj = rand() % n2 + 1;

       // search for matrix from random places for statisfied vacant places
        
        for (int j = starti; j < n1+1; j++) {
            for (int k = startj; k < n2+1; k++) {
                char typeofPoint = *(*(a+j)+k);
                if (typeofPoint == 'R' || typeofPoint == 'G') {
                    continue;
                }
                
                if (typeofPoint == ' ' ) {
                    double satRNum = calNeighborR(j, k, a);
                    double satGNum = calNeighborG(j, k, a);
                    if (typeofTarget == 'R' && prefRCheck(satGNum, satRNum, f)) {
                        **(unsatLoc+i) = ' ';
                        *(*(a+j)+k) = 'R';
                        transfer = 1;
                        goto end1;
                    }
                    
                    if (typeofTarget == 'G' && prefGCheck(satGNum, satRNum, f)) {
                        **(unsatLoc+i) = ' ';
                        *(*(a+j)+k) = 'G';
                        transfer = 1;
                        goto end1;
                    }
                }
        
            }
            
        }
        
        end1:
        
        if (transfer == 1) {
            numTransfer++;
            continue;
            }
        //Search for the rest part of matrix for satisfied places
        
        else {
            for (int j = 1; j < n1; j++) {
                for (int k = 1; k < n2; k++) {
                    char typeofPoint = *(*(a+j)+k);
                    if (typeofPoint == 'R' || typeofPoint == 'G') {
                        continue;
                    }
                    
                    if (typeofPoint == ' ' ) {
                        double satRNum = calNeighborR(j, k, a);
                        double satGNum = calNeighborG(j, k, a);
                        if (typeofTarget == 'R' && prefRCheck(satGNum, satRNum, f)) {
                            **(unsatLoc+i) = ' ';
                            *(*(a+j)+k) = 'R';
                            transfer = 1;
                            goto end2;
                        }
                        
                        if (typeofTarget == 'G' && prefGCheck(satGNum, satRNum, f)) {
                            **(unsatLoc+i) = ' ';
                            *(*(a+j)+k) = 'G';
                            transfer = 1;
                            goto end2;
                        }
                    }
                    
                }
                
            }

        end2:
            
            if (transfer == 1) {
                numTransfer++;
            }
            
            else {
                **(unsatLoc+i) = ' ';
                numMoveout++;
            }
            
        }
        
    }
    free(unsatLoc);
    int totalMov = numMoveout+numTransfer;
    return totalMov;
}
