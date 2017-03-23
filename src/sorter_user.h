#ifndef SORTER_USER_H_
#define SORTER_USER_H_

#include <array>
#include <string>

#include "sorter_par.h"
#include "sorter_root.h"
#include "sorter_treedata.h"

class Sorter_user {

public:
  unsigned int num_EvtID0 = 0, num_EvtID1 = 0, num_EvtID2 = 0, num_EvtID4 = 0,
               num_EvtID8 = 0;

  double _abs(double in);

  int apply_offset(double &_Thtgt, double &_Phtgt, double &_Zttgt, double &_Xfp,
                   struct parameters &_par_sorter);

  int cleanup_tdc_u(int WCID, std::array<int, 208> _tdc, int _wire_num,
                    struct parameters &_par_sorter, Sorter_root &s_root);
  int cleanup_tdc_x(int WCID, std::array<int, 192> _tdc, int _wire_num,
                    struct parameters &_par_sorter, Sorter_root &s_root);

  void combine_ray(double _X1, double _X2, double _U1, double _U2, double &_Y1,
                   double &_Y2, double &_Yfp, double &_Thfp, double &_Psfp,
                   double &_Phfp);

  int compare_vdc_xferet(int _eventid, double _X1, double _U1, double _X2,
                         double _U2, double _Xferet,
                         struct scalers &_sca_sorter);
  void corr_tof(int _tof, double &_cor_tof, double _Thtgt, double _Xfp,
                struct parameters &_par_sorter);

  void count_cluster_u(std::array<int, 208> _tdc, int &_num_cluster, int WCID,
                       struct parameters &_par_sorter);
  void count_cluster_x(std::array<int, 192> _tdc, int &_num_cluster, int WCID,
                       struct parameters &_par_sorter);
  int fp_correction(double &_Xfp, double _Thtgt, double _Phtgt,
                    struct parameters &_par_sorter);

  void get_driftlength(
      std::array<int, 192> &_tdc_x1, std::array<int, 208> &_tdc_u1,
      std::array<int, 192> &_tdc_x2, std::array<int, 208> &_tdc_u2,
      std::array<double, 192> &_drift_x1, std::array<double, 208> &_drift_u1,
      std::array<double, 192> &_drift_x2, std::array<double, 208> &_drift_u2,
      std::array<double, 1024> &_drifttable_x1,
      std::array<double, 1024> &_drifttable_u1,
      std::array<double, 1024> &_drifttable_x2,
      std::array<double, 1024> &_drifttable_u2, struct parameters &_par_sorter,
      Sorter_root &s_root);

  void get_drifttable1(std::array<double, 1024> &_drifttable_x1,
                       std::array<double, 1024> &_drifttable_u1,
                       std::array<double, 1024> &_drifttable_x2,
                       std::array<double, 1024> &_drifttable_u2,
                       struct parameters &_par_sorter);
  void get_drifttable2(std::array<double, 1024> &_drifttable_x1,
                       std::array<double, 1024> &_drifttable_u1,
                       std::array<double, 1024> &_drifttable_x2,
                       std::array<double, 1024> &_drifttable_u2,
                       struct parameters &_par_sorter);
  void get_drifttable3(std::array<double, 1024> &_drifttable_x1,
                       std::array<double, 1024> &_drifttable_u1,
                       std::array<double, 1024> &_drifttable_x2,
                       std::array<double, 1024> &_drifttable_u2,
                       struct parameters &_par_sorter);
  void get_drifttable4(std::array<double, 1024> &_drifttable_x1,
                       std::array<double, 1024> &_drifttable_u1,
                       std::array<double, 1024> &_drifttable_x2,
                       std::array<double, 1024> &_drifttable_u2,
                       struct parameters &_par_sorter);

  int get_epout(double _Xfp, double &_Pout, double &_Eout,
                struct parameters &_par_sorter);

  int get_erec(double _Zttgt, double _Eout, double &_Erec_center,
               double &_Erec_Zt, struct parameters &_par_sorter);

