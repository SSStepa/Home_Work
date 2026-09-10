#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int *Matrix;
    int x, y;
};

void ShowMatrix(Matrix Matrix)
{
    if (Matrix.Matrix == NULL) {
        printf("WRONG INPUT");

    } else {
        for (int y = 0; y < Matrix.y; y++) {
            printf("|");

            for (int x = 0; x < Matrix.x; x++) {
                printf("%3d ", *(Matrix. Matrix + y * Matrix.x + x));
            }

            printf("\b|\n");
        }
    }
}

int *SumMatrix(Matrix Matrix1, Matrix Matrix2)
{
    if (Matrix1.Matrix == NULL || Matrix2.Matrix == NULL || Matrix1.x != Matrix2.x || Matrix1.y != Matrix2.y) {
        printf("WRONG INPUT");
        return NULL;
    }

    int *result = (int *) calloc(Matrix1.x * Matrix1.y, sizeof(int));

    if (result == NULL) {
        printf("NO MEMORY\n");
        return NULL;
    }

    for (int y = 0; y < Matrix1.y; y++) {
        for (int x = 0; x < Matrix1.x; x++) {
            result[y*Matrix1.x + x] = *(Matrix1.Matrix++) + *(Matrix2.Matrix++);
        }
    }

    return result;
}