//---------------------------------------------------------------------------
#include "Creator.h"
//---------------------------------------------------------------------------

SubjectType *Subject;

TCreator  *pCreator;

//TCreator::TCreator()
//{
//}

SubjectType* TCreator::CreateApplication(void)
{
  return new SubjectType;
}

TViewApp* TCreator::CreateViewApp(void)
{
  // 下のコンストラクターを，拡張クラスのコンストラクターに
  // 書き換える
  return new TViewApp;
}


