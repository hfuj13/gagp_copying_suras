#pragma once

//#define  UWM_REPLY       WM_USER
//#define  UWM_PRINTSTATE  UWM_REPLY+1
//#define  UWM_DRAWSTATE   UWM_PRINTSTATE+1
//#define  UWM_DRAWFITNESS UWM_DRAWSTATE+1

static constexpr int MaxPopulation = 500;
static constexpr int MaxString     = 100;
static constexpr int MaxSubString  = 20;
static constexpr int MaxStep       = 1000;
static constexpr int MaxSeed       = 500;
static constexpr int MaxCluster    = 50;

enum class ResultState {
  None = 0,
  Complete = 1,
  NotComplete = 2,
  ArriveAtGoal = 3,
};
