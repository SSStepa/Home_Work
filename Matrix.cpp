#include <stdio.h>
#include <stdlib.h>

/**
 * @brief function to show matrix.
 * @param [in] Matrix matrix to show.
 * @param [in] sizeX matrix x len.
 * @param [in] sizeY matrix y len.
 */
void FShowMatrix(int *Matrix, int sizeX, int sizeY);

/**
 * @brief function to sum matrixes.
 * @param [in] Matrix1 first matrix to add.
 * @param [in] Matrix2 second matrix to add.
 * @param [in] sizeX x size of matrix.
 * @param [in] sizeY y size of matrix.
 * @return sum matrix(pointer to the first element in dinamic mamory). 
 */
int *FSumMatrix(int *Matrix1, int *Matrix2, int sizeX, int sizeY);

/**
 * @brief get's traengle matrix from user
 * @param [in] numTeams amount of teams which are going to partecipate in compitition.
 * @return pointer to first element of matrix.
 */
int *CreateGame(int numTeams);

/**
 * @brief gets one value from traengle matrix.
 * @param [in] Matrix matrix to get coef from.
 * @param [in] x x coordinate of element.
 * @param [in] y y coordinate of element.
 * @param [in] numTeams amount of participating teams.
 * @return value or NULL if something went wrong. 
 */
int GetTrCoeff(int *Matrix, int x, int y, int numTeams);


/**
 * @brief shows full game table.
 * @param [in] Matrix matrix to show
 * @param [in] numTeams amount of playing teams.
 */
void ShowGame(int *Matrix, int numTeams);


#define ShowMatrix(Matrix, sizeX, sizeY) FShowMatrix((int *) Matrix, sizeX, sizeY)
#define SumMatrix(Matrix1, Matrix2, sizeX, sizeY) FSumMatrix((int *) Matrix1, (int *) Matrix2, sizeX, sizeY)

int main()
{
    int Matrix1[4][5] = {
        { 1, 4, 6, 78,  3},
        {12, 4, 5,  6,  7},
        { 3, 8, 9, 10, 11},
        { 7, 3, 2,  8,  9}
    };

    int Matrix2[4][5] = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    // // Show 
    ShowMatrix(Matrix1, 5, 4);
    
    // Sum
    int *Matrix3 = SumMatrix(Matrix1, Matrix2, 5, 4);
    ShowMatrix(Matrix3, 5, 4);
    free(Matrix3);

    // Game
    int numTeams = 0;
    printf("How much teams are playing today? ");
    scanf("%d", &numTeams);

    Matrix3 = CreateGame(numTeams);
    int v1 = GetTrCoeff(Matrix3, 1, 2, numTeams);
    int v2 = GetTrCoeff(Matrix3, 10, 10, numTeams);
    int v3 = GetTrCoeff(Matrix3, 3, 1, numTeams);
    printf("(1, 2) = <%d>, (10, 10) = <%d>, (3, 1) = <%d>\n", v1, v2, v3);

    ShowGame(Matrix3, numTeams);
    free(Matrix3);

}

void FShowMatrix(int *Matrix, int sizeX, int sizeY)
{
    if (Matrix == NULL) {
        printf("WRONG INPUT");

    } else {
        for (int y = 0; y < sizeY; y++) {
            printf("|");

            for (int x = 0; x < sizeX; x++) {
                printf("%3d ", *(Matrix + y * sizeX + x));
            }

            printf("\b|\n");
        }
    }
}

int *FSumMatrix(int *Matrix1, int *Matrix2, int sizeX, int sizeY)
{
    if (Matrix1 == NULL || Matrix2 == NULL) {
        printf("WRONG INPUT");
        return NULL;
    }

    int *result = (int *) calloc(sizeX*sizeY, sizeof(int));

    if (result == NULL) {
        printf("NO MEMORY\n");
        return NULL;
    }

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            result[y*sizeX + x] = *(Matrix1++) + *(Matrix2++);
        }
    }

    return result;
}

int *CreateGame(int numTeams)
{
    int numGames = (numTeams + 1) * numTeams/2;
    int *result = (int *) calloc(numGames, sizeof(int));

    int ind = 0;
    for (int first = 2; first <= numTeams; first++) {
        for (int second = 1; second < first; second++) {
            printf("Game between %d %d teams finished to (goals %d - goals %d): ", first, second, first, second);
            scanf("%d", &result[ind++]);
        }
    }
    return result;
}

int GetTrCoeff(int *Matrix, int x, int y, int numTeams)
{
    if(Matrix == NULL) {
        printf("WRONG INPUT\n");
        return NULL;
    }
    if ((y > numTeams - 2) || x > y) {
        printf("NO ELEMENT WITH THIS INDEX\n");
        return NULL;
    }

    int ind = y * (y + 1)/2 + x;
    int numGames = numTeams * (numTeams + 1)/2;

    if (ind < numGames)
        return Matrix[ind];

    else {
        printf("INDEX OUT OF RANGE\n");
        return NULL;
    } 
}

void ShowGame(int *Matrix, int numTeams)
{
    // first line
    printf("     ");
    for (int x = 1; x < numTeams; x++)
        printf("%3d ", x);
    printf("\n");

    for (int y = 1; y < numTeams; y++) {
        printf("%3d: ", y + 1);
        for (int x = 0; x < y; x++)
            printf("%3d ", GetTrCoeff(Matrix, x, y - 1, numTeams));
        
        printf("\n");
    }
}
