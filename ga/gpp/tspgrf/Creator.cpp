#include "Creator.h"
#include "ViewTsp.h"

SubjectType *Subject;

TCreator  *pCreator;

TCreator::TCreator()
{
}

SubjectType* TCreator::CreateApplication()
{
  return new TTspApplication;
}

TViewApp* TCreator::CreateViewApp()
{
  // 下のコンストラクターを，拡張クラスのコンストラクターに
  // 書き換える
  return new TViewTsp;
}
