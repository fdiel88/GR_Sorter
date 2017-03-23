#include "sorter_user.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "sorter_const.h"
#include "sorter_par.h"
#include "sorter_root.h"
#include "sorter_scaler.h"
#include "sorter_treedata.h"

double Sorter_user::_abs(double in) {
  if (in < 0) {
    return (-1) * in;
  } else {
    return in;
  }
}

int Sorter_user::apply_offset(double &_Thtgt, double &_Phtgt, double &_Zttgt,
                              double &_Xfp, struct parameters &_par_sorter) {
  // === This process must be done after GLOBAL FP CORRECTION! ===
  if (_par_sorter.thtgt_offset) {
    _Thtgt += _par_sorter.thtgt_offset;
  }
  if (_par_sorter.phtgt_offset) {
    _Phtgt += _par_sorter.phtgt_offset;
  }
  if (_par_sorter.xfp_offset) {
    _Xfp += _par_sorter.xfp_offset; // hoka mo += ni subeki???
  }
  _Zttgt = sqrt(pow((_Thtgt + _par_sorter.ThGR), 2) + pow(_Phtgt, 2));

  return 0;
}

int Sorter_user::cleanup_tdc_u(int WCID, std::array<int, 208> _tdc,
                               int _wire_num, struct parameters &_par_sorter,
                               Sorter_root &s_root) {
  // WCID -> X1:0, U1:1, X2:2, U2:3

  int i, n_wire = 0,
         rubbishwire_count = 0; // min_num_wire = 0, max_num_wire = 0;

  if (WCID == 1) {
    n_wire = 208;
    // min_num_wire = _par_sorter.clustersize_u1_min;
    // max_num_wire = _par_sorter.clustersize_u1_max;
  } else if (WCID == 3) {
    n_wire = 208;
    // min_num_wire = _par_sorter.clustersize_u2_min;
    // max_num_wire = _par_sorter.clustersize_u2_max;
  } else {
    std::cout << "ERROR : Unknown WCID in cleanup_tdc_u()" << std::endl;
    exit(1);
  }

  // if 2 neighboring wires are not fired -> ignored
  // Wire 0
  if (_tdc[0] && !_tdc[1] && !_tdc[2]) {
    _tdc[0] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(0, WCID);
    ++rubbishwire_count;
  }
  // Wire 1
  if (_tdc[1] && !_tdc[0] && !_tdc[2] && !_tdc[3]) {
    _tdc[1] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(1, WCID);
    ++rubbishwire_count;
  }
  // Wire 2 to n_wire-2
  for (i = 2; i < n_wire - 2; ++i) {
    if (_tdc[i] && !_tdc[i - 2] && !_tdc[i - 1] && !_tdc[i + 1] &&
        !_tdc[i + 2]) {
      _tdc[i] = 0;
      --_wire_num;
      s_root.fill_hist_rubbishwire(i, WCID);
      ++rubbishwire_count;
    }
  }
  // Wire n_wire-1 (2 wires from the end)
  if (_tdc[n_wire - 1] && !_tdc[n_wire] && !_tdc[n_wire - 2] &&
      !_tdc[n_wire - 3]) {
    _tdc[n_wire - 1] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(n_wire - 1, WCID);
    ++rubbishwire_count;
  }
  // Wire n_wire (final wire)
  if (_tdc[n_wire] && !_tdc[n_wire - 1] && !_tdc[n_wire - 2]) {
    _tdc[n_wire] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(n_wire - 2, WCID);
    ++rubbishwire_count;
  }

  // for C shape histograms
  for (i = 0; i < n_wire - 1; ++i) {
    if (_tdc[i] && _tdc[i + 1]) { // default
      //    if(_tdc[i]&&_tdc[i+1]&&_wire_num>=5){ // for test 1
      //    if(_tdc[i]&&_tdc[i+1]&&_wire_num<3){ // for test 2
      //      s_root.fill_hist_twowires(WCID,_tdc[i],_tdc[i+1],2); <- saigo no 2
      //      ha
      //      nani?
      s_root.fill_hist_twowires(WCID, _tdc[i], _tdc[i + 1]);
    }
  }

  return rubbishwire_count;
}
int Sorter_user::cleanup_tdc_x(int WCID, std::array<int, 192> _tdc,
                               int _wire_num, struct parameters &_par_sorter,
                               Sorter_root &s_root) {
  // WCID -> X1:0, U1:1, X2:2, U2:3

  int i, n_wire = 0,
         rubbishwire_count = 0; // min_num_wire = 0, max_num_wire = 0;

  if (WCID == 0) {
    n_wire = 192;
    // min_num_wire = _par_sorter.clustersize_x1_min;
    // max_num_wire = _par_sorter.clustersize_x1_max;
  } else if (WCID == 2) {
    n_wire = 192;
    // min_num_wire = _par_sorter.clustersize_x2_min;
    // max_num_wire = _par_sorter.clustersize_x2_max;
  } else {
    std::cout << "ERROR : Unknown WCID in cleanup_tdc_x()" << std::endl;
    exit(1);
  }

  // if 2 neighboring wires are not fired -> ignored
  // Wire 0
  if (_tdc[0] && !_tdc[1] && !_tdc[2]) {
    _tdc[0] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(0, WCID);
    ++rubbishwire_count;
  }
  // Wire 1
  if (_tdc[1] && !_tdc[0] && !_tdc[2] && !_tdc[3]) {
    _tdc[1] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(1, WCID);
    ++rubbishwire_count;
  }
  // Wire 2 to n_wire-2
  for (i = 2; i < n_wire - 2; ++i) {
    if (_tdc[i] && !_tdc[i - 2] && !_tdc[i - 1] && !_tdc[i + 1] &&
        !_tdc[i + 2]) {
      _tdc[i] = 0;
      --_wire_num;
      s_root.fill_hist_rubbishwire(i, WCID);
      ++rubbishwire_count;
    }
  }
  // Wire n_wire-1 (2 wires from the end)
  if (_tdc[n_wire - 1] && !_tdc[n_wire] && !_tdc[n_wire - 2] &&
      !_tdc[n_wire - 3]) {
    _tdc[n_wire - 1] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(n_wire - 1, WCID);
    ++rubbishwire_count;
  }
  // Wire n_wire (final wire)
  if (_tdc[n_wire] && !_tdc[n_wire - 1] && !_tdc[n_wire - 2]) {
    _tdc[n_wire] = 0;
    --_wire_num;
    s_root.fill_hist_rubbishwire(n_wire - 2, WCID);
    ++rubbishwire_count;
  }

  // for C shape histograms
  for (i = 0; i < n_wire - 1; ++i) {
    if (_tdc[i] && _tdc[i + 1]) { // default
      //    if(_tdc[i]&&_tdc[i+1]&&_wire_num>=5){ // for test 1
      //    if(_tdc[i]&&_tdc[i+1]&&_wire_num<3){ // for test 2
      //      s_root.fill_hist_twowires(WCID,_tdc[i],_tdc[i+1],2); <- saigo no 2
      //      ha
      //      nani?
      s_root.fill_hist_twowires(WCID, _tdc[i], _tdc[i + 1]);
    }
  }

  return rubbishwire_count;
}

void Sorter_user::combine_ray(double _X1, double _X2, double _U1, double _U2,
                              double &_Y1, double &_Y2, double &_Yfp,
                              double &_Thfp, double &_Psfp, double &_Phfp) {

  double u_X1X2 = x_X1X2 * COS4181;

  _Thfp =
      57.29578 * (atan((_X2 - _X1 - x_X1X2) / z_X1X2) + atan(x_X1X2 / z_X1X2));

  _Psfp =
      57.29578 * (atan(z_X1X2 / (_U1 - _U2 + u_X1X2)) - atan(z_X1X2 / u_X1X2));

  // Y can be upside-down? (seems to be correct)
  _Y1 = (-1) * U_TAN_INV * _X1 + _U1 * U_CONST;
  _Y2 = (-1) * U_TAN_INV * _X2 + _U2 * U_CONST;

  _Phfp = 57.29578 * atan((_Y2 - _Y1) / z_X1X2);

  _Yfp = _Y1;
}
int Sorter_user::compare_vdc_xferet(int _eventid, double _X1, double _U1,
                                    double _X2, double _U2, double _Xferet,
                                    struct scalers &_sca_sorter) {
  // int flg_x1 = 0, flg_u1 = 0, flg_x2 = 0, flg_u2 = 0;

  if (_eventid == 0) {
  }

  if ((_Xferet - _X2 > 100. || _Xferet - _X2 < -100.) && _X2 != DEFAULT_WC) {
    //    printf("chkchk : Xferet (%5.2f) <=> X2 (%5.2f) more than
    //    100mm.\n",_Xferet,_X2);
    // わりとおおい。内容要チェック
  }

  if (_Xferet > -600. && _Xferet < +600.) {
    if (_X1 == DEFAULT_WC) {
      // flg_x1 = 1;
    }
    if (_U1 == DEFAULT_WC) {
      // flg_u1 = 1;
    }
    if (_X2 == DEFAULT_WC) {
      // flg_x2 = 1;
    }
    if (_U2 == DEFAULT_WC) {
      // flg_u2 = 1;
    }
  }

  if (_Xferet == DEFAULT_WC) {
  }
  return 1;
}
void Sorter_user::corr_tof(int _tof, double &_cor_tof, double _Thtgt,
                           double _Xfp, struct parameters &_par_sorter) {

  _cor_tof = (double)_tof + _par_sorter.cortof_par[0] -
             (_par_sorter.cortof_par[1] * _Thtgt +
              _par_sorter.cortof_par[2] * pow(_Thtgt, 2)) -
             (_par_sorter.cortof_par[3] * _Xfp +
              _par_sorter.cortof_par[4] * pow(_Xfp, 2));

  if (_cor_tof < 0.) {
    _cor_tof += 256.;
  }
  if (_cor_tof > 256.) {
    _cor_tof -= 256.;
  }
}

