#ifndef SORTER_PAR_H_
#define SORTER_PAR_H_

#include <array>
#include <string>

#define MAX_THTGT_PAR 50
#define MAX_PHTGT_PAR 100
#define MAX_CORTOF_PAR 5
#define MAX_FERETPOS_PAR 3
#define MAX_GLOBAL_XCOR_TH_PAR 50
#define MAX_GLOBAL_XCOR_PH_PAR 50
#define MAX_XCOR_TH_PAR 50
#define MAX_XCOR_PH_PAR 50
#define MAX_RECOIL_PAR 20
#define MAX_POUT_PAR 6
#define MAX_EXCOR_PAR 4
#define MAX_XGATE_SIEVESLIT 20

struct parameters {
  std::string globalareaname;
  std::string online_host;
  int switch_online;
  int switch_byteswap; //<- jidou de yomitoru you ni shita
  int start_block, stop_block;
  double scinti_1_min, scinti_1_max, scinti_2_min, scinti_2_max;
  double cortof_1_min, cortof_1_max, cortof_2_min, cortof_2_max;
  std::array<int, 12> tdcoffset16_x1= {0};
  std::array<int, 13> tdcoffset16_u1= {0};
  std::array<int, 12> tdcoffset16_x2= {0};
  std::array<int, 13> tdcoffset16_u2= {0};
  std::array<int, 192> tdcoffset_x1= {0};
  std::array<int, 208> tdcoffset_u1= {0};
  std::array<int, 192> tdcoffset_x2= {0};
  std::array<int, 208> tdcoffset_u2= {0};
  //  double tdc_x1_shift,tdc_u1_shift,tdc_x2_shift,tdc_u2_shift; <- not used
  double chisq_x1_max, chisq_u1_max, chisq_x2_max, chisq_u2_max;
  int clustersize_x1_min, clustersize_x1_max, clustersize_u1_min,
      clustersize_u1_max, clustersize_x2_min, clustersize_x2_max,
      clustersize_u2_min, clustersize_u2_max;
  int tdc_x1_min, tdc_x1_max, tdc_u1_min, tdc_u1_max, tdc_x2_min, tdc_x2_max,
      tdc_u2_min, tdc_u2_max;
  std::array<double, 3> drifttable1_x1_par= {0.0}, drifttable1_u1_par= {0.0},
      drifttable1_x2_par= {0.0}, drifttable1_u2_par= {0.0};
  std::array<double, 4> drifttable2_x1_par= {0.0}, drifttable2_u1_par= {0.0},
      drifttable2_x2_par= {0.0}, drifttable2_u2_par= {0.0};
  std::array<int, MAX_THTGT_PAR> thtgt_par_xorder= {0}, thtgt_par_thorder= {0};
  std::array<int, MAX_PHTGT_PAR> phtgt_par_xorder= {0}, phtgt_par_thorder= {0},
      phtgt_par_yorder;
  std::array<double, MAX_THTGT_PAR> thtgt_par= {0.0};
    std::array<double, MAX_PHTGT_PAR> phtgt_par= {0.0};
  double thtgt_offset, phtgt_offset, xfp_offset;
  std::array<double, MAX_CORTOF_PAR> cortof_par= {0.0};
  std::array<double, MAX_FERETPOS_PAR> feretposi_par= {0.0};
  std::string bldfilename, hbfilename, rootfilename, ntpfilename, logfilename,
      drifttablefilename, scalerfilename, histconfigfilename;
  double ThGR;
  int switch_ntuple, switch_feret;
  int switch_thtgt, switch_phtgt, switch_global_xcor_th, switch_global_xcor_ph,
      switch_xcor_th, switch_xcor_ph, switch_ex, switch_dl,
      switch_discard_shortdl, switch_pout, switch_recoil_cor;
  //    switch_tdc_optimize;
  int switch_plot_fera, switch_plot_feret, switch_plot_3377, switch_plot_system,
      switch_plot_vdc, switch_plot_scinti_tof,
      switch_plot_user, // switch_plot_user_gated,
      switch_plot_high_reso;
  int switch_plot_dama; // NO:0, Y:1, Ph:2
  int switch_histconfig;
  std::array<double, MAX_XGATE_SIEVESLIT> xgate_min_dama = {0.0}, xgate_max_dama= {0.0};
  std::string target;
  std::array<double, MAX_GLOBAL_XCOR_TH_PAR> global_xcor_th_par= {0.0};

  std::array<double, MAX_GLOBAL_XCOR_PH_PAR> global_xcor_ph_par= {0.0};
  std::array<double, MAX_XCOR_TH_PAR> xcor_th_par= {0.0};
  std::array<double, MAX_XCOR_PH_PAR> xcor_ph_par= {0.0};

  std::array<int, MAX_GLOBAL_XCOR_TH_PAR> global_xcor_th_xorder= {0},
      global_xcor_th_thorder= {0};

  std::array<int, MAX_GLOBAL_XCOR_PH_PAR> global_xcor_ph_xorder= {0},
      global_xcor_ph_phorder= {0};

  std::array<int, MAX_XCOR_TH_PAR> xcor_th_xorder= {0}, xcor_th_thorder= {0};
  std::array<int, MAX_XCOR_PH_PAR> xcor_ph_xorder= {0}, xcor_ph_phorder= {0};
  // keVpermm,
  double ebeam, qvalue, mout;
  std::array<double, MAX_RECOIL_PAR> recoil_par= {0.0};
  std::array<int, MAX_RECOIL_PAR> recoil_eorder= {0}, recoil_ztorder= {0};

  std::array<double, MAX_POUT_PAR> pout_par= {0.0}, pout_cor_par= {0.0};

  std::array<double, MAX_EXCOR_PAR> ex_cor_par= {0.0};

  // スケーラ情報をここに含めても良いかも
  int num_discard_event;
  int flg_discard_event;
};

#endif
