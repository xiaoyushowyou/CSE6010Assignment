//
//  main.c
//  kMeans
//
//  Created by Xiaoyu Yang on 9/15/17.
//  Copyright © 2017 Learning. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>     // for rand, srand
#include <time.h>       // for time, clock
#include <string.h>     // for strncmp
#include <float.h>
#include <math.h>

double** malloc_matrix(int n, int k);
double** init_centers(int k, int m, double** myData);
double calDis(double** myData, double** myCenter, int rowNum, int centerNum, int numDim);
double updateLable(int numData, int numDim, int k, double** myData, double** myCenter);
void printMatrix(int numData, int numDim, double** myData);
void resetCenter(int numDim, int k, double** myCenter);
void updateCenter(int numData, int numDim, int k, double** myData, double** myCenter);
void free_matrix(int n, int m, double **a);

void usage(const char *programName);

int main(int argc, const char * argv[]) {
    
    if (argc != 5) {
        usage(argv[0]);
        return 1;
    }
    
    const char *fileName = argv[1];
    int k = (int) strtol(argv[2], NULL, 10);
    int maxLoop = (int) strtol(argv[3], NULL, 10);
    double stopDis = (double) strtod(argv[4], NULL);

    printf("start main!\n");

    //1. open file
    FILE* inPointer;
    FILE* outPointer;
    
    const char* inputFile = fileName;
    char* outputFile = "dataOut.txt";
    
    inPointer = fopen(inputFile, "r");
    outPointer = fopen(outputFile, "w");
    
    if (inPointer == NULL) {
        printf("input file has errors");
        return 1;
    }
    
    if (outPointer == NULL) {
        printf("output file has errors");
        return 1;
    }
    
    
    //2. reading from/writing to file
    
    int numData = 0;
    int numDim = 0;
    
    if(fscanf(inPointer, "%d %d", &numData, &numDim) != 2) {
        printf("First Line ERROR");
    }
    
    double** data = malloc_matrix(numData, numDim+1);
    
    for (int i = 0; i < numData; i++) {
        for (int j = 0; j < numDim; j++) {
            fscanf(inPointer, "%lf", (*(data+i)+j));
        }
    }
    
    //Initial the center matrix
    
    double** center = init_centers(k, numDim, data);
    
    double currentDis =  DBL_MAX;
    double previousDis = DBL_MAX;
    double changeDis = DBL_MAX;
    
    int loopNum = 0;
    
    //3. Kmeans algorithm
    while (loopNum < maxLoop && changeDis > stopDis){
        currentDis = updateLable(numData, numDim, k, data, center);
        changeDis = previousDis - currentDis;
        updateCenter(numData, numDim, k, data, center);
        previousDis = currentDis;
        loopNum = loopNum + 1;
    }
    
    printf("number of cluster, incluster distance %d %lf\n", k, currentDis);
    
    //4. write result to file
    fprintf(outPointer, "%d %d %d\n", numData, numDim, k);
    for (int i = 0; i < numData; i++) {
        for (int j = 0; j < numDim; j++) {
            fprintf(outPointer, "%lf ", *(*(data+i)+j));
        }
        fprintf(outPointer, "%d ", (int)(*(*(data+i)+numDim)));
        fprintf(outPointer, "%s", "\n");
    }
    
    
    //5. Closing file
    
    fclose(inPointer);
    fclose(outPointer);
    
    printf("end main!\n");
    
    //6. free all the memory
    
    free_matrix(k, numDim+1, center);
    free_matrix(numData, numDim+1, data);

    return 0;
}

void usage(const char *programName) {
    printf("usage: %s fileName k maxLoop s\n", programName);
    printf("where:\n");
    printf(" fileName   : the name of input file\n");
    printf("    k       : number of clusters\n");
    printf(" maxLoop    : max number of iteration\n");
    printf(" stopDis    : threshold of total incluster distance compared to previous round\n");
    printf("\nExample: %s dataIn.txt 12 100 0.001\n", programName);
}