void Sorter_user::count_cluster_u(std::array<int, 208> _tdc, int &_num_cluster,
                                  int WCID, struct parameters &_par_sorter) {
  // WCID -> X1:0, U1:1, X2:2, U2:3
  // chk_num : 連続して鳴ったwireの本数
  // flg_offwire : 一本だけ歯抜けを許すためのフラグ
  int i, n_wire, chk_num = 0, flg_offwire = 0, tdc_min, tdc_max;

  int min_num_wire = 3;

  if (WCID == 1) {
    n_wire = 208;
    tdc_min = _par_sorter.tdc_u1_min;
    tdc_max = _par_sorter.tdc_u1_max;
  } else if (WCID == 3) {
    n_wire = 208;
    tdc_min = _par_sorter.tdc_u2_min;
    tdc_max = _par_sorter.tdc_u2_max;
  } else {
    fprintf(stderr,
            "ERROR : Inconsistent wirechamber ID (%d) in count_cluster().\n",
            WCID);
    exit(1);
  }

  for (i = 0; i < n_wire; ++i) {
    if (_tdc[i] >= tdc_min && _tdc[i] <= tdc_max) {
      ++chk_num;
      flg_offwire = 2;
      // (min_num_wire)本以上連続していたらclusterとみなす
      if (chk_num == min_num_wire)
        ++(_num_cluster);
    } else if (flg_offwire == 2)
      --flg_offwire;
    else if (flg_offwire == 1) {
      --flg_offwire;
      chk_num = 0;
    } else if (flg_offwire == 0)
      chk_num = 0;
    else
      flg_offwire = 0;
  }
}
void Sorter_user::count_cluster_x(std::array<int, 192> _tdc, int &_num_cluster,
                                  int WCID, struct parameters &_par_sorter) {
  // WCID -> X1:0, U1:1, X2:2, U2:3
  // chk_num : 連続して鳴ったwireの本数
  // flg_offwire : 一本だけ歯抜けを許すためのフラグ
  int i, n_wire, chk_num = 0, flg_offwire = 0, tdc_min, tdc_max;

  int min_num_wire = 3;

  if (WCID == 0) {
    n_wire = 192;
    tdc_min = _par_sorter.tdc_x1_min;
    tdc_max = _par_sorter.tdc_x1_max;
  } else if (WCID == 2) {
    n_wire = 192;
    tdc_min = _par_sorter.tdc_x2_min;
    tdc_max = _par_sorter.tdc_x2_max;
  } else {
    fprintf(stderr,
            "ERROR : Inconsistent wirechamber ID (%d) in count_cluster().\n",
            WCID);
    exit(1);
  }

  for (i = 0; i < n_wire; ++i) {
    if (_tdc[i] >= tdc_min && _tdc[i] <= tdc_max) {
      ++chk_num;
      flg_offwire = 2;
      // (min_num_wire)本以上連続していたらclusterとみなす
      if (chk_num == min_num_wire)
        ++(_num_cluster);
    } else if (flg_offwire == 2)
      --flg_offwire;
    else if (flg_offwire == 1) {
      --flg_offwire;
      chk_num = 0;
    } else if (flg_offwire == 0)
      chk_num = 0;
    else
      flg_offwire = 0;
  }
}

int Sorter_user::fp_correction(double &_Xfp, double _Thtgt, double _Phtgt,
                               struct parameters &_par_sorter) {
  int i = 0;
  double correction_th_g = 0.0, correction_ph_g = 0.0, correction_th = 0.0,
         correction_ph = 0.0;

  // Global (common) X-Th correction
  if (_par_sorter.switch_global_xcor_th == TRUE) {
    for (i = 0; i < MAX_GLOBAL_XCOR_TH_PAR; ++i) {
      if (_par_sorter.global_xcor_th_par[i]) {
        correction_th_g += _par_sorter.global_xcor_th_par[i] *
                           pow(_Thtgt, _par_sorter.global_xcor_th_thorder[i]) *
                           pow(_Xfp, _par_sorter.global_xcor_th_xorder[i]);
      }
    }
  }

  // Global (common) X-Ph correction
  if (_par_sorter.switch_global_xcor_ph == TRUE) {
    for (i = 0; i < MAX_GLOBAL_XCOR_PH_PAR; ++i) {
      if (_par_sorter.global_xcor_ph_par[i]) {
        correction_ph_g += _par_sorter.global_xcor_ph_par[i] *
                           pow(_Phtgt, _par_sorter.global_xcor_ph_phorder[i]) *
                           pow(_Xfp, _par_sorter.global_xcor_ph_xorder[i]);
      }
    }
  }

  // X-Th correction
  if (_par_sorter.switch_xcor_th == TRUE) {
    for (i = 0; i < MAX_XCOR_TH_PAR; ++i) {
      if (_par_sorter.xcor_th_par[i]) {
        correction_th += _par_sorter.xcor_th_par[i] *
                         pow(_Thtgt, _par_sorter.xcor_th_thorder[i]) *
                         pow(_Xfp, _par_sorter.xcor_th_xorder[i]);
      }
    }
  }

  // X-Ph correction
  if (_par_sorter.switch_xcor_ph == TRUE) {
    for (i = 0; i < MAX_XCOR_PH_PAR; ++i) {
      if (_par_sorter.xcor_ph_par[i]) {
        correction_ph += _par_sorter.xcor_ph_par[i] *
                         pow(_Phtgt, _par_sorter.xcor_ph_phorder[i]) *
                         pow(_Xfp, _par_sorter.xcor_ph_xorder[i]);
      }
    }
  }

  _Xfp += correction_th_g + correction_ph_g + correction_th + correction_ph;

  return 0;
}

void Sorter_user::get_driftlength(
    std::array<int, 192> &_tdc_x1, std::array<int, 208> &_tdc_u1,
    std::array<int, 192> &_tdc_x2, std::array<int, 208> &_tdc_u2,
    std::array<double, 192> &_drift_x1, std::array<double, 208> &_drift_u1,
    std::array<double, 192> &_drift_x2, std::array<double, 208> &_drift_u2,
    std::array<double, 1024> &_drifttable_x1,
    std::array<double, 1024> &_drifttable_u1,
    std::array<double, 1024> &_drifttable_x2,
    std::array<double, 1024> &_drifttable_u2, struct parameters &_par_sorter,
    Sorter_root &s_root) {

  int i; // _tdc_x1_v, _tdc_u1_v, _tdc_x2_v, _tdc_u2_v;
  // double corr_x1 = 0.017, corr_x2 = 0.016;// corr_u1 = -0.025, corr_u2 =
  // -0.023;

  // corr_x1 = -0.25;
  // corr_x2 = 0.0;

  for (i = 0; i < 192; ++i) {
    _drift_x1[i] = 0.0;
    _drift_x2[i] = 0.0;
    //_tdc_x1_v = _tdc_x1[i];
    //_tdc_x2_v = _tdc_x2[i];

    if ((_drifttable_x1[_tdc_x1[i]] > 0.0) &&
        (_tdc_x1[i] >= _par_sorter.tdc_x1_min) &&
        (_tdc_x1[i] <= _par_sorter.tdc_x1_max)) {

      _drift_x1[i] = X1_DRIFT * _drifttable_x1[_tdc_x1[i]];
    }
    if ((_drifttable_x2[_tdc_x2[i]] > 0.0) &&
        (_tdc_x2[i] >= _par_sorter.tdc_x2_min) &&
        (_tdc_x2[i] <= _par_sorter.tdc_x2_max)) {
      _drift_x2[i] = X2_DRIFT * _drifttable_x2[_tdc_x2[i]];
    }
  }
  for (i = 0; i < 208; ++i) {
    _drift_u1[i] = 0.0;
    _drift_u2[i] = 0.0;
    // _tdc_u1_v = _tdc_u1[i];
    // _tdc_u2_v = _tdc_u2[i];

    if ((_drifttable_u1[_tdc_u1[i]] > 0.0) &&
        (_tdc_u1[i] >= _par_sorter.tdc_u1_min) &&
        (_tdc_u1[i] <= _par_sorter.tdc_u1_max)) {

      _drift_u1[i] = U1_DRIFT * _drifttable_u1[_tdc_u1[i]];
    }
    if ((_drifttable_u2[_tdc_u2[i]] > 0.0) &&
        (_tdc_u2[i] >= _par_sorter.tdc_u2_min) &&
        (_tdc_u2[i] <= _par_sorter.tdc_u2_max)) {

      _drift_u2[i] = U2_DRIFT * _drifttable_u2[_tdc_u2[i]];
    }
  }
  s_root.fill_hist_driftlength(_drift_x1, _drift_u1, _drift_x2, _drift_u2);
}

