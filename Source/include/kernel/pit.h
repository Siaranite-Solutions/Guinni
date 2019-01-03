/*
 * pit.h
 *
 *  Created on: Jan 3, 2019
 *      Author: arawn
 */

#ifndef PIT_H
#define PIT_H

#include <stdint.h>
#include <kernel/interrupt.h>

void init_pit(uint32_t freq);

#endif