  int get_eventid(int _num_wire_x1, int _num_wire_u1, int _num_wire_x2,
                  int _num_wire_u2, double _chisq_x1, double _chisq_u1,
                  double _chisq_x2, double _chisq_u2, int _num_cluster_x1,
                  int _num_cluster_u1, int _num_cluster_x2, int _num_cluster_u2,
                  double _scintillator_ave_1, double _scintillator_ave_2,
                  int _tof, double _cor_tof, double _Xferet,
                  struct parameters &_par_sorter, int &_success_X1,
                  int &_success_U1, int &_success_X2, int &_success_U2);

  int get_ex(double _Eout, double _Erec_center, double &_Ex,
             struct parameters &_par_sorter, double _Xfp);

  void get_tdc_offset(
      std::array<int, 192> &_tdc_x1, std::array<int, 208> &_tdc_u1,
      std::array<int, 192> &_tdc_x2, std::array<int, 208> &_tdc_u2,
      std::array<int, 192> &_tdc_x1_cor, std::array<int, 208> &_tdc_u1_cor,
      std::array<int, 192> &_tdc_x2_cor, std::array<int, 208> &_tdc_u2_cor,
      struct parameters &_par_sorter);

  void get_x_feret(std::array<unsigned int, 5> &_feret, double &_Xferet,
                   struct parameters &_par_sorter, struct scalers &_sca_sorter);

  int kinema_correction(double &_Xfp, double _Erec_center, double _Erec_Zt,
                        double _Eout, double _Pout,
                        struct parameters &_par_sorter);
  int raytrace_u(std::array<double, 208> _drift, double &_X, double &_Th,
                 double &_chisq, int &_wire_num, int WCID,
                 struct parameters &_par_sorter, struct scalers &_sca_sorter,
                 Sorter_root &s_root);
  int raytrace_x(std::array<double, 192> _drift, double &_X, double &_Th,
                 double &_chisq, int &_wire_num, int WCID,
                 struct parameters &_par_sorter, struct scalers &_sca_sorter,
                 Sorter_root &s_root);
  void reconstruct_thphtgt(double _Xfp, double _Thfp, double _Yfp, double _Phfp,
                           double &_Thtgt, double &_Phtgt,
                           struct parameters &_par_sorter);

  int user_analysis(std::array<int, 192> &_tdc_x1,
                    std::array<int, 208> &_tdc_u1,
                    std::array<int, 192> &_tdc_x2,
                    std::array<int, 208> &_tdc_u2,
                    std::array<unsigned int, 4> &_fera,
                    std::array<unsigned int, 5> &_feret,
                    std::array<double, 1024> &_drifttable_x1,
                    std::array<double, 1024> &_drifttable_u1,
                    std::array<double, 1024> &_drifttable_x2,
                    std::array<double, 1024> &_drifttable_u2, int _num_wire_x1,
                    int _num_wire_u1, int _num_wire_x2, int _num_wire_u2,
                    struct parameters &_par_sorter, struct scalers &_sca_sorter,
                    struct hist_parameters &_par_hist, Sorter_root &s_root,
                    Sorter_treedata &s_treedata);

private:
  /* ---------- maximum chi square ---------- */
  double MAXCHISQ_X1 = 0;
  double MAXCHISQ_U1 = 0;
  double MAXCHISQ_X2 = 0;
  double MAXCHISQ_U2 = 0;

  /* minimum and maximum number of wire */
  int min_num_wire_x1 = 0;
  int min_num_wire_u1 = 0;
  int min_num_wire_x2 = 0;
  int min_num_wire_u2 = 0;

  int max_num_wire_x1 = 0;
  int max_num_wire_u1 = 0;
  int max_num_wire_x2 = 0;
  int max_num_wire_u2 = 0;

  /* ----- TDC useful range ----- */
  int min_apply_tdc_x1 = 0;
  int min_apply_tdc_u1 = 0;
  int min_apply_tdc_x2 = 0;
  int min_apply_tdc_u2 = 0;

  int max_apply_tdc_x1 = 0;
  int max_apply_tdc_u1 = 0;
  int max_apply_tdc_x2 = 0;
  int max_apply_tdc_u2 = 0;
};

#endif