void Sorter_user::get_drifttable1(std::array<double, 1024> &_drifttable_x1,
                                  std::array<double, 1024> &_drifttable_u1,
                                  std::array<double, 1024> &_drifttable_x2,
                                  std::array<double, 1024> &_drifttable_u2,
                                  struct parameters &_par_sorter) {

  int i, size_dtable_x1, size_dtable_u1, size_dtable_x2, size_dtable_u2;
  int x1_endpoint = 0, u1_endpoint = 0, x2_endpoint = 0, u2_endpoint = 0;
  double dummy;

  std::array<double, 2> cor_x1 = {0.0};
  std::array<double, 2> cor_u1 = {0.0};
  std::array<double, 2> cor_x2 = {0.0};
  std::array<double, 2> cor_u2 = {0.0};

  cor_x1[0] = _par_sorter.drifttable1_x1_par[0];
  cor_x1[1] = _par_sorter.drifttable1_x1_par[1];
  cor_u1[0] = _par_sorter.drifttable1_u1_par[0];
  cor_u1[1] = _par_sorter.drifttable1_u1_par[1];
  cor_x2[0] = _par_sorter.drifttable1_x2_par[0];
  cor_x2[1] = _par_sorter.drifttable1_x2_par[1];
  cor_u2[0] = _par_sorter.drifttable1_u2_par[0];
  cor_u2[1] = _par_sorter.drifttable1_u2_par[1];

  std::array<double, 270> default_dtable_x1 = {
      1.00000, 1.00000, 1.00000, 1.00000, 1.00000, 1.00000, 1.00000, 1.00000,
      1.00000, 1.00000, 1.00000, 0.99999, 0.99998, 0.99997, 0.99996, 0.99995,
      0.99993, 0.99992, 0.99991, 0.99990, 0.99988, 0.99986, 0.99983, 0.99979,
      0.99972, 0.99962, 0.99948, 0.99926, 0.99895, 0.99853, 0.99797, 0.99722,
      0.99629, 0.99513, 0.99375, 0.99205, 0.99009, 0.98782, 0.98527, 0.98237,
      0.97923, 0.97582, 0.97222, 0.96833, 0.96431, 0.96019, 0.95603, 0.95168,
      0.94738, 0.94303, 0.93873, 0.93431, 0.92997, 0.92561, 0.92128, 0.91684,
      0.91250, 0.90815, 0.90383, 0.89938, 0.89501, 0.89065, 0.88632, 0.88192,
      0.87757, 0.87324, 0.86895, 0.86456, 0.86026, 0.85596, 0.85168, 0.84730,
      0.84300, 0.83869, 0.83442, 0.83006, 0.82577, 0.82147, 0.81719, 0.81284,
      0.80855, 0.80425, 0.80000, 0.79566, 0.79135, 0.78708, 0.78285, 0.77852,
      0.77423, 0.76992, 0.76569, 0.76130, 0.75700, 0.75267, 0.74839, 0.74398,
      0.73965, 0.73530, 0.73099, 0.72656, 0.72220, 0.71781, 0.71346, 0.70898,
      0.70461, 0.70020, 0.69584, 0.69131, 0.68686, 0.68238, 0.67797, 0.67342,
      0.66897, 0.66447, 0.66005, 0.65550, 0.65105, 0.64656, 0.64212, 0.63756,
      0.63310, 0.62860, 0.62418, 0.61964, 0.61513, 0.61062, 0.60614, 0.60157,
      0.59711, 0.59262, 0.58818, 0.58361, 0.57911, 0.57462, 0.57017, 0.56564,
      0.56121, 0.55672, 0.55229, 0.54771, 0.54323, 0.53874, 0.53430, 0.52975,
      0.52526, 0.52077, 0.51630, 0.51172, 0.50720, 0.50268, 0.49819, 0.49358,
      0.48906, 0.48455, 0.48009, 0.47550, 0.47097, 0.46644, 0.46193, 0.45733,
      0.45280, 0.44825, 0.44373, 0.43910, 0.43454, 0.42998, 0.42548, 0.42086,
      0.41634, 0.41180, 0.40733, 0.40270, 0.39817, 0.39361, 0.38909, 0.38446,
      0.37992, 0.37538, 0.37087, 0.36626, 0.36171, 0.35714, 0.35260, 0.34796,
      0.34341, 0.33886, 0.33439, 0.32980, 0.32535, 0.32092, 0.31656, 0.31211,
      0.30778, 0.30345, 0.29919, 0.29480, 0.29040, 0.28599, 0.28160, 0.27708,
      0.27264, 0.26817, 0.26375, 0.25918, 0.25470, 0.25020, 0.24574, 0.24117,
      0.23668, 0.23215, 0.22764, 0.22301, 0.21842, 0.21384, 0.20926, 0.20454,
      0.19992, 0.19526, 0.19063, 0.18581, 0.18106, 0.17623, 0.17140, 0.16643,
      0.16147, 0.15642, 0.15136, 0.14608, 0.14078, 0.13533, 0.12978, 0.12396,
      0.11804, 0.11188, 0.10559, 0.09889, 0.09205, 0.08500, 0.07779, 0.07022,
      0.06254, 0.05465, 0.04658, 0.03797, 0.02926, 0.02060, 0.01247, 0.00603,
      0.00253, 0.00089, 0.00028, 0.00011, 0.00008, 0.00006, 0.00005, 0.00004,
      0.00003, 0.00003, 0.00002, 0.00001, 0.00001, 0.00001, 0.00001, 0.00001,
      0.00001, 0.00001, 0.00001, 0.00001, 0.00001, 0.00001};

  std::array<double, 300> default_dtable_u1 = {
      1.00000, 0.99999, 0.99998, 0.99997, 0.99996, 0.99995, 0.99994, 0.99993,
      0.99992, 0.99991, 0.99989, 0.99988, 0.99987, 0.99985, 0.99984, 0.99982,
      0.99980, 0.99979, 0.99976, 0.99974, 0.99971, 0.99969, 0.99966, 0.99962,
      0.99958, 0.99952, 0.99946, 0.99938, 0.99927, 0.99911, 0.99891, 0.99864,
      0.99829, 0.99783, 0.99725, 0.99656, 0.99565, 0.99459, 0.99332, 0.99188,
      0.99019, 0.98829, 0.98618, 0.98388, 0.98134, 0.97862, 0.97573, 0.97268,
      0.96938, 0.96596, 0.96242, 0.95879, 0.95499, 0.95113, 0.94717, 0.94326,
      0.93922, 0.93520, 0.93114, 0.92712, 0.92302, 0.91896, 0.91486, 0.91082,
      0.90666, 0.90259, 0.89848, 0.89440, 0.89024, 0.88615, 0.88204, 0.87799,
      0.87384, 0.86972, 0.86561, 0.86152, 0.85739, 0.85330, 0.84919, 0.84514,
      0.84097, 0.83687, 0.83275, 0.82867, 0.82450, 0.82040, 0.81628, 0.81219,
      0.80804, 0.80392, 0.79979, 0.79572, 0.79153, 0.78746, 0.78335, 0.77927,
      0.77510, 0.77099, 0.76689, 0.76283, 0.75866, 0.75456, 0.75042, 0.74632,
      0.74216, 0.73803, 0.73392, 0.72984, 0.72566, 0.72153, 0.71739, 0.71331,
      0.70913, 0.70501, 0.70088, 0.69678, 0.69260, 0.68846, 0.68432, 0.68025,
      0.67606, 0.67192, 0.66782, 0.66371, 0.65951, 0.65538, 0.65121, 0.64712,
      0.64290, 0.63874, 0.63457, 0.63043, 0.62622, 0.62209, 0.61792, 0.61383,
      0.60962, 0.60548, 0.60132, 0.59717, 0.59293, 0.58878, 0.58458, 0.58044,
      0.57620, 0.57198, 0.56780, 0.56364, 0.55942, 0.55526, 0.55108, 0.54696,
      0.54271, 0.53857, 0.53440, 0.53026, 0.52604, 0.52190, 0.51774, 0.51365,
      0.50942, 0.50529, 0.50114, 0.49700, 0.49279, 0.48860, 0.48438, 0.48022,
      0.47594, 0.47168, 0.46740, 0.46313, 0.45876, 0.45448, 0.45013, 0.44587,
      0.44149, 0.43716, 0.43282, 0.42851, 0.42409, 0.41977, 0.41542, 0.41115,
      0.40676, 0.40245, 0.39815, 0.39394, 0.38963, 0.38544, 0.38126, 0.37711,
      0.37288, 0.36873, 0.36459, 0.36053, 0.35638, 0.35229, 0.34821, 0.34415,
      0.34001, 0.33590, 0.33179, 0.32772, 0.32359, 0.31950, 0.31538, 0.31138,
      0.30724, 0.30316, 0.29907, 0.29504, 0.29091, 0.28690, 0.28291, 0.27909,
      0.27524, 0.27152, 0.26785, 0.26429, 0.26063, 0.25699, 0.25328, 0.24961,
      0.24575, 0.24187, 0.23788, 0.23388, 0.22978, 0.22573, 0.22167, 0.21764,
      0.21349, 0.20937, 0.20524, 0.20114, 0.19693, 0.19274, 0.18849, 0.18430,
      0.17991, 0.17551, 0.17104, 0.16657, 0.16189, 0.15717, 0.15230, 0.14732,
      0.14198, 0.13646, 0.13062, 0.12454, 0.11808, 0.11151, 0.10470, 0.09787,
      0.09075, 0.08367, 0.07648, 0.06921, 0.06164, 0.05393, 0.04574, 0.03687,
      0.02646, 0.01571, 0.00753, 0.00296, 0.00084, 0.00030, 0.00022, 0.00020,
      0.00019, 0.00018, 0.00018, 0.00017, 0.00016, 0.00016, 0.00015, 0.00015,
      0.00014, 0.00013, 0.00013, 0.00012, 0.00011, 0.00010, 0.00010, 0.00009,
      0.00008, 0.00008, 0.00007, 0.00006, 0.00006, 0.00005, 0.00004, 0.00004,
      0.00003, 0.00002, 0.00001, 0.00001};

  for (i = 0; i < 1024; ++i) {
    _drifttable_x1[i] = -1.0;
    _drifttable_u1[i] = -1.0;
    _drifttable_x2[i] = -1.0;
    _drifttable_u2[i] = -1.0;
  }

  size_dtable_x1 = sizeof(default_dtable_x1) / sizeof(dummy);
  size_dtable_u1 = sizeof(default_dtable_u1) / sizeof(dummy);
  size_dtable_x2 = sizeof(default_dtable_x1) / sizeof(dummy); // X1を流用
  size_dtable_u2 = sizeof(default_dtable_u1) / sizeof(dummy);

  x1_endpoint = _par_sorter.drifttable1_x1_par[0];
  u1_endpoint = _par_sorter.drifttable1_u1_par[0];
  x2_endpoint = _par_sorter.drifttable1_x2_par[0];
  u2_endpoint = _par_sorter.drifttable1_u2_par[0];

  for (i = 1023; i >= 0; --i) {
    if (i <= x1_endpoint && i > x1_endpoint - size_dtable_x1) {
      _drifttable_x1[i] =
          default_dtable_x1[i - (x1_endpoint - size_dtable_x1 + 1)];
      if (_drifttable_x1[i] < 0.0)
        _drifttable_x1[i] = -1.0;
    }
    if (i <= u1_endpoint && i > u1_endpoint - size_dtable_u1) {
      _drifttable_u1[i] =
          default_dtable_u1[i - (u1_endpoint - size_dtable_u1 + 1)];
      if (_drifttable_u1[i] < 0.0)
        _drifttable_u1[i] = -1.0;
    }
    if (i <= x2_endpoint && i > x2_endpoint - size_dtable_x2) {
      _drifttable_x2[i] =
          default_dtable_x1[i - (x2_endpoint - size_dtable_x2 + 1)];
      if (_drifttable_x2[i] < 0.0)
        _drifttable_x2[i] = -1.0;
    }
    if (i <= u2_endpoint && i > u2_endpoint - size_dtable_u2) {
      _drifttable_u2[i] =
          default_dtable_u1[i - (u2_endpoint - size_dtable_u2 + 1)];
      if (_drifttable_u2[i] < 0.0)
        _drifttable_u2[i] = -1.0;
    }
  }
}

