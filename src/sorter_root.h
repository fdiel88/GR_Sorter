#ifndef SORTER_ROOT_H_
#define SORTER_ROOT_H_

#include <vector>

#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

#include "sorter_histpar.h"
#include "sorter_par.h"
//#include "fd_sorter.h"

class Sorter_root {

public:
  TH1F *find_hist_1D(std::string name, std::vector<TH1F *> &list);
  TH1F *find_hist_1D_global(std::string name);
  TH2F *find_hist_2D(std::string name, std::vector<TH2F *> &list);
  TH2F *find_hist_2D_global(std::string name);
  TProfile *find_hist_Prof(std::string name, std::vector<TProfile *> &list);

  void fill_gatedhist_user(
      double _X1, double _U1, double _Y1, double _X2, double _U2, double _Y2,
      double _Th1, double _Ps1, double _Th2, double _Ps2, double _Xfp,
      double _Yfp, double _Thfp, double _Psfp, double _Phfp, double _Thtgt,
      double _Phtgt, double _Zttgt, double _Xferet,
      std::array<unsigned int, 4> &_fera, std::array<unsigned int, 5> &_feret,
      int _tof, double _cor_tof, double _scintillator_ave_1,
      double _scintillator_ave_2, double _chisq_x1, double _chisq_u1,
      double _chisq_x2, double _chisq_u2,
      //			 double __pad_posi1,double __pad_posi2,
      int _eventid,
      //			 double _t_mom, double _Ex){
      double _Pout, double _Eout, double _Ex, struct parameters &_par_sorter);

  void fill_gatedwire(std::array<int, 192> &_v3377_tdc_X1,
                      std::array<int, 208> &_v3377_tdc_U1,
                      std::array<int, 192> &_v3377_tdc_X2,
                      std::array<int, 208> &_v3377_tdc_U2);

  void fill_hist_cluster(int _num_cluster_x1, int _num_cluster_u1,
                         int _num_cluster_x2, int _num_cluster_u2);
  void fill_hist_config(double _X1, double _U1, double _Y1, double _X2,
                        double _U2, double _Y2, double _Th1, double _Ps1,
                        double _Th2, double _Ps2, double _Xfp, double _Yfp,
                        double _Thfp, double _Psfp, double _Phfp, double _Thtgt,
                        double _Phtgt, double _Zttgt, double _Xferet,
                        std::array<unsigned int, 4> _fera,
                        std::array<unsigned int, 5> _feret, int _tof,
                        double _cor_tof, double _scintillator_ave_1,
                        double _scintillator_ave_2, double _chisq_x1,
                        double _chisq_u1, double _chisq_x2, double _chisq_u2,
                        int _eventid, int _num_wire_x1, int _num_wire_u1,
                        int _num_wire_x2, int _num_wire_u2, double _Eout,
                        int _success_X1, int _success_U1, int _success_X2,
                        int _success_U2, struct hist_parameters &_par_hist);
  void fill_hist_dama(double _Xfp, double _Thtgt, double _Yfp, double _Phtgt,
                      int _eventid, struct parameters &_par_sorter);
  void fill_hist_dl_accuracy(double dif, int _WCID);
  void fill_hist_driftlength(std::array<double, 192> &_drift_x1,
                             std::array<double, 208> &_drift_u1,
                             std::array<double, 192> &_drift_x2,
                             std::array<double, 208> &_drift_u2);

  void fill_hist_drifttable(std::array<double, 1024> _drifttable_x1,
                            std::array<double, 1024> _drifttable_u1,
                            std::array<double, 1024> _drifttable_x2,
                            std::array<double, 1024> _drifttable_u2);

  void fill_hist_high_reso(double _Xfp, double _Yfp, double _Thfp,
                           double _Thtgt, double _Phtgt, double _Zttgt,
                           double _Ex, int _eventid,
                           struct parameters &_par_sorter);

  void fill_hist_rayid(int _WCID, int _rayid);
  void fill_hist_resolution(int _wireID, double drift, double drift_esti,
                            int _XID);
  void fill_hist_rubbishwire(int wireid, int xid);
  void fill_hist_twowires(int _WCID, int TDC_firstwire, int TDC_secondwire);

