//---------------------------------------------------------------------------
#include <cstdlib>

#include "FrRandom.h"
//---------------------------------------------------------------------------
double unitRandom(void)
{
  int i = rand();
  if ( i != 0 )
      i--;
  double r = (double)i/RAND_MAX;
  return( r );
}
