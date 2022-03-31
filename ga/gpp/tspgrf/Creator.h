//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------

#include "SubjDef.h"
#include "GaAppTpl.h"
#include "FrSubjView.h"

#include "TspApp.h"

using SubjectType = TSubject<TspGeneticPool>;

class TCreator
{
private:

public:
  TCreator();

  SubjectType*  CreateApplication(void);
  TViewApp*     CreateViewApp(void);
};

//---------------------------------------------------------------------------
extern TCreator    *pCreator;
extern SubjectType *Subject;
//---------------------------------------------------------------------------
