/* 
 * File:   console.c
 * Author: Benjamin Bachmayr
 *
 * Created on 11. Jänner 2017, 21:56
 */

#include <stdio.h>
#include <stdlib.h>
#include "console.h"

extern int rgLedCube[LEDCUBESIDE][LEDCUBESIDE][LEDCUBESIDE];

void PrintCube() {
    printf("\033[%d;%dH", 0, 0);
    int i, j, k;
    for (k = 0; k < LEDCUBESIDE; k++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < LEDCUBESIDE; i++) {
        for (j = 0; j < LEDCUBESIDE; j++) {
            for (k = 0; k < LEDCUBESIDE; k++) {

                if (rgLedCube[i][j][k] == 1) {
                    printf("#");
                } else {
                    printf(" ");
                }

            }
            printf("\n");
        }
        for (k = 0; k < LEDCUBESIDE; k++) {
            printf("-");
        }
        printf("\n");
    }
}

void* PrintThread() {
    while (1) {
        printf("\033[%d;%dH", 0, 0);
        int i, j, k;
        for (k = 0; k < LEDCUBESIDE; k++) {
            printf("-");
        }
        printf("\n");
        for (i = 0; i < LEDCUBESIDE; i++) {
            for (j = 0; j < LEDCUBESIDE; j++) {
                for (k = 0; k < LEDCUBESIDE; k++) {

                    if (rgLedCube[i][j][k] == 1) {
                        printf("#");
                    } else {
                        printf(" ");
                    }

                }
                printf("\n");
            }
            for (k = 0; k < LEDCUBESIDE; k++) {
                printf("-");
            }
            printf("\n");
        }
    }

}