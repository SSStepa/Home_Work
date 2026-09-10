#include <stdio.h>
#include <assert.h>
#include "basic.h"

WORK_RES my_qsort(int *arr, size_t sNum);
#define NUMLEN 14

int main()
{
    int Nums[NUMLEN] = {234, 10, 11, 100, 200, 5, 45, 50, 40, 49, 15, 60, 10, 70};

    my_qsort(Nums, NUMLEN);

}

void ErrorPrint(int *arr, size_t sNum, size_t MidleInd, size_t LeftInd, size_t RightInd, const char *Place)
{
    printf("%s\n", Place);

    for (size_t ind= 0; ind < sNum; ind++) {
        if (ind < LeftInd) 
            printf(BLU);
        else if (ind == LeftInd)
            printf(CYN);
        else if (ind < MidleInd) 
            ;
        else if (ind == MidleInd)
            printf(MAG);
        else if (ind < RightInd)
            ;
        else if (ind == RightInd)
            printf(YEL);
        else if (ind < sNum)
            printf(RED);
        else 
            printf(RED "OUT OF RANGE!!!!");
        
        printf("%d ", arr[ind]);
        printf(COLOR_RESET);
    }
    printf("\n");

    printf("Left = <%d> Right = <%d>\n\n", LeftInd, RightInd);

    getchar();
}

WORK_RES my_qsort(int *arr, size_t sNum)
{
    assert(arr != NULL);

    size_t MidleInd = sNum/2;
    size_t LeftInd  = 0;
    size_t RightInd = sNum - 1;

    int BaseEl = arr[MidleInd];

    while (LeftInd < RightInd) {
        while (arr[LeftInd] < BaseEl) LeftInd++;
        ErrorPrint(arr, sNum, MidleInd, LeftInd, RightInd, "COME TO THE left el needed");

        while (arr[RightInd] >= BaseEl) RightInd--;
        ErrorPrint(arr, sNum, MidleInd, LeftInd, RightInd, "COME TO THE NEEDED COUPLE");

        int buff = arr[LeftInd];
        arr[LeftInd] = arr[RightInd];
        arr[RightInd] = buff;
        LeftInd++;
        RightInd--;

        ErrorPrint(arr, sNum, MidleInd, LeftInd, RightInd, "COUPLE OF ELEMENTS CHANGED");
    }
    
    ErrorPrint(arr, sNum, MidleInd, LeftInd, RightInd, "ALL LIST SORTED(almost)");

    return OK;
}
