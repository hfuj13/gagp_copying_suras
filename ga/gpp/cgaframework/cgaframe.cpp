//---------------------------------------------------------------------------
#include "FrSubject.h"

#include <iostream>
//---------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
  pFrSubject = new FrSubject();

  pFrSubject->ExecuteGa(argc, argv);

//  std::cout << "何か入力すると終了: " << std::flush;
//  char  buf[100];
//  std::cin.getline( buf,100 );
  return 0;
}
//---------------------------------------------------------------------------
