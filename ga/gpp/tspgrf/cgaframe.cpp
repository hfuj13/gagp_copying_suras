//---------------------------------------------------------------------------
#include "FrSubject.h"

#include <iostream.h>
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  pFrSubject = new FrSubject();

  pFrSubject->ExecuteGa( argc,argv );

  char  buf[100];
  cin.getline( buf,100 );
  return 0;
}
//---------------------------------------------------------------------------
