#include "prob.h"
#include "print.h"
#include <cstdlib>
#include <cmath>

Prob::Prob( )
{

}

Prob::Prob( Probsum & probsum )
{
	uint8_t size = probsum.size( );
	uint8_t symbol;
	for( symbol = 0; symbol < size; symbol++ )
	{
    sum.push_back( probsum[ symbol ] );
		std::pair< uint32_t, uint8_t > sumsymb( probsum[ symbol ], symbol );
		symb.insert( sumsymb );
	}
  sum.push_back( 0 );
}

uint32_t Prob::operator[ ]( uint32_t n )
{
  uint32_t prob = sum[ n ];
	if( n == 0 )
	{
    return prob;
	}
	prob -= sum[ n-1 ];
	return prob;
}

uint8_t Prob::sample( )
{
  uint32_t sample = ( rand( ) << 1 );
	Probsum::iterator begin = sum.begin( );
	Probsum::iterator middle;
	Probsum::iterator end   = sum.end( );
	uint8_t symbol = 0;
	for( middle = begin; middle != end; middle++ )
	{
    if( * middle > sample )
		{
      return symbol;
		}
		symbol++;
	}
	symbol--;
	return symbol;
}

Data Prob::sample( uint32_t size )
{
  Data data;
	uint32_t index;
	for( index = 0; index < size; index++ )
	{
    data.push_back( sample( ) );
	}
	return data;
}

float Prob::information( uint8_t symbol )
{
  float prob = ( float ) ( *this )[ symbol ];
	float info = PRECISION - log2f( prob );
  return info;
}

float Prob::information( Data & data )
{
	float info = 0;
	Data::iterator begin = data.begin( );
	Data::iterator middle;
	Data::iterator end = data.end( );
	for( middle = begin; middle != end; middle++ )
	{
    info += information( * middle );
	}
	return info;
}

double Prob::entropy( )
{
  uint8_t size = sum.size( );
	uint8_t symbol;
	float   entropy = 0;
	double  prob;
	for( symbol = 0; symbol < size; symbol++ )
	{
    prob     = ( double ) ( * this )[ symbol ];
	  entropy += prob * information( symbol );
	}
  entropy /= DENOMINATOR;
	return entropy;
}
