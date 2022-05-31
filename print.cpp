#include "print.h"
#include "prob.h"
#include <stdio.h>
#include <cmath>

void printbits( uint8_t n )
{
	uint8_t precision = 8;
	uint8_t mask      = ( 1 << ( precision - 1 ) );
	while( precision != 0 )
	{
    if( ( n & mask ) == 0 )
		{
      printf( "0" );
		}
		else
		{
      printf( "1" );
		}
		n <<= 1;
		precision--;
	}
}

void printbits( uint16_t n )
{
	uint8_t  precision = 16;
	uint16_t mask      = ( 1 << ( precision - 1 ) );
	while( precision != 0 )
	{
    if( ( n & mask ) == 0 )
		{
      printf( "0" );
		}
		else
		{
      printf( "1" );
		}
		n <<= 1;
		precision--;
	}
}

void printbits( uint32_t n )
{
	uint8_t  precision = 32;
	uint32_t mask      = ( 1 << ( precision - 1 ) );
	while( precision != 0 )
	{
    if( ( n & mask ) == 0 )
		{
      printf( "0" );
		}
		else
		{
      printf( "1" );
		}
		n <<= 1;
		precision--;
	}
}

void printbits( uint64_t n )
{
	uint8_t  precision = 64;
	uint64_t mask      = ( ( ( uint64_t ) 1 ) << ( precision - 1 ) );
	while( precision != 0 )
	{
    if( ( n & mask ) == 0 )
		{
      printf( "0" );
		}
		else
		{
      printf( "1" );
		}
		n <<= 1;
		precision--;
	}
}

void printbits( Body & body )
{
	Body::iterator begin = body.begin( );
	Body::iterator middle;
	Body::iterator end   = body.end( );
	for( middle = begin; middle != end; middle++ )
	{
		printbits( * middle );
	}
}

void print( Prob & prob )
{
	uint32_t size = prob.sum.size( );
  printf( "\n" );
	printf( "\nthe probability distribution on %u symbols", size );
  printf( " given by" );
	printf( "\n  symbol     probability     bits of information" );
	uint32_t symbol;
  for( symbol = 0; symbol < size; symbol++ )
	{
		printf( "\n  %u          ", symbol );
		printf( "%f        ",       ( float ) prob[ symbol ] / DENOMINATOR );
		printf( "%f",               prob.information( symbol ) );
	}
  printf( "\nhas %f bits of entropy", prob.entropy( ) );
	printf( "\n" );
}

void print( Data  & data )
{
  printf( "\nthe data\n  " );
	Data::iterator begin = data.begin( );
	Data::iterator middle;
	Data::iterator end = data.end( );
	for( middle = begin; middle != end; middle++ )
	{
    printf( "%i", * middle );
	}
}

void print( Data & data,
            Prob & prob  )
{
	print( data );
  printf( "\ncontains %4.1f bits of information", prob.information( data ) );
}

void print( Coder & coder )
{
  printf( "\n" );
	printf( "\nthe encoding" );
	printf( "\n  head " );
	printbits( coder.head );
	printf( "\n  body " );
	printbits( coder.body );
	printf( "\ncontains %u bits of information", coder.information( ) );
  printf( "\n" );
}