void Sorter_user::get_drifttable2(std::array<double, 1024> &_drifttable_x1,
                                  std::array<double, 1024> &_drifttable_u1,
                                  std::array<double, 1024> &_drifttable_x2,
                                  std::array<double, 1024> &_drifttable_u2,
                                  struct parameters &_par_sorter) {

  int i = 0;

  std::array<double, 2> par_x1 = {0.0};
  std::array<double, 2> par_u1 = {0.0};
  std::array<double, 2> par_x2 = {0.0};
  std::array<double, 2> par_u2 = {0.0};

  std::array<double, 2> cor_x1 = {0.0};
  std::array<double, 2> cor_u1 = {0.0};
  std::array<double, 2> cor_x2 = {0.0};
  std::array<double, 2> cor_u2 = {0.0};

  par_x1[0] = _par_sorter.drifttable2_x1_par[0];
  par_x1[1] = _par_sorter.drifttable2_x1_par[1];
  cor_x1[0] = _par_sorter.drifttable2_x1_par[2];
  cor_x1[1] = _par_sorter.drifttable2_x1_par[3];
  par_u1[0] = _par_sorter.drifttable2_u1_par[0];
  par_u1[1] = _par_sorter.drifttable2_u1_par[1];
  cor_u1[0] = _par_sorter.drifttable2_u1_par[2];
  cor_u1[1] = _par_sorter.drifttable2_u1_par[3];
  par_x2[0] = _par_sorter.drifttable2_x2_par[0];
  par_x2[1] = _par_sorter.drifttable2_x2_par[1];
  cor_x2[0] = _par_sorter.drifttable2_x2_par[2];
  cor_x2[1] = _par_sorter.drifttable2_x2_par[3];
  par_u2[0] = _par_sorter.drifttable2_u2_par[0];
  par_u2[1] = _par_sorter.drifttable2_u2_par[1];
  cor_u2[0] = _par_sorter.drifttable2_u2_par[2];
  cor_u2[1] = _par_sorter.drifttable2_u2_par[3];

  for (i = 0; i < 1024; ++i) {
    _drifttable_x1[i] = -1.0;
    _drifttable_u1[i] = -1.0;
    _drifttable_x2[i] = -1.0;
    _drifttable_u2[i] = -1.0;

    if (i >= _par_sorter.tdc_x1_min && i <= _par_sorter.tdc_x1_max) {
      _drifttable_x1[i] = par_x1[0] * ((double)i - par_x1[1]);
      if (_drifttable_x1[i] < 0.0) {
        _drifttable_x1[i] = -1.0;
      }
      if (cor_x1[0] && cor_x1[1] && _drifttable_x1[i] != -1.0 &&
          _drifttable_x1[i] < 0.4) {
        _drifttable_x1[i] *=
            1 - exp(cor_x1[0] + cor_x1[1] * _drifttable_x1[i] * X1_DRIFT);
      }
    }
    if (i >= _par_sorter.tdc_u1_min && i <= _par_sorter.tdc_u1_max) {
      _drifttable_u1[i] = par_u1[0] * ((double)i - par_u1[1]);
      if (_drifttable_u1[i] < 0.0) {
        _drifttable_u1[i] = -1.0;
      }
      if (cor_u1[0] && cor_u1[1] && _drifttable_u1[i] != -1.0 &&
          _drifttable_u1[i] < 0.4) {
        _drifttable_u1[i] *=
            1 - exp(cor_u1[0] + cor_u1[1] * _drifttable_u1[i] * U1_DRIFT);
      }
    }
    if (i >= _par_sorter.tdc_x2_min && i <= _par_sorter.tdc_x2_max) {
      _drifttable_x2[i] = par_x2[0] * ((double)i - par_x2[1]);
      if (_drifttable_x2[i] < 0.0) {
        _drifttable_x2[i] = -1.0;
      }
      if (cor_x2[0] && cor_x2[1] && _drifttable_x2[i] != -1.0 &&
          _drifttable_x2[i] < 0.4) {
        _drifttable_x2[i] *=
            1 - exp(cor_x2[0] + cor_x2[1] * _drifttable_x2[i] * X2_DRIFT);
      }
    }
    if (i >= _par_sorter.tdc_u2_min && i <= _par_sorter.tdc_u2_max) {
      _drifttable_u2[i] = par_u2[0] * ((double)i - par_u2[1]);
      if (_drifttable_u2[i] < 0.0) {
        _drifttable_u2[i] = -1.0;
      }
      if (cor_u2[0] && cor_u2[1] && _drifttable_u2[i] != -1.0 &&
          _drifttable_u2[i] < 0.4) {
        _drifttable_u2[i] *=
            1 - exp(cor_u2[0] + cor_u2[1] * _drifttable_u2[i] * U2_DRIFT);
      }
    }
  }
}
void Sorter_user::get_drifttable3(std::array<double, 1024> &_drifttable_x1,
                                  std::array<double, 1024> &_drifttable_u1,
                                  std::array<double, 1024> &_drifttable_x2,
                                  std::array<double, 1024> &_drifttable_u2,
                                  struct parameters &_par_sorter) {

  int i = 0;
  double ch = 0.0;
  double tmp = 0.0;

  // genten wo tooru youni zurasita drifttable function (no constant term)
  std::array<double, 5> param_x1 = {-0.0068914, -1.05212e-05, 3.05324e-13,
                                    6.74266e-16, -4.24368e-20};
  std::array<double, 5> param_u1 = {-0.0068914, -1.05212e-05, 3.05324e-13,
                                    6.74266e-16, -4.24368e-20};
  std::array<double, 5> param_x2 = {-0.0068914, -1.05212e-05, 3.05324e-13,
                                    6.74266e-16, -4.24368e-20};
  std::array<double, 5> param_u2 = {-0.0068914, -1.05212e-05, 3.05324e-13,
                                    6.74266e-16, -4.24368e-20};

  double x1_max = 328.0; // temporary given explicit value
  double u1_max = 320.0; // temporary given explicit value
  double x2_max = 311.0; // temporary given explicit value
  double u2_max = 307.0; // temporary given explicit value

  for (i = 0; i < 1024; ++i) {
    _drifttable_x1[i] = -1.0;
    _drifttable_u1[i] = -1.0;
    _drifttable_x2[i] = -1.0;
    _drifttable_u2[i] = -1.0;

    ch = (double)i - x1_max;
    tmp = param_x1[0] * ch + param_x1[1] * pow(ch, 2) +
          param_x1[2] * pow(ch, 3) + param_x1[3] * pow(ch, 4) +
          param_x1[4] * pow(ch, 5);
    if (tmp > 1.0)
      tmp = 1.0;
    else if (tmp < 0.0)
      tmp = 0.0; // although cannnot be true with proper param_x1
    if (i < _par_sorter.tdc_x1_min || i > _par_sorter.tdc_x1_max)
      tmp = -1.0;
    _drifttable_x1[i] = tmp;

    ch = (double)i - u1_max;
    tmp = param_u1[0] * ch + param_u1[1] * pow(ch, 2) +
          param_u1[2] * pow(ch, 3) + param_u1[3] * pow(ch, 4) +
          param_u1[4] * pow(ch, 5);
    if (tmp > 1.0)
      tmp = 1.0;
    else if (tmp < 0.0)
      tmp = 0.0; // although cannnot be true with proper param_u1
    if (i < _par_sorter.tdc_u1_min || i > _par_sorter.tdc_u1_max)
      tmp = -1.0;
    _drifttable_u1[i] = tmp;

    ch = (double)i - x2_max;
    tmp = param_x2[0] * ch + param_x2[1] * pow(ch, 2) +
          param_x2[2] * pow(ch, 3) + param_x2[3] * pow(ch, 4) +
          param_x2[4] * pow(ch, 5);
    if (tmp > 1.0)
      tmp = 1.0;
    else if (tmp < 0.0)
      tmp = 0.0; // although cannnot be true with proper param_x2
    if (i < _par_sorter.tdc_x2_min || i > _par_sorter.tdc_x2_max)
      tmp = -1.0;
    _drifttable_x2[i] = tmp;

    ch = (double)i - u2_max;
    tmp = param_u2[0] * ch + param_u2[1] * pow(ch, 2) +
          param_u2[2] * pow(ch, 3) + param_u2[3] * pow(ch, 4) +
          param_u2[4] * pow(ch, 5);
    if (tmp > 1.0)
      tmp = 1.0;
    else if (tmp < 0.0)
      tmp = 0.0; // although cannnot be true with proper param_u2
    if (i < _par_sorter.tdc_u2_min || i > _par_sorter.tdc_u2_max)
      tmp = -1.0;
    _drifttable_u2[i] = tmp;
  }
}

void Sorter_user::get_drifttable4(std::array<double, 1024> &_drifttable_x1,
                                  std::array<double, 1024> &_drifttable_u1,
                                  std::array<double, 1024> &_drifttable_x2,
                                  std::array<double, 1024> &_drifttable_u2,
                                  struct parameters &_par_sorter) {
  int i = 0;

  // double read_dt_x1 = 0.0, read_dt_u1 = 0.0, read_dt_x2 = 0.0, read_dt_u2 =
  // 0.0;

  std::ifstream drift_f(_par_sorter.drifttablefilename);

  std::vector<std::vector<std::string>> drift;
  std::string line;
  if (drift_f.is_open()) {

    while (getline(drift_f, line)) {
      std::stringstream iss(line);

      // istringstream iss(sentence);
      std::vector<std::string> line_entries;

      copy(std::istream_iterator<std::string>(iss),
           std::istream_iterator<std::string>(), back_inserter(line_entries));

      if (line_entries.size() > 0) {
        drift.push_back(line_entries);
      }
    }

  } else {
    std::cout << "ERROR : External Drift Table "
              << _par_sorter.drifttablefilename << " not found." << std::endl;
    exit(1);
  }

  if (drift.size() > 1023) {
    for (i = 0; i < 1024; ++i) {

      if (drift[i].size() > 1)
        _drifttable_x1[i] = stof(drift[i][1]);
      else
        _drifttable_x1[i] = -1.0;
      if (drift[i].size() > 2)
        _drifttable_u1[i] = stof(drift[i][2]);
      else
        _drifttable_u1[i] = -1.0;
      if (drift[i].size() > 3)
        _drifttable_x2[i] = stof(drift[i][3]);
      else
        _drifttable_x2[i] = -1.0;
      if (drift[i].size() > 4)
        _drifttable_u2[i] = stof(drift[i][4]);
      else
        _drifttable_u2[i] = -1.0;
    }
  } else {
    std::cout << "ERROR : External Drift Table to small " << drift.size()
              << "/ 1024 entries." << std::endl;
    exit(1);
  }
}

int Sorter_user::get_epout(double _Xfp, double &_Pout, double &_Eout,
                           struct parameters &_par_sorter) {
  int i = 0;
  double Pout_cor = 0.0;

  _Pout = 0.0;
  for (i = 0; i < MAX_POUT_PAR; ++i) {
    if (_par_sorter.pout_par[i]) {
      _Pout += _par_sorter.pout_par[i] * pow(_Xfp, i);
    }
  }

  for (i = 0; i < MAX_POUT_PAR; ++i) {
    if (_par_sorter.pout_cor_par[i]) {
      Pout_cor += _par_sorter.pout_cor_par[i] * pow(_Pout, i);
    }
  }
  if (Pout_cor != 0) {
    _Pout = Pout_cor;
  }

  _Eout = sqrt(pow(_Pout, 2) + pow(_par_sorter.mout, 2)) - _par_sorter.mout;

  return 0;
}

