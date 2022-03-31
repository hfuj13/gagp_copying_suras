//---------------------------------------------------------------------------
#pragma once

//--- Cluster Averaging Method を使う場合に，CAM 1 とする．
#define CAM  0

#include <sstream>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <ostream>
#include <vector>
#include <algorithm>

#define  TOK   0

#include "SubjDef.h"
#include "FrRandom.h"

template<typename... Args> inline std::string format(const std::string& fmt, Args... args)
{
  constexpr int capacity = 512;
  std::string buff(capacity, '\0');

  int ret = snprintf(&buff[0], buff.capacity(), fmt.c_str(), args...);
  if (ret > capacity) {
    buff.reserve(ret);
    ret = snprintf(&buff[0], buff.capacity(), fmt.c_str(), args...);
  }
  else if (ret < 0) {
    abort();
  }
  return buff;
}

//--------------------------------------------------------------------------------
class Gene final
{
public:
  Gene() = default;
  ~Gene() = default;
  Gene(const Gene&) = default;
  Gene(Gene&&) = default;
  Gene& operator=(const Gene&) = default;
  Gene& operator=(Gene&&) = default;

  std::string viewGene(void)
  {
    std::string str = format("%#08x", vGene);
    return str;
  }

  uint32_t vGene = 0;
};

//--------------------------------------------------------------------------------
template<class T> class Individual
{
public:
  Individual()
  : chrom(MaxString)
  {
  }
  virtual ~Individual() = default;
  Individual(const Individual&) = default;
  Individual(Individual&&) = default;
  Individual(int chromSize)
  : chrom(chromSize)
  {
  }
  virtual Individual& operator=(const Individual&) = default;
  virtual Individual& operator=(Individual&&) = default;

  virtual void Mutation(void) { };
  virtual std::string viewString(int size);
  virtual void setFitness(void)
  {
    fitness = unitRandom();
  }
  virtual void set_chromSize(int cs)
  {
    chrom.resize(cs);
  }

  double getFitness(void) { return fitness; }

  std::vector<T> chrom;
  double fitness = 0.0;
};

//--------------------------------------------------------------------
template<class T> class GeneticPool
{
protected:
  std::vector<T> gPool;
  int nGeneration = 0;
  int chromSize = 0;
  double pCrossover = 0.0;
  double pMutation = 0.0;

  double sumFitness = 0.0;
  double maxFitness = 0.0;
  double avgFitness = 0.0;
  T maxIndividual;   //世代単位の最良個体
  T bestIndividual;  //全世代における最良個体
  int curGen = 0;
  int bestStep = 0;

  int nCluster = 5; // CAM適用の場合のクラスタ数

protected:
  virtual void GenerateChrom(int iP);
  virtual void CrossoverChromosome(int iA, int iB, T* cA, T* cB);

  int SelectParent(void);
  void Replace(const T *idA ,const T *idB);
  int GetWorstIndividual(int rmin);

public:
  GeneticPool(int np, int ng, int cs, double pC, double pM)
  : gPool(np)
  , nGeneration(ng)
  , chromSize(cs)
  , pCrossover(pC)
  , pMutation(pM)
  {
#if 0
    std::for_each(std::begin(gPool), std::end(gPool), [cs](T& g){
      g.set_chromSize(cs);
    });
#else
    for (auto& i : gPool) {
      i.set_chromSize(cs);
    }
#endif
  }
  GeneticPool()
  : gPool(MaxPopulation)
  {
  }
  virtual ~GeneticPool() = default;
  GeneticPool(const GeneticPool&) = default;
  GeneticPool(GeneticPool&&) = default;
  virtual GeneticPool& operator=(const GeneticPool&) = default;
  virtual GeneticPool& operator=(GeneticPool&&) = default;

  void set_nGeneration(int ng) { nGeneration = ng; }
  int get_nGeneration(void) { return nGeneration; }
  void set_curGen(int n) { curGen = n; }
  int get_curGen(void) { return curGen; }

  void set_pCrossover(double p) { pCrossover = p; }
  double get_pCrossover(void) { return pCrossover; }
  void set_pMutation(double p) { pMutation = p; }
  double get_pMutation(void) { return pMutation; }

  void set_nPopulation(int np) {
    gPool.resize(np);
  }
  int get_nPopulation(void) {
    return gPool.size();
  }
  void set_chromSize(int cs)
  {
#if 0
    std::for_each(std::begin(gPool), std::end(gPool), [cs](T& g){
      g.set_chromSize(cs);
    });
#else
    for (auto& i : gPool) {
      i.set_chromSize(cs);
    }
#endif
    chromSize = cs;
  }
  int get_chromSize(void) { return chromSize; }

  void set_nCluster( int np ) { nCluster = np; }
  int get_nCluster(void) { return nCluster; }

  double get_maxFitness(void) { return maxFitness; }
  double get_avgFitness(void) { return avgFitness; }

  T* get_maxIndividual(void) { return &maxIndividual; }
  T* get_bestIndividual(void) { return &bestIndividual; }
  int get_bestStep(void) { return bestStep; }

  void InitializePopulation(void);
  void NextGeneration(void);
  void TakeStatistic(void);
  bool flip(double probability);
};