  void fill_hist_user(double _X1, double _U1, double _Y1, double _X2,
                      double _U2, double _Y2, double _Th1, double _Ps1,
                      double _Th2, double _Ps2, double _Xfp, double _Yfp,
                      double _Thfp, double _Psfp, double _Phfp, double _Thtgt,
                      double _Phtgt, double _Zttgt, double _Xferet,
                      std::array<unsigned int, 4> &_fera,
                      std::array<unsigned int, 5> &_feret, int _tof,
                      double _cor_tof, double _scintillator_ave_1,
                      double _scintillator_ave_2, double _chisq_x1,
                      double _chisq_u1, double _chisq_x2, double _chisq_u2,
                      int _eventid, int _num_wire_x1, int _num_wire_u1,
                      int _num_wire_x2, int _num_wire_u2, double _Eout,
                      int _success_X1, int _success_U1, int _success_X2,
                      int _success_U2, struct parameters &_par_sorter);
  void fill_hist_wire(
      std::array<int, 192> &_tdc_x1, std::array<int, 208> &_tdc_u1,
      std::array<int, 192> &_tdc_x2, std::array<int, 208> &_tdc_u2,
      std::array<int, 192> &_tdc_x1_cor, std::array<int, 208> &_tdc_u1_cor,
      std::array<int, 192> &_tdc_x2_cor, std::array<int, 208> &_tdc_u2_cor);

  int get_values_hist_config(
      double _X1, double _U1, double _Y1, double _X2, double _U2, double _Y2,
      double _Th1, double _Ps1, double _Th2, double _Ps2, double _Xfp,
      double _Yfp, double _Thfp, double _Psfp, double _Phfp, double _Thtgt,
      double _Phtgt, double _Zttgt, double _Xferet,
      std::array<unsigned int, 4> _fera, std::array<unsigned int, 5> _feret,
      int _tof, double _cor_tof, double _scintillator_ave_1,
      double _scintillator_ave_2, double _chisq_x1, double _chisq_u1,
      double _chisq_x2, double _chisq_u2, int _eventid, int _num_wire_x1,
      int _num_wire_u1, int _num_wire_x2, int _num_wire_u2, double _Eout,
      int _success_X1, int _success_U1, int _success_X2, int _success_U2,
      std::string &par_name, double &par_double);

  void open_hist(struct parameters &_par_sorter,
                 struct hist_parameters &_par_hist);
  void open_hist_config(struct hist_parameters &_par_hist);

  void open_hist_dama(struct parameters &_par_sorter);
  void open_hist_fera();
  void open_hist_feret();
  void open_hist_scaler();
  void open_hist_scintillator_tof();
  void open_hist_system();
  void open_hist_user(struct parameters &_par_sorter);
  void open_hist_wire();
  void write_root(struct parameters &_par_sorter);

private:
  // std::vector<TH1F*> m_fera_hist;

  std::vector<TH1F *> m_hist_conf_1D;
  std::vector<TH2F *> m_hist_conf_2D;

  std::vector<TH1F *> m_hist_dama_1D;
  std::vector<TH2F *> m_hist_dama_2D;

  std::vector<TH1F *> m_hist_fera_1D;

  std::vector<TH1F *> m_hist_feret_1D;

  std::vector<TH1F *> m_hist_scaler_1D;

  std::vector<TH1F *> m_hist_scintillator_tof_1D;
  std::vector<TH2F *> m_hist_scintillator_tof_2D;

  std::vector<TH1F *> m_hist_system_1D;
  std::vector<TH2F *> m_hist_system_2D;
  std::vector<TProfile *> m_hist_system_prof;

  std::vector<TH1F *> m_hist_user_1D;
  std::vector<TH2F *> m_hist_user_2D;
  std::vector<TProfile *> m_hist_user_prof;

  std::vector<TH1F *> m_hist_v3377_1D;
  std::vector<TH2F *> m_hist_v3377_2D;

  std::vector<TH1F *> m_hist_wire_1D;

  const int fera_histID = 400;  // 0~+12
  const int feret_histID = 500; // 0~+15

  const int scaler_histID = 1;  // 0~+4
  const int scinti_histID = 10; // 0~+21
  const int v3377_histID = 40;  // 0~+23
  const int wire_histID = 70;   // 0~+15
  const int sys_histID = 100;   // 0~+36
  const int user_histID = 200;  // 0
  const int dama_histID = 600;  // 0~20
};

#endif
