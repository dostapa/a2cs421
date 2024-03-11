//
// Created by soup99 on 2024-03-08.
//

#include "../include/functions.h"
void takeInputs(unsigned int *vars, float *tightness, float *alpha, float *r){
    printf(" Enter Number of Variables: "); scanf("%u", vars);

    printf("Enter Constraint Tightness: "); scanf("%f",tightness);

    printf("Enter Alpha: "); scanf("%f", alpha);

    printf("Enter r: "); scanf("%f", r);
}
void printTuple(tuple t, bool s) {
    if(s) printf("(X%u, X%u)", t.x, t.y);
    else printf("(%u, %u)", t.x, t.y);
}

//Iterative factorial
int factorial(int n){
    int accum=1;
    while(n!=0){
        accum=accum*n;
        n--;
    }
    return accum;
}

//Combination formula
int comb(int n, int r){
    int comb = (factorial(n)) / (factorial(r)*(factorial(n-r)));
    return comb;
}

tuple* generate2AryCombinations(int n, bool t){
    tuple* combinations;
    if(t)
        combinations = (tuple*)malloc(sizeof(tuple)*comb(n,2));
    else
        combinations = (tuple *) malloc(sizeof(tuple) * comb(n+2-1,2));
    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = i ; j < n; j++){
            if(i==j && t) continue;
            else{
                combinations[k].x = i;
                combinations[k++].y = j;
            }
        }
    }
    return combinations;
}

int* selectK(int n, int m){
    int* out = (int*)malloc(m*sizeof(int));
    unsigned char *is_used = (unsigned int*)malloc(sizeof(unsigned int)*n);
    for(int i = 0; i < n; i++)
        is_used[i] = 0;
    int in, im;

    im = 0;

    for (in = n - m; in < n && im < m; ++in) {
        int r = rand() % (in + 1); /* generate a random number 'r' */

        if (is_used[r])
            /* we already have 'r' */
            r = in; /* use 'in' instead of the generated number */

        out[im++] = r + 1; /* +1 since your range begins from 1 */
        is_used[r] = 1;
    }
    return out;
}

tuple checkSolution(node *state, tuple **badTuples, tuple *constraints, int n, int numberOfConstraints, int numberOfIncompatibleTuples) {
    for(int i = 0 ; i < numberOfConstraints; i++){
        tuple pair = constraints[i];
        for(int j = 0 ; j < numberOfIncompatibleTuples; j++){
            tuple check = badTuples[i][j];
            if((state->datum[pair.x] == check.x) && (state->datum[pair.y] == check.y)) {
                return pair;
            }
        }
    }

    return (tuple){-1,-1};
}
