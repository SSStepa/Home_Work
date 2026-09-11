#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

WORK_RES my_qsortInt(int *arr, size_t arrLen);
WORK_RES my_qsort(void *arr, size_t arrLen, size_t size, int (* comp)(const void *, const void *));
WORK_RES SwapElls(size_t firstPtr, size_t secondPtr, size_t size);
void ErrorPrint(int *arr, size_t arrLen, size_t MidleInd, size_t LeftInd, size_t RightInd, const char *Place);

const int NUMLEN = 14;
const int STRNUM = 12;
const int STRLEN = 20;

// TODO обернуть в функцию а не макрос
#define MacroSwapElls(buff, type) \
    buff = *((type *) (firstPtr + realLen)); \
    *((type *) (firstPtr + realLen)) = *((type *) (secondPtr + realLen)); \
    *((type *) (secondPtr + realLen)) = buff; \
    realLen += sizeof(buff);

int CompInt(const void *firstPtr, const void *secondPtr)
{
    int first  = *((int *) firstPtr);
    int second = *((int *) secondPtr);
    return first - second;
}

int CompStr(const void *firstPtr, const void *secondPtr)
{
    return strcmp((char *) firstPtr, (char *) secondPtr);
}

int main()
{
    int Nums[NUMLEN] = {234, 10, 11, 100, 200, 5, 45, 50, 40, 49, 15, 60, 10, 70};
    const char text[STRNUM][STRLEN] = {
        "zaz",
        "zaa",
        "x",
        "hh",
        "ah",
        "hah",
        "z",
        "b",
        "a",
        "hi my name is stepa",
        "hi my name is sophy",
        "hi my name is nikit"
    };

    my_qsort(Nums, NUMLEN, sizeof(int), CompInt);
    my_qsort((void*) text, STRNUM, STRLEN, CompStr);

    for (int n = 0; n < NUMLEN; n++) {
        printf("%d ", Nums[n]);
    }
    for (int i = 0; i < STRNUM; i++) {
        printf("%s\n", text[i]);
    }
}

WORK_RES my_qsort(void *arr, size_t arrLen, size_t size, int (* comp)(const void *, const void *))
{
    assert(arr != NULL);
    
    if (arrLen < 2) 
        return OK;

    size_t LeftInd  = (size_t) arr;
    size_t RightInd = (size_t) arr + (arrLen - 1) * size;
    size_t BaseEl   = (size_t) arr + arrLen/2 * size;

    while (LeftInd < RightInd) {
        while (LeftInd < (size_t) arr + arrLen * size  && (*comp)((void *) LeftInd, (void *) BaseEl) < 0)
            LeftInd += size;

        assert((size_t) arr <= LeftInd && LeftInd <(size_t) arr + arrLen * size);

        while (RightInd > (size_t) arr && (*comp)((void *) RightInd, (void *) BaseEl) > 0)
            RightInd -= size;

        if (LeftInd >= RightInd) break;

        if      (LeftInd  == BaseEl) BaseEl = RightInd;
        else if (RightInd == BaseEl) BaseEl = LeftInd;

        assert((size_t) arr <= RightInd && RightInd <(size_t) arr + arrLen * size);

        SwapElls(LeftInd, RightInd, size);

        LeftInd += size;
        if (RightInd > (size_t) arr)
            RightInd -= size;
        else break;

        assert((size_t) arr <= LeftInd  && LeftInd  <= (size_t) arr + arrLen * size);
        assert((size_t) arr <= RightInd && RightInd <= (size_t) arr + arrLen * size);
    }
    
    if (RightInd > 0)
        my_qsort(arr, (LeftInd - (size_t) arr)/size, size, comp);

    if (LeftInd <(size_t) arr + arrLen*size) 
        my_qsort((void *) LeftInd, arrLen - (LeftInd - (size_t) arr)/size, size, comp);
    
    return OK;

}

WORK_RES SwapElls(size_t firstPtr, size_t secondPtr, size_t size)
{
    unsigned long long buff = 0;
    int buffInt = 0;
    short buffShort = 0;
    char buffChar = 0;


    size_t realLen = 0;
    
    // first stage - fill main part
    while (realLen + sizeof(buff) <= size) {
        MacroSwapElls(buff, unsigned long long);       
    }

    // second stage - fill last part (max 7 bites)
    if (size - realLen >= sizeof(int)) {
        MacroSwapElls(buffInt, int);
    }

    if (size - realLen >= sizeof(short)) {
        MacroSwapElls(buffShort, short);
    }

    if (size - realLen == sizeof(char)) {
        MacroSwapElls(buffChar, char);
    }

    return OK;
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

