//
//  main.c
//  6010_2
//
//  Created by Sunil Timalsina on 8/25/17.
//  Copyright © 2017 Learning. All rights reserved.
//

#include <stdio.h>

void printVector(int someVector[], int length);
void dotProduct(int u[], int v[], int length);

void printVector(int someVector[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d\n",someVector[i]);
    }
}

void dotProduct(int u[], int v[], int length) {
    int result;
    result = 0;
    for (int i= 0; i< length; i++) {
            result = result + u[i]*v[i];
    }
    printf("DotProduce = %d\n", result);
}

int main(void) {
    int u[4] = {1,2,3,4};
    int v[4] = {5,6,7,8};
    printf("u=\n"); printVector(u, 4);
    printf("v=\n"); printVector(v, 4);
    dotProduct(u,v,4);
}
    
 // get two vector u and v
 // print vector
 // compute the vectors
 // print out the results
