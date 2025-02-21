#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TIMEOUT 60 // Program terminates after TIMEOUT secs

int N;           // Number of propositions
int M;           // Number of sentences
int K;           // Number of propositions per sentence

int *Problem;    // This is a table to keep all the sentences of the problem

// Structure used for the stack of the depth-first search algorithm
struct stack_item {
    int *vector;
    struct stack_item *next;
};

// The head of the stack
struct stack_item *head = NULL;

// Reading the input file
int readfile(char *filename) {
    int i, j;

    FILE *infile;
    int err;

    // Opening the input file
    infile = fopen(filename, "r");
    if (infile == NULL) {
        printf("Cannot open input file. Now exiting...\n");
        fclose(infile);
        return -1;
    }

    // Reading the number of propositions
    err = fscanf(infile, "%d", &N);
    if (err < 1) {
        printf("Cannot read the number of propositions. Now exiting...\n");
        fclose(infile);
        return -1;
    }

    if (N < 1) {
        printf("Small number of propositions. Now exiting...\n");
        fclose(infile);
        return -1;
    }

    // Reading the number of sentences
    err = fscanf(infile, "%d", &M);
    if (err < 1) {
        printf("Cannot read the number of sentences. Now exiting...\n");
        fclose(infile);
        return -1;
    }

    if (M < 1) {
        printf("Low number of sentences. Now exiting...\n");
        fclose(infile);
        return -1;
    }

    // Reading the number of propositions per sentence
    err = fscanf(infile, "%d", &K);
    if (err < 1) {
        printf("Cannot read the number of propositions per sentence. Now exiting...\n");
        fclose(infile);
        return -1;
    }

    if (K < 2) {
        printf("Low number of propositions per sentence. Now exiting...\n");
        fclose(infile);
        return -1;
    }

    // Allocating memory for the sentences...
    Problem = (int *)malloc(M * K * sizeof(int));

    // ...and read them
    for (i = 0; i < M; i++)
        for (j = 0; j < K; j++) {
            err = fscanf(infile, "%d", Problem + i * K + j);
            if (err < 1) {
                printf("Cannot read the #%d proposition of the #%d sentence. Now exiting...\n", j + 1, i + 1);
                fclose(infile);
                return -1;
            }
            if (Problem[i * K + j] == 0 || Problem[i * K + j] > N || Problem[i * K + j] < -N) {
                printf("Wrong value for the #%d proposition of the #%d sentence. Now exiting...\n", j + 1, i + 1);
                fclose(infile);
                return -1;
            }
        }

    fclose(infile);

    return 0;
}

// Auxiliary function that displays all the sentences of the problem
void display_problem() {
    int i, j;

    printf("The current problem:\n");
    printf("====================\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            if (j > 0)
                printf(" or ");
            if (Problem[i * K + j] > 0)
                printf("P%d", Problem[i * K + j]);
            else
                printf("not P%d", -Problem[i * K + j]);
        }
        printf("\n");
    }
}

// Initializing a vector of values for the propositions with random values
void initialize(int *vector) {
    int i, r;
    for (i = 0; i < N; i++) {
        r = rand() % 100;
        vector[i] = (r >= 50) ? 1 : -1;
    }
}

// This function counts how many of the sentences are not satisfied by the current assignment
int count(int *vector) {
    int c = 0, i, j, satisfied;
    for (i = 0; i < M; i++) {
        satisfied = 0;
        for (j = 0; j < K; j++)
            if ((Problem[i * K + j] > 0 && vector[Problem[i * K + j] - 1] == 1) ||
                (Problem[i * K + j] < 0 && vector[-Problem[i * K + j] - 1] == -1))
                satisfied = 1;

        c += satisfied;
    }

    return M - c;
}

// Auxiliary function that displays the current assignment of truth values to the propositions.
void display(int *vector) {
    int i;
    for (i = 0; i < N; i++)
        printf("P%d=%d  ", i + 1, vector[i]);
}

// Check whether a vector is a complete assignment and it is also valid.
int solution(int *vector) {
    int i;
    for (i = 0; i < N; i++)
        if (vector[i] == 0)
            return 0;

    return count(vector) == 0;
}

// The WalkSAT algorithm
void walksat(char **argv) {
    int steps = 0;
    int i, h;
    clock_t t, t1, t2;
    long restarts = 0;
    int best_change;

    int *vector = (int *)malloc(N * sizeof(int));

    t1 = clock();

    // Initialization steps
    initialize(vector);
    h = count(vector);

    while (h > 0) {
        // Check for time limit
        t = clock();
        if (t - t1 > CLOCKS_PER_SEC * TIMEOUT) {
            t2 = clock();
            printf("\n\nNO SOLUTION found with WalkSAT...\n");
            printf("Time spent: %f secs\n", ((float)t2 - t1) / CLOCKS_PER_SEC);
            printf("Number of restarts: %d\n", restarts);
            printf("Number of steps: %d\n", steps);
            return;
        }

        steps++;
        h = count(vector);
        best_change = -1;

        for (i = 0; i < N; i++) {
            vector[i] = -vector[i];
            int h1 = count(vector);

            if (h1 < h) {
                h = h1;
                best_change = i;
            }

            vector[i] = -vector[i];
        }

        if (best_change >= 0)
            vector[best_change] = -vector[best_change];
        else {
            initialize(vector);
            restarts++;
        }
    }

    t2 = clock();
    printf("\n\nSolution found with WalkSAT!\n");
    display(vector);
    printf("\n");
    printf("Time spent: %f secs\n", ((float)t2 - t1) / CLOCKS_PER_SEC);
    printf("Number of restarts: %d\n", restarts);
    printf("Number of steps: %d\n", steps);

    FILE *outfile = fopen(argv[3], "w");
    if (outfile == NULL) {
        printf("Cannot open output file. Now exiting...\n");
        return;
    }

    for (i = 0; i < N; i++)
        fprintf(outfile, "%d ", vector[i]);

    fclose(outfile);
}

void syntax_error(char **argv) {
    printf("Use the following syntax:\n\n");
    printf("%s walksat <inputfile> <outputfile>\n\n", argv[0]);
    printf("where:\n");
    printf("<inputfile> is the name of the file with the problem description\n");
    printf("<outputfile> is the name of the output file with the solution\n");
}

int main(int argc, char **argv) {
    int err;

    srand((unsigned)time(NULL));

    if (argc != 4) {
        printf("Wrong number of arguments. Now exiting...\n");
        syntax_error(argv);
        return -1;
    }

    if (strcmp(argv[1], "walksat") != 0) {
        printf("Invalid method. Now exiting...\n");
        syntax_error(argv);
        return -1;
    }

    err = readfile(argv[2]);
    if (err < 0)
        return -1;

    // display_problem();

    walksat(argv);

    return 0;
}
