//---------------------------------------------------------------------------
#include <ctime>

#include "FrSubjView.h"
#include "Creator.h"

#include "GaAppTpl.h"

//---------------------------------------------------------------------------
TViewApp  *ViewApp;

//TViewApp::TViewApp()
//{
//}

std::string TViewApp::GetTimeDiff(std::time_t sT, std::time_t eT)
{
  int32_t dT = eT - sT;

  uint16_t s = dT % 60;
  dT = dT / 60;
  uint16_t m = dT % 60;
  uint16_t h  = dT / 60;

  std::string str = format("%hu:%hu'%hu\"", h, m, s);
  return str;
}

void TViewApp::PrintBestSolution(void)
{
  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision( 3 );
  std::cout << "Pop.:" << Subject->gP.get_nPopulation();
  std::cout << ", Gen.:" << Subject->gP.get_nGeneration();
  std::cout << ", pCrossover:" << Subject->gP.get_pCrossover();
  std::cout << ", pMutation:" << Subject->gP.get_pMutation();
  std::cout << std::endl;
}

void TViewApp::PrintMaxSolution(void)
{
  std::string work = Subject->gP.get_maxIndividual()->viewString(Subject->gP.get_chromSize());
  std::cout << work << std::endl;
}
