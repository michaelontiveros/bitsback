#ifndef PROB_H
#define PROB_H

#include <vector>
#include <map>
#include <list>

#define PRECISION   32
#define DENOMINATOR pow( 2, PRECISION )

typedef std::vector< uint32_t >       Probsum;
typedef std::map< uint32_t, uint8_t > Probsymb;
typedef std::list< uint8_t >          Data;

class Prob
{
public:
	Probsum  sum;
  Probsymb symb;

	Prob( );
	Prob( Probsum & probsum );

	uint32_t  operator[ ]( uint32_t symbol );
  
	uint8_t sample( );
	Data    sample( uint32_t size );
	float   information( uint8_t symbol );
  float   information( Data  & data );
	double  entropy( );
};

#endif
