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
    if (wiringPiSetup() == -1) return 1;
    Setup();
#endif

    srand(time(NULL));

    pthread_t thread;
    pthread_create(&thread, NULL, THREAD, NULL);
    /*
    int i, j, k;

    FILE *fp = NULL;
    
    while (1) {
        //fp = fopen("Pattern.txt", "rt");
        fp = fopen("/var/www/html/ledcube/Pattern.txt", "rt");
        if (fp != NULL) {
            for (i = 0; i < LEDCUBESIDE; i++) {
                for (j = 0; j < LEDCUBESIDE; j++) {
                    for (k = 0; k < LEDCUBESIDE; k++) {
                        fscanf(fp, "%d", &rgLedCube[i][j][k]);
                    }
                }
            }
            fclose(fp);
        }
    }*/
    int i, j, k;
    signed char input = '0';
    int delay, probability, id;
    long int marker[MAX_MARKER];
    int count[3] = {0, 0, 0};
    int control[3] = {0, 0, 0};
    
    FILE *fp = NULL;

    //fp = fopen("Pattern.txt", "rt");
    fp = fopen("/var/www/html/ledcube/Pattern.txt", "rt");

    if (fp != NULL) {
        fclose(fp);
        printf("\e[?25l");

        do {
            fp = fopen("/var/www/html/ledcube/Pattern.txt", "rt");
            fscanf(fp, "%c", &input);

            switch (input) {
                case PATTERN:
                    for (i = 0; i < LEDCUBESIDE; i++) {
                        for (j = 0; j < LEDCUBESIDE; j++) {
                            for (k = 0; k < LEDCUBESIDE; k++) {
                                fscanf(fp, "%d", &rgLedCube[i][j][k]);
                            }
                        }
                    }
                    break;
                case MARKER:
                    fscanf(fp, "%d", &id);
                    marker[id] = ftell(fp);
                    break;
                case JUMPER:
                    fscanf(fp, "%d", &id);
                    if (control[id] == 0) {
                        control[id] = 1;
                        fscanf(fp, "%d", &count[id]);
                    }
                    if (count[id]) {
                        fseek(fp, marker[id], SEEK_SET);
                        count[id]--;
                    } else {
                        control[id] = 0;
                    }
                    break;
                case 'R':
                    fscanf(fp, "%c", &input);
                    switch (input) {
                        case ROTATE_RIGHT:
                            Rotate45right();
                            break;
                        case ROTATE_LEFT:
                            Rotate45left();
                            break;
                        case RANDOM_CUBE:
                            fscanf(fp, "%d", &probability);
                            RandomCube(probability);
                            break;
                        case RANDOM_DIODE:
                            RandomLed();
                            break;
                        default:
                            break;
                    }
                    break;
                case DELAY:
                    fscanf(fp, "%d", &delay);
                    usleep(delay * 1000);
                    break;
                default:
                    break;
            }
            fclose(fp);
        } while (input != 'E');

        
    }

    return (EXIT_SUCCESS);
}