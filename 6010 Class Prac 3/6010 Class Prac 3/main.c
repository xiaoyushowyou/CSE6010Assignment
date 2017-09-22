//
//  main.c
//  6010 Class Prac 3
//
//  Created by Sunil Timalsina on 9/15/17.
//  Copyright © 2017 Learning. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("starit main\n");
    
    //1. openning file
    FILE* ifp;
    FILE* ofp;
    
    char* inputFile = "dataIn.txt"; //"./data/testIn.txt";
    char* outputFile = "dataOut.txt"; //"./data/testOut.txt";
    
    
    ifp = fopen(inputFile,"r"); //wring 'w'  reading 'r'
    ofp = fopen(outputFile,"w");
    
    
    if(ifp == NULL) {
        printf("inputfile io error");
        return 1;}
    
    if(ofp == NULL) {
        printf("outputfile io error");
        return 1;
    }
    
    
    
    //2. read file
    int numData;
    int numDim;
    
    
    fscanf(ifp,"%d %d",&numData,&numDim); //scanf
    
    printf("%d, %d\n", numData, numDim);
    
    double data[numData][numDim];
    
    for (int i = 0; i < numData ; i++) {
        for(int j = 0; j < numDim ; j++)
        {
            fscanf(ifp,"%lf",&data[i][j]);
        }
    }
    

    fprintf(ofp, "%d \n", numData);
    
    fclose(ifp);
    fclose(ofp);
    
    
    printf("end main \n");
    return 0;
}
