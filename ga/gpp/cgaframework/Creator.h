//---------------------------------------------------------------------------
#ifndef CreatorH
#define CreatorH
//---------------------------------------------------------------------------

#include "SubjDef.h"
#include "GaAppTpl.h"
#include "FrSubjView.h"

using SubjectType = TSubject<GeneticPool<Individual<Gene> > >;

class TCreator final
{
private:

public:
  TCreator() = default;
  ~TCreator() = default;
  TCreator(const TCreator&) = default;
  TCreator(TCreator&&) = default;
  TCreator& operator=(const TCreator&) = default;
  TCreator& operator=(TCreator&&) = default;

  SubjectType*  CreateApplication(void);
  TViewApp*     CreateViewApp(void);
};

//---------------------------------------------------------------------------
extern TCreator    *pCreator;
extern SubjectType *Subject;
//---------------------------------------------------------------------------
#endif
