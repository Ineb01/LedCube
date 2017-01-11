/* 
 * File:   general.c
 * Author: Benjamin Bachmayr
 *
 * Created on 11. Jänner 2017, 22:07
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef PINHEAD26 
#include "pinhead26.h"
#endif
#ifdef PINHEAD40 
#include "pinhead40.h"
#endif
#ifdef DEBUG
#include "console.h"
#endif

extern int rgLedCube[LEDCUBESIDE][LEDCUBESIDE][LEDCUBESIDE];

void RandomCube(int probability) {
    int i, j, k;
    for (i = 0; i < LEDCUBESIDE; i++) {
        for (j = 0; j < LEDCUBESIDE; j++) {
            for (k = 0; k < LEDCUBESIDE; k++) {
                if ((rand() % 100 + 1)-(100 - probability) > 0)rgLedCube[i][j][k] = 1;
            }
        }
    }
}

void RandomLed() {
    rgLedCube[rand() % LEDCUBESIDE][rand() % LEDCUBESIDE][rand() % LEDCUBESIDE] = 1;
}

void SetCube0() {
    int i, j, k;
    for (i = 0; i < LEDCUBESIDE; i++) {
        for (j = 0; j < LEDCUBESIDE; j++) {
            for (k = 0; k < LEDCUBESIDE; k++) {
                rgLedCube[i][j][k] = 0;
            }
        }
    }
}

void Rotate45left() {
    int ar[LEDCUBESIDE];
    int i, j = 0, k = 0;

    for (i = 0; i < LEDCUBESIDE; i++) {
        ar[i] = rgLedCube[i][j][k];
    }
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k + 1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k + 1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j + 1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j + 1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k - 1];
    }
    k--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k - 1];
    }
    k--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j - 1][k];
    }
    j--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = ar[i];
    }
}

void Rotate45right() {
    int ar[LEDCUBESIDE];
    int i, j = 0, k = 0;

    for (i = 0; i < LEDCUBESIDE; i++) {
        ar[i] = rgLedCube[i][j][k];
    }
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j + 1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j + 1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k + 1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k + 1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j - 1][k];
    }
    j--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j - 1][k];
    }
    j--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k - 1];
    }
    k--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = ar[i];
    }
}