//--------------------------------------------------------------------
template<class TG> class TSubject
{
protected:
  bool findGoal = false;

public:
  TG gP{100, 100, 10, 0.8, 0.5};

  TSubject() = default;
  virtual ~TSubject() = default;
  TSubject(const TSubject&) = default;
  TSubject(TSubject&&) = default;
  virtual TSubject& operator=(const TSubject&) = default;
  virtual TSubject& operator=(TSubject&&) = default;

  virtual void InitializeSubj(void) { };

  void AppInitialize(void);
  ResultState AppExecute(void);

  void OutMessage(const std::string& mesA, const std::string& mesB, int kind);
};

//-----------------------------------------------------------------------------
//-- template<class T> class Individual　のメンバー関数定義

template<class T>
std::string Individual<T>::viewString(int size)
{
  std::string str("染色体(");
  for (int i = 0; i < size; i++) {
    str += chrom[i].viewGene();
    if (i < size - 1) {
      str += " : ";
    }
  }
  str += ")";
  return str;
}


//-----------------------------------------------------------------------------
//-- template<class T> class GeneticPool　のメンバー関数定義

template<class T>
void GeneticPool<T>::GenerateChrom(int iP)
{ 
}

template<class T>
int GeneticPool<T>::SelectParent()
{
  double sum = 0.0;
  int i = 0;
  double r = unitRandom() * sumFitness;
  do {
    sum += gPool[i].fitness;
    i++;
  } while (sum < r && i < gPool.size());
  return (i - 1);
}

template<class T>
void GeneticPool<T>::CrossoverChromosome(int iA, int iB, T* cA, T* cB)
{
  for (int i = 0; i < chromSize; i++) {
    cA->chrom[i] = gPool[iA].chrom[i];
    cB->chrom[i] = gPool[iB].chrom[i];
  }
  if (flip(pCrossover)) {
    /*交叉処理を記述する*/
  }
}

template<class T>
void GeneticPool<T>::Replace(const T *idA, const T *idB)
{
  int imin1 = GetWorstIndividual(-1);
  int imin2 = GetWorstIndividual(imin1);

  gPool[imin1] = *idA;
  gPool[imin2] = *idB;

  gPool[imin1].setFitness();
  gPool[imin2].setFitness();
}

