//---------------------------------------------------------------------------
#pragma once

#include "FrSubjView.h"

//---------------------------------------------------------------------------
class TViewTsp final : public TViewApp
{
private:

protected:

public:
    TViewTsp();

    virtual void PrintBestSolution(void) override;
};
//----------------------------------------------------------------------------
extern TViewTsp *ViewTsp;
//----------------------------------------------------------------------------