// get recoil energy at ThGR=0 for Ex calibration
int Sorter_user::get_erec(double _Zttgt, double _Eout, double &_Erec_center,
                          double &_Erec_Zt, struct parameters &_par_sorter) {
  int i = 0;
  _Erec_center = 0.0, _Erec_Zt = 0.0;

  for (i = 0; i < MAX_RECOIL_PAR; ++i) {
    _Erec_center += _par_sorter.recoil_par[i] *
                    pow(_Eout, _par_sorter.recoil_eorder[i]) *
                    pow(_par_sorter.ThGR, _par_sorter.recoil_ztorder[i]);
    _Erec_Zt += _par_sorter.recoil_par[i] *
                pow(_Eout, _par_sorter.recoil_eorder[i]) *
                pow(_Zttgt, _par_sorter.recoil_ztorder[i]);
  }

  return 0;
}
int Sorter_user::get_eventid(
    int _num_wire_x1, int _num_wire_u1, int _num_wire_x2, int _num_wire_u2,
    double _chisq_x1, double _chisq_u1, double _chisq_x2, double _chisq_u2,
    int _num_cluster_x1, int _num_cluster_u1, int _num_cluster_x2,
    int _num_cluster_u2, double _scintillator_ave_1, double _scintillator_ave_2,
    int _tof, double _cor_tof, double _Xferet, struct parameters &_par_sorter,
    int &_success_X1, int &_success_U1, int &_success_X2, int &_success_U2) {
  int _eventid = 0;

  /*
     eventID |
     --------+-----------------------------------------------
      0      | good event in X1, U1, X2 and U2
     +1      | not sufficient num. of wire or bad chisq or multi-cluster in X1
     +2      | not sufficient num. of wire or bad chisq or multi-cluster in U1
     +4      | not sufficient num. of wire or bad chisq or multi-cluster in X2
     +8      | not sufficient num. of wire or bad chisq or multi-cluster in U2
     +16     | bad corrected tof
     32      | no good TDC (no wire)
     -1      | bad plastic scintillation detector 1
     -2      | bad plastic scintillation detector 2
//     -4      | bad tof (deleted 060113)
     -4      | no Xferet (Plastic.ADC outputs lost)

     --- not included yet ---
     +32?    | Th1-Thfp > ???
     +64?    | Th2-Thfp > ???
     +128?   | Ps1-Psfp > ???
     +256?   | Ps2-Psfp > ???
   */

  // vdc check

  if (_num_wire_x1 < _par_sorter.clustersize_x1_min ||
      _num_wire_x1 > _par_sorter.clustersize_x1_max ||
      _chisq_x1 > _par_sorter.chisq_x1_max || _num_cluster_x1 > 1) {
    _success_X1 = FALSE;
  } else {
    _success_X1 = TRUE;
  }
  if (_num_wire_u1 < _par_sorter.clustersize_u1_min ||
      _num_wire_u1 > _par_sorter.clustersize_u1_max ||
      _chisq_u1 > _par_sorter.chisq_u1_max || _num_cluster_u1 > 1) {
    _success_U1 = FALSE;
  } else {
    _success_U1 = TRUE;
  }
  if (_num_wire_x2 < _par_sorter.clustersize_x2_min ||
      _num_wire_x2 > _par_sorter.clustersize_x2_max ||
      _chisq_x2 > _par_sorter.chisq_x2_max || _num_cluster_x2 > 1) {
    _success_X2 = FALSE;
  } else {
    _success_X2 = TRUE;
  }
  if (_num_wire_u2 < _par_sorter.clustersize_u2_min ||
      _num_wire_u2 > _par_sorter.clustersize_u2_max ||
      _chisq_u2 > _par_sorter.chisq_u2_max || _num_cluster_u2 > 1) {
    _success_U2 = FALSE;
  } else {
    _success_U2 = TRUE;
  }

  // eventid check from here

  if (_scintillator_ave_1 < _par_sorter.scinti_1_min ||
      _scintillator_ave_1 > _par_sorter.scinti_1_max) {
    _eventid -= 1;
  }
  if (_scintillator_ave_2 < _par_sorter.scinti_2_min ||
      _scintillator_ave_2 > _par_sorter.scinti_2_max) {
    _eventid -= 2;
  }
  if (_Xferet == DEFAULT_WC) {
    _eventid -= 4;
  }

  if (_eventid) {
    return _eventid;
  } // no more check

  if (_success_X1 == FALSE) {
    _eventid += 1;
  }
  if (_success_U1 == FALSE) {
    _eventid += 2;
  }
  if (_success_X2 == FALSE) {
    _eventid += 4;
  }
  if (_success_U2 == FALSE) {
    _eventid += 8;
  }
  if (_cor_tof && ((_cor_tof < _par_sorter.cortof_1_min ||
                    _cor_tof > _par_sorter.cortof_1_max) &&
                   (_cor_tof < _par_sorter.cortof_2_min ||
                    _cor_tof > _par_sorter.cortof_2_max))) {
    _eventid += 16;
  }
  if (!(_num_wire_x1 + _num_wire_u1 + _num_wire_x2 + _num_wire_u2)) {
    _eventid = 32;
  } // NO wire event

  return _eventid;
}

int Sorter_user::get_ex(double _Eout, double _Erec_center, double &_Ex,
                        struct parameters &_par_sorter, double _Xfp) {
  double Ex_cor = 0.0;
  int i;

  // konoyouna parameter check ha dokoka ni matomeru beki
  if (_par_sorter.switch_pout == FALSE) {
    std::cout << "ERROR : GET_POUT must be TRUE if GET_EX is TRUE."
              << std::endl;
    exit(1);
  }

  _Ex = _par_sorter.ebeam - _Eout - _Erec_center + _par_sorter.qvalue;

  for (i = 0; i < MAX_EXCOR_PAR; ++i) {
    if (_par_sorter.ex_cor_par[i]) {
      Ex_cor += _par_sorter.ex_cor_par[i] * pow(_Xfp, i);
    }
  }

  if (Ex_cor != 0) {
    _Ex += Ex_cor;
  }

  return 0;
}

void Sorter_user::get_tdc_offset(
    std::array<int, 192> &_tdc_x1, std::array<int, 208> &_tdc_u1,
    std::array<int, 192> &_tdc_x2, std::array<int, 208> &_tdc_u2,
    std::array<int, 192> &_tdc_x1_cor, std::array<int, 208> &_tdc_u1_cor,
    std::array<int, 192> &_tdc_x2_cor, std::array<int, 208> &_tdc_u2_cor,
    struct parameters &_par_sorter) {
  int i;

  //  for(i=0;i<192;++i){ _tdc_x1_cor[i] = _tdc_x1[i]; _tdc_x2_cor[i] =
  //  _tdc_x2[i]; }
  //  for(i=0;i<208;++i){ _tdc_u1_cor[i] = _tdc_u1[i]; _tdc_u2_cor[i] =
  //  _tdc_u2[i]; }

  for (i = 0; i < 192; ++i) {
    if (i < 16) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[0];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[0];
    } else if (i < 32) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[1];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[1];
    } else if (i < 48) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[2];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[2];
    } else if (i < 64) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[3];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[3];
    } else if (i < 80) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[4];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[4];
    } else if (i < 96) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[5];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[5];
    } else if (i < 112) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[6];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[6];
    } else if (i < 128) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[7];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[7];
    } else if (i < 144) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[8];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[8];
    } else if (i < 160) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[9];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[9];
    } else if (i < 176) {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[10];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[10];
    } else {
      if (_tdc_x1[i])
        _tdc_x1_cor[i] = _tdc_x1[i] + _par_sorter.tdcoffset16_x1[11];
      if (_tdc_x2[i])
        _tdc_x2_cor[i] = _tdc_x2[i] + _par_sorter.tdcoffset16_x2[11];
    }
  }

  for (i = 0; i < 208; ++i) {
    if (i < 16) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[0];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[0];
    } else if (i < 32) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[1];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[1];
    } else if (i < 48) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[2];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[2];
    } else if (i < 64) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[3];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[3];
    } else if (i < 80) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[4];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[4];
    } else if (i < 96) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[5];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[5];
    } else if (i < 112) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[6];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[6];
    } else if (i < 128) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[7];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[7];
    } else if (i < 144) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[8];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[8];
    } else if (i < 160) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[9];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[9];
    } else if (i < 176) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[10];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[10];
    } else if (i < 192) {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[11];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[11];
    } else {
      if (_tdc_u1[i])
        _tdc_u1_cor[i] = _tdc_u1[i] + _par_sorter.tdcoffset16_u1[12];
      if (_tdc_u2[i])
        _tdc_u2_cor[i] = _tdc_u2[i] + _par_sorter.tdcoffset16_u2[12];
    }
  }

  for (i = 0; i < 192; ++i) {
    if (_tdc_x1[i])
      _tdc_x1_cor[i] += _par_sorter.tdcoffset_x1[i];
    if (_tdc_x2[i])
      _tdc_x2_cor[i] += _par_sorter.tdcoffset_x2[i];
  }
  for (i = 0; i < 208; ++i) {
    if (_tdc_u1[i])
      _tdc_u1_cor[i] += _par_sorter.tdcoffset_u1[i];
    if (_tdc_u2[i])
      _tdc_u2_cor[i] += _par_sorter.tdcoffset_u2[i];
  }
}

