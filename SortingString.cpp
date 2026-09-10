#include <stdio.h>
#include <string.h>
#include "basic.h"

const int STRNUM = 12;
const int STRLEN = 20;

/**
 * @brief sorts(bubble sort) array of strings with usage of huge buffer and rewriting all strings.
 * @param [out] text pointer to text(array) with lines.
 * @param [in] sLen len of one line.
 * @param [in] sNum number of lines.
 * @return result of work in terms of WORK_RES.
 */
WORK_RES FSlowStupidBubblesort(char *text, size_t sLen, size_t sNum);

/**
 * @brief sorts(bubble sort) array of strings with usage of one ell buffer and rewriting all strings.
 * @param [out] text pointer to text(array) with lines.
 * @param [in] sLen len of one line.
 * @param [in] sNum number of lines.
 * @return result of work in terms of WORK_RES.
 */
WORK_RES FFastStupidBubblesort(char *text, size_t sLen, size_t sNum);

/**
 * @brief sorts(bubble sort) array of strings with usage of unsigned long long technology.
 *
 * Idea is: we read data as unsigned long long and write it in this type. when amount of left symbols is to small we go to int, short, char.
 *
 * @param [out] text pointer to text(array) with lines.
 * @param [in] sLen len of one line.
 * @param [in] sNum number of lines.
 * @return result of work in terms of WORK_RES.
 */
WORK_RES FSuperFastStupidBubblesort(char *text, size_t sLen, size_t sNum);

#define SlowStupidBubblesort(text, sLen, sNum) FSlowStupidBubblesort((char *) text, sLen, sNum)
#define FastStupidBubblesort(text, sLen, sNum) FFastStupidBubblesort((char *) text, sLen, sNum)
#define SuperFastStupidBubblesort(text, sLen, sNum) FSuperFastStupidBubblesort((char *) text, sLen, sNum)

int main()
{
    char text[STRNUM][STRLEN] = {
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
    SuperFastStupidBubblesort(text, STRLEN, STRNUM);

    for (int i = 0; i < STRNUM; i++) {
        printf("%s\n", text[i]);
    }
}

WORK_RES FSlowStupidBubblesort(char *text, size_t sLen, size_t sNum)
{
    if (text == NULL) {
        printf("FSlowStupidBulsort felt: Text points to NULL");
        return WRIN;
    }

    char buff[sLen] = {};

    for (size_t n = 0; n < sNum - 1; n++) {
        for (size_t ch = 0; ch < sNum - 1 - n; ch++) {

            size_t ind = ch * sLen;
            if (strncmp(&text[ind], &text[ind + sLen], sLen) < 0) {

                strncpy(buff, &text[ind], sLen);
                strncpy(&text[ind], &text[ind + sLen], sLen);
                strncpy(&text[ind + sLen], buff, sLen);
            }
        }
    }

    return OK;
}

WORK_RES FFastStupidBubblesort(char *text, size_t sLen, size_t sNum)
{
    if (text == NULL) {
        printf("FFastStupidBulsort felt: Text points to NULL");
        return WRIN;
    }

    for (size_t n = 0; n < sNum - 1; n++) {
        for (size_t ch = 0; ch < sNum - 1 - n; ch++) {

            size_t ind = ch * sLen;
            if (strncmp(&text[ind], &text[ind + sLen], sLen) < 0) {

                for (size_t i = ind; i < ind + sLen; i++) {
                    if (text[i] == '\0' && text[i + sLen] == '\0') break;

                    char buff = text[i];
                    text[i] = text[i + sLen];
                    text[i + sLen] = buff;
                }
            }
        }
    }

    return OK;
}

WORK_RES FSuperFastStupidBubblesort(char *text, size_t sLen, size_t sNum)
{
    if (text == NULL) {
        printf("FSuperFastStupidBulsort felt: Text points to NULL");
        return WRIN;
    }
    if (sLen == 0 || sNum <= 1) {
        return OK;
    }

    unsigned long long buff = 0;

    for (size_t n = 0; n < sNum - 1; n++) {
        for (size_t ch = 0; ch < sNum - 1 - n; ch++) {

            char *indPtr = text + ch * sLen; // pointing to the first element of needed line
            if (strncmp(indPtr, (indPtr + sLen), sLen) < 0) {

                size_t realLen = 0;
                // first stage - fill main part
                while (realLen <= (int) sLen - sizeof(buff)) {
                    buff = *((unsigned long long *) (indPtr + realLen));
                    // change
                    *((unsigned long long *) (indPtr + realLen)) = *((unsigned long long *) (indPtr + sLen + realLen));
                    *((unsigned long long *) (indPtr + sLen + realLen)) = buff;
                    realLen += sizeof(buff);
                }

                // second stage - fill last part (max 7 bites)
                if (sLen - realLen >= sizeof(int)) {
                    int buffInt = *((int *) (indPtr + realLen));
                    *((int *) (indPtr + realLen)) = *((int *) (indPtr + sLen + realLen));
                    *((int *) (indPtr + sLen + realLen)) = buffInt;
                    realLen += sizeof(int);
                }
                if (sLen - realLen >= sizeof(short)) {
                    short buffShort = *((short *) (indPtr + realLen));
                    *((short *) (indPtr + realLen)) = *((short *) (indPtr + sLen + realLen));
                    *((short *) (indPtr + sLen + realLen)) = buffShort;
                    realLen += sizeof(short);
                }
                if (sLen - realLen == sizeof(char)) {
                    char buffChar = *((char *) (indPtr + realLen));
                    *((char *) (indPtr + realLen)) = *((char *) (indPtr + sLen + realLen));
                    *((char *) (indPtr + sLen + realLen)) = buffChar;
                    realLen += sizeof(char);
                }
            }
        }
        buff = 0;
    }

    return OK;
}


