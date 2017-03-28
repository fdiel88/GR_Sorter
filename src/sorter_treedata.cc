
#include "sorter_treedata.h"

#include "TTree.h"

int Sorter_treedata::init_tree(TTree *tree_i) {

  tree = tree_i;

  tree->Branch("eventID", &t_eventID, "t_eventID/I");

  tree->Branch("X1pos", &t_X1pos, "t_X1pos/D");
  tree->Branch("X1th", &t_X1th, "t_X1th/D");

  // tree->Branch("thetaFP", &t_thetaFP, "t_thetaFP/D");
  // t1->Branch("thetaFPx",&t_thetaFPx,"t_thetaFPx/D");
  // tree->Branch("phiFP", &t_phiFP, "t_phiFP/D");
  tree->Branch("Y1", &t_Y1, "t_Y1/D");
  tree->Branch("Y2", &t_Y2, "t_Y2/D");

  tree->Branch("X1pos", &t_X1pos, "t_X1pos/D");
  tree->Branch("X1posC", &t_X1posC, "t_X1posC/D");
  tree->Branch("Y1pos", &t_Y1pos, "t_Y1pos/D");
  tree->Branch("Y1posC", &t_Y1posC, "t_Y1posC/D");

  tree->Branch("Th1", &t_Th1, "t_Th1/D");
  tree->Branch("Ps1", &t_Ps1, "t_Ps1/D");
  tree->Branch("Th2", &t_Th2, "t_Th2/D");
  tree->Branch("Ps2", &t_Ps2, "t_Ps2/D");

  tree->Branch("psiFP", &t_psiFP, "t_psiFP/D");
  tree->Branch("thetaFP", &t_thetaFP, "t_thetaFP/D");
  tree->Branch("phiFP", &t_phiFP, "t_phiFP/D");

  tree->Branch("thetaSCAT", &t_thetaSCAT, "t_thetaSCAT/D");
  tree->Branch("phiSCAT", &t_phiSCAT, "t_phiSCAT/D");
  tree->Branch("ztSCAT", &t_Zttgt, "t_Zttgt/D");

  // tree->Branch("tdc_x1", &t_tdc_x1, "t_tdc_x1/D");
  // tree->Branch("tdc_u1", &t_tdc_u1, "t_tdc_u1/D");
  // tree->Branch("tdc_x2", &t_tdc_x2, "t_tdc_x2/D");
  // tree->Branch("tdc_u2", &t_tdc_u2, "t_tdc_u2/D");
  // tree->Branch("x1_cor", &t_tdc_x1_cor, "t_tdc_x1_cor/D");
  // tree->Branch("u1_cor", &t_tdc_u1_cor, "t_tdc_u1_cor/D");
  // tree->Branch("x2_cor", &t_tdc_x2_cor, "t_tdc_x2_cor/D");
  // tree->Branch("u2_cor", &t_tdc_u2_cor, "t_tdc_u2_cor/D");

  // tree->Branch("Xferet", &t_Xferet, "t_Xferet\D");
  // tree->Branch("fera", &t_fera, "t_fera\D");
  // tree->Branch("feret", &t_feret, "t_feret\D");
  tree->Branch("tof", &t_tof, "t_tof/D");
  tree->Branch("cor_tof", &t_cor_tof, "t_cor_tof/D");
  tree->Branch("scintillator_ave_1", &t_scintillator_ave_1,
               "scintillator_ave_1/D");
  tree->Branch("scintillator_ave_1", &t_scintillator_ave_1,
               "scintillator_ave_1/D");
  tree->Branch("scintillator_ave_2", &t_scintillator_ave_2,
               "scintillator_ave_2/D");
  tree->Branch("scintillator_ave_2", &t_scintillator_ave_2,
               "scintillator_ave_2/D");
  tree->Branch("chisq_x1", &t_chisq_x1, "t_chisq_x1/D");
  tree->Branch("chisq_u1", &t_chisq_u1, "t_chisq_u1/D");
  tree->Branch("chisq_x2", &t_chisq_x2, "t_chisq_x2/D");
  tree->Branch("chisq_u2", &t_chisq_u2, "t_chisq_u2/D");
  tree->Branch("num_wire_x1", &t_num_wire_x1, "t_num_wire_x1/D");
  tree->Branch("num_wire_u1", &t_num_wire_u1, "t_num_wire_u1/D");
  tree->Branch("num_wire_x2", &t_num_wire_x2, "t_num_wire_x2/D");
  tree->Branch("num_wire_u2", &t_num_wire_u2, "t_num_wire_u2/D");

  tree->Branch("Pout", &t_Pout, "t_Pout/D");
  tree->Branch("Eout", &t_Eout, "t_Eout/D");
  tree->Branch("Ex", &t_Ex, "t_Ex/D");

  tree->Branch("success_X1", &t_success_X1, "t_success_X1/D");
  tree->Branch("success_U1", &t_success_U1, "t_success_U1/D");
  tree->Branch("success_X2", &t_success_X2, "t_success_X2/D");
  tree->Branch("success_U2", &t_success_U2, "t_success_U2/D");

  return 1;
}

