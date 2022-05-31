#ifndef CODER_H
#define CODER_H

#include "prob.h"

typedef std::vector< uint32_t > Body;

// bits back asymmetric numeral system
class Coder
{
public:
	uint64_t mask;
	uint64_t head;
	uint64_t latent;
	uint32_t tail;
	Body     body;

	Coder( );

  void headoff( uint8_t   symbol,
	              Prob    & prob    );
	void headon( );

	void encode( uint8_t   symbol,
	             Prob    & prob    );
	void encode( Data    & data,
	             Prob    & prob    );

	uint8_t decode( Prob & prob );
  Data    decode( Data & data,
	                Prob & prob );

  uint32_t information( );
  float    bitrate( Data & data );
};

#endif
