#include "../include/functions.h"
//Main function
int main() {
    srand(time(NULL));

    //Input Variables.
    unsigned int n;
    float p, a, r;

    printf("\n");
    //Function to take inputs.
    takeInputs(&n, &p, &a, &r);

    //Calculations
    int domainSize = (int) (powf((float) n, a));
    int numberOfConstraints = round(r * n * log(n));
    int numberOfIncompatibleTuples = round(p * pow(domainSize, 2.0));
    double phaseT = 1 - exp(-a / r);

    printf("\n");

    //Prints calculations, domain size, variables.
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

    //Constraint tuple section
    printf("Constraints  |  Incompatible Tuples\n");

    //Generates all combinations of variables.
    tuple *constraintComb = generate2AryCombinations(n, 1);
    //Randomly select comb(n, 2) distinct index numbers
    int *selectConstraint = selectK(comb(n, 2), numberOfConstraints);
    //Generates all combinations of variables and includes (i,j) where i==j, flag '0'
    tuple *tupleComb = generate2AryCombinations(domainSize, 0);

    //Array of constraints
    tuple *constraints = (tuple *) malloc(sizeof(tuple) * numberOfConstraints);
    //For each constraint, numberOfIncompatibleTuple tuples.
    tuple **badTuples = (tuple **) malloc(sizeof(tuple *) * numberOfConstraints);
    for (i = 0; i < numberOfConstraints; i++) {
        //each pointer points to an array of numberOfIncompatibleTuple tuples
        badTuples[i] = (tuple *) malloc(sizeof(tuple) * numberOfIncompatibleTuples);
        //using selectConstraint, select a combination from the set and add it to our constraints
        constraints[i] = constraintComb[selectConstraint[i] - 1];
        //randomly selects comb(domainSize+2-1,2) (number of combinations with repetition ) distinct index numbers
        int *selectTuple = selectK(comb(domainSize+2-1,2), numberOfIncompatibleTuples);
        //using selectTuple, select numberOfIncompatibleTuples combinations from the set and add it to our badTuples
        for (int j = 0; j < numberOfIncompatibleTuples; j++) {
            badTuples[i][j] = tupleComb[selectTuple[j] - 1];
        }
    }

    //Print out the constraints and corresponding tuples formatted.
    for (i = 0; i < numberOfConstraints; i++) {
        printTuple(constraints[i], 1);
        for (int j = 0; j < numberOfIncompatibleTuples; j++) {
            printf("\t");
            printTuple(badTuples[i][j], 0);
        }
        printf("\n");
    }

    //Using the phase transition, determine if the generated instances will be consistent
    if (p < phaseT)
        printf("p=%f < pt(%f) -> Generated CSP instances are guaranteed to be consistent.\n", p, phaseT);
    else
        printf("p=%f > pt(%f) -> Generated CSP instances are NOT guaranteed  to be consistent.\n", p, phaseT);

    //State, and pointer to start of search.
    node *root = (node *) malloc(sizeof(node));
    root->datum = (int *) malloc(sizeof(int) * n);
    node *pRoot = root;

    //Start state = x0=0,x1=0,....,xn = 0
    for (i = 0; i < n; i++) root->datum[i] = 0;
    //Check the state against our constraints and bad tuples
    tuple bad = checkSolution(root, badTuples, constraints, n, numberOfConstraints,numberOfIncompatibleTuples);
    //If bad=={-1,-1} a solution was found. This loop will not complete if a solution is never found.
    // Bad = {z,y} means Xz Xy are in an invalid pair
    while (bad.x != -1 && bad.y != -1) {
        //New State
        node *new = (node*)malloc(sizeof(node));
        new->datum = (int*)malloc(sizeof(int)*n);
        for(i=0;i<n;i++){
            //Hard Copy Old State
            new->datum[i] = root->datum[i];
        }
        //Set the child of root equal to our new state.
        root->next=new;
        bool t = rand()%2; //Binary 0/1 to determine whether to increment Xbad.x or Xbad.y
        if(t) new->datum[bad.x] = (new->datum[bad.x] + 1)%domainSize;
        else new->datum[bad.y] = (new->datum[bad.y] + 1)%domainSize;
        root = new;
        bad = checkSolution(root, badTuples, constraints, n, numberOfConstraints,numberOfIncompatibleTuples);
    }
    printf("Solution: \n");

    for(i=0;i<n;i++){
        printf("X%i=%i\n",i,root->datum[i]);
    }

    //Free heap memory
    free(root->datum);
    free(root);
    free(constraints);
    for (i = 0; i < numberOfConstraints; i++)
        free(badTuples[i]);
    free(badTuples);



        return 0;
    }