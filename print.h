#ifndef PRINT_H
#define PRINT_H

#include <stdlib.h>
#include "coder.h"

void printbits( uint8_t  n );
void printbits( uint16_t n );
void printbits( uint32_t n );
void printbits( uint64_t n );

void printbits( Body & body );

void print( Prob  & prob );
void print( Data  & data );
void print( Data  & data,
            Prob  & prob );
void print( Coder & coder);

#endif
