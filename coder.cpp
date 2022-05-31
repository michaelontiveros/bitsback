#include "coder.h"

Coder::Coder( )
{
	mask = ( ( ( uint64_t ) 1 ) << PRECISION ) - 1;
  head = 0;
}

void Coder::headoff( uint8_t   symbol,
                     Prob    & prob    )
{
	if( ( head >> PRECISION ) >= prob[ symbol ] )
	{
		tail = head & mask;
		body.push_back( tail );
		head >>= PRECISION;
	}
}

void Coder::headon( )
{
  if( body.empty( ) == true )
  {
    return;
	}
	if( ( head >> PRECISION ) == 0 )
	{
		tail = body.back( );
		body.pop_back( );
		head = ( head << PRECISION ) | tail;
	}
}

void Coder::encode( uint8_t   symbol,
                    Prob    & prob    )
{
  headoff( symbol, prob );
	latent = head % prob[ symbol ];
	if( symbol > 0 )
	{
	  latent += prob.sum[ symbol-1 ]; 
  }
	head /= prob[ symbol ];
	head = ( head << PRECISION ) | latent;
}

void Coder::encode( Data & data,
                    Prob & prob  )
{
  Data::iterator begin = data.begin( );
	Data::iterator middle;
	Data::iterator end   = data.end( );
	for( middle = begin; middle != end; middle++ )
	{
    encode( * middle, prob );
	}
}

uint8_t Coder::decode( Prob & prob )
{
  uint8_t symbol = 0;
	latent = head & mask;
	Probsymb::iterator probsymb;
	probsymb = prob.symb.lower_bound( latent );
	if( probsymb != prob.symb.begin( ) )
	{
	  if( probsymb == prob.symb.end( ) )
		{
      probsymb--;
		}
		else if( latent != probsymb->first )
		{
      probsymb--;
	  }
		latent -= probsymb->first;
    symbol  = probsymb->second + 1;
	}
	/*
	while( latent >= prob[ symbol ] )
	{
    latent -= prob[ symbol ];
	  symbol++;
	}
	*/
	head >>= PRECISION;
  head = head * prob[ symbol ] + latent;
	headon( );
	return symbol;
}

Data Coder::decode( Data & data,
                    Prob & prob  )
{
  Data decoded;
	uint32_t size = data.size( );
	while( size != 0 )
	{
    decoded.push_front( decode( prob ) );
	  size--;
	}
	return decoded;
}

uint32_t Coder::information( )
{
  uint32_t info = 32 * ( body.size( ) + 2 );
	return info;
}

float Coder::bitrate( Data & data )
{
  float  info = information( );
	float  size = data.size( );
	return info / size;
}
