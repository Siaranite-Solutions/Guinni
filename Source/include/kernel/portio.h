/*
 * portio.h
 *
 *  Created on: Jan 3, 2019
 *      Author: arawn
 */

#include <stdint.h>
#ifndef PORTIO_H_
#define PORTIO_H_

uint8_t inb(uint16_t port);

uint16_t inw(uint16_t port);

uint32_t inl(uint16_t port);

void insl(uint16_t port, void *address, int count);

void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);

void outl(uint16_t port, uint32_t val);

#endif /* PORTIO_H_ */