void printMatrix(int numData, int numDim, double** myData) {
    if (myData == NULL || numData < 1 || numDim < 1) {
        printf("Error. Print error");
    }
    
    for (int i = 0; i < numData; i++) {
        for (int j = 0; j < numDim; j++) {
            printf("%lf ", *(*(myData+i)+j));
        }
        printf("\n");
    }
}

double **malloc_matrix(int n, int m) {
    double** mat = NULL;
    mat = (double**) malloc (n*sizeof(double*));
    
    for (int i = 0; i < n; i++) {
        mat[i] = (double*) malloc (m*sizeof(double));
    }
    
    if (mat == NULL) {
        printf("Error: No memory to create matrix");
        return NULL;
    }
    
    else {
        return mat;
    }
}

//free the memory of matrix
void free_matrix(int n, int m, double **a) {
    if (a == NULL) {
        printf("Error, no memory for matrix");
    }
    for (int i = 0; i < n; i++) {
        free(*(a+i));
    }
    free(a);
    a = NULL;
}

//Initial the values of centers
double **init_centers(int k, int m, double** myData) {
    if (k < 0 || myData == NULL) {
        printf("Error, no memory for matrix");
    }
    
    double ** myCenter = malloc_matrix(k, m+1);
    
    //trabsfer the data from orginal one to initial values for centers
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < m; j++) {
            *(*(myCenter+i)+j) = *(*(myData+i)+j);
        }
    }
    
    if (myCenter == NULL) {
        printf("Error, no memory for matrix");
    }
    
    return myCenter;
}


double updateLable(int numData, int numDim, int k, double** myData, double** myCenter) {
    
    //update the last column of the data
    //struct updataLableResult result;
    if (myData == NULL || myCenter == NULL) {
        printf("Error, no memory for matrix");
    }
    
    double totalDis = 0;
    
    for (int i = 0; i < numData; i++) {
        double disMin = DBL_MAX;
        int clusterNum = 0;
        
        for (int j = 0; j < k; j++) {
            double temp = calDis(myData, myCenter, i, j, numDim);
            
            if (temp < disMin) {
                clusterNum = j;
                disMin = temp;
            }
        }
        
        *(*(myData+i)+numDim) = clusterNum;
        
        totalDis = totalDis + disMin;
    }
    
    return totalDis;
}


void updateCenter(int numData, int numDim, int k, double** myData, double** myCenter) {
    if (myData == NULL || myCenter == NULL) {
        printf("Error, no memory for matrix");
    }
    
    //set every value in center into 0;
    resetCenter(numDim, k, myCenter);
    
    for (int i = 0; i < numData; i++) {
        int dataLable = (int)(*(*(myData+i)+numDim));
        
        for (int j = 0; j < numDim; j++) {
            *(*(myCenter+dataLable)+j) = *(*(myCenter+dataLable)+j) + *(*(myData+i)+j);
        }
        
        *(*(myCenter+dataLable)+numDim) = *(*(myCenter+dataLable)+numDim) + 1;
    }
    
    for (int m = 0; m < k; m++) {
        for (int j = 0; j < numDim; j++) {
            *(*(myCenter+m)+j) = (*(*(myCenter+m)+j)) / (*(*(myCenter+m)+numDim));
        }
    }
}


void resetCenter(int numDim, int k, double** myCenter) {
    if (myCenter == NULL) {
        printf("Error, no memory for center matrix");
    }
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < numDim + 1; j++) {
            *(*(myCenter+i)+j) = 0;
        }
    }
}

double calDis(double** myData, double** myCenter, int rowNum, int centerNum, int numDim) {
    double myDis = 0.0;

    for (int i = 0; i < numDim; i++) {
        myDis = myDis + pow((*(*(myData+rowNum)+i) - *(*(myCenter+centerNum)+i)),2);
    }
    
    return myDis;
}

double totalDis(double** myData, double** myCenter, int numData, int numDim) {
    double myDis = 0;
    
    for (int i = 0; i < numData; i++) {
        int dataLable = (int)(*(*(myData+i)+numDim));
        for (int j = 0; j < numDim; j++) {
        myDis = myDis + pow((*(*(myData+i)+j) - *(*(myCenter+dataLable)+j)),2);
        }
    }
    return myDis;
}