void Sorter_user::get_x_feret(std::array<unsigned int, 5> &_feret,
                              double &_Xferet, struct parameters &_par_sorter,
                              struct scalers &_sca_sorter) {
  int i = 0;
  int feret_L = 999, feret_R = 999;

  if (_par_sorter.switch_feret == 1) {
    feret_L = _feret[0];
    feret_R = _feret[1];
  } else {
    feret_L = _feret[2];
    feret_R = _feret[3];
  }

  // 計算結果はなんかおかしい。Xfpの印象と一致しない?
  if (feret_L && feret_R) {
    _Xferet = 0.0;
    for (i = 0; i < MAX_FERETPOS_PAR; ++i) {
      _Xferet +=
          _par_sorter.feretposi_par[i] * pow((double)(feret_L - feret_R), i);
    }
    ++(_sca_sorter.xferet_cnt);
  }
}
int Sorter_user::raytrace_x(std::array<double, 192> _drift, double &_X,
                            double &_Th, double &_chisq, int &_wire_num,
                            int WCID, struct parameters &_par_sorter,
                            struct scalers &_sca_sorter, Sorter_root &s_root) {
  /* WCID -> X1:0, U1:1, X2:2, U2:3 */
  /* Center of X/U plane is aligned to be 0 */

  int i;
  // double sign = 1.
  double x_tttv, sum_0 = 0., sum_x = 0., sum_z = 0., sum_xz = 0., sum_x2 = 0.,
                 a, b; // a_err, b_err;

  int wireID_first = 0, wireID_last = 0, wireID_min = 0, n_wire;
  // double wireID_ave = 0.0;
  double wirenum = 0.0, x_first, x_last, a_pre, b_pre;
  // Th_pre;
  // double    X_pre,
  double drift_esti, wirespace, drift_difference;
  double chisq_swap, X_swap, Th_swap;
  double max_chisq = 0.0;
  int min_wire = 0, max_wire = 0;

  int rayid = 0;
  double _x_X1X2 = x_X1X2;

  // double X_err; // <- user_analysisから渡す？

  if (WCID == 0) {
    n_wire = N_WIRE_X1;
    wirespace = X_WIRESPACE;
    max_chisq = _par_sorter.chisq_x1_max;
    min_wire = _par_sorter.clustersize_x1_min;
    max_wire = _par_sorter.clustersize_x1_max;
  } else if (WCID == 1) {
    n_wire = N_WIRE_U1;
    wirespace = U_WIRESPACE;
    max_chisq = _par_sorter.chisq_u1_max;
    min_wire = _par_sorter.clustersize_u1_min;
    max_wire = _par_sorter.clustersize_u1_max;
    _x_X1X2 *= SIN4181; // COS4181; どっちが正しいのかよくわからん
  } else if (WCID == 2) {
    n_wire = N_WIRE_X2;
    wirespace = X_WIRESPACE;
    max_chisq = _par_sorter.chisq_x2_max;
    min_wire = _par_sorter.clustersize_x2_min;
    max_wire = _par_sorter.clustersize_x2_max;
  } else if (WCID == 3) {
    n_wire = N_WIRE_U2;
    wirespace = U_WIRESPACE;
    max_chisq = _par_sorter.chisq_u2_max;
    min_wire = _par_sorter.clustersize_u2_min;
    max_wire = _par_sorter.clustersize_u2_max;
    _x_X1X2 *= SIN4181; // COS4181;
  } else {
    std::cout << "ERROR : Unknown wirechamber ID in raytrace()." << std::endl;
    exit(1);
  }

  if (_wire_num < min_wire) {
    s_root.fill_hist_rayid(WCID, 1);
    return -1;
  } else if (_wire_num > max_wire) {
    s_root.fill_hist_rayid(WCID, 2);
    return -1;
  }

  // label first, last and minimum drift wire
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i] && wireID_first == 0) {
      wireID_first = i;
      wireID_min = i;
    }
    if (_drift[i] && _abs(_drift[wireID_min]) > _abs(_drift[i]))
      wireID_min = i;

    if (_drift[n_wire - (i + 1)] && !wireID_last)
      wireID_last = n_wire - (i + 1);
  }

  x_first = wirespace * (n_wire - wireID_first);
  x_last = wirespace * (n_wire - wireID_last);

  // determine tantative ray
  a_pre = (_drift[wireID_first] + _drift[wireID_last]) / (x_first - x_last);
  b_pre = _drift[wireID_first] - a_pre * x_first;

  // X_pre = (-1) * b_pre / a_pre;
  // Th_pre = 57.29578 * (atan(a_pre) - atan(z_X1X2 / _x_X1X2));

  // determine tentative sign
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i] && a_pre * wirespace * (n_wire - i) + b_pre < 0)
      _drift[i] *= -1;
  }

  // - - - - - for resolution plot - - - - -
  if (wireID_last != wireID_first) {
    for (i = wireID_first + 1; i < wireID_last; ++i) {
      drift_esti = ((wireID_last - i) * _drift[wireID_first] +
                    (i - wireID_first) * _drift[wireID_last]) /
                   (wireID_last - wireID_first);
      s_root.fill_hist_resolution(i, _drift[i], drift_esti, WCID);
    }
  }

  // - - - - - for drift length accuracy check - - - - -
  if ((wireID_last - wireID_first >= 3) && (_drift[wireID_first]) &&
      (_drift[wireID_first + 1]) && (_drift[wireID_last]) &&
      (_drift[wireID_last - 1])) {
    drift_difference = (_drift[wireID_first] - _drift[wireID_first + 1]) -
                       (_drift[wireID_last - 1] - _drift[wireID_last]);
    s_root.fill_hist_dl_accuracy(drift_difference, WCID);
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Discard minimum drift wire.
  // Even if drift table looks proper, it may give 4/6mm crack.
  if (_par_sorter.switch_discard_shortdl == TRUE && _wire_num >= 3) {
    _drift[wireID_min] = 0.0;
  }

  /* least square fit */
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i]) {
      x_tttv = wirespace * (n_wire - i);

      sum_0 += 1.0;
      sum_x += x_tttv;
      sum_z += _drift[i];
      sum_xz += x_tttv * _drift[i];
      sum_x2 += pow(x_tttv, 2);
    }
  }

  a = (sum_x * sum_z - sum_0 * sum_xz) / (pow(sum_x, 2) - sum_0 * sum_x2);
  b = (sum_x * sum_xz - sum_x2 * sum_z) / (pow(sum_x, 2) - sum_0 * sum_x2);

  _X = (-1) * b / a;
  _Th = 57.29578 * (atan(a) - atan(z_X1X2 / _x_X1X2)); // [deg.]

  _chisq = 0.0;
  wirenum = 0.0;
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i]) {
      _chisq += pow(_drift[i] - (a * wirespace * (n_wire - i) + b), 2);
      ++wirenum;
    }
  }
  _chisq /= wirenum;

  // sign (+-) check of minimum wire (not so effective)
  if (_wire_num >= 3) {
    _drift[wireID_min] *= -1;
    sum_0 = 0;
    sum_x = 0;
    sum_z = 0;
    sum_xz = 0;
    sum_x2 = 0;
    for (i = 0; i < n_wire; ++i) {
      if (_drift[i]) {
        x_tttv = wirespace * (n_wire - i);

        sum_0 += 1.0;
        sum_x += x_tttv;
        sum_z += _drift[i];
        sum_xz += x_tttv * _drift[i];
        sum_x2 += pow(x_tttv, 2);
      }
    }
    a = (sum_x * sum_z - sum_0 * sum_xz) / (pow(sum_x, 2) - sum_0 * sum_x2);
    b = (sum_x * sum_xz - sum_x2 * sum_z) / (pow(sum_x, 2) - sum_0 * sum_x2);

    X_swap = (-1) * b / a;
    Th_swap = 57.29578 * (atan(a) - atan(z_X1X2 / _x_X1X2)); // [deg.]

    chisq_swap = 0.0;
    for (i = 0; i < n_wire; ++i) {
      if (_drift[i]) {
        chisq_swap += pow(_drift[i] - (a * wirespace * (n_wire - i) + b), 2);
      }
    }
    chisq_swap /= wirenum;

    if (_chisq > chisq_swap) {

      _X = X_swap;
      _Th = Th_swap;
      _chisq = chisq_swap;
    } else {
      _drift[wireID_min] *= -1; // ハズレだったら戻す
    }
  }
  // - - - - - - - - - - - - - - - - - - - - - - - -

  // 中心を0にズラす
  _X -= wirespace * (n_wire / 2 + 0.5);

  if (_chisq > max_chisq) {
    rayid = 3; // とりあえずrayid=3, 値は暫定
  }
  s_root.fill_hist_rayid(WCID, rayid);

  return 0;
}

// ThGR=0 no Erec ha get_erec() de motomeru you ni shita
int Sorter_user::kinema_correction(double &_Xfp, double _Erec_center,
                                   double _Erec_Zt, double _Eout, double _Pout,
                                   struct parameters &_par_sorter) {
  int i = 0;
  double dPdX = 0.0, dEdX = 0.0;

  //  // konoyouna parameter check ha dokoka ni matomeru beki
  //  if(!_par_sorter.keVpermm){
  //    fprintf(stderr,"ERROR : KEVPERMM must be given if RECOIL_COR is
  //    TRUE.\n");
  //    exit(1);
  //  }

  for (i = 1; i < MAX_POUT_PAR; ++i) {
    if (_par_sorter.pout_par[i])
      dPdX += i * _par_sorter.pout_par[i] * pow(_Xfp, i - 1);
  }
  dEdX = 2 * _Eout / _Pout * dPdX;

  _Xfp += (_Erec_Zt - _Erec_center) / dEdX; // dEdX is negative

  return 0;
}

