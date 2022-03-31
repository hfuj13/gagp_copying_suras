#include "GaAppTpl.h"
#include "ViewTsp.h"
#include "TspApp.h"
#include "Creator.h"

TViewTsp  *ViewTsp;

TViewTsp::TViewTsp()
{
}

void TViewTsp::PrintBestSolution(void)
{
  TTspApplication* tP = static_cast<TTspApplication*>(Subject);
  int pheno[TypeNo] = {0};

  int chromSize = tP->gP.get_chromSize();
  (tP->gP.get_bestIndividual())->decodeCh(pheno, chromSize);

  for (int i = 0; i < chromSize; i++ ) {
    if ( i%10 == 0 ) {
      if ( i == 0 )
        std::cout << "生産順  ";
      else
        std::cout << "\n            ";
    }
    int ip = pheno[i];
    std::cout << tP->getTypeName( ip ) << " ";
  }

  std::cout.setf(std::ios::fixed, std::ios::floatfield );
  std::cout.precision( 3 );
  std::cout << std::endl << "生産種類数: " << tP->gP.get_chromSize();
  std::cout << "  切替コスト: " << (tP->gP.get_bestIndividual())->getCost();
  std::cout << "(Fitness: " << (tP->gP.get_bestIndividual())->getFitness();
  std::cout << ")" << std::endl;

  TViewApp::PrintBestSolution();
}
