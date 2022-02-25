/*
 * macros.h
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#ifndef MACROS_H_
#define MACROS_H_
#include "System.h"

// zabranjuje prekide
#define lock {asm{ pushf; cli;}}
// dozvoljava prekide
#define unlock {asm{ popf }}
//maksimalna velicina steka
#define maxStSz 65535



#endif /* MACROS_H_ */
