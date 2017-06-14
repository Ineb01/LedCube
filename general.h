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

void SetCube0();
void RandomCube(int probability);
void RandomLed();
void Rotate45left();
void Rotate45right();


#ifdef __cplusplus
}
#endif

#endif /* GENERAL_H */