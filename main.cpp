#include "print.h"

int main( )
{
	printf( "\nbits back" );
  
  Probsum sum;
	sum.push_back( 700000100 );
	sum.push_back( 708000100 );
	sum.push_back( 808000100 );
	sum.push_back( 1000000100 );
	sum.push_back( 1200000100 );
  sum.push_back( 2100000000 );
  sum.push_back( 3800500000 );
  sum.push_back( 3900000000 );
  
	Prob prob( sum );
	print( prob );

  Coder coder;

  Data data = prob.sample( 1000 );
  print( data, prob );
	
	coder.encode( data, prob );
	print( coder );
  printf( "at a bitrate of %4.2f bits per symbol\n", coder.bitrate( data ) );
  
	data = coder.decode( data, prob );
	print( data );

  printf( "\n\n" );
	return 0;
}
