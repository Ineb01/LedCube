/*----------------------------------------------------------------------
 *            Hoehere Technische Bundeslehranstalt STEYR
 *         Fachrichtung Elektronik und Technische Informatik
 *---------------------------------------------------------------------*/

/**
 * Kurzbeschreibung
 *  
 * @author  : Maximilian Faller
 *            2BHEL
 * @date    : %<%DATE%>%
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

#endif /* %<%GUARD_NAME%>% */