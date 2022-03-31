#include "FrSubject.h"

#include <iostream>

int main(int argc, char *argv[])
{
  pFrSubject = new FrSubject();

  pFrSubject->ExecuteGa(argc, argv);

  return 0;
}
