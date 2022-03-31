//---------------------------------------------------------------------------
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "SubjDef.h"
#include "FrSubject.h"
#include "FrSubjView.h"

#include "GaAppTpl.h"
#include "Creator.h"

FrSubject *pFrSubject;
//---------------------------------------------------------------------------
FrSubject::FrSubject()
{
    pCreator = new TCreator;
    Subject = pCreator->CreateApplication();
    ViewApp = pCreator->CreateViewApp();

#if CAM==1
    if (Subject->gP.get_nCluster() == 0) {
        Subject->OutMessage("Cluster数が定義されていません．", "***Error", 0);
        exit(0);
    }
#endif
}

void FrSubject::ExecuteGa(int argc, char** argv)
{
    ResultState state = ResultState::None;

    argN = argc;
    argV = argv;
    goodFlag = true;
    Subject->InitializeSubj();
    if (goodFlag) {
        std::time_t sT = time(nullptr);
        Subject->AppInitialize();
        do {
          state = Subject->AppExecute();
          if ( (Subject->gP.get_curGen() % 5) == 0 )
              DispState();
        } while (state == ResultState::NotComplete);

        std::time_t eT = time( nullptr );
        std::cout << std::endl << ViewApp->GetTimeDiff(sT, eT) << std::endl;
        if (state == ResultState::Complete) {
          std::cout << "指定世代を終了しました" << std::endl;
        } else {
          std::cout << "解を発見しました" << std::endl;
        }

        ViewApp->PrintBestSolution();
    }
}

void FrSubject::DispState(void)
{
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout.precision( 3 );
    std::cout << "[" << Subject->gP.get_curGen() << "] Max:";
    std::cout << Subject->gP.get_maxFitness() << "  Avg:";
    std::cout << Subject->gP.get_avgFitness() << std::endl;

    std::string buf = Subject->gP.get_maxIndividual()->viewString(Subject->gP.get_chromSize());
    std::cout << buf << std::endl;
}
