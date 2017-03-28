
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
  Double_t t_X1posC;

  Double_t t_thetaFP;
  Double_t t_phiFP;
  Double_t t_Y1;
  Double_t t_Y2;
  Double_t t_thetaSCAT;
  Double_t t_phiSCAT;
  Double_t t_X1;
  Double_t t_U1;
  Double_t t_X2;
  Double_t t_U2;

  Double_t t_Y1pos;
  Double_t t_Y1posC;
  Double_t t_Th1;
  Double_t t_Ps1;
  Double_t t_Th2;
  Double_t t_Ps2;
  Double_t t_psiFP;

  Double_t t_Zttgt;
  // Int_t t_tdc_x1;
  // Int_t t_tdc_u1;
  // Int_t t_tdc_x2;
  // Int_t t_tdc_u2;
  // Int_t t_tdc_x1_cor;
  // Int_t t_tdc_u1_cor;
  // Int_t t_tdc_x2_cor;
  // Int_t t_tdc_u2_cor;
  // Double_t t_Xferet;
  // Double_t t_fera;
  // Double_t t_feret;
  Double_t t_tof;
  Double_t t_cor_tof;
  Double_t t_scintillator_ave_1;

  Double_t t_scintillator_ave_2;

  Double_t t_chisq_x1;
  Double_t t_chisq_u1;
  Double_t t_chisq_x2;
  Double_t t_chisq_u2;
  Double_t t_num_wire_x1;
  Double_t t_num_wire_u1;
  Double_t t_num_wire_x2;
  Double_t t_num_wire_u2;
  Double_t t_Pout;
  Double_t t_Eout;
  Double_t t_Ex;
  Double_t t_success_X1;
  Double_t t_success_U1;
  Double_t t_success_X2;
  Double_t t_success_U2;
};

#endif
