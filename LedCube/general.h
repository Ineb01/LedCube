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
 * File     : general.h
 * 
 * @details
 *   
 */
#ifndef GENERAL_H
#define GENERAL_H

#ifdef __cplusplus
extern "C" {
#endif

    
void SetCube0();
void RandomCube(int probability);
void RandomLed();
void Rotate45left();
void Rotate45right();


#ifdef __cplusplus
}
#endif

#endif /* GENERAL_H */