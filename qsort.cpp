#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "basic.h"

WORK_RES my_qsortInt(int *arr, size_t arrLen);
void ErrorPrint(int *arr, size_t arrLen, size_t MidleInd, size_t LeftInd, size_t RightInd, const char *Place);

WORK_RES Test_my_qsortInt();

#define NUMLEN 14
#define TESTNUM 50;

int main()
{
    int Nums[NUMLEN] = {234, 10, 11, 100, 200, 5, 45, 50, 40, 49, 15, 60, 10, 70};

    my_qsortInt(Nums, NUMLEN);

    for (int n = 0; n < NUMLEN; n++) {
        printf("%d ", Nums[n]);
    }
}



WORK_RES my_qsortInt(int *arr, size_t arrLen)
{
    assert(arr != NULL);
    
    if (arrLen < 2) {
        return OK;

    } 
    else {
        size_t MidleInd = arrLen/2;
        size_t LeftInd  = 0;
        size_t RightInd = arrLen - 1;

        int BaseEl = arr[MidleInd];

        while (LeftInd < RightInd) {
            while (LeftInd < arrLen && arr[LeftInd] < BaseEl) {
                LeftInd++;
            }

            // ErrorPrint(arr, arrLen, MidleInd, LeftInd, RightInd, "COME TO THE left el needed");
            assert(0 <= LeftInd && LeftInd < arrLen);

            while (RightInd > 0 && arr[RightInd] > BaseEl ) {
                    RightInd--;
            }

            if (LeftInd >= RightInd) break;

            // ErrorPrint(arr, arrLen, MidleInd, LeftInd, RightInd, "COME TO THE NEEDED COUPLE");
            assert(0 <= RightInd && RightInd < arrLen);

            int buff = arr[LeftInd];
            arr[LeftInd] = arr[RightInd];
            arr[RightInd] = buff;

            LeftInd++;
            if (RightInd > 0)
                RightInd--;
            else break;

            assert(0 <= LeftInd  && LeftInd  <= arrLen);
            assert(0 <= RightInd && RightInd <= arrLen);
            // ErrorPrint(arr, arrLen, MidleInd, LeftInd, RightInd, "COUPLE OF ELEMENTS CHANGED");
        }
        
        // ErrorPrint(arr, arrLen, MidleInd, LeftInd, RightInd, "ALL LIST SORTED(almost)");
        // Call only if something is in the left of right.
        if (RightInd > 0)
            my_qsortInt(arr, LeftInd);
        // call only if something is in the right of left.
        if (LeftInd < arrLen) 
            my_qsortInt(arr + LeftInd, arrLen - LeftInd);
        
        return OK;
    }
}

void ErrorPrint(int *arr, size_t arrLen, size_t MidleInd, size_t LeftInd, size_t RightInd, const char *Place)
{
    printf("%s\n", Place);

    for (size_t ind= 0; ind < arrLen; ind++) {
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
        else if (ind < arrLen)
            printf(RED);
        else 
            printf(RED "OUT OF RANGE!!!!");
        
        printf("%d ", arr[ind]);
        printf(COLOR_RESET);
    }
    printf("\n");

    printf("Left = <%d> Right = <%d> ArrLen = <%d>\n", LeftInd, RightInd, arrLen);

    getchar();
}