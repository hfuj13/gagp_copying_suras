//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------

#include "GaAppTpl.h"

constexpr int TypeNo = 15;
constexpr int MaxNameSize = 40;

//--------------------------------------------------------------
class TspIndividual final : public Individual<Gene>
{
private:
  double  pCost;

public:
  TspIndividual() = default;
  ~TspIndividual() = default;
  TspIndividual(const TspIndividual&) = default;
  TspIndividual(TspIndividual&&) = default;
  TspIndividual& operator=(const TspIndividual&) = default;
  TspIndividual& operator=(TspIndividual&&) = default;
  TspIndividual(int chromSize)
  : Individual<Gene>(chromSize)
  {
  }

  virtual void Mutation(void) override;
  virtual void setFitness(void) override;
  virtual std::string viewString(int size) override;

  void decodeCh(int pheno[], int size);
  void setCost(double pC) { pCost = pC; }
  double getCost() { return pCost; }
};

//--------------------------------------------------------------
class TspGeneticPool : public GeneticPool<TspIndividual>
{
public:
  TspGeneticPool( int np,int ng,int cs,double pC,double pM ) :
     GeneticPool<TspIndividual>( np,ng,cs,pC,pM ) { };

  TspGeneticPool() { }
  ~TspGeneticPool() { }

  virtual void GenerateChrom(int ip) override;
  virtual void CrossoverChromosome(int iA, int iB, TspIndividual *cA, TspIndividual *cB) override;

protected:
};

//--------------------------------------------------------------

class TTspApplication : public TSubject<TspGeneticPool>
{
protected:
  double normD;
  int prodData[TypeNo];

  int readData(void);
  double calcNormD(int csz);

public:
  TTspApplication();

  virtual void InitializeSubj() override;

  double calcFitness(TspIndividual *indv);

  double  getNormD() { return normD; }
  std::string getTypeName(int np);
  double  getCost(int ia, int ib);
};
