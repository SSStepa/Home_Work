#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

WORK_RES my_qsort(void *arr, size_t arrLen, size_t size, int (* comp)(const void *, const void *));
WORK_RES SwapElls(unsigned char *firstPtr, unsigned char *secondPtr, size_t size);
unsigned char *Partition(unsigned char *LeftInd,unsigned char *RightInd, size_t elSize, int (*comp)(const void *, const void *));

WORK_RES my_qsortInt(int *arr, size_t arrLen);
void ErrorPrint(int *arr, size_t arrLen, size_t MidleInd, size_t LeftInd, size_t RightInd, const char *Place);

const int NUMLEN = 10;
const int STRNUM = 12;
const int STRLEN = 20;

// TODO обернуть в функцию а не макрос
#define MacroChangeMamory(buff, type, firstPl, secondPl) \
    buff = *((type *) (firstPl)); \
    *((type *) (firstPl)) = *((type *) (secondPl)); \
    *((type *) (secondPl)) = buff; \
    firstPl += sizeof(buff); \
    secondPl += sizeof(buff);

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
    int Nums[NUMLEN] = {35, 10, 25, 23, 1, 15, 2, 1, 1, 1};
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

    printf("\n");

    for (int i = 0; i < STRNUM; i++) {
        printf("%s\n", text[i]);
    }
}

WORK_RES my_qsort(void *arr, size_t arrLen, size_t elSize, int (* comp)(const void *, const void *))
{
    assert(arr != NULL);
    assert(elSize > 0);
    assert(comp != NULL);
    
    if (arrLen < 2) 
        return OK;
    
    unsigned char *divider = Partition((unsigned char *) arr, (unsigned char *) arr + (arrLen - 1) * elSize, elSize, comp);
    
    if (divider > (unsigned char *) arr)
        my_qsort(arr, (divider - (unsigned char *) arr)/elSize, elSize, comp);

    if (divider < (unsigned char *) arr + arrLen * elSize) 
        my_qsort((void *) divider, arrLen - (divider - (unsigned char *) arr)/elSize, elSize, comp);
    
    return OK;

}



unsigned char *Partition(unsigned char *LeftPtr, unsigned char *RightPtr, size_t elSize, int (*comp)(const void *, const void *))
{
    assert(LeftPtr != NULL);
    assert(RightPtr != NULL);
    assert(comp != NULL);
    assert(elSize > 0);

    unsigned char *BaseElPtr = LeftPtr + ((RightPtr - LeftPtr)/2/elSize) * elSize; // /elSize * elSize to have num of ells 

    while (LeftPtr <= RightPtr) {
        while (LeftPtr < RightPtr && (*comp)((void *) LeftPtr, (void *) BaseElPtr) < 0)
            LeftPtr += elSize;

        while (RightPtr > LeftPtr && (*comp)((void *) RightPtr, (void *) BaseElPtr) > 0)
            RightPtr -= elSize;

        if      (LeftPtr  == BaseElPtr) BaseElPtr = RightPtr;
        else if (RightPtr == BaseElPtr) BaseElPtr = LeftPtr;

        SwapElls(LeftPtr, RightPtr, elSize);

        LeftPtr += elSize;
        RightPtr -= elSize;
    }
    return LeftPtr;
}

WORK_RES SwapElls(unsigned char *firstPtr, unsigned char *secondPtr, size_t elSize)
{
    assert(firstPtr != NULL);
    assert(secondPtr != NULL);
    assert(elSize > 0);

    unsigned long long buff = 0;
    int buffInt = 0;
    short buffShort = 0;
    char buffChar = 0;

    // first stage - fill main part
    while (elSize/sizeof(buff) > 0) {
        MacroChangeMamory(buff, unsigned long long, firstPtr, secondPtr);       
        elSize -= sizeof(buff);
    }

    // second stage - fill last part (max 7 bites)
    if (elSize >= sizeof(int)) {
        MacroChangeMamory(buffInt, int, firstPtr, secondPtr);
        elSize -= sizeof(int);
    }

    if (elSize >= sizeof(short)) {
        MacroChangeMamory(buffShort, short, firstPtr, secondPtr);
        elSize -= sizeof(short);
    }

    if (elSize == sizeof(char)) {
        MacroChangeMamory(buffChar, char, firstPtr, secondPtr);
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
