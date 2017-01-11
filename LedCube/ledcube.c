/* 
 * File:   ledcube.c
 * Author: Benjamin Bachmayr
 *
 * Created on 11. Jänner 2017, 21:58
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef LEDCUBE_H
#include "ledcube.h"
#endif

#ifdef LEDCUBE_H
#include <wiringPi.h>
#endif

#ifdef PINHEAD26
#include "pinhead26.h"
#endif
#ifdef PINHEAD40
#include "pinhead40.h"
#endif

#ifdef LEDCUBE_H
extern int rgLayerID[LEDCUBESIDE] = {LAYER0, LAYER1, LAYER2};
extern int rgPillarID[LEDCUBESIDE][LEDCUBESIDE] = {PILLAR1, PILLAR2, PILLAR3,
                                            PILLAR4, PILLAR5, PILLAR6,
                                            PILLAR7, PILLAR8, PILLAR9};
#endif


#ifdef LEDCUBE_H

extern int rgLedCube[LEDCUBESIDE][LEDCUBESIDE][LEDCUBESIDE];

void ShowCube() {
    int i, j, k;
    for (i = 0; i < LEDCUBESIDE; i++) {
        digitalWrite(rgLayerID[i], LOW);
        for (j = 0; j < LEDCUBESIDE; j++) {
            for (k = 0; k < LEDCUBESIDE; k++) {
                if (rgLedCube[i][j][k] == 1)digitalWrite(rgPillarID[j][k], LOW);
            }
        }
        All0();
    }
}

void* ShowThread() {
    int i, j, k;
    while (1) {
        for (i = 0; i < LEDCUBESIDE; i++) {
            digitalWrite(rgLayerID[i], LOW);
            for (j = 0; j < LEDCUBESIDE; j++) {
                for (k = 0; k < LEDCUBESIDE; k++) {
                    if (rgLedCube[i][j][k] == 1)digitalWrite(rgPillarID[j][k], LOW);
                }
            }
            delay(5);
            All0();
        }
    }
}

void Setup() {
    int i, j, k;

    for (j = 0; j < LEDCUBESIDE; j++) {
        for (k = 0; k < LEDCUBESIDE; k++) {
            pinMode(rgPillarID[j][k], OUTPUT);
            digitalWrite(rgPillarID[j][k], LOW);
        }
    }
    for (i = 0; i < LEDCUBESIDE; i++) {
        pinMode(rgLayerID[i], OUTPUT);
        digitalWrite(rgLayerID[i], LOW);
    }
    pinMode(TASTE1, INPUT);
}

void All() {
    int i, j, k;

    for (j = 0; j < LEDCUBESIDE; j++) {
        for (k = 0; k < LEDCUBESIDE; k++) {
            digitalWrite(rgPillarID[j][k], LOW);
        }
    }
    for (i = 0; i < LEDCUBESIDE; i++) {
        digitalWrite(rgLayerID[i], LOW);
    }
}

void All0() {
    int i, j, k;

    for (j = 0; j < LEDCUBESIDE; j++) {
        for (k = 0; k < LEDCUBESIDE; k++) {
            digitalWrite(rgPillarID[j][k], HIGH);
        }
    }
    for (i = 0; i < LEDCUBESIDE; i++) {
        digitalWrite(rgLayerID[i], HIGH);
    }
}
#endif