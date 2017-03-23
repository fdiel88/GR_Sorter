
#ifndef SORTER_TREEDATA_H_
#define SORTER_TREEDATA_H_

#include "TTree.h"

class Sorter_treedata {

public:
  int init_tree(TTree *tree_i);
  int init_treeVariables();
  TTree *tree;

  Int_t t_eventID;
  Double_t t_X1pos;
  Double_t t_X1th;
  Double_t t_thetaFP;
  Double_t t_phiFP;
  Double_t t_Y1;
  Double_t t_Y2;
  Double_t t_thetaSCAT;
  Double_t t_phiSCAT;
};

#endif
