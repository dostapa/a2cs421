#include "functions.h"
int main() {
    srand(time(NULL));
    unsigned int n;
    float p, a, r;

    takeInputs(&n, &p, &a, &r);

    int domainSize = (int) (powf((float) n, a));
    int numberOfConstraints = round(r * n * log(n));
    int numberOfIncompatibleTuples = round(p * pow(domainSize, 2.0));

    double phaseT = 1 - exp(-a / r);
    printf("\n");

    printf("Calculations:\n----------------------------\n");
    printf("Domain Size: %i\n", domainSize);
    printf("Number of Constraints: %i \n", numberOfConstraints);
    printf("Number of Incompatible Tuples: %i\n", numberOfIncompatibleTuples);
    printf("Variables: {");
    unsigned int i;
    for (i = 0; i < n; i++) {
        if (i == n - 1) printf("X%u", i);
        else printf("X%u,", i);
    }
    printf("}\n");

    printf("Domain: {");
    for (i = 0; i < domainSize; i++) {
        if (i == domainSize - 1) printf("%u", i);
        else printf("%u,", i);
    }
    printf("}\n");
    printf("\n");
    printf("Constraints  |  Incompatible Tuples\n");

    tuple *constraintComb = generate2AryCombinations(n, 1);
    int *selectConstraint = selectK(comb(n, 2), numberOfConstraints);
    tuple *tupleComb = generate2AryCombinations(domainSize, 0);

    tuple **badTuples = (tuple **) malloc(sizeof(tuple *) * numberOfConstraints);
    for (i = 0; i < numberOfConstraints; i++) {
        badTuples[i] = (tuple *) malloc(sizeof(tuple) * numberOfIncompatibleTuples);
        int *selectTuple = selectK(comb(domainSize+2-1,2), numberOfIncompatibleTuples);
        for (int j = 0; j < numberOfIncompatibleTuples; j++) {
            badTuples[i][j] = tupleComb[selectTuple[j] - 1];
        }
    }

    tuple *constraints = (tuple *) malloc(sizeof(tuple) * numberOfConstraints);
    for (i = 0; i < numberOfConstraints; i++) {
        constraints[i] = constraintComb[selectConstraint[i] - 1];
    }

    for (i = 0; i < numberOfConstraints; i++) {
        printTuple(constraints[i], 1);
        for (int j = 0; j < numberOfIncompatibleTuples; j++) {
            printf("\t");
            printTuple(badTuples[i][j], 0);
        }
        printf("\n");
    }

    if (p < phaseT)
        printf("p=%f < pt(%f) -> Generated CSP instances are guaranteed to be consistent.\n", p, phaseT);
    else
        printf("p=%f > pt(%f) -> Generated CSP instances are NOT guaranteed  to be consistent.\n", p, phaseT);

    node *root = (node *) malloc(sizeof(node));
    root->datum = (int *) malloc(sizeof(int) * n);
    node *pRoot = root;

    for (i = 0; i < n; i++) root->datum[i] = 0;
    tuple bad = checkSolution(root, badTuples, constraints, n, numberOfConstraints,numberOfIncompatibleTuples);
    while (bad.x != -1 && bad.y != -1) {
        node *new = (node*)malloc(sizeof(node));
        new->datum = (int*)malloc(sizeof(int)*n);
        for(i=0;i<n;i++){
            new->datum[i] = root->datum[i];
        }
        root->next=new;
        bool t = rand()%2;
        if(t) new->datum[bad.x] = (new->datum[bad.x] + 1)%domainSize;
        else new->datum[bad.y] = (new->datum[bad.y] + 1)%domainSize;
        root = new;
        bad = checkSolution(root, badTuples, constraints, n, numberOfConstraints,numberOfIncompatibleTuples);
    }
    printf("Solution: \n");

    for(i=0;i<n;i++){
        printf("X%i=%i\n",i,root->datum[i]);
    }
    free(root->datum);
    free(root);
    free(constraints);
    for (i = 0; i < numberOfConstraints; i++)
        free(badTuples[i]);
    free(badTuples);



        return 0;
    }