int Sorter_user::raytrace_u(std::array<double, 208> _drift, double &_X,
                            double &_Th, double &_chisq, int &_wire_num,
                            int WCID, struct parameters &_par_sorter,
                            struct scalers &_sca_sorter, Sorter_root &s_root) {
  /* WCID -> X1:0, U1:1, X2:2, U2:3 */
  /* Center of X/U plane is aligned to be 0 */

  int i;
  // double sign = 1.;
  double x_tttv, sum_0 = 0., sum_x = 0., sum_z = 0., sum_xz = 0., sum_x2 = 0.,
                 a, b; //, a_err, b_err;

  int wireID_first = 0, wireID_last = 0, wireID_min = 0, n_wire;
  // double wireID_ave = 0.0;
  double wirenum = 0.0, x_first, x_last, a_pre, b_pre;

  // double    X_pre,  Th_pre;
  double drift_esti, wirespace, drift_difference;
  double chisq_swap, X_swap, Th_swap;
  double max_chisq = 0.0;
  int min_wire = 0, max_wire = 0;

  int rayid = 0;
  double _x_X1X2 = x_X1X2;

  // double X_err; // <- user_analysisから渡す？

  if (WCID == 0) {
    n_wire = N_WIRE_X1;
    wirespace = X_WIRESPACE;
    max_chisq = _par_sorter.chisq_x1_max;
    min_wire = _par_sorter.clustersize_x1_min;
    max_wire = _par_sorter.clustersize_x1_max;
  } else if (WCID == 1) {
    n_wire = N_WIRE_U1;
    wirespace = U_WIRESPACE;
    max_chisq = _par_sorter.chisq_u1_max;
    min_wire = _par_sorter.clustersize_u1_min;
    max_wire = _par_sorter.clustersize_u1_max;
    _x_X1X2 *= SIN4181; // COS4181; どっちが正しいのかよくわからん
  } else if (WCID == 2) {
    n_wire = N_WIRE_X2;
    wirespace = X_WIRESPACE;
    max_chisq = _par_sorter.chisq_x2_max;
    min_wire = _par_sorter.clustersize_x2_min;
    max_wire = _par_sorter.clustersize_x2_max;
  } else if (WCID == 3) {
    n_wire = N_WIRE_U2;
    wirespace = U_WIRESPACE;
    max_chisq = _par_sorter.chisq_u2_max;
    min_wire = _par_sorter.clustersize_u2_min;
    max_wire = _par_sorter.clustersize_u2_max;
    _x_X1X2 *= SIN4181; // COS4181;
  } else {
    std::cout << "ERROR : Unknown wirechamber ID in raytrace()." << std::endl;
    exit(1);
  }

  if (_wire_num < min_wire) {
    s_root.fill_hist_rayid(WCID, 1);
    return -1;
  } else if (_wire_num > max_wire) {
    s_root.fill_hist_rayid(WCID, 2);
    return -1;
  }

  // label first, last and minimum drift wire
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i] && wireID_first == 0) {
      wireID_first = i;
      wireID_min = i;
    }
    if (_drift[i] && _abs(_drift[wireID_min]) > _abs(_drift[i]))
      wireID_min = i;

    if (_drift[n_wire - (i + 1)] && !wireID_last)
      wireID_last = n_wire - (i + 1);
  }

  x_first = wirespace * (n_wire - wireID_first);
  x_last = wirespace * (n_wire - wireID_last);

  // determine tantative ray
  a_pre = (_drift[wireID_first] + _drift[wireID_last]) / (x_first - x_last);
  b_pre = _drift[wireID_first] - a_pre * x_first;

  // X_pre = (-1) * b_pre / a_pre;
  // Th_pre = 57.29578 * (atan(a_pre) - atan(z_X1X2 / _x_X1X2));

  // determine tentative sign
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i] && a_pre * wirespace * (n_wire - i) + b_pre < 0)
      _drift[i] *= -1;
  }

  // - - - - - for resolution plot - - - - -
  if (wireID_last != wireID_first) {
    for (i = wireID_first + 1; i < wireID_last; ++i) {
      drift_esti = ((wireID_last - i) * _drift[wireID_first] +
                    (i - wireID_first) * _drift[wireID_last]) /
                   (wireID_last - wireID_first);
      s_root.fill_hist_resolution(i, _drift[i], drift_esti, WCID);
    }
  }

  // - - - - - for drift length accuracy check - - - - -
  if ((wireID_last - wireID_first >= 3) && (_drift[wireID_first]) &&
      (_drift[wireID_first + 1]) && (_drift[wireID_last]) &&
      (_drift[wireID_last - 1])) {
    drift_difference = (_drift[wireID_first] - _drift[wireID_first + 1]) -
                       (_drift[wireID_last - 1] - _drift[wireID_last]);
    s_root.fill_hist_dl_accuracy(drift_difference, WCID);
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Discard minimum drift wire.
  // Even if drift table looks proper, it may give 4/6mm crack.
  if (_par_sorter.switch_discard_shortdl == TRUE && _wire_num >= 3) {
    _drift[wireID_min] = 0.0;
  }

  /* least square fit */
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i]) {
      x_tttv = wirespace * (n_wire - i);

      sum_0 += 1.0;
      sum_x += x_tttv;
      sum_z += _drift[i];
      sum_xz += x_tttv * _drift[i];
      sum_x2 += pow(x_tttv, 2);
    }
  }

  a = (sum_x * sum_z - sum_0 * sum_xz) / (pow(sum_x, 2) - sum_0 * sum_x2);
  b = (sum_x * sum_xz - sum_x2 * sum_z) / (pow(sum_x, 2) - sum_0 * sum_x2);

  _X = (-1) * b / a;
  _Th = 57.29578 * (atan(a) - atan(z_X1X2 / _x_X1X2)); // [deg.]

  _chisq = 0.0;
  wirenum = 0.0;
  for (i = 0; i < n_wire; ++i) {
    if (_drift[i]) {
      _chisq += pow(_drift[i] - (a * wirespace * (n_wire - i) + b), 2);
      ++wirenum;
    }
  }
  _chisq /= wirenum;

  // sign (+-) check of minimum wire (not so effective)
  if (_wire_num >= 3) {
    _drift[wireID_min] *= -1;
    sum_0 = 0;
    sum_x = 0;
    sum_z = 0;
    sum_xz = 0;
    sum_x2 = 0;
    for (i = 0; i < n_wire; ++i) {
      if (_drift[i]) {
        x_tttv = wirespace * (n_wire - i);

        sum_0 += 1.0;
        sum_x += x_tttv;
        sum_z += _drift[i];
        sum_xz += x_tttv * _drift[i];
        sum_x2 += pow(x_tttv, 2);
      }
    }
    a = (sum_x * sum_z - sum_0 * sum_xz) / (pow(sum_x, 2) - sum_0 * sum_x2);
    b = (sum_x * sum_xz - sum_x2 * sum_z) / (pow(sum_x, 2) - sum_0 * sum_x2);

    X_swap = (-1) * b / a;
    Th_swap = 57.29578 * (atan(a) - atan(z_X1X2 / _x_X1X2)); // [deg.]

    chisq_swap = 0.0;
    for (i = 0; i < n_wire; ++i) {
      if (_drift[i]) {
        chisq_swap += pow(_drift[i] - (a * wirespace * (n_wire - i) + b), 2);
      }
    }
    chisq_swap /= wirenum;

    if (_chisq > chisq_swap) {

      _X = X_swap;
      _Th = Th_swap;
      _chisq = chisq_swap;
    } else {
      _drift[wireID_min] *= -1; // ハズレだったら戻す
    }
  }
  // - - - - - - - - - - - - - - - - - - - - - - - -

  // 中心を0にズラす
  _X -= wirespace * (n_wire / 2 + 0.5);

  if (_chisq > max_chisq)
    rayid = 3; // とりあえずrayid=3, 値は暫定

  s_root.fill_hist_rayid(WCID, rayid);

  return 0;
}

// Zttgt calculation was moved after applying th/ph offset
void Sorter_user::reconstruct_thphtgt(double _Xfp, double _Thfp, double _Yfp,
                                      double _Phfp, double &_Thtgt,
                                      double &_Phtgt,
                                      struct parameters &_par_sorter) {
  int i; // j;

  _Thtgt = 0.0;
  _Phtgt = 0.0;

  for (i = 0; i < MAX_THTGT_PAR; ++i) {
    if (_par_sorter.thtgt_par[i]) {
      _Thtgt += _par_sorter.thtgt_par[i] *
                pow(_Xfp, (double)_par_sorter.thtgt_par_xorder[i]) *
                pow(_Thfp, (double)_par_sorter.thtgt_par_thorder[i]);
    }
  }

  if (_par_sorter.switch_phtgt == TRUE) {
    for (i = 0; i < MAX_PHTGT_PAR; ++i) {
      if (_par_sorter.phtgt_par[i]) {
        _Phtgt += _par_sorter.phtgt_par[i] *
                  pow(_Xfp, (double)_par_sorter.phtgt_par_xorder[i]) *
                  pow(_Thtgt, (double)_par_sorter.phtgt_par_thorder[i]) *
                  pow(_Yfp, (double)_par_sorter.phtgt_par_yorder[i]);
      }
    }
  }
}