#if CAM==0
//Cluster Averaging Method ではない劣勢個体の選択
template<class T>
int GeneticPool<T>::GetWorstIndividual(int rmin)
{
  int imin = 0;
  double minV = 99999.0;
  for (int i = 0; i < gPool.size(); i++) {
    if (gPool[i].fitness < minV && i != rmin) {
      minV = gPool[i].fitness;
      imin = i;
    }
  }
  return imin;
}
#else
//Cluster Averaging Method による劣勢個体の選択
template<class T>
int GeneticPool<T>::GetWorstIndividual(int rmin)
{
  int cls = 0;
  int ic[MaxCluster] = {0};

  for (int i = 0; i < gPool.size(); i++) {
    ic[gPool[i].chrom[0].vGene]++;
  }

  int icmax = 0;
  int icmin = 9999;
  for (int i = 0; i < nCluster; i++) {
    if ( ic[i] > icmax ) {
      icmax = ic[i]; cls = i;
    }
    if ( ic[i] != 0 && ic[i] < icmin ) {
      icmin = ic[i];
    }
  }

  double min = 99999.0;
  int imin = -9999;
  if (icmax - icmin < 40) {
    for( int i = 0; i < gPool.size(); i++ ) {
      if ( gPool[i].fitness < min && i != rmin ) {
        min  = gPool[i].fitness;
        imin = i;
      }
    }
  } else {
    for( int i = 0; i < gPool.size(); i++ ) {
      if ( gPool[i].chrom[0].vGene == cls ) {
        if ( gPool[i].fitness < min && i != rmin ) {
          min  = gPool[i].fitness;
          imin = i;
        }
      }
    }
  }

  return imin;
}
#endif

template<class T>
void GeneticPool<T>::InitializePopulation()
{
  maxIndividual.fitness  = 0.0;
  bestIndividual.fitness = 0.0;

  for (int i = 0; i < gPool.size(); i++) {
    GenerateChrom(i);
    gPool[i].setFitness();
  }
}

template<class T>
void GeneticPool<T>::NextGeneration()
{
  T child1(chromSize);
  T child2(chromSize);

  int i = 0;
  do {
    int mate1 = SelectParent();
    int mate2 = SelectParent();
    CrossoverChromosome(mate1, mate2, &child1, &child2);

    child1.Mutation();
    child2.Mutation();

    Replace(&child1, &child2);

    i += 2;
  } while (i < gPool.size());

  curGen++;
}

template<class T>
void GeneticPool<T>::TakeStatistic()
{
  sumFitness = maxFitness = gPool[0].fitness;
  int imax = 0;

  for (int i = 1; i < gPool.size(); i++) { 
    sumFitness += gPool[i].fitness;
    if (gPool[i].fitness >= maxFitness) {
      maxFitness = gPool[i].fitness;
      imax = i;
    }
  }
  avgFitness = sumFitness / gPool.size();
  maxIndividual = gPool[imax];

  if (bestIndividual.fitness < maxIndividual.fitness) {
    bestIndividual = maxIndividual;
    bestStep = curGen;
  }
}

template<class T>
bool GeneticPool<T>::flip(double probability)
{
  if (probability == 1.0) {
    return true;
  } else if (unitRandom() <= probability) {
    return true;
  } else {
    return false;
  }
};


//-----------------------------------------------------------------------------
//-- template<class TG> class TSubject　のメンバー関数定義

template<class TG>
void TSubject<TG>::OutMessage(const std::string& mesA, const std::string& mesB,int kind )
{
  std::cout << mesB << ": " << mesA;
}

template<class TG>
void TSubject<TG>::AppInitialize()
{
  if (gP.get_chromSize() < 0) {
    gP.set_curGen(gP.get_nGeneration() + 999);
    OutMessage("ノード数が多すぎます", "Error", TOK);
  } else {
    gP.set_curGen(0);
  }

  gP.InitializePopulation();
  gP.TakeStatistic();
}

template<class TG>
ResultState TSubject<TG>::AppExecute()
{
  ResultState ret = ResultState::None;

  findGoal = false;
  if (gP.get_curGen() < gP.get_nGeneration()) {
    gP.NextGeneration();
    gP.TakeStatistic();
    ret = ResultState::NotComplete;
  } else {
    ret = ResultState::Complete;
  }

  if (findGoal) {
    ret = ResultState::ArriveAtGoal;
  }

  return ret;
}
