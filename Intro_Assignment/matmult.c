#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Matrix {
    double** mat;
    int r;
    int c;
};
struct Matrix arr2Matrix(double* arr, int row, int col);
double* readMatrixFromFile(char* fileName, int height, int width);
int writeMatrixToFile(char* fileName, double* matrix, int height, int width);
struct Matrix matmult(struct Matrix matA, struct Matrix matB);
double* matrix2Arr(struct Matrix mat);
void dimCheck(char** argv);


int main(int argc, char** argv) {
    clock_t t_start, t_end;
    t_start = clock();

    dimCheck(argv);

    struct Matrix matA, matB, matC;
    int rowA = atoi(argv[1]);
    int colA = atoi(argv[2]);
    int rowB = atoi(argv[3]);
    int colB = atoi(argv[4]);

    matA = arr2Matrix(readMatrixFromFile("A.csv", rowA, colA), rowA, colA);
    matB = arr2Matrix(readMatrixFromFile("B.csv", rowB, colB), rowB, colB);

    matC = matmult(matA, matB);
    double* out = matrix2Arr(matC);

    writeMatrixToFile("C.csv", out, matC.r, matC.c);
    
    t_end = clock();
    printf("Time = %.0ld microseconds.\n", t_end - t_start);
    return 0;
}


double* readMatrixFromFile(char* fileName, int height, int width) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s.\n", fileName);
        return NULL;
    }
    double val;
    double* M = (double*) malloc(height * width * sizeof(double));
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
        if (fscanf(fp, " %lf", &val) != 1) {
            fprintf(stderr, "Couldn't read value.\n");
            return NULL;
        }
        // Discard the comma without checking.
        fgetc(fp);
        M[i * width + j] = val;
        }
    }
    fclose(fp);
    return M;
}

int writeMatrixToFile(char* fileName, double* matrix, int height, int width) {
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL) {
        return 1;
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        if (j > 0) {
            fputc(',', fp);
        }
        fprintf(fp, "%lf", matrix[i*width +j]);
        }
        fputs("\r\n", fp);
    }
    fclose(fp);
    return 0;
}

struct Matrix matmult(struct Matrix matA, struct Matrix matB) {
    struct Matrix out;
    out.r = matA.r;
    out.c = matB.c;
    out.mat = (double**)malloc( sizeof(double*)*out.r*out.c );
    for(int i = 0; i < out.r; i++) {
        for(int j = 0; j < out.c; j++) {
            out.mat[i] = (double*)malloc( sizeof(double)*out.c );
            out.mat[i][j] = 0;
        }
    }

    for(int i = 0; i < matA.r; i++) {
        for(int j = 0; j < matB.c; j++) {
            for(int k = 0; k < matB.r; k++) {
                out.mat[i][j] += matA.mat[i][k]*matB.mat[k][j];
            }
        }
    }
    return out;
}

double* matrix2Arr(struct Matrix mat) {
    double* arr;
    arr = (double*)malloc(sizeof(double)*mat.r*mat.c);
    for(int i = 0; i < mat.r*mat.c; i++) {
        arr[i] = mat.mat[i/mat.c][i%mat.c];
    }
    return arr;
}

struct Matrix arr2Matrix(double* arr, int row, int col) {
    struct Matrix mat;
    mat.r = row;
    mat.c = col;
    mat.mat = (double **)malloc( sizeof(double *)*row*col );
    for(int i = 0; i < row; i++) {
        mat.mat[i] = (double *)malloc( sizeof(double)*col );
        for(int j = 0; j < col; j++) {
            mat.mat[i][j] = arr[i*col + j];
        }
    }
    free(arr);
    return mat;
}

void dimCheck(char** argv) {
    int dim[4];
    for(int i = 0; i < 4; i++) {
        dim[i] = atoi(argv[i+1]);
        if( dim[i] <= 0) {
            fprintf(stderr, "InputArgError: expected positive integers - argv[%d]\n", i+1);
            exit(EXIT_FAILURE);
        }
    }
    if( dim[1] != dim[2]) {
        printf("MatDimError: Matrix dimensions did not match.\n");
        exit(EXIT_FAILURE);
    }
}