int Sorter_user::user_analysis(
    std::array<int, 192> &_tdc_x1, std::array<int, 208> &_tdc_u1,
    std::array<int, 192> &_tdc_x2, std::array<int, 208> &_tdc_u2,
    std::array<unsigned int, 4> &_fera, std::array<unsigned int, 5> &_feret,
    std::array<double, 1024> &_drifttable_x1,
    std::array<double, 1024> &_drifttable_u1,
    std::array<double, 1024> &_drifttable_x2,
    std::array<double, 1024> &_drifttable_u2, int _num_wire_x1,
    int _num_wire_u1, int _num_wire_x2, int _num_wire_u2,
    struct parameters &_par_sorter, struct scalers &_sca_sorter,
    struct hist_parameters &_par_hist, Sorter_root &s_root,
    Sorter_treedata &s_treedata

    ) {

  s_treedata.init_treeVariables();

  // drift-length
  std::array<double, 192> drift_x1 = {0.0}, drift_x2 = {0.0};
  std::array<double, 208> drift_u1 = {0.0}, drift_u2 = {0.0};
  // corrected TDC

  std::array<int, 192> tdc_x1_cor = {0}, tdc_x2_cor = {0};
  std::array<int, 208> tdc_u1_cor = {0}, tdc_u2_cor = {0};
  // average of paddle outputs
  double scintillator_ave_1, scintillator_ave_2;

  // parameters in focal plane (Th:angle on X plane, Ps:angle on U, Ph:angle on
  // Y, Zeta:sqrt(Th^2+Ph^2))
  double X1 = DEFAULT_WC, U1 = DEFAULT_WC, Y1 = DEFAULT_WC, X2 = DEFAULT_WC,
         U2 = DEFAULT_WC, Y2 = DEFAULT_WC, Xfp = DEFAULT_WC, Yfp = DEFAULT_WC;
  double Th1 = DEFAULT_WC, Th2 = DEFAULT_WC, Thfp = DEFAULT_WC,
         Ps1 = DEFAULT_WC, Ps2 = DEFAULT_WC, Psfp = DEFAULT_WC;
  double Phfp = DEFAULT_WC, Thtgt = DEFAULT_WC, Phtgt = DEFAULT_WC;
  //  double _pad_posi1=DEFAULT_WC,_pad_posi2=DEFAULT_WC;
  double Zttgt = DEFAULT_WC;
  double Pout = DEFAULT_WC, Ex = DEFAULT_WC, Eout = DEFAULT_WC,
         Erec_center = 0.0, Erec_Zt = 0.0;
  double Xferet = DEFAULT_WC;

  double chisq_x1 = 0.0, chisq_u1 = 0.0, chisq_x2 = 0.0, chisq_u2 = 0.0;
  double cor_tof = 0.0;

  int eventid;
  int num_cluster_x1 = 0, num_cluster_u1 = 0, num_cluster_x2 = 0,
      num_cluster_u2 = 0;
  int tof = _feret[4];

  int success_X1 = FALSE, success_U1 = FALSE, success_X2 = FALSE,
      success_U2 = FALSE;

  //  int tof_threshold = 130; not used

  // _scintillator-> 0:1L, 1:1R, 2:2L, 3:2R
  scintillator_ave_1 = sqrt(_fera[0] * _fera[1]);
  scintillator_ave_2 = sqrt(_fera[2] * _fera[3]);

  // rough position from L-R time difference
  get_x_feret(_feret, Xferet, _par_sorter, _sca_sorter);

  // Discard rubbish wires
  cleanup_tdc_x(0, _tdc_x1, _num_wire_x1, _par_sorter, s_root);
  cleanup_tdc_u(1, _tdc_u1, _num_wire_u1, _par_sorter, s_root);
  cleanup_tdc_x(2, _tdc_x2, _num_wire_x2, _par_sorter, s_root);
  cleanup_tdc_u(3, _tdc_u2, _num_wire_u2, _par_sorter, s_root);

  // tdc correction
  get_tdc_offset(_tdc_x1, _tdc_u1, _tdc_x2, _tdc_u2, tdc_x1_cor, tdc_u1_cor,
                 tdc_x2_cor, tdc_u2_cor, _par_sorter);

  // Fill TDC histogram for Drift table (not used?)
  //  make_hist_drifttable(scintillator_ave_1,scintillator_ave_2,
  //		       _tdc_x1,_tdc_u1,_tdc_x2,_tdc_u2,_hist4dt_x1,_hist4dt_u1,_hist4dt_x2,_hist4dt_u2,
  //		       _par_sorter);

  // check number of cluster
  //  //count_cluster(_tdc_x1,_tdc_x2,&num_cluster_x1,&num_cluster_x2);
  //  count_cluster(_tdc_x1,&num_cluster_x1,0,_par_sorter);
  //  count_cluster(_tdc_u1,&num_cluster_u1,1,_par_sorter);
  //  count_cluster(_tdc_x2,&num_cluster_x2,2,_par_sorter);
  //  count_cluster(_tdc_u2,&num_cluster_u2,3,_par_sorter);
  count_cluster_x(tdc_x1_cor, num_cluster_x1, 0, _par_sorter);
  count_cluster_u(tdc_u1_cor, num_cluster_u1, 1, _par_sorter);
  count_cluster_x(tdc_x2_cor, num_cluster_x2, 2, _par_sorter);
  count_cluster_u(tdc_u2_cor, num_cluster_u2, 3, _par_sorter);

  // ----------------------------- kokomade -------------------------------

  get_driftlength(tdc_x1_cor, tdc_u1_cor, tdc_x2_cor, tdc_u2_cor, drift_x1,
                  drift_u1, drift_x2, drift_u2, _drifttable_x1, _drifttable_u1,
                  _drifttable_x2, _drifttable_u2, _par_sorter, s_root);

  // raytraceの返り値
  // 0:正常,-1:wire数でアウト,1:2本wire例外(E252)
  if (raytrace_x(drift_x1, X1, Th1, chisq_x1, _num_wire_x1, 0, _par_sorter,
                 _sca_sorter, s_root) == -1)
    X1 = DEFAULT_WC;
  if (raytrace_u(drift_u1, U1, Ps1, chisq_u1, _num_wire_u1, 1, _par_sorter,
                 _sca_sorter, s_root) == -1)
    U1 = DEFAULT_WC;
  if (raytrace_x(drift_x2, X2, Th2, chisq_x2, _num_wire_x2, 2, _par_sorter,
                 _sca_sorter, s_root) == -1)
    X2 = DEFAULT_WC;
  if (raytrace_u(drift_u2, U2, Ps2, chisq_u2, _num_wire_u2, 3, _par_sorter,
                 _sca_sorter, s_root) == -1)
    U2 = DEFAULT_WC;

  // 時々NaNが返ってきている?(miho上で確認)
  // Note: this will not be s_root.filled in the "Chi square"
  // histograms because of
  // "DEFAULT_WC values"
  if (!finite(X1)) {
    X1 = DEFAULT_WC;
    chisq_x1 = -1.0;
  }
  if (!finite(U1)) {
    U1 = DEFAULT_WC;
    chisq_u1 = -1.0;
  }
  if (!finite(X2)) {
    X2 = DEFAULT_WC;
    chisq_x2 = -1.0;
  }
  if (!finite(U2)) {
    U2 = DEFAULT_WC;
    chisq_u2 = -1.0;
  }

  if ((X1 != DEFAULT_WC) && (X2 != DEFAULT_WC) && (U1 != DEFAULT_WC) &&
      (U2 != DEFAULT_WC)) {
    Xfp = X1; // Initial Xfp value
    combine_ray(X1, X2, U1, U2, Y1, Y2, Yfp, Thfp, Psfp, Phfp);
    if (_par_sorter.switch_thtgt == TRUE)
      reconstruct_thphtgt(Xfp, Thfp, Yfp, Phfp, Thtgt, Phtgt, _par_sorter);

    fp_correction(Xfp, Thtgt, Phtgt, _par_sorter);
    apply_offset(Thtgt, Phtgt, Zttgt, Xfp, _par_sorter);

    if (_par_sorter.switch_pout == TRUE) {
      get_epout(Xfp, Pout, Eout, _par_sorter);
      get_erec(Zttgt, Eout, Erec_center, Erec_Zt, _par_sorter);
    }
    if (_par_sorter.switch_recoil_cor == TRUE)
      kinema_correction(Xfp, Erec_center, Erec_Zt, Eout, Pout, _par_sorter);

    // Xfp seems incorrect!!!

    if (_par_sorter.switch_ex == TRUE)
      get_ex(Eout, Erec_center, Ex, _par_sorter, Xfp);
    corr_tof(tof, cor_tof, Thtgt, Xfp, _par_sorter); // <- should be done before
                                                     // correction? after?
  }

  // 注 X1,X2 がなければcor_tof=0.0
  eventid =
      get_eventid(_num_wire_x1, _num_wire_u1, _num_wire_x2, _num_wire_u2,
                  chisq_x1, chisq_u1, chisq_x2, chisq_u2, num_cluster_x1,
                  num_cluster_u1, num_cluster_x2, num_cluster_u2,
                  scintillator_ave_1, scintillator_ave_2, tof, cor_tof, Xferet,
                  _par_sorter, success_X1, success_U1, success_X2, success_U2);

  if (eventid == 0) {
    ++num_EvtID0;
    ++_sca_sorter.eventID0_cnt;
  } else if (eventid == 1) {
    ++num_EvtID1;
    ++_sca_sorter.eventID1_cnt;
  } else if (eventid == 2) {
    ++num_EvtID2;
    ++_sca_sorter.eventID2_cnt;
  } else if (eventid == 4) {
    ++num_EvtID4;
    ++_sca_sorter.eventID4_cnt;
  } else if (eventid == 8) {
    ++num_EvtID8;
    ++_sca_sorter.eventID8_cnt;
  }

  compare_vdc_xferet(eventid, X1, U1, X2, U2, Xferet, _sca_sorter);

  if (_par_sorter.switch_plot_high_reso == TRUE && eventid == 0) {
    s_root.fill_gatedwire(tdc_x1_cor, tdc_u1_cor, tdc_x2_cor, tdc_u2_cor);
  }
  //  s_root.fill_hist_eventid(eventid);

  // For Ex calculation
  //  if(eventid==0) get_ex(Xfp, &Pout, &Eout, &Ex);

  // eventid=0 nomi ni sitai
  if (_par_sorter.switch_plot_dama != 0) {
    s_root.fill_hist_dama(Xfp, Thtgt, Yfp, Phtgt, eventid, _par_sorter);
  } else if (_par_sorter.switch_plot_high_reso == TRUE) {
    s_root.fill_hist_high_reso(Xfp, Yfp, Thfp, Thtgt, Phtgt, Zttgt, Ex, eventid,
                               _par_sorter);
  } else {
    s_root.fill_hist_wire(_tdc_x1, _tdc_u1, _tdc_x2, _tdc_u2, tdc_x1_cor,
                          tdc_u1_cor, tdc_x2_cor, tdc_u2_cor);

    //    corrected tdc output
    s_root.fill_hist_cluster(num_cluster_x1, num_cluster_u1, num_cluster_x2,
                             num_cluster_u2);

    // Fill user defined histgrams
    s_root.fill_hist_user(X1, U1, Y1, X2, U2, Y2, Th1, Ps1, Th2, Ps2, Xfp, Yfp,
                          Thfp, Psfp, Phfp, Thtgt, Phtgt, Zttgt, Xferet, _fera,
                          _feret, tof, cor_tof, scintillator_ave_1,
                          scintillator_ave_2, chisq_x1, chisq_u1, chisq_x2,
                          chisq_u2, eventid, _num_wire_x1, _num_wire_u1,
                          _num_wire_x2, _num_wire_u2, Eout, success_X1,
                          success_U1, success_X2, success_U2, _par_sorter);

    if (eventid == 0) {
      if (_par_sorter.switch_ntuple == TRUE) {
        std::cout << "INFO: NTUPLE Mode not yet implemented!" << std::endl;
        // s_root.fill_ntp_cwn(Xfp, Thtgt, Phtgt, Ex); // s_root.fill CWN ntuple
      } else {

        s_root.fill_gatedhist_user(X1, U1, Y1, X2, U2, Y2, Th1, Ps1, Th2, Ps2,
                                   Xfp, Yfp, Thfp, Psfp, Phfp, Thtgt, Phtgt,
                                   Zttgt, Xferet, _fera, _feret, tof, cor_tof,
                                   scintillator_ave_1, scintillator_ave_2,
                                   chisq_x1, chisq_u1, chisq_x2, chisq_u2,
                                   //_pad_posi1,_pad_posi2,
                                   eventid, Pout, Eout, Ex, _par_sorter);
      }
    }
  }

  if (_par_sorter.switch_histconfig == TRUE) {
    s_root.fill_hist_config(X1, U1, Y1, X2, U2, Y2, Th1, Ps1, Th2, Ps2, Xfp,
                            Yfp, Thfp, Psfp, Phfp, Thtgt, Phtgt, Zttgt, Xferet,
                            _fera, _feret, tof, cor_tof, scintillator_ave_1,
                            scintillator_ave_2, chisq_x1, chisq_u1, chisq_x2,
                            chisq_u2, eventid, _num_wire_x1, _num_wire_u1,
                            _num_wire_x2, _num_wire_u2, Eout, success_X1,
                            success_U1, success_X2, success_U2, _par_hist);
  }

  // std::cout << eventid << " " << Xfp << " " << Thfp << " " << Phfp <<
  // std::endl;
  s_treedata.t_eventID = eventid;
  s_treedata.t_X1pos = Xfp;
  s_treedata.t_X1th = Th1;
  s_treedata.t_thetaFP = Thfp;
  s_treedata.t_phiFP = Phfp;
  s_treedata.t_Y1 = Y1;
  s_treedata.t_Y2 = Y2;
  s_treedata.t_thetaSCAT = Thtgt;
  s_treedata.t_phiSCAT = Phtgt;

  s_treedata.tree->Fill();

  return 0;
}

// とりあえずraytraceに引数としてsca_sorterを入れているが、get_eventidでgoodとされた場合に++するようにしたほうが良いかも
// xferetとx2(x1も)が大きくことなる場合になんか数えるようにするか?矛盾か抜けがある場合に位置依存性を見たい
