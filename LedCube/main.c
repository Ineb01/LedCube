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

#include "general.h"

#ifdef PINHEAD40
#include "pinhead40.h"
#include "ledcube.h"
#endif

#ifdef PINHEAD26
#include "pinhead26.h"
#include "ledcube.h"
#endif

#ifdef DEBUG
#include "console.h"
#endif

#ifdef LEDCUBE_H
int rgLayerID[LEDCUBESIDE] = {LAYER0, LAYER1, LAYER2};
int rgPillarID[LEDCUBESIDE][LEDCUBESIDE] = {PILLAR1, PILLAR2, PILLAR3,
                                            PILLAR4, PILLAR5, PILLAR6,
                                            PILLAR7, PILLAR8, PILLAR9};
#endif

int rgLedCube[LEDCUBESIDE][LEDCUBESIDE][LEDCUBESIDE];

int main(int argc, char** argv) {
    
#ifdef LEDCUBE_H
    Setup();
    if(wiringPiSetup() == -1) return 1;
#endif
    
    srand(time(NULL));
    
    pthread_t thread;
    pthread_create(&thread, NULL, THREAD, NULL);
    
    FILE *fp = NULL;
    
    int i, j, k;
    
    fp = fopen("Pattern.txt", "rt");
    
    if(fp != NULL){
        printf("\e[?25l");

        for (i = 0; i < LEDCUBESIDE; i++) {
            for (j = 0; j < LEDCUBESIDE; j++) {
                for (k = 0; k < LEDCUBESIDE; k++) {
                    fscanf(fp, "%d", &rgLedCube[i][j][k]);
                }
            }
        }

        fclose(fp);
    }
    
    while (1) {
        delay(600);
        RandomCube(50);
        //SetCube0;
    }
    
    return (EXIT_SUCCESS);
}