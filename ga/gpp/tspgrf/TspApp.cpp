#include <cstdlib>
#include <cmath>
#include <fstream>

#include "SubjDef.h"
#include "GaAppTpl.h"
#include "FrSubject.h"
#include "TspApp.h"
#include "Creator.h"

char productName[TypeNo][MaxNameSize] =
{ "TypeA","TypeB","TypeC","TypeD","TypeE","TypeF","TypeG",
  "T-10A","T-10B","T-10C","T-10D","T-771","T-772","T-773","T-774"
};

double costMatrix[TypeNo][TypeNo] =
{ {   0.00, 32.59, 40.57, 56.02,117.07, 51.35, 70.12, 55.50, 82.61,101.67,
    125.72, 47.16,125.92,121.82, 74.49 },
  {  32.59,  0.00, 18.50, 25.91, 98.67, 41.54, 70.23, 22.93, 80.04, 81.07,
    104.90, 41.01,101.55, 97.49, 58.31 },
  {  40.57, 18.50,  0.00, 18.25, 80.97, 24.10, 54.06, 27.27, 62.78, 63.89,
     87.96, 25.00, 86.23, 82.13, 39.91 },
  {  56.02, 25.91, 18.25,  0.00, 77.16, 36.12, 66.00, 15.66, 72.26, 58.77,
     81.71, 39.26, 76.62, 72.63, 41.79 },
  { 117.07, 98.67, 80.97, 77.16,  0.00, 66.08, 64.26, 91.85, 55.17, 18.61,
     12.76, 71.05, 27.53, 26.27, 42.57 },
  {  51.35, 41.54, 24.10, 36.12, 66.08,  0.00, 30.32, 49.60, 38.70, 52.07,
     75.57,  5.80, 78.46, 74.49, 23.83 },
  {  70.12, 70.23, 54.06, 66.00, 64.26, 30.32,  0.00, 79.91, 13.00, 58.03,
     76.46, 29.30, 85.53, 82.20, 35.45 },
  {  55.50, 22.93, 27.27, 15.66, 91.85, 49.60, 79.91,  0.00, 87.08, 73.29,
     95.50, 51.71, 88.74, 84.89, 57.45 },
  {  82.61, 80.04, 62.78, 72.26, 55.17, 38.70, 13.00, 87.08,  0.00, 52.28,
     67.79, 39.24, 78.78, 75.80, 35.51 },
  { 101.67, 81.07, 63.89, 58.77, 18.61, 52.07, 58.03, 73.29, 52.28,  0.00,
     24.13, 57.55, 27.74, 24.22, 28.36 },
  { 125.72,104.90, 87.96, 81.71, 12.76, 75.57, 76.46, 95.50, 67.79, 24.13,
      0.00, 80.85, 17.32, 17.67, 51.73 },
  {  47.16, 41.01, 25.00, 39.26, 71.05,  5.80, 29.30, 51.71, 39.24, 57.55,
     80.85,  0.00, 84.13, 80.18, 29.20 },
  { 125.92,101.55, 86.23, 76.62, 27.53, 78.46, 85.53, 88.74, 78.78, 27.74,
     17.32, 84.13,  0.00,  4.10, 55.38 },
  { 121.82, 97.49, 82.13, 72.63, 26.27, 74.49, 82.20, 84.89, 75.80, 24.22,
     17.67, 80.18,  4.10,  0.00, 51.52 },
  {  74.49, 58.31, 39.91, 41.79, 42.57, 23.83, 35.45, 57.45, 35.51, 28.36,
     51.73, 29.20, 55.38, 51.52,  0.00 }
};

std::string TspIndividual::viewString(int size)
{
  TTspApplication* tP = static_cast<TTspApplication*>(Subject);
  int pheno[TypeNo] = {0};
  int chromSize = tP->gP.get_chromSize();

  decodeCh(pheno, chromSize);

  std::string str("生産順(");
  for (int i = 0; i < size; i++) {
    str += tP->getTypeName(pheno[i]);
    if (i < size - 1) {
      str += ",";
    }
  }
  str += ")";
  return str;
}

void TspIndividual::setFitness(void)
{
  TTspApplication* tP = static_cast<TTspApplication*>(Subject);
  fitness = tP->calcFitness(this);
}

void TspIndividual::decodeCh(int pheno[], int size)
{
  int ord[MaxString] = {0};

  for (int i = 0; i < size; i++) {
    ord[i] = i;
  }

  for (int i = 0; i < size; i++) {
    int n = chrom[i].vGene;
    pheno[i] = ord[n];
    for (int j = n; j < size - i - 1; j++ )
      ord[j] = ord[j+1];
  }
}