int Sorter_treedata::init_treeVariables() {

  t_eventID = 0;

  // t_tdcsperevent = 0;
  // t_pad1hiP = -1;
  // t_pad1lowP = -1;
  // t_pad2hiP = -1;
  // t_pad2lowP = -1;
  // t_pad1hiPT = -1;
  // t_pad1lowPT = -1;
  // t_pad2hiPT = -1;
  // t_pad2lowPT = -1;
  // t_tof = 0;
  // t_toftdc2 = 0;
  // t_toftdc3 = 0;
  // t_toftdc4 = 0;
  // t_toftdc5 = 0;
  // t_toftdc6 = 0;
  // t_toftdc7 = 0;
  // t_k600 = 0;
  // t_runtime = -1;
  // t_triggerI = 0, t_triggerU = 0, t_CII = 0, t_CIU = 0;
  // t_X1hits = -100;
  // t_X2hits = -100;
  // t_U1hits = -100;
  // t_U2hits = -100;
  t_X1pos = -100.;
  // t_X2pos = -100.;
  // t_U1pos = -100.;
  // t_U2pos = -100.;
  t_X1th = -100.;
  // t_X2th = -100.;
  // t_U1th = -100.;
  // t_U2th = -100.;
  // t_X1posO = -100.;
  // t_X1posC = -100.;
  // t_Ex = -1.;
  // t_ExC = -1.;
  // t_X1chisq = -100.;
  // t_X2chisq = -100.;
  // t_U1chisq = -100.;
  // t_U2chisq = -100.;
  // t_X1flag = -100;
  // t_X2flag = -100;
  // t_U1flag = -100;
  // t_U2flag = -100;
  // t_X1effID = -100.;
  // t_X2effID = -100.;
  // t_U1effID = -100.;
  // t_U2effID = -100.;
  // t_X1res0 = -100.0;
  // t_X2res0 = -100.0;
  // t_U1res0 = -100.0;
  // t_U2res0 = -100.0;
  // t_X1res1 = -100.0;
  // t_X2res1 = -100.0;
  // t_U1res1 = -100.0;
  // t_U2res1 = -100.0;
  //#ifdef _VDCRESCALCS
  // t_X1res2 = -100.0;
  // t_X2res2 = -100.0;
  // t_U1res2 = -100.0;
  // t_U2res2 = -100.0;
  // t_X1res3 = -100.0;
  // t_X2res3 = -100.0;
  // t_U1res3 = -100.0;
  // t_U2res3 = -100.0;
  // t_X1res4 = -100.0;
  // t_X2res4 = -100.0;
  // t_U1res4 = -100.0;
  // t_U2res4 = -100.0;
  // t_X1res5 = -100.0;
  // t_X2res5 = -100.0;
  // t_U1res5 = -100.0;
  // t_U2res5 = -100.0;
  // t_X1res6 = -100.0;
  // t_X2res6 = -100.0;
  // t_U1res6 = -100.0;
  // t_U2res6 = -100.0;
  // t_X1res7 = -100.0;
  // t_X2res7 = -100.0;
  // t_U1res7 = -100.0;
  // t_U2res7 = -100.0;
  // t_X1res8 = -100.0;
  // t_X2res8 = -100.0;
  // t_U1res8 = -100.0;
  // t_U2res8 = -100.0;
  //#endif
  t_thetaFP = -100.;
  // t_thetaFPx = -100;
  t_phiFP = -100.;
  t_thetaSCAT = -100.;
  t_phiSCAT = -100.;
  // t_theta = -100;
  t_Y1 = -100.0;
  t_Y2 = -100.0;

  // t_X1effall = -1;
  // t_X1effdt = -1;
  // t_X1effgroup = -1;
  // t_X1effgood = -1;
  // t_U1effall = -1;
  // t_U1effdt = -1;
  // t_U1effgroup = -1;
  // t_U1effgood = -1;
  // t_X2effall = -1;
  // t_X2effdt = -1;
  // t_X2effgroup = -1;
  // t_X2effgood = -1;
  // t_U2effall = -1;
  // t_U2effdt = -1;
  // t_U2effgroup = -1;
  // t_U2effgood = -1;

  //#ifdef _FULLANALYSIS
  // t_X1TimeDiff = -100;
  // t_nX1wiresUsed = 0;
  // t_nU1wiresUsed = 0;
  // t_nX2wiresUsed = 0;
  // t_nU2wiresUsed = 0;
  // t_X1doublewires = -1;
  // t_U1doublewires = -1;
  // t_X2doublewires = -1;
  // t_U2doublewires = -1;
  // t_X1multiplemin = -1;
  // t_U1multiplemin = -1;
  // t_X2multiplemin = -1;
  // t_U2multiplemin = -1;
  // for (int i = 0; i < MAX_WIRES_PER_EVENT; i++) {
  // t_X1wireUsed[i] = -1;
  // t_U1wireUsed[i] = -1;
  // t_X2wireUsed[i] = -1;
  // t_U2wireUsed[i] = -1;
  // t_X1distUsed[i] = -1.;
  //}
  //#endif

  // t_pulser = 0;

  //#ifdef _MOVIE
  // for (int i = 0; i < MAX_WIRES_PER_EVENT; i++) {
  // t_X1dt[i] = -1.0;
  // t_U1dt[i] = -1.0;
  // t_X2dt[i] = -1.0;
  // t_U2dt[i] = -1.0; // without this the X1dt will have junk in above and
  //                  // beyond the good data
  // t_X1wire[i] = -1;
  // t_U1wire[i] = -1;
  // t_X2wire[i] = -1;
  // t_U2wire[i] = -1;
  //}
  //#endif

  //#ifdef _POLARIZATION
  // t_polu = 0;
  // t_pold = 0;
  //#endif

  t_eventID = 0.0;
  t_X1 = 0.0;
  t_U1 = 0.0;
  t_X2 = 0.0;
  t_U2 = 0.0;
  t_Y1 = 0.0;
  t_Y2 = 0.0;
  t_X1pos = 0.0;
  t_X1posC = 0.0;
  t_Y1pos = 0.0;
  t_Y1posC = 0.0;
  t_Th1 = 0.0;
  t_Ps1 = 0.0;
  t_Th2 = 0.0;
  t_Ps2 = 0.0;
  t_psiFP = 0.0;
  t_thetaFP = 0.0;
  t_phiFP = 0.0;
  t_thetaSCAT = 0.0;
  t_phiSCAT = 0.0;
  t_Zttgt = 0.0;
  // t_tdc_x1 = 0.0;
  // t_tdc_u1 = 0.0;
  // t_tdc_x2 = 0.0;
  // t_tdc_u2 = 0.0;
  // t_tdc_x1_cor = 0.0;
  // t_tdc_u1_cor = 0.0;
  // t_tdc_x2_cor = 0.0;
  // t_tdc_u2_cor = 0.0;
  // t_Xferet = 0.0;
  // t_fera = 0.0;
  // t_feret = 0.0;
  t_tof = 0.0;
  t_cor_tof = 0.0;
  t_scintillator_ave_1 = 0.0;
  t_scintillator_ave_1 = 0.0;
  t_scintillator_ave_2 = 0.0;
  t_scintillator_ave_2 = 0.0;
  t_chisq_x1 = 0.0;
  t_chisq_u1 = 0.0;
  t_chisq_x2 = 0.0;
  t_chisq_u2 = 0.0;
  t_num_wire_x1 = 0.0;
  t_num_wire_u1 = 0.0;
  t_num_wire_x2 = 0.0;
  t_num_wire_u2 = 0.0;
  t_Pout = 0.0;
  t_Eout = 0.0;
  t_Ex = 0.0;
  t_success_X1 = 0.0;
  t_success_U1 = 0.0;
  t_success_X2 = 0.0;
  t_success_U2 = 0.0;

  return 1;
}
