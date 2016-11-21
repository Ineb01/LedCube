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
//#include <wiringPi.h>

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


int rgLedCube[LEDCUBESIDE][LEDCUBESIDE][LEDCUBESIDE]={1,0,0,   
                                                      0,0,0,  
                                                      0,0,0,

                                                      0,0,0,   
                                                      0,1,0,  
                                                      0,0,0,

                                                      1,0,0,
                                                      0,0,0, 
                                                      0,0,1};

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
    int temp;
    
    //clear();
    printf("\e[?25l");
    fp = fopen("Pattern.txt", "r");
    
    if(fp == NULL){
        printf("fail\n");
    }else{
        while((temp = fgetc(fp))!=EOF) {
		printf("%c ", temp);
	}
	fclose(fp);
    }
    
    printf("\e[?25l");
    
    /*thread_args[ 0 ] = 0;
    result_code = pthread_create(threads, NULL, PrintThread, thread_args);
    
    while(1){
        SetCube0();
        RandomCube(50);
        sleep(1);
    }*/
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
                if((rand() % 100+1)-(100-probability)>0)rgLedCube[i][j][k] = 1;
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

/*void ShowCube() {
    int i, j, k;
    for (i = 0; i < LEDCUBESIDE; i++) {
        digitalWrite(rgLayerID[i], LOW);
        for (j = 0; j < LEDCUBESIDE; j++) {
            for (k = 0; k < LEDCUBESIDE; k++) {
                if(rgLedCube[i][j][k]==1)digitalWrite(rgPillarID[j][k], LOW);
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
                    if(rgLedCube[i][j][k]==1)digitalWrite(rgPillarID[j][k], LOW);
                }
            }
            delay(5);
            all0();
        }
    }
}*/

void Rotate45left(){
    int ar[3];
    int i,j=0,k=0;
    
    for (i = 0; i < LEDCUBESIDE; i++) {
        ar[i] = rgLedCube[i][j][k];
    }
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k+1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k+1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j+1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j+1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k-1];
    }
    k--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k-1];
    }
    k--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j-1][k];
    }
    j--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = ar[i];
    }
}

void Rotate45right(){
    int ar[3];
    int i,j=0,k=0;
    
    for (i = 0; i < LEDCUBESIDE; i++) {
        ar[i] = rgLedCube[i][j][k];
    }
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j+1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j+1][k];
    }
    j++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k+1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k+1];
    }
    k++;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j-1][k];
    }
    j--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j-1][k];
    }
    j--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = rgLedCube[i][j][k-1];
    }
    k--;
    for (i = 0; i < LEDCUBESIDE; i++) {
        rgLedCube[i][j][k] = ar[i];
    }
}

/*void clear() {

    if (wiringPiSetup() == -1) return 1;
    pinMode(LAYER0, OUTPUT);
    pinMode(LAYER1, OUTPUT);
    pinMode(LAYER2, OUTPUT);
    pinMode(PILLAR1, OUTPUT);
    pinMode(PILLAR2, OUTPUT);
    pinMode(PILLAR3, OUTPUT);
    pinMode(PILLAR4, OUTPUT);
    pinMode(PILLAR5, OUTPUT);
    pinMode(PILLAR6, OUTPUT);
    pinMode(PILLAR7, OUTPUT);
    pinMode(PILLAR8, OUTPUT);
    pinMode(PILLAR9, OUTPUT);
    pinMode(TASTE1, INPUT);


    digitalWrite(LAYER0, HIGH);
    digitalWrite(LAYER1, HIGH);
    digitalWrite(LAYER2, HIGH);
    digitalWrite(PILLAR1, HIGH);
    digitalWrite(PILLAR2, HIGH);
    digitalWrite(PILLAR3, HIGH);
    digitalWrite(PILLAR4, HIGH);
    digitalWrite(PILLAR5, HIGH);
    digitalWrite(PILLAR6, HIGH);
    digitalWrite(PILLAR7, HIGH);
    digitalWrite(PILLAR8, HIGH);
    digitalWrite(PILLAR9, HIGH);

}

void all() {
    digitalWrite(LAYER0, LOW);
    digitalWrite(LAYER1, LOW);
    digitalWrite(LAYER2, LOW);
    digitalWrite(PILLAR1, LOW);
    digitalWrite(PILLAR2, LOW);
    digitalWrite(PILLAR3, LOW);
    digitalWrite(PILLAR4, LOW);
    digitalWrite(PILLAR5, LOW);
    digitalWrite(PILLAR6, LOW);
    digitalWrite(PILLAR7, LOW);
    digitalWrite(PILLAR8, LOW);
    digitalWrite(PILLAR9, LOW);
}

void all0() {
    digitalWrite(LAYER0, HIGH);
    digitalWrite(LAYER1, HIGH);
    digitalWrite(LAYER2, HIGH);
    digitalWrite(PILLAR1, HIGH);
    digitalWrite(PILLAR2, HIGH);
    digitalWrite(PILLAR3, HIGH);
    digitalWrite(PILLAR4, HIGH);
    digitalWrite(PILLAR5, HIGH);
    digitalWrite(PILLAR6, HIGH);
    digitalWrite(PILLAR7, HIGH);
    digitalWrite(PILLAR8, HIGH);
    digitalWrite(PILLAR9, HIGH);

}*/