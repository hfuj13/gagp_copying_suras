//---------------------------------------------------------------------------
#ifndef FrSubjViewH
#define FrSubjViewH

#include <ctime>
#include <string>

#include "SubjDef.h"
#include "GaAppTpl.h"

//---------------------------------------------------------------------------
class TViewApp
{
//private:
//    char  tDiff[100] = {0};
    
protected:
    std::string work;

public:
    TViewApp() = default;
    virtual ~TViewApp() = default;
    TViewApp(const TViewApp&) = default;
    TViewApp(TViewApp&&) = default;
    TViewApp& operator=(const TViewApp&) = default;
    TViewApp& operator=(TViewApp&&) = default;

    std::string GetTimeDiff(std::time_t sT, std::time_t eT);
    virtual void PrintBestSolution(void);
    virtual void PrintMaxSolution(void);
};
//----------------------------------------------------------------------------
extern TViewApp *ViewApp;
//----------------------------------------------------------------------------
#endif
