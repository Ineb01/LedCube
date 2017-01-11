/*----------------------------------------------------------------------
 *            Hoehere Technische Bundeslehranstalt STEYR
 *         Fachrichtung Elektronik und Technische Informatik
 *---------------------------------------------------------------------*/

/**
 * Kurzbeschreibung
 *  
 * @author  : Maximilian Faller
 *            2BHEL
 * @date    : 11. Jänner 2017
 * File     : main.c
 * 
 * @details
 *   
 */
#ifndef LEDCUBE_H
#define LEDCUBE_H

#ifdef __cplusplus
extern "C" {
#endif


void ShowCube();
void* ShowThread();
void Setup();
void All();
void All0();


#ifdef __cplusplus
}
#endif

#endif /* LEDCUBE_H */