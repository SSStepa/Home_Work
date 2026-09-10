/**
 * @file basic.h
 * @brief structs, consts and funcs i use daily.
 */
#ifndef BASIC_H
#define BASIC_H
/**
 * @brief Work of function avalible results.
 */
enum WORK_RES {
    OK = 0, // all good
    WRIN = 1, // function got bad args

};

/**
 * Basic colors
 */
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

#endif
