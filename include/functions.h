//
// Created by soup99 on 2024-03-08.
//

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

#endif //UNTITLED_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
typedef _Bool bool;
typedef struct tuple{
    int y;
    int x;
}tuple;
typedef struct node{
    int* datum;
    struct node *next;

}node;

void takeInputs(unsigned int *vars, float *tightness, float *alpha, float *r);
void printTuple(tuple t, bool s);

tuple* generate2AryCombinations(int n, bool t);

int* selectK(int n, int m);
int factorial(int n);
int comb(int n, int r);

tuple checkSolution(node *state, tuple **badTuples, tuple *constraints, int n, int numberOfConstraints, int numberOfIncompatibleTuples);