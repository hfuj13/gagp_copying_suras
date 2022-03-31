//---------------------------------------------------------------------------
#include <cstdlib>

#include "FrRandom.h"
//---------------------------------------------------------------------------
double unitRandom(void)
{
  int i = rand();
  if ( i != 0 ) {
      i--;
  }
  double r = static_cast<double>(i) / RAND_MAX;
  return r;
}
