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
#ifndef CONSOLE_H
#define CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define THREAD PrintThread
#define LEDCUBESIDE 3

void PrintCube();
void* PrintThread();

#ifdef __cplusplus
}
#endif

#endif /* %<%GUARD_NAME%>% */