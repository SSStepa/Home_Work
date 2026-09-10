#include <stdio.h>
#include <string.h>
#include "basic.h"

const int STRNUM = 12;
const int STRLEN = 20;

/**
 * @brief sorts(bubble sort) array of strings with usage of huge buffer and rewriting all strings.
 * @param [out] text pointer to text(array) with lines.
 * @param [in] sSize len of one line.
 * @param [in] sNum number of lines.
 * @return result of work in terms of WORK_RES.
 */
WORK_RES FSlowStupidBubblesort(char *text, size_t sSize, size_t sNum);

/**
 * @brief sorts(bubble sort) array of strings with usage of one ell buffer and rewriting all strings.
 * @param [out] text pointer to text(array) with lines.
 * @param [in] sSize len of one line.
 * @param [in] sNum number of lines.
 * @return result of work in terms of WORK_RES.
 */
WORK_RES FFastStupidBubblesort(char *text, size_t sSize, size_t sNum);

/**
 * @brief sorts(bubble sort) array of strings with usage of unsigned long long technology.
 *
 * Idea is: we read data as unsigned long long and write it in this type. when amount of left symbols is to small we go to int, short, char.
 *
 * @param [out] text pointer to text(array) with lines.
 * @param [in] sSize len of one line.
 * @param [in] sNum number of lines.
 * @return result of work in terms of WORK_RES.
 */
WORK_RES FSuperFastStupidBubblesort(char *text, size_t sSize, size_t sNum);

WORK_RES FastCleverBubbleSort(const char *text[], size_t sNum);

#define SlowStupidBubblesort(text, sSize, sNum) FSlowStupidBubblesort((char *) text, sSize, sNum)
#define FastStupidBubblesort(text, sSize, sNum) FFastStupidBubblesort((char *) text, sSize, sNum)
#define SuperFastStupidBubblesort(text, sSize, sNum) FSuperFastStupidBubblesort((char *) text, sSize, sNum)

#define SwapElls(buff, type) \
    buff = *((type *) (indPtr + realLen)); \
    *((type *) (indPtr + realLen)) = *((type *) (indPtr + sSize + realLen)); \
    *((type *) (indPtr + sSize + realLen)) = buff; \
    realLen += sizeof(buff); 

int main()
{
    const char *text[] = {
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

    // SlowStupidBubblesort(text, STRLEN, STRNUM);
    // FastStupidBubblesort(text, STRLEN, STRNUM);
    // SuperFastStupidBubblesort(text, STRLEN, STRNUM);
    FastCleverBubbleSort(text, STRNUM);

    for (int i = 0; i < STRNUM; i++) {
        printf("%s\n", text[i]);
    }
}

WORK_RES FSlowStupidBubblesort(char *text, size_t sSize, size_t sNum)
{
    if (text == NULL) {
        printf("FSlowStupidBulsort felt: Text points to NULL");
        return WRIN;
    }
    if (sSize == 0 || sNum <= 1) {
        return OK;
    }

    char buff[sSize] = {};

    for (size_t n = 0; n < sNum - 1; n++) {
        for (size_t ch = 0; ch < sNum - 1 - n; ch++) {

            size_t ind = ch * sSize;
            if (strncmp(&text[ind], &text[ind + sSize], sSize) < 0) {

                strncpy(buff, &text[ind], sSize);
                strncpy(&text[ind], &text[ind + sSize], sSize);
                strncpy(&text[ind + sSize], buff, sSize);
            }
        }
    }

    return OK;
}

WORK_RES FFastStupidBubblesort(char *text, size_t sSize, size_t sNum)
{
    if (text == NULL) {
        printf("FFastStupidBulsort felt: Text points to NULL");
        return WRIN;
    }
    if (sSize == 0 || sNum <= 1) {
        return OK;
    }

    for (size_t n = 0; n < sNum - 1; n++) {
        for (size_t ch = 0; ch < sNum - 1 - n; ch++) {

            size_t ind = ch * sSize;
            if (strncmp(&text[ind], &text[ind + sSize], sSize) < 0) {

                for (size_t i = ind; i < ind + sSize; i++) {
                    if (text[i] == '\0' && text[i + sSize] == '\0') break;

                    char buff = text[i];
                    text[i] = text[i + sSize];
                    text[i + sSize] = buff;
                }
            }
        }
    }

    return OK;
}

WORK_RES FSuperFastStupidBubblesort(char *text, size_t sSize, size_t sNum)
{
    if (text == NULL) {
        printf("FSuperFastStupidBulsort felt: Text points to NULL");
        return WRIN;
    }
    if (sSize == 0 || sNum <= 1) {
        return OK;
    }

    unsigned long long buff = 0;
    int buffInt = 0;
    short buffShort = 0;
    char buffChar = 0;

    for (size_t n = 0; n < sNum - 1; n++) {
        for (size_t ch = 0; ch < sNum - 1 - n; ch++) {

            char *indPtr = text + ch * sSize; // pointing to the first element of needed line
            if (strncmp(indPtr, (indPtr + sSize), sSize) < 0) {

                size_t realLen = 0;
                // first stage - fill main part
                while (realLen + sizeof(buff) <= sSize) {
                    SwapElls(buff, unsigned long long);       
                }

                // second stage - fill last part (max 7 bites)
                if (sSize - realLen >= sizeof(int)) {
                    SwapElls(buffInt, int);
                }

                if (sSize - realLen >= sizeof(short)) {
                    SwapElls(buffShort, short);
                }

                if (sSize - realLen == sizeof(char)) {
                    SwapElls(buffChar, char);
                }
            }
        }
    }

    return OK;
}

WORK_RES FastCleverBubbleSort(const char *text[], size_t sNum)
{
    if (text == NULL) {
        printf("FastCleverBulsort felt: Text points to NULL");
        return WRIN;
    }
    if (sNum <= 1) {
        return OK;
    }

    for (size_t n = 0; n < sNum - 1; n++) {
        for (size_t ch = 0; ch < sNum - 1 - n; ch++) {
            if (strncmp(text[ch], text[ch + 1], STRLEN) < 0) {

                const char *buff = text[ch];
                text[ch] = text[ch + 1];
                text[ch + 1] = buff;
            }  
        }   
    }
    
    return OK;
}