void TspIndividual::Mutation(void)
{
  int p1 = 0;
  int p2 = 0;
  int chromSize = Subject->gP.get_chromSize();

  if (Subject->gP.flip(Subject->gP.get_pMutation())) {
    p1 = static_cast<int>(chromSize*unitRandom());
    p2 = static_cast<int>((chromSize - p1)*unitRandom());
    chrom[p1].vGene = p2;
  }
}

void TspGeneticPool::GenerateChrom(int ip)
{
  int limt = chromSize;
  for (int i = 0; i < chromSize; i++ ) {
    gPool[ip].chrom[i].vGene = static_cast<int>(limt*unitRandom());
    limt--;
  }
}

void TspGeneticPool::CrossoverChromosome( int iA,int iB,TspIndividual *cA,TspIndividual *cB )
{
  for (int i = 0; i < chromSize; i++) {
    cA->chrom[i] = gPool[iA].chrom[i];
    cB->chrom[i] = gPool[iB].chrom[i];
  }

  if (flip(pCrossover)) {
    int cps = static_cast<int>(chromSize*unitRandom());
    int cpe = static_cast<int>(chromSize*unitRandom());
    if (cps > cpe) {
      int tmp = cps;
      cps = cpe;
      cpe = tmp;
    }
    for (int i = cps; i <= cpe; i++ ) {
      cB->chrom[i] = gPool[iA].chrom[i];
      cA->chrom[i] = gPool[iB].chrom[i];
    }
  }
}

TTspApplication::TTspApplication(void)
{
}

double TTspApplication::calcFitness( TspIndividual *indv )
{
  int ie;
  int pheno[TypeNo] = {0};

  int chromSize = Subject->gP.get_chromSize();
  indv->decodeCh(pheno, chromSize);

  double dtotal = 0.0;
  for (int is = 0; is < chromSize; is++ ) {
    ie = is + 1;
    if (ie == chromSize) {
      ie = 0;
    }
    dtotal += getCost(pheno[is], pheno[ie]);
  }
  indv->setCost(dtotal);

  return normD / dtotal;
}

void TTspApplication::InitializeSubj(void)
{
  if (pFrSubject->getArgN() < 6) {
    std::cout << "Usage: prog NPop NGen PCros PMuta Seed" << std::endl;
    std::cout << "  NPop    個体数" << std::endl;
    std::cout << "  NGen    世代数" << std::endl;
    std::cout << "  PCros   交叉確率(0.0〜1.0)" << std::endl;
    std::cout << "  PMuta   突然変異確率(0.0〜1.0)" << std::endl;
    std::cout << "  Seed    乱数種" << std::endl;
    std::cout << "  生産対象種別 Product.txt を定義しておく必要があります" << std::endl;
    pFrSubject->setFalseGoodFlag();
    return;
  }

  int chromSize = readData();
  if (chromSize <= 2) {
    pFrSubject->setFalseGoodFlag();
    return;
  }
  pFrSubject->setTrueGoodFlag();

  normD = calcNormD( chromSize );
  Subject->gP.set_chromSize( chromSize );

  char** arg = pFrSubject->getArgV();

  Subject->gP.set_nPopulation(atoi(arg[1]));
  Subject->gP.set_nGeneration(atoi(arg[2]));
  Subject->gP.set_pCrossover(atof(arg[3]));
  Subject->gP.set_pMutation(atof(arg[4]));
  srand(atoi(arg[5]));
}

int TTspApplication::readData(void)
{
  int csz = 0;
  std::ifstream tProg("Product.txt");
  if (tProg.bad()) {
    std::cout << "*** ファイル Product.txt オープンエラーです．";
    return 0;
  } else { csz = 0; int wk;
    while( tProg >> wk ) {
      prodData[csz++] = wk;
    }
  }
  return csz;
}

double TTspApplication::calcNormD(int csz)
{
  // 選択された製品タイプに関するコストマトリックスの
  // 正規化ファクタを計算する．
  double sCost[TypeNo*TypeNo],vMin;
  int ip = 0;
  int jMin;

  for (int i = 0; i < csz; i++) {
    for (int j = i + 1; j < csz; j++) {
      sCost[ip++] = getCost(i, j);
    }
}

  for (int i = 0; i < ip; i++) {
    vMin = sCost[i]; jMin = i;
    for (int j = i + 1; j < ip; j++) {
      if ( sCost[j] < vMin ) {
        vMin = sCost[j]; jMin = j;
      }
    }
    double wk = sCost[i]; sCost[i] = sCost[jMin]; sCost[jMin] = wk;
  }

  normD = 0.0;
  for (int i = 0; i < csz; i++) {
    normD += sCost[i];
  }

  return normD;
}

std::string TTspApplication::getTypeName(int np)
{
  std::string str(productName[prodData[np]]);
  return str;
}

double TTspApplication::getCost(int ia, int ib)
{ 
  double rC = costMatrix[prodData[ia]][prodData[ib]];
  return  rC;
}
