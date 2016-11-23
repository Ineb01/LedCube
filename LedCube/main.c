/*----------------------------------------------------------------------
 *            Hoehere Technische Bundeslehranstalt STEYR
 *         Fachrichtung Elektronik und Technische Informatik
 *---------------------------------------------------------------------*/

/**
 * Kurzbeschreibung
 *  
 * @author  : Bachmayr, Faller
 *            2BHEL
 * @date    : 21. November 2016
 * File     : main.c
 * 
 * @details
 *   
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <wiringPi.h>

#include "define.h"


void PrintCube();
void* PrintThread();
void RandomCube(int probability);
void RandomLed();
void SetCube0();
void ShowCube();
void* ShowThread();
void Rotate45left();
void Rotate45right();

void clear();
void all();
void all0();


int rgLedCube[LEDCUBESIDE][LEDCUBESIDE][LEDCUBESIDE];

int rgLayerID[LEDCUBESIDE] = {LAYER0, LAYER1, LAYER2};
int rgPillarID[LEDCUBESIDE][LEDCUBESIDE] = {PILLAR1, PILLAR2, PILLAR3,
    PILLAR4, PILLAR5, PILLAR6,
    PILLAR7, PILLAR8, PILLAR9};

int main(int argc, char** argv) {

    srand(time(NULL));

    pthread_t threads[ 1 ];
    int thread_args[ 1 ];
    int result_code;
    FILE *fp;
    int i, j, k;

    clear();
    printf("\e[?25l");
    fp = fopen("Pattern.txt", "r");

    for (i = 0; i < LEDCUBESIDE; i++) {
        for (j = 0; j < LEDCUBESIDE; j++) {
            for (k = 0; k < LEDCUBESIDE; k++) {
                fscanf(fp, "%d", &rgLedCube[i][j][k]);
            }
        }
    }

    fclose(fp);

    thread_args[ 0 ] = 0;
    result_code = pthread_create(threads, NULL, ShowThread, thread_args);

    while (1) {
        sleep(1);
        Rotate45right();
    }
    return (EXIT_SUCCESS);
}

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

void ShowCube() {
    int i, j, k;
    for (i = 0; i < LEDCUBESIDE; i++) {
        digitalWrite(rgLayerID[i], LOW);
        for (j = 0; j < LEDCUBESIDE; j++) {
            for (k = 0; k < LEDCUBESIDE; k++) {
                if (rgLedCube[i][j][k] == 1)digitalWrite(rgPillarID[j][k], LOW);
            }
        }
        all0();
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
            all0();
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

void clear() {
    if (wiringPiSetup() == -1) return 1;
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

void all() {
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

void all0() {
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