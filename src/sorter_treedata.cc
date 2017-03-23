
#include "sorter_treedata.h"

#include "TTree.h"

int Sorter_treedata::init_tree(TTree *tree_i) {

  tree = tree_i;

  tree->Branch("eventID", &t_eventID, "t_eventID/I");

  // t1->Branch("runtime",&t_runtime,"t_runtime/I");
  // t1->Branch("evtcounter",&t_evtcounter,"t_evtcounter/I");
  // t1->Branch("tdcsperevent",&t_tdcsperevent,"t_tdcsperevent/I");

  // t1->Branch("triggerI",&t_triggerI,"t_triggerI/I");
  // t1->Branch("triggerU",&t_triggerU,"t_triggerU/I");
  // t1->Branch("CIU",&t_CIU,"t_CIU/I");
  // t1->Branch("CII",&t_CII,"t_CII/I");

  // t1->Branch("tof",&t_tof,"t_tof/I");
  // t1->Branch("toftdc2",&t_toftdc2,"t_toftdc2/I");
  // t1->Branch("toftdc3",&t_toftdc3,"t_toftdc3/I");
  // t1->Branch("toftdc4",&t_toftdc4,"t_toftdc4/I");
  // t1->Branch("toftdc5",&t_toftdc5,"t_toftdc5/I");
  // t1->Branch("toftdc6",&t_toftdc6,"t_toftdc6/I");
  // t1->Branch("toftdc7",&t_toftdc7,"t_toftdc7/I");

  // t1->Branch("k600",&t_k600,"t_k600/I");

  // t1->Branch("pad1",&t_pad1,"t_pad1/D");
  // t1->Branch("pad2",&t_pad2,"t_pad2/D");
  // t1->Branch("pad1hiP",&t_pad1hiP,"t_pad1hiP/D");
  // t1->Branch("pad1lowP",&t_pad1lowP,"t_pad1lowP/D");
  // t1->Branch("pad2hiP",&t_pad2hiP,"t_pad2hiP/D");
  // t1->Branch("pad2lowP",&t_pad2lowP,"t_pad2lowP/D");
  // t1->Branch("pad1hiPT",&t_pad1hiPT,"t_pad1hiPT/D");
  // t1->Branch("pad1lowPT",&t_pad1lowPT,"t_pad1lowPT/D");
  // t1->Branch("pad2hiPT",&t_pad2hiPT,"t_pad2hiPT/D");
  // t1->Branch("pad2lowPT",&t_pad2lowPT,"t_pad2lowPT/D");

  tree->Branch("X1pos", &t_X1pos, "t_X1pos/D");
  tree->Branch("X1th", &t_X1th, "t_X1th/D");
  // t1->Branch("X1flag",&t_X1flag,"t_X1flag/I");
  // t1->Branch("X1chisq",&t_X1chisq,"t_X1chisq/D");
  // t1->Branch("X1res0",&t_X1res0,"t_X1res0/D");
  // t1->Branch("X1res1",&t_X1res1,"t_X1res1/D");
  // t1->Branch("X1hits",&t_X1hits,"t_X1hits/I");
  // t1->Branch("X1effID",&t_X1effID,"t_X1effID/D");
  // t1->Branch("X1effall",&t_X1effall,"t_X1effall/D");
  // t1->Branch("X1effdt",&t_X1effdt,"t_X1effdt/D");
  // t1->Branch("X1effgroup",&t_X1effgroup,"t_X1effgroup/D");
  // t1->Branch("X1effgood",&t_X1effgood,"t_X1effgood/D");
  //#ifdef _VDCRESCALCS
  // t1->Branch("X1res2",&t_X1res2,"t_X1res2/D");
  // t1->Branch("X1res3",&t_X1res3,"t_X1res3/D");
  // t1->Branch("X1res4",&t_X1res4,"t_X1res4/D");
  // t1->Branch("X1res5",&t_X1res5,"t_X1res5/D");
  // t1->Branch("X1res6",&t_X1res6,"t_X1res6/D");
  // t1->Branch("X1res7",&t_X1res7,"t_X1res7/D");
  // t1->Branch("X1res8",&t_X1res8,"t_X1res8/D");
  //#endif
  // #ifdef _FULLANALYSIS
  // t1->Branch("nX1wiresUsed",&t_nX1wiresUsed,"t_nX1wiresUsed/I");
  // t1->Branch("X1doublewires",&t_X1doublewires,"t_X1doublewires/I");
  // t1->Branch("X1multiplemin",&t_X1multiplemin,"t_X1multiplemin/I");
  // t1->Branch("X1TimeDiff",&t_X1TimeDiff,"t_X1TimeDiff/D");
  // t1->Branch("X1wireUsed",t_X1wireUsed,"t_X1wireUsed[t_nX1wiresUsed]/I");
  // t1->Branch("X1distUsed",t_X1distUsed,"t_X1distUsed[t_nX1wiresUsed]/D");
  //#endif

  // t1->Branch("U1pos",&t_U1pos,"t_U1pos/D");
  // t1->Branch("U1th",&t_U1th,"t_U1th/D");
  // t1->Branch("U1flag",&t_U1flag,"t_U1flag/I");
  // t1->Branch("U1chisq",&t_U1chisq,"t_U1chisq/D");
  // t1->Branch("U1res0",&t_U1res0,"t_U1res0/D");
  // t1->Branch("U1res1",&t_U1res1,"t_U1res1/D");
  // t1->Branch("U1effID",&t_U1effID,"t_U1effID/D");
  // t1->Branch("U1hits",&t_U1hits,"t_U1hits/I");
  // t1->Branch("U1effall",&t_U1effall,"t_U1effall/D");
  // t1->Branch("U1effdt",&t_U1effdt,"t_U1effdt/D");
  // t1->Branch("U1effgroup",&t_U1effgroup,"t_U1effgroup/D");
  // t1->Branch("U1effgood",&t_U1effgood,"t_U1effgood/D");
  //#ifdef _VDCRESCALCS
  // t1->Branch("U1res2",&t_U1res2,"t_U1res2/D");
  // t1->Branch("U1res3",&t_U1res3,"t_U1res3/D");
  // t1->Branch("U1res4",&t_U1res4,"t_U1res4/D");
  // t1->Branch("U1res5",&t_U1res5,"t_U1res5/D");
  // t1->Branch("U1res6",&t_U1res6,"t_U1res6/D");
  // t1->Branch("U1res7",&t_U1res7,"t_U1res7/D");
  // t1->Branch("U1res8",&t_U1res8,"t_U1res8/D");
  //#endif
  //#ifdef _FULLANALYSIS
  // t1->Branch("nU1wiresUsed",&t_nU1wiresUsed,"t_nU1wiresUsed/I");
  // t1->Branch("U1doublewires",&t_U1doublewires,"t_U1doublewires/I");
  // t1->Branch("U1multiplemin",&t_U1multiplemin,"t_U1multiplemin/I");
  // t1->Branch("U1wireUsed",t_U1wireUsed,"t_U1wireUsed[t_nU1wiresUsed]/I");
  //#endif

  // t1->Branch("X2pos",&t_X2pos,"t_X2pos/D");
  // t1->Branch("X2th",&t_X2th,"t_X2th/D");
  // t1->Branch("X2flag",&t_X2flag,"t_X2flag/I");
  // t1->Branch("X2chisq",&t_X2chisq,"t_X2chisq/D");
  // t1->Branch("X2res0",&t_X2res0,"t_X2res0/D");
  // t1->Branch("X2res1",&t_X2res1,"t_X2res1/D");
  // t1->Branch("X2effID",&t_X2effID,"t_X2effID/D");
  // t1->Branch("X2hits",&t_X2hits,"t_X2hits/I");
  // t1->Branch("X2effall",&t_X2effall,"t_X2effall/D");
  // t1->Branch("X2effdt",&t_X2effdt,"t_X2effdt/D");
  // t1->Branch("X2effgroup",&t_X2effgroup,"t_X2effgroup/D");
  // t1->Branch("X2effgood",&t_X2effgood,"t_X2effgood/D");
  //#ifdef _VDCRESCALCS
  // t1->Branch("X2res2",&t_X2res2,"t_X2res2/D");
  // t1->Branch("X2res3",&t_X2res3,"t_X2res3/D");
  // t1->Branch("X2res4",&t_X2res4,"t_X2res4/D");
  // t1->Branch("X2res5",&t_X2res5,"t_X2res5/D");
  // t1->Branch("X2res6",&t_X2res6,"t_X2res6/D");
  // t1->Branch("X2res7",&t_X2res7,"t_X2res7/D");
  // t1->Branch("X2res8",&t_X2res8,"t_X2res8/D");
  //#endif
  //#ifdef _FULLANALYSIS
  // t1->Branch("nX2wiresUsed",&t_nX2wiresUsed,"t_nX2wiresUsed/I");
  // t1->Branch("X2doublewires",&t_X2doublewires,"t_X2doublewires/I");
  // t1->Branch("X2multiplemin",&t_X2multiplemin,"t_X2multiplemin/I");
  // t1->Branch("X2wireUsed",t_X2wireUsed,"t_X2wireUsed[t_nX2wiresUsed]/I");
  //#endif

  // t1->Branch("U2pos",&t_U2pos,"t_U2pos/D");
  // t1->Branch("U2th",&t_U2th,"t_U2th/D");
  // t1->Branch("U2flag",&t_U2flag,"t_U2flag/I");
  // t1->Branch("U2chisq",&t_U2chisq,"t_U2chisq/D");
  // t1->Branch("U2res0",&t_U2res0,"t_U2res0/D");
  // t1->Branch("U2res1",&t_U2res1,"t_U2res1/D");
  // t1->Branch("U2effID",&t_U2effID,"t_U2effID/D");
  // t1->Branch("U2hits",&t_U2hits,"t_U2hits/I");
  // t1->Branch("U2effall",&t_U2effall,"t_U2effall/D");
  // t1->Branch("U2effdt",&t_U2effdt,"t_U2effdt/D");
  // t1->Branch("U2effgroup",&t_U2effgroup,"t_U2effgroup/D");
  // t1->Branch("U2effgood",&t_U2effgood,"t_U2effgood/D");
  //#ifdef _VDCRESCALCS
  // t1->Branch("U2res2",&t_U2res2,"t_U2res2/D");
  // t1->Branch("U2res3",&t_U2res3,"t_U2res3/D");
  // t1->Branch("U2res4",&t_U2res4,"t_U2res4/D");
  // t1->Branch("U2res5",&t_U2res5,"t_U2res5/D");
  // t1->Branch("U2res6",&t_U2res6,"t_U2res6/D");
  // t1->Branch("U2res7",&t_U2res7,"t_U2res7/D");
  // t1->Branch("U2res8",&t_U2res8,"t_U2res8/D");
  //#endif
  //#ifdef _FULLANALYSIS
  // t1->Branch("nU2wiresUsed",&t_nU2wiresUsed,"t_nU2wiresUsed/I");
  // t1->Branch("U2doublewires",&t_U2doublewires,"t_U2doublewires/I");
  // t1->Branch("U2multiplemin",&t_U2multiplemin,"t_U2multiplemin/I");
  // t1->Branch("U2wireUsed",t_U2wireUsed,"t_U2wireUsed[t_nU2wiresUsed]/I");
  //#endif

  tree->Branch("thetaFP", &t_thetaFP, "t_thetaFP/D");
  // t1->Branch("thetaFPx",&t_thetaFPx,"t_thetaFPx/D");
  tree->Branch("phiFP", &t_phiFP, "t_phiFP/D");
  tree->Branch("Y1", &t_Y1, "t_Y1/D");
  tree->Branch("Y2", &t_Y2, "t_Y2/D");
  // t1->Branch("pulser",&t_pulser,"t_pulser/I");
  // t1->Branch("X1posC",&t_X1posC,"t_X1posC/D");
  // t1->Branch("X1posO",&t_X1posO,"t_X1posO/D");
  // t1->Branch("Ex",&t_Ex,"t_Ex/D");
  // t1->Branch("ExC",&t_ExC,"t_ExC/D");
  // t1->Branch("T3",&t_T3,"t_T3/D");
  // t1->Branch("rigidity3",&t_rigidity3,"t_rigidity3/D");
  // t1->Branch("theta",&t_theta,"t_theta/D");
  tree->Branch("thetaSCAT", &t_thetaSCAT, "t_thetaSCAT/D");
  tree->Branch("phiSCAT", &t_phiSCAT, "t_phiSCAT/D");

  //#ifdef _POLARIZATION
  // t1->Branch("polu", &t_polu, "t_polu/I"); // PR153, polarized beam
  // t1->Branch("pold", &t_pold, "t_pold/I"); // PR153, polarized beam
  //#endif

  //#ifdef _MOVIE
  // t1->Branch("nX1wires", &t_nX1wires,
  //           "t_nX1wires/I"); // for dynamic size of X1dt in tree
  // t1->Branch("nU1wires", &t_nU1wires,
  //           "t_nU1wires/I"); // for dynamic size of U1dt in tree
  // t1->Branch("nX2wires", &t_nX2wires,
  //           "t_nX2wires/I"); // for dynamic size of X2dt in tree
  // t1->Branch("nU2wires", &t_nU2wires,
  //           "t_nU2wires/I"); // for dynamic size of X2dt in tree
  // t1->Branch("X1dt", t_X1dt, "t_X1dt[t_nX1wires]/D");
  // t1->Branch("U1dt", t_U1dt, "t_U1dt[t_nU1wires]/D");
  // t1->Branch("X2dt", t_X2dt, "t_X2dt[t_nX2wires]/D");
  // t1->Branch("U2dt", t_U2dt, "t_U2dt[t_nU2wires]/D");
  // t1->Branch("X1wire", t_X1wire, "t_X1wire[t_nX1wires]/I");
  // t1->Branch("U1wire", t_U1wire, "t_U1wire[t_nU1wires]/I");
  // t1->Branch("X2wire", t_X2wire, "t_X2wire[t_nX2wires]/I");
  // t1->Branch("U2wire", t_U2wire, "t_U2wire[t_nU2wires]/I");

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

  return 1;
}
