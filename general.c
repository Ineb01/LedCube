/*----------------------------------------------------------------------
 *            Hoehere Technische Bundeslehranstalt STEYR
 *         Fachrichtung Elektronik und Technische Informatik
 *---------------------------------------------------------------------*/

/**
 * Kurzbeschreibung
 *  
 * @author  : Bachmayr, Faller
 *            2BHEL
 * @date    : 11. Jänner 2017
 * File     : general.c
 * 
 * @details
 *   
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef PINHEAD40 
#include "pinhead40.h"
#endif

#ifdef PINHEAD26 
#include "pinhead26.h"
#endif

#ifdef DEBUG
#include "console.h"
#endif


// Pattern is used to read a whole ledcube-pattern from the file.
// Syntax P
// 1 = HIGH; 0 = LOW
// A whitespace is needed after every single number.
#define PATTERN 'P'

// Marker is used to remember a position.
// Syntax M <x>
// x .... Marker Number x
#define MARKER 'M'
#define MAX_MARKER 3

// Jumper is used to jump back to the Marker with the same index.
// Syntax J <x>
#define JUMPER 'J'

// Rotate right is used to rotate the cube 45° to the right.
// Syntax RR
#define ROTATE_RIGHT 'R'

// Rotate left is used to rotate the cube 45° to the left.
// Syntax RL
#define ROTATE_LEFT 'L'

// Random cube is used to set a random cube with a probability of <x> [percent]
// for every LED to be on.
// Syntax RC
// x [next linie in the file] .... probability for each LED
#define RANDOM_CUBE 'C'

// Random diode is used to turn on a random LED
// Syntax RD
#define RANDOM_DIODE 'D'

// Delay is used to wait after an action.
// Syntax D
// x [next linie in the file] .... Delay in milliseconds
#define DELAY 'D'


extern int rgLedCube[LEDCUBESIDE][LEDCUBESIDE][LEDCUBESIDE];

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

void RandomCube(int probability) {
    int i, j, k;
    SetCube0();
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