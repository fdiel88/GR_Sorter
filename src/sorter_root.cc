
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TList.h"
#include "TProfile.h"

#include "sorter_const.h"
#include "sorter_histpar.h"
#include "sorter_par.h"
#include "sorter_root.h"

// double __drifttable_x1[], double __drifttable_u1[],
//                        double __drifttable_x2[], double __drifttable_u2[]

TH1F *Sorter_root::find_hist_1D(std::string name, std::vector<TH1F *> &list) {
  auto it_1 = std::find_if(list.begin(), list.end(), [&name](const TH1F *obj) {
    return obj->GetName() == name;
  });
  if (it_1 != list.end()) {
    return (*it_1);
  } else { // for debugging now
    std::cout << "ERROR: Histogram " << name
              << " not found in this list (find_hist_1D)." << std::endl;
    exit(1);
  }
  return nullptr;
}

TH1F *Sorter_root::find_hist_1D_global(std::string name) {

  auto it_1 =
      std::find_if(m_hist_conf_1D.begin(), m_hist_conf_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_conf_1D.end()) {

    return (*it_1);
  }

  it_1 =
      std::find_if(m_hist_dama_1D.begin(), m_hist_dama_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_dama_1D.end()) {

    return (*it_1);
  }

  it_1 =
      std::find_if(m_hist_fera_1D.begin(), m_hist_fera_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_fera_1D.end()) {

    return (*it_1);
  }
  it_1 =
      std::find_if(m_hist_feret_1D.begin(), m_hist_feret_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_feret_1D.end()) {

    return (*it_1);
  }
  it_1 =
      std::find_if(m_hist_scaler_1D.begin(), m_hist_scaler_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_scaler_1D.end()) {

    return (*it_1);
  }
  it_1 = std::find_if(
      m_hist_scintillator_tof_1D.begin(), m_hist_scintillator_tof_1D.end(),
      [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_scintillator_tof_1D.end()) {

    return (*it_1);
  }
  it_1 =
      std::find_if(m_hist_system_1D.begin(), m_hist_system_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_system_1D.end()) {

    return (*it_1);
  }
  it_1 =
      std::find_if(m_hist_user_1D.begin(), m_hist_user_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_user_1D.end()) {

    return (*it_1);
  }
  it_1 =
      std::find_if(m_hist_v3377_1D.begin(), m_hist_v3377_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_v3377_1D.end()) {

    return (*it_1);
  }
  it_1 =
      std::find_if(m_hist_wire_1D.begin(), m_hist_wire_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_wire_1D.end()) {

    return (*it_1);
  } else {
    std::cout << "ERROR: Histogram " << name
              << " not found in any list (find_hist_1D_global)." << std::endl;
    exit(1);
  }

  return nullptr;
}

TH2F *Sorter_root::find_hist_2D(std::string name, std::vector<TH2F *> &list) {
  auto it_1 = std::find_if(list.begin(), list.end(), [&name](const TH2F *obj) {
    return obj->GetName() == name;
  });
  if (it_1 != list.end()) {
    return (*it_1);
  } else {
    std::cout << "ERROR: Histogram " << name
              << " not found in this list (find_hist_2D)." << std::endl;
    exit(1);
  }
  return nullptr;
}

TH2F *Sorter_root::find_hist_2D_global(std::string name) {

  auto it_1 =
      std::find_if(m_hist_conf_2D.begin(), m_hist_conf_2D.end(),
                   [&name](const TH2F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_conf_2D.end()) {

    return (*it_1);
  }

  it_1 =
      std::find_if(m_hist_dama_2D.begin(), m_hist_dama_2D.end(),
                   [&name](const TH2F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_dama_2D.end()) {

    return (*it_1);
  }

  it_1 = std::find_if(
      m_hist_scintillator_tof_2D.begin(), m_hist_scintillator_tof_2D.end(),
      [&name](const TH2F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_scintillator_tof_2D.end()) {

    return (*it_1);
  }

  it_1 =
      std::find_if(m_hist_system_2D.begin(), m_hist_system_2D.end(),
                   [&name](const TH2F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_system_2D.end()) {

    return (*it_1);
  }

  it_1 =
      std::find_if(m_hist_user_2D.begin(), m_hist_user_2D.end(),
                   [&name](const TH2F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_user_2D.end()) {

    return (*it_1);
  }

  it_1 =
      std::find_if(m_hist_v3377_2D.begin(), m_hist_v3377_2D.end(),
                   [&name](const TH2F *obj) { return obj->GetName() == name; });
  if (it_1 != m_hist_v3377_2D.end()) {

    return (*it_1);
  } else {
    std::cout << "ERROR: Histogram " << name
              << " not found in any list (find_hist_2D_global)." << std::endl;
    exit(1);
  }
}

TProfile *Sorter_root::find_hist_Prof(std::string name,
                                      std::vector<TProfile *> &list) {
  auto it_1 =
      std::find_if(list.begin(), list.end(), [&name](const TProfile *obj) {
        return obj->GetName() == name;
      });
  if (it_1 != list.end()) {
    return (*it_1);
  } else {
    std::cout << "ERROR: Histogram " << name
              << " not found in this list (find_hist_Prof)." << std::endl;
    exit(1);
  }
  return nullptr;
}

/* called if eventid==0 */
void Sorter_root::fill_gatedhist_user(
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
    double _Pout, double _Eout, double _Ex, struct parameters &_par_sorter) {

  TH1F *h1 = find_hist_1D(std::to_string(scinti_histID + 8),
                          m_hist_scintillator_tof_1D);
  h1->Fill(_scintillator_ave_1);
  h1 = find_hist_1D(std::to_string(scinti_histID + 9),
                    m_hist_scintillator_tof_1D);
  h1->Fill(_scintillator_ave_2);
  h1 = find_hist_1D(std::to_string(scinti_histID + 23),
                    m_hist_scintillator_tof_1D);
  h1->Fill(_cor_tof);

  TH2F *h2 = find_hist_2D(std::to_string(scinti_histID + 11),
                          m_hist_scintillator_tof_2D);
  h2->Fill(_scintillator_ave_1, _scintillator_ave_2);

  h1 = find_hist_1D(std::to_string(user_histID + 46), m_hist_user_1D);
  h1->Fill(_Xfp);

  if (_Phtgt > -1.5 && _Phtgt < 1.5) {
    h1 = find_hist_1D(std::to_string(user_histID + 48), m_hist_user_1D);
    h1->Fill(_Thtgt);
  }
  if (_Thtgt > -0.5 && _Thtgt < 0.5) {
    h1 = find_hist_1D(std::to_string(user_histID + 49), m_hist_user_1D);
    h1->Fill(_Phtgt);
  }

  h2 = find_hist_2D(std::to_string(user_histID + 134), m_hist_user_2D);
  h2->Fill(_Xfp, _Yfp);
  h2 = find_hist_2D(std::to_string(user_histID + 135), m_hist_user_2D);
  h2->Fill(_Thtgt, _Phtgt);

  h1 = find_hist_1D(std::to_string(user_histID + 70), m_hist_user_1D);
  h1->Fill(_Pout);
  h1 = find_hist_1D(std::to_string(user_histID + 81), m_hist_user_1D);
  h1->Fill(_Ex);

  // 0deg
  //  if( get_GRangle()==0 ){
  if (_par_sorter.ThGR == 0.0) {
    if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
      if (_Zttgt < 0.5) {
        h1 = find_hist_1D(std::to_string(user_histID + 51), m_hist_user_1D);
        h1->Fill(_Xfp);

      } else if (_Zttgt > 0.5 && _Zttgt < 0.8) {

        h1 = find_hist_1D(std::to_string(user_histID + 52), m_hist_user_1D);
        h1->Fill(_Xfp);
      } else if (_Zttgt > 0.8 && _Zttgt < 1.2) {

        h1 = find_hist_1D(std::to_string(user_histID + 53), m_hist_user_1D);
        h1->Fill(_Xfp);

      } else if (_Zttgt > 1.2 && _Zttgt < 1.6) {

        h1 = find_hist_1D(std::to_string(user_histID + 54), m_hist_user_1D);
        h1->Fill(_Xfp);

      } else if (_Zttgt > 1.6 && _Zttgt < 2.0) {
        h1 = find_hist_1D(std::to_string(user_histID + 55), m_hist_user_1D);
        h1->Fill(_Xfp);
      }
    }
    if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
      if (_Zttgt < 0.5) {
        h1 = find_hist_1D(std::to_string(user_histID + 71), m_hist_user_1D);
        h1->Fill(_Ex);

      } else if (_Zttgt > 0.5 && _Zttgt < 0.8) {
        h1 = find_hist_1D(std::to_string(user_histID + 72), m_hist_user_1D);
        h1->Fill(_Ex);
      } else if (_Zttgt > 0.8 && _Zttgt < 1.2) {
        h1 = find_hist_1D(std::to_string(user_histID + 73), m_hist_user_1D);
        h1->Fill(_Ex);
      } else if (_Zttgt > 1.2 && _Zttgt < 1.6) {
        h1 = find_hist_1D(std::to_string(user_histID + 74), m_hist_user_1D);
        h1->Fill(_Ex);
      } else if (_Zttgt > 1.6 && _Zttgt < 2.0) {
        h1 = find_hist_1D(std::to_string(user_histID + 75), m_hist_user_1D);
        h1->Fill(_Ex);
      }
    }
  }
  // 2.5deg
  //  else if(get_GRangle()==2.5 ){
  else if (_par_sorter.ThGR == 2.5) {
    if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
      if (_Zttgt > 2.0 && _Zttgt < 2.5) {
        h1 = find_hist_1D(std::to_string(user_histID + 56), m_hist_user_1D);
        h1->Fill(_Xfp);

      } else if (_Zttgt > 2.5 && _Zttgt < 3.0) {
        h1 = find_hist_1D(std::to_string(user_histID + 57), m_hist_user_1D);
        h1->Fill(_Xfp);
      } else if (_Zttgt > 3.0 && _Zttgt < 3.5) {
        h1 = find_hist_1D(std::to_string(user_histID + 58), m_hist_user_1D);
        h1->Fill(_Xfp);
      }
    }
    if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
      if (_Zttgt > 2.0 && _Zttgt < 2.5) {
        h1 = find_hist_1D(std::to_string(user_histID + 76), m_hist_user_1D);
        h1->Fill(_Ex);

      } else if (_Zttgt > 2.5 && _Zttgt < 3.0) {
        h1 = find_hist_1D(std::to_string(user_histID + 77), m_hist_user_1D);
        h1->Fill(_Ex);
      } else if (_Zttgt > 3.0 && _Zttgt < 3.5) {
        h1 = find_hist_1D(std::to_string(user_histID + 78), m_hist_user_1D);
        h1->Fill(_Ex);
      }
    }
  }

  // Th<0.2 would be OK for Mass>40, but for 12C(if needed), be careful!!
  if (_Thtgt > -0.2 && _Thtgt < 0.2 && _Phtgt > -0.5 && _Phtgt < 0.5) {
    h1 = find_hist_1D(std::to_string(user_histID + 60), m_hist_user_1D);
    h1->Fill(_X1);
  }

  if (_eventid == 0) {
    h1 = find_hist_1D(std::to_string(user_histID + 90), m_hist_user_1D);
    h1->Fill(_X1);
    h1 = find_hist_1D(std::to_string(user_histID + 91), m_hist_user_1D);
    h1->Fill(_U1);
    h1 = find_hist_1D(std::to_string(user_histID + 92), m_hist_user_1D);
    h1->Fill(_X2);
    h1 = find_hist_1D(std::to_string(user_histID + 93), m_hist_user_1D);
    h1->Fill(_U2);
  }
}

void Sorter_root::fill_gatedwire(std::array<int, 192> &_v3377_tdc_X1,
                                 std::array<int, 208> &_v3377_tdc_U1,
                                 std::array<int, 192> &_v3377_tdc_X2,
                                 std::array<int, 208> &_v3377_tdc_U2) {
  // gated tdc histogram (temporarily process here)
  int i;
  TH1F *h1 = find_hist_1D(std::to_string(v3377_histID), m_hist_v3377_1D);
  TH1F *h2 = find_hist_1D(std::to_string(v3377_histID + 2), m_hist_v3377_1D);
  TH1F *h3 = find_hist_1D(std::to_string(v3377_histID + 1), m_hist_v3377_1D);
  TH1F *h4 = find_hist_1D(std::to_string(v3377_histID + 3), m_hist_v3377_1D);

  for (i = 0; i < 192; ++i) {
    if (_v3377_tdc_X1[i]) {
      h1->Fill(_v3377_tdc_X1[i]);
    }
    if (_v3377_tdc_X2[i]) {
      h2->Fill(_v3377_tdc_X2[i]);
    }
  }
  for (i = 0; i < 208; ++i) {
    if (_v3377_tdc_U1[i]) {
      h3->Fill(_v3377_tdc_U1[i]);
    }
    if (_v3377_tdc_U2[i]) {
      h4->Fill(_v3377_tdc_U2[i]);
    }
  }
}

void Sorter_root::fill_hist_cluster(int _num_cluster_x1, int _num_cluster_u1,
                                    int _num_cluster_x2, int _num_cluster_u2) {
  TH1F *h1 = find_hist_1D(std::to_string(sys_histID + 29), m_hist_system_1D);
  h1->Fill(_num_cluster_x1);
  h1 = find_hist_1D(std::to_string(sys_histID + 30), m_hist_system_1D);
  h1->Fill(_num_cluster_u1);
  h1 = find_hist_1D(std::to_string(sys_histID + 31), m_hist_system_1D);
  h1->Fill(_num_cluster_x2);
  h1 = find_hist_1D(std::to_string(sys_histID + 32), m_hist_system_1D);
  h1->Fill(_num_cluster_u2);
}

// not finished yet
void Sorter_root::fill_hist_config(
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
    struct hist_parameters &_par_hist) {
  int i = 0, j = 0;
  double param_d1 = 0.0, param_d2 = 0.0;

  std::array<int, MAX_GATE> gate_result = {FALSE};
  int flg_fill = FALSE;

  TH1F *h1;
  TH2F *h2;

  // ¥¤¥Ù¥ó¥È¤¬¥²¡¼¥ÈÆâ¤«¤É¤¦¤«¥Á¥§¥Ã¥¯
  for (j = 0; _par_hist.gate_id[j] >= 0 && j < MAX_GATE; ++j) {
    get_values_hist_config(
        _X1, _U1, _Y1, _X2, _U2, _Y2, _Th1, _Ps1, _Th2, _Ps2, _Xfp, _Yfp, _Thfp,
        _Psfp, _Phfp, _Thtgt, _Phtgt, _Zttgt, _Xferet, _fera, _feret, _tof,
        _cor_tof, _scintillator_ave_1, _scintillator_ave_2, _chisq_x1,
        _chisq_u1, _chisq_x2, _chisq_u2, _eventid, _num_wire_x1, _num_wire_u1,
        _num_wire_x2, _num_wire_u2, _Eout, _success_X1, _success_U1,
        _success_X2, _success_U2, _par_hist.gate_param[j], param_d1);
    if (_par_hist.gate_type[j] == G_EQUAL) { // EQUAL GATE
      if (param_d1 == _par_hist.gate_min[j]) {
        gate_result[j] = TRUE;
      } else {
        gate_result[j] = FALSE;
      }
    } else if (_par_hist.gate_type[j] == G_MINMAX) { // MIN-MAX GATE
      if (param_d1 > _par_hist.gate_min[j] &&
          param_d1 < _par_hist.gate_max[j]) {
        gate_result[j] = TRUE;
      } else {
        gate_result[j] = FALSE;
      }
    }
  }

  // filling histograms¤Ê¤ó¤«¤¦¤Þ¤¯¤¤¤«¤Ê¤¤¡£¡£¡£
  for (i = 0, flg_fill = TRUE; _par_hist.hist_id[i] && i < MAX_HIST; ++i) {
    //    printf("aaa %d %d %d\n",i,_par_hist.hist_id[i],MAX_HIST);

    for (j = 0; _par_hist.gate_id[j] >= 0 && j < MAX_GATE; ++j) {
      if (_par_hist.hist_gate[i][j] == TRUE && gate_result[j] == FALSE &&
          flg_fill == TRUE) {
        flg_fill = FALSE;
        //	printf("bbb histgram %d flg false -> gate
        //%s\n",_par_hist.hist_id[i],_par_hist.gate_name[j]);
      }
    }

    get_values_hist_config(
        _X1, _U1, _Y1, _X2, _U2, _Y2, _Th1, _Ps1, _Th2, _Ps2, _Xfp, _Yfp, _Thfp,
        _Psfp, _Phfp, _Thtgt, _Phtgt, _Zttgt, _Xferet, _fera, _feret, _tof,
        _cor_tof, _scintillator_ave_1, _scintillator_ave_2, _chisq_x1,
        _chisq_u1, _chisq_x2, _chisq_u2, _eventid, _num_wire_x1, _num_wire_u1,
        _num_wire_x2, _num_wire_u2, _Eout, _success_X1, _success_U1,
        _success_X2, _success_U2, _par_hist.hist_param1[i], param_d1);

    //    printf("aaa histgram %d flg %d\n",_par_hist.hist_id[i],flg_fill);

    if (_par_hist.hist_order[i] == 1) {
      // ²¿ÈÖÌÜ¤Î¥²¡¼¥È¤òapply¤·¤Æ¤¤¤ë¤«³ÎÇ§¤·¤ä¤¹¤¯¤·¤¿
      if (flg_fill == TRUE) { // This should check all 1D hist vectors!
        h1 = find_hist_1D_global(std::to_string(_par_hist.hist_id[i]));
        h1->Fill(param_d1);
      }
    } else if (_par_hist.hist_order[i] == 2) {
      get_values_hist_config(
          _X1, _U1, _Y1, _X2, _U2, _Y2, _Th1, _Ps1, _Th2, _Ps2, _Xfp, _Yfp,
          _Thfp, _Psfp, _Phfp, _Thtgt, _Phtgt, _Zttgt, _Xferet, _fera, _feret,
          _tof, _cor_tof, _scintillator_ave_1, _scintillator_ave_2, _chisq_x1,
          _chisq_u1, _chisq_x2, _chisq_u2, _eventid, _num_wire_x1, _num_wire_u1,
          _num_wire_x2, _num_wire_u2, _Eout, _success_X1, _success_U1,
          _success_X2, _success_U2, _par_hist.hist_param2[i], param_d2);
      if (flg_fill == TRUE) {

        h2 = find_hist_2D_global(std::to_string(_par_hist.hist_id[i]));
        h2->Fill(param_d1, param_d2);
      }
    } else {
      fprintf(stderr, "ERROR : Unknown histgram (%d th, id:%d) order of %d. "
                      "(must be 1 or 2)\n",
              i, _par_hist.hist_id[i], _par_hist.hist_order[i]);
    }
    param_d1 = 0;
    param_d2 = 0;
    flg_fill = TRUE;
  }
}

void Sorter_root::fill_hist_dama(double _Xfp, double _Thtgt, double _Yfp,
                                 double _Phtgt, int _eventid,
                                 struct parameters &_par_sorter) {
  int i = 0;
  TH2F *h1;
  TH1F *h2;
  for (i = 0; i < MAX_XGATE_SIEVESLIT; ++i) {
    if (_par_sorter.xgate_min_dama[i] != 99999.0 &&
        _par_sorter.xgate_max_dama[i] != 99999.0) { // <- kore iran kamo
      if (_Xfp >= _par_sorter.xgate_min_dama[i] &&
          _Xfp <= _par_sorter.xgate_max_dama[i] && _eventid == 0) {
        if (_par_sorter.switch_plot_dama == 1) {
          h1 =
              find_hist_2D(std::to_string(dama_histID + i * 6), m_hist_dama_2D);
          h1->Fill(_Thtgt, _Yfp);
          if (_Thtgt >= -1.25 && _Thtgt < -0.75) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 1),
                              m_hist_dama_1D);
            h2->Fill(_Yfp);

          } // Thtgt=-1.0
          if (_Thtgt >= -0.75 && _Thtgt < -0.25) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 2),
                              m_hist_dama_1D);
            h2->Fill(_Yfp);
          } // Thtgt=-0.5
          if (_Thtgt >= -0.25 && _Thtgt < 0.25) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 3),
                              m_hist_dama_1D);
            h2->Fill(_Yfp);
          } // Thtgt= 0.0
          if (_Thtgt >= 0.25 && _Thtgt < 0.75) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 4),
                              m_hist_dama_1D);
            h2->Fill(_Yfp);
          } // Thtgt= 0.5
          if (_Thtgt >= 0.75 && _Thtgt < 1.25) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 5),
                              m_hist_dama_1D);
            h2->Fill(_Yfp);
          } // Thtgt= 1.0
        } else if (_par_sorter.switch_plot_dama == 2) {
          h1 =
              find_hist_2D(std::to_string(dama_histID + i * 6), m_hist_dama_2D);
          h1->Fill(_Thtgt, _Phtgt);
          if (_Thtgt >= -1.25 && _Thtgt < -0.75) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 1),
                              m_hist_dama_1D);
            h2->Fill(_Phtgt * DEG2MRAD);

          } // Thtgt=-1.0
          if (_Thtgt >= -0.75 && _Thtgt < -0.25) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 2),
                              m_hist_dama_1D);
            h2->Fill(_Phtgt * DEG2MRAD);
          } // Thtgt=-0.5
          if (_Thtgt >= -0.25 && _Thtgt < 0.25) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 3),
                              m_hist_dama_1D);
            h2->Fill(_Phtgt * DEG2MRAD);
          } // Thtgt= 0.0
          if (_Thtgt >= 0.25 && _Thtgt < 0.75) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 4),
                              m_hist_dama_1D);
            h2->Fill(_Phtgt * DEG2MRAD);
          } // Thtgt= 0.5
          if (_Thtgt >= 0.75 && _Thtgt < 1.25) {
            h2 = find_hist_1D(std::to_string(dama_histID + i * 6 + 5),
                              m_hist_dama_1D);
            h2->Fill(_Phtgt * DEG2MRAD);
          } // Thtgt= 1.0
        }
      }
    }
  }
}

void Sorter_root::fill_hist_dl_accuracy(double dif, int _WCID) {

  TH1F *h1;
  if (_WCID == 0) {
    h1 = find_hist_1D(std::to_string(v3377_histID + 24), m_hist_v3377_1D);
    h1->Fill(dif);
  } else if (_WCID == 1) {
    h1 = find_hist_1D(std::to_string(v3377_histID + 25), m_hist_v3377_1D);
    h1->Fill(dif);
  } else if (_WCID == 2) {
    h1 = find_hist_1D(std::to_string(v3377_histID + 26), m_hist_v3377_1D);
    h1->Fill(dif);
  } else if (_WCID == 3) {
    h1 = find_hist_1D(std::to_string(v3377_histID + 27), m_hist_v3377_1D);
    h1->Fill(dif);
  } else {
    std::cout << "WARNING : Inconsistent chamber ID (" << _WCID
              << ") in fill_hist_dl_accuarcy." << std::endl;
  }
}
void Sorter_root::fill_hist_driftlength(std::array<double, 192> &_drift_x1,
                                        std::array<double, 208> &_drift_u1,
                                        std::array<double, 192> &_drift_x2,
                                        std::array<double, 208> &_drift_u2) {
  int i;
  TH1F *h1 = find_hist_1D(std::to_string(v3377_histID + 4), m_hist_v3377_1D);
  TH1F *h2 = find_hist_1D(std::to_string(v3377_histID + 6), m_hist_v3377_1D);
  TH1F *h3 = find_hist_1D(std::to_string(v3377_histID + 5), m_hist_v3377_1D);
  TH1F *h4 = find_hist_1D(std::to_string(v3377_histID + 7), m_hist_v3377_1D);

  for (i = 0; i < N_WIRE_X1; ++i) {
    if (_drift_x1[i]) {

      h1->Fill(_drift_x1[i]);
    }
  }
  for (i = 0; i < N_WIRE_X2; ++i) {
    if (_drift_x2[i]) {
      h2->Fill(_drift_x2[i]);
    }
  }
  for (i = 0; i < N_WIRE_U1; ++i) {
    if (_drift_u1[i]) {
      h3->Fill(_drift_u1[i]);
    }
  }
  for (i = 0; i < N_WIRE_U2; ++i) {
    if (_drift_u2[i]) {
      h4->Fill(_drift_u2[i]);
    }
  }
}

void Sorter_root::fill_hist_high_reso(double _Xfp, double _Yfp, double _Thfp,
                                      double _Thtgt, double _Phtgt,
                                      double _Zttgt, double _Ex, int _eventid,
                                      struct parameters &_par_sorter) {

  TH1F *h1 = find_hist_1D(std::to_string(sys_histID + 10), m_hist_system_1D);
  h1->Fill(_eventid);

  if (_Xfp != DEFAULT_WC) {
    h1 = find_hist_1D(std::to_string(user_histID + 20), m_hist_user_1D);
    h1->Fill(_Xfp);
    h1 = find_hist_1D(std::to_string(user_histID + 24), m_hist_user_1D);
    h1->Fill(_Thtgt);
    h1 = find_hist_1D(std::to_string(user_histID + 25), m_hist_user_1D);
    h1->Fill(_Phtgt);
  }
  TH2F *h2;
  if (_eventid == 0) {
    h1 = find_hist_1D(std::to_string(user_histID + 46), m_hist_user_1D);
    h1->Fill(_Xfp);

    h2 = find_hist_2D(std::to_string(user_histID + 106), m_hist_user_2D);
    h2->Fill(_Xfp, _Thfp);
    h2 = find_hist_2D(std::to_string(user_histID + 109), m_hist_user_2D);
    h2->Fill(_Xfp, _Thtgt);
    h2 = find_hist_2D(std::to_string(user_histID + 133), m_hist_user_2D);
    h2->Fill(_Xfp, _Phtgt);

    if (_Yfp > 12. || _Yfp < -12.) {
      h2 = find_hist_2D(std::to_string(user_histID + 107), m_hist_user_2D);
      h2->Fill(_Xfp, _Thfp);
      h2 = find_hist_2D(std::to_string(user_histID + 110), m_hist_user_2D);
      h2->Fill(_Xfp, _Thtgt);
    }

    // 0deg
    //    if( get_GRangle()==0 ){
    if (_par_sorter.ThGR == 0.0) {
      if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
        if (_Zttgt < 0.5) {
          h1 = find_hist_1D(std::to_string(user_histID + 51), m_hist_user_1D);
          h1->Fill(_Xfp);

        } else if (_Zttgt > 0.5 && _Zttgt < 0.8) {
          h1 = find_hist_1D(std::to_string(user_histID + 52), m_hist_user_1D);
          h1->Fill(_Xfp);

        } else if (_Zttgt > 0.8 && _Zttgt < 1.2) {
          h1 = find_hist_1D(std::to_string(user_histID + 53), m_hist_user_1D);
          h1->Fill(_Xfp);

        } else if (_Zttgt > 1.2 && _Zttgt < 1.6) {
          h1 = find_hist_1D(std::to_string(user_histID + 54), m_hist_user_1D);
          h1->Fill(_Xfp);
        } else if (_Zttgt > 1.6 && _Zttgt < 2.0) {
          h1 = find_hist_1D(std::to_string(user_histID + 55), m_hist_user_1D);
          h1->Fill(_Xfp);
        }
      }
      if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
        if (_Zttgt < 0.5) {
          h1 = find_hist_1D(std::to_string(user_histID + 71), m_hist_user_1D);
          h1->Fill(_Ex);

        } else if (_Zttgt > 0.5 && _Zttgt < 0.8) {
          h1 = find_hist_1D(std::to_string(user_histID + 72), m_hist_user_1D);
          h1->Fill(_Ex);
        } else if (_Zttgt > 0.8 && _Zttgt < 1.2) {
          h1 = find_hist_1D(std::to_string(user_histID + 73), m_hist_user_1D);
          h1->Fill(_Ex);
        } else if (_Zttgt > 1.2 && _Zttgt < 1.6) {
          h1 = find_hist_1D(std::to_string(user_histID + 74), m_hist_user_1D);
          h1->Fill(_Ex);
        } else if (_Zttgt > 1.6 && _Zttgt < 2.0) {
          h1 = find_hist_1D(std::to_string(user_histID + 75), m_hist_user_1D);
          h1->Fill(_Ex);
        }
      }
      h1 = find_hist_1D(std::to_string(user_histID + 90), m_hist_user_1D);
      h1->Fill(_Ex);

    }
    // 2.5deg
    //    else if(get_GRangle()==2.5 ){
    else if (_par_sorter.ThGR == 2.5) {
      if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
        if (_Zttgt > 2.0 && _Zttgt < 2.5) {
          h1 = find_hist_1D(std::to_string(user_histID + 56), m_hist_user_1D);
          h1->Fill(_Xfp);

        } else if (_Zttgt > 2.5 && _Zttgt < 3.0) {
          h1 = find_hist_1D(std::to_string(user_histID + 57), m_hist_user_1D);
          h1->Fill(_Xfp);
        } else if (_Zttgt > 3.0 && _Zttgt < 3.5) {
          h1 = find_hist_1D(std::to_string(user_histID + 58), m_hist_user_1D);
          h1->Fill(_Xfp);
        }
      }
      if (_Thtgt > -0.8 && _Thtgt < 0.8 && _Phtgt > -2.0 && _Phtgt < 2.0) {
        if (_Zttgt > 2.0 && _Zttgt < 2.5) {
          h1 = find_hist_1D(std::to_string(user_histID + 76), m_hist_user_1D);
          h1->Fill(_Ex);
        } else if (_Zttgt > 2.5 && _Zttgt < 3.0) {
          h1 = find_hist_1D(std::to_string(user_histID + 77), m_hist_user_1D);
          h1->Fill(_Ex);
        } else if (_Zttgt > 3.0 && _Zttgt < 3.5) {
          h1 = find_hist_1D(std::to_string(user_histID + 78), m_hist_user_1D);
          h1->Fill(_Ex);
        }
      }
    }
  }
}

void Sorter_root::fill_hist_rayid(int _WCID, int _rayid) {

  TH1F *h1 =
      find_hist_1D(std::to_string(wire_histID + 16 + _WCID), m_hist_wire_1D);
  h1->Fill(_rayid);
}
void Sorter_root::fill_hist_resolution(int _wireID, double drift,
                                       double drift_esti, int _XID) {
  /* _XID 0:X1 1:U1 2:X2 3:U2 */
  if (_XID == 0) {
    TH2F *h1 = find_hist_2D(std::to_string(sys_histID + 17), m_hist_system_2D);

    h1->Fill(drift - drift_esti, drift);

    TH2F *h2 = find_hist_2D(std::to_string(sys_histID + 25), m_hist_system_2D);
    if (drift != 0) {
      TProfile *h3 =
          find_hist_Prof(std::to_string(sys_histID + 21), m_hist_system_prof);

      h3->Fill(drift, 1 - drift_esti / drift);

      h2->Fill(drift, 1 - drift_esti / drift);
    }

    h2->Fill(_wireID, drift - drift_esti);

    if (drift > 2) {
      TH1F *h4 =
          find_hist_1D(std::to_string(sys_histID + 33), m_hist_system_1D);
      h4->Fill(drift - drift_esti);
    }

  } else if (_XID == 1) {
    TH2F *h1 = find_hist_2D(std::to_string(sys_histID + 18), m_hist_system_2D);

    h1->Fill(drift - drift_esti, drift);

    TH2F *h2 = find_hist_2D(std::to_string(sys_histID + 26), m_hist_system_2D);
    if (drift != 0) {
      TProfile *h3 =
          find_hist_Prof(std::to_string(sys_histID + 22), m_hist_system_prof);

      h3->Fill(drift, 1 - drift_esti / drift);

      h2->Fill(drift, 1 - drift_esti / drift);
    }

    h2->Fill(_wireID, drift - drift_esti);

    if (drift > 2) {
      TH1F *h4 =
          find_hist_1D(std::to_string(sys_histID + 34), m_hist_system_1D);
      h4->Fill(drift - drift_esti);
    }

  } else if (_XID == 2) {
    TH2F *h1 = find_hist_2D(std::to_string(sys_histID + 19), m_hist_system_2D);

    h1->Fill(drift - drift_esti, drift);

    TH2F *h2 = find_hist_2D(std::to_string(sys_histID + 27), m_hist_system_2D);
    if (drift != 0) {
      TProfile *h3 =
          find_hist_Prof(std::to_string(sys_histID + 23), m_hist_system_prof);

      h3->Fill(drift, 1 - drift_esti / drift);

      h2->Fill(drift, 1 - drift_esti / drift);
    }

    h2->Fill(_wireID, drift - drift_esti);

    if (drift > 2) {
      TH1F *h4 =
          find_hist_1D(std::to_string(sys_histID + 35), m_hist_system_1D);
      h4->Fill(drift - drift_esti);
    }

  } else if (_XID == 3) {
    TH2F *h1 = find_hist_2D(std::to_string(sys_histID + 20), m_hist_system_2D);

    h1->Fill(drift - drift_esti, drift);

    TH2F *h2 = find_hist_2D(std::to_string(sys_histID + 28), m_hist_system_2D);
    if (drift != 0) {
      TProfile *h3 =
          find_hist_Prof(std::to_string(sys_histID + 24), m_hist_system_prof);

      h3->Fill(drift, 1 - drift_esti / drift);

      h2->Fill(drift, 1 - drift_esti / drift);
    }

    h2->Fill(_wireID, drift - drift_esti);

    if (drift > 2) {
      TH1F *h4 =
          find_hist_1D(std::to_string(sys_histID + 36), m_hist_system_1D);
      h4->Fill(drift - drift_esti);
    }
  }
}

void Sorter_root::fill_hist_drifttable(
    std::array<double, 1024> _drifttable_x1,
    std::array<double, 1024> _drifttable_u1,
    std::array<double, 1024> _drifttable_x2,
    std::array<double, 1024> _drifttable_u2) {
  int i, j;

  std::string name;
  name = std::to_string(v3377_histID + 8);

  TH1F *h1 = find_hist_1D(std::to_string(v3377_histID + 8), m_hist_v3377_1D);
  TH1F *h2 = find_hist_1D(std::to_string(v3377_histID + 9), m_hist_v3377_1D);
  TH1F *h3 = find_hist_1D(std::to_string(v3377_histID + 10), m_hist_v3377_1D);
  TH1F *h4 = find_hist_1D(std::to_string(v3377_histID + 11), m_hist_v3377_1D);
  /*auto it_1 =
      std::find_if(m_hist_v3377_1D.begin(), m_hist_v3377_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name;
  });

  name = std::to_string(v3377_histID + 9);
  auto it_2 =
      std::find_if(m_hist_v3377_1D.begin(), m_hist_v3377_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name;
  });

  name = std::to_string(v3377_histID + 10);
  auto it_3 =
      std::find_if(m_hist_v3377_1D.begin(), m_hist_v3377_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name;
  });

  name = std::to_string(v3377_histID + 11);
  auto it_4 =
      std::find_if(m_hist_v3377_1D.begin(), m_hist_v3377_1D.end(),
                   [&name](const TH1F *obj) { return obj->GetName() == name;
  });
*/
  for (i = 0; i < 1024; ++i) {
    // if (h1 != m_hist_v3377_1D.end()) {
    for (j = 1; j <= _drifttable_x1[i] * 1000; ++j) {
      h1->Fill(i);
    }

    // }

    // if (h2 != m_hist_v3377_1D.end()) {
    for (j = 1; j <= _drifttable_u1[i] * 1000; ++j) {
      h2->Fill(i);
    }
    //}
    // if (h3 != m_hist_v3377_1D.end()) {
    for (j = 1; j <= _drifttable_x2[i] * 1000; ++j) {

      h3->Fill(i);
    }
    //}
    // if (h4 != m_hist_v3377_1D.end()) {
    for (j = 1; j <= _drifttable_u2[i] * 1000; ++j) {

      h4->Fill(i);
    }
    // }
  }
}
void Sorter_root::fill_hist_rubbishwire(int wireid, int xid) {

  if (xid == 0) { // X1
    TH1F *h1 = find_hist_1D(std::to_string(wire_histID + 4), m_hist_wire_1D);
    h1->Fill(wireid);
  } else if (xid == 1) { // U1
    TH1F *h1 = find_hist_1D(std::to_string(wire_histID + 5), m_hist_wire_1D);
    h1->Fill(wireid);
  } else if (xid == 2) { // X2
    TH1F *h1 = find_hist_1D(std::to_string(wire_histID + 6), m_hist_wire_1D);
    h1->Fill(wireid);
  } else if (xid == 3) { // U2
    TH1F *h1 = find_hist_1D(std::to_string(wire_histID + 7), m_hist_wire_1D);
    h1->Fill(wireid);
  }
}

void Sorter_root::fill_hist_twowires(int _WCID, int TDC_firstwire,
                                     int TDC_secondwire) {
  TH2F *h1 =
      find_hist_2D(std::to_string(v3377_histID + 20 + _WCID), m_hist_v3377_2D);
  h1->Fill(TDC_firstwire, TDC_secondwire);
}

// void fill_hist_wire(int _v3377_tdc_X1[],int _v3377_tdc_U1[],int
// _v3377_tdc_X2[],int _v3377_tdc_U2[]){

void Sorter_root::fill_hist_user(
    double _X1, double _U1, double _Y1, double _X2, double _U2, double _Y2,
    double _Th1, double _Ps1, double _Th2, double _Ps2, double _Xfp,
    double _Yfp, double _Thfp, double _Psfp, double _Phfp, double _Thtgt,
    double _Phtgt, double _Zttgt, double _Xferet,
    std::array<unsigned int, 4> &_fera, std::array<unsigned int, 5> &_feret,
    int _tof, double _cor_tof, double _scintillator_ave_1,
    double _scintillator_ave_2, double _chisq_x1, double _chisq_u1,
    double _chisq_x2, double _chisq_u2,
    //		    double _pad_posi1,double _pad_posi2,
    int _eventid, int _num_wire_x1, int _num_wire_u1, int _num_wire_x2,
    int _num_wire_u2, double _Eout, int _success_X1, int _success_U1,
    int _success_X2, int _success_U2, struct parameters &_par_sorter) {

  TH1F *h1 = find_hist_1D(std::to_string(sys_histID + 10), m_hist_system_1D);
  h1->Fill(_eventid);

  TH2F *h2 = find_hist_2D(std::to_string(sys_histID + 14), m_hist_system_2D);
  h2->Fill(_Xferet, _eventid);

  h1 = find_hist_1D(std::to_string(scinti_histID + 20),
                    m_hist_scintillator_tof_1D);
  h1->Fill(_tof);

  if (_cor_tof) {
    h1 = find_hist_1D(std::to_string(scinti_histID + 21),
                      m_hist_scintillator_tof_1D);
    h1->Fill(_cor_tof);
  }

  if ((_scintillator_ave_1 > _par_sorter.scinti_1_min) &&
      (_scintillator_ave_1 < _par_sorter.scinti_1_max)) {
    h1 = find_hist_1D(std::to_string(scinti_histID + 6),
                      m_hist_scintillator_tof_1D);
    h1->Fill(_scintillator_ave_1);
  }
  if ((_scintillator_ave_2 > _par_sorter.scinti_2_min) &&
      (_scintillator_ave_2 < _par_sorter.scinti_2_max)) {

    h1 = find_hist_1D(std::to_string(scinti_histID + 7),
                      m_hist_scintillator_tof_1D);
    h1->Fill(_scintillator_ave_2);
  }

  if (_cor_tof && ((_cor_tof > _par_sorter.cortof_1_min &&
                    _cor_tof < _par_sorter.cortof_1_max) ||
                   (_cor_tof > _par_sorter.cortof_2_min &&
                    _cor_tof < _par_sorter.cortof_2_max))) {
    h1 = find_hist_1D(std::to_string(scinti_histID + 22),
                      m_hist_scintillator_tof_1D);
    h1->Fill(_cor_tof);
  }

  h2 = find_hist_2D(std::to_string(user_histID + 36), m_hist_user_2D);
  h2->Fill(_Xferet, _fera[0]);
  h2 = find_hist_2D(std::to_string(user_histID + 37), m_hist_user_2D);
  h2->Fill(_Xferet, _fera[1]);

  h2 = find_hist_2D(std::to_string(user_histID + 38), m_hist_user_2D);
  h2->Fill(_Xferet, _scintillator_ave_1);
  h2 = find_hist_2D(std::to_string(user_histID + 39), m_hist_user_2D);
  h2->Fill(_Xferet, _fera[2]);
  h2 = find_hist_2D(std::to_string(user_histID + 40), m_hist_user_2D);
  h2->Fill(_Xferet, _fera[3]);
  h2 = find_hist_2D(std::to_string(user_histID + 41), m_hist_user_2D);
  h2->Fill(_Xferet, _scintillator_ave_2);

  if (_X1 != DEFAULT_WC) {
    if (_chisq_x1) {

      h1 = find_hist_1D(std::to_string(user_histID), m_hist_user_1D);
      h1->Fill(_chisq_x1);

      h2 = find_hist_2D(std::to_string(user_histID + 32), m_hist_user_2D);
      h2->Fill(_X1, _chisq_x1);
    }

    h1 = find_hist_1D(std::to_string(user_histID + 10), m_hist_user_1D);
    h1->Fill(_X1);
    h1 = find_hist_1D(std::to_string(user_histID + 11), m_hist_user_1D);
    h1->Fill(_Th1);
    h2 = find_hist_2D(std::to_string(user_histID + 100), m_hist_user_2D);
    h2->Fill(_X1, _Th1);
  }
  if (_U1 != DEFAULT_WC) {
    if (_chisq_u1) {
      h1 = find_hist_1D(std::to_string(user_histID + 1), m_hist_user_1D);
      h1->Fill(_chisq_u1);
      h2 = find_hist_2D(std::to_string(user_histID + 33), m_hist_user_2D);
      h2->Fill(_U1, _chisq_u1);
    }

    h1 = find_hist_1D(std::to_string(user_histID + 12), m_hist_user_1D);
    h1->Fill(_U1);
    h1 = find_hist_1D(std::to_string(user_histID + 13), m_hist_user_1D);
    h1->Fill(_Ps1);
    h2 = find_hist_2D(std::to_string(user_histID + 101), m_hist_user_2D);
    h2->Fill(_U1, _Ps1);
  }

  if (_X2 != DEFAULT_WC) {
    if (_chisq_x2) {
      h1 = find_hist_1D(std::to_string(user_histID + 2), m_hist_user_1D);
      h1->Fill(_chisq_x2);
      h2 = find_hist_2D(std::to_string(user_histID + 34), m_hist_user_2D);
      h2->Fill(_X2, _chisq_x2);
    }

    h1 = find_hist_1D(std::to_string(user_histID + 15), m_hist_user_1D);
    h1->Fill(_X2);
    h1 = find_hist_1D(std::to_string(user_histID + 16), m_hist_user_1D);
    h1->Fill(_Th2);
    h2 = find_hist_2D(std::to_string(user_histID + 102), m_hist_user_2D);
    h2->Fill(_X2, _Th2);
  }

  if (_U2 != DEFAULT_WC) {
    if (_chisq_u2) {
      h1 = find_hist_1D(std::to_string(user_histID + 3), m_hist_user_1D);
      h1->Fill(_chisq_u2);
      h2 = find_hist_2D(std::to_string(user_histID + 35), m_hist_user_2D);
      h2->Fill(_U2, _chisq_u2);
    }
    h1 = find_hist_1D(std::to_string(user_histID + 17), m_hist_user_1D);
    h1->Fill(_U2);
    h1 = find_hist_1D(std::to_string(user_histID + 18), m_hist_user_1D);
    h1->Fill(_Ps2);
    h2 = find_hist_2D(std::to_string(user_histID + 103), m_hist_user_2D);
    h2->Fill(_U2, _Ps2);
  }

  if (_X1 != DEFAULT_WC && _U1 != DEFAULT_WC) {
    h1 = find_hist_1D(std::to_string(user_histID + 14), m_hist_user_1D);
    h1->Fill(_Y1);
    h2 = find_hist_2D(std::to_string(user_histID + 130), m_hist_user_2D);
    h2->Fill(_X1, _Y1);
  }

  if (_X2 != DEFAULT_WC && _U2 != DEFAULT_WC) {
    h1 = find_hist_1D(std::to_string(user_histID + 19), m_hist_user_1D);
    h1->Fill(_Y2);
    h2 = find_hist_2D(std::to_string(user_histID + 131), m_hist_user_2D);
    h2->Fill(_X2, _Y2);
  }

  if (_U1 != DEFAULT_WC && _U2 != DEFAULT_WC) {
    h2 = find_hist_2D(std::to_string(user_histID + 140), m_hist_user_2D);
    h2->Fill(_U1, _Psfp);
  }
  h1 = find_hist_1D(std::to_string(user_histID + 50), m_hist_user_1D);
  h1->Fill(_Xferet);

  if (_Xferet != DEFAULT_WC && _success_X1 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 150), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  if (_Xferet != DEFAULT_WC && _success_U1 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 151), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  if (_Xferet != DEFAULT_WC && _success_X2 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 152), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  if (_Xferet != DEFAULT_WC && _success_U2 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 153), m_hist_user_1D);
    h1->Fill(_Xferet);
  }

  // --- test
  if (_success_X1 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 154), m_hist_user_1D);
    h1->Fill(_X1);
  }
  if (_success_U1 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 155), m_hist_user_1D);
    h1->Fill(_U1);
  }
  if (_success_X2 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 156), m_hist_user_1D);
    h1->Fill(_X2);
  }
  if (_success_U2 == FALSE) {
    h1 = find_hist_1D(std::to_string(user_histID + 157), m_hist_user_1D);
    h1->Fill(_U2);
  }
  // ---
  if (_eventid == 1) {
    h1 = find_hist_1D(std::to_string(user_histID + 158), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  if (_eventid == 2) {
    h1 = find_hist_1D(std::to_string(user_histID + 159), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  if (_eventid == 4) {
    h1 = find_hist_1D(std::to_string(user_histID + 160), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  if (_eventid == 8) {
    h1 = find_hist_1D(std::to_string(user_histID + 161), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  if (_eventid == 0) {
    h1 = find_hist_1D(std::to_string(user_histID + 162), m_hist_user_1D);
    h1->Fill(_Xferet);
  }
  // ---

  if (_X1 != DEFAULT_WC && _U1 != DEFAULT_WC && _X2 != DEFAULT_WC &&
      _U2 != DEFAULT_WC) {
    h1 = find_hist_1D(std::to_string(user_histID + 20), m_hist_user_1D);
    h1->Fill(_Xfp);
    h1 = find_hist_1D(std::to_string(user_histID + 21), m_hist_user_1D);
    h1->Fill(_Thfp);
    h1 = find_hist_1D(std::to_string(user_histID + 22), m_hist_user_1D);
    h1->Fill(_Yfp);
    h1 = find_hist_1D(std::to_string(user_histID + 23), m_hist_user_1D);
    h1->Fill(_Phfp);

    if (_Phtgt > -20. && _Phtgt < 20.) { // just to reject junk events
      h1 = find_hist_1D(std::to_string(user_histID + 24), m_hist_user_1D);
      h1->Fill(_Thtgt);
    }

    if (_Thtgt > -20. && _Thtgt < 20.) {
      h1 = find_hist_1D(std::to_string(user_histID + 25), m_hist_user_1D);
      h1->Fill(_Phtgt);
    }
    h1 = find_hist_1D(std::to_string(user_histID + 26), m_hist_user_1D);
    h1->Fill(_Thfp - _Th1);
    h1 = find_hist_1D(std::to_string(user_histID + 27), m_hist_user_1D);
    h1->Fill(_Thfp - _Th2);
    h1 = find_hist_1D(std::to_string(user_histID + 28), m_hist_user_1D);
    h1->Fill(_Th1 - _Th2);

    h1 = find_hist_1D(std::to_string(user_histID + 29), m_hist_user_1D);
    h1->Fill(_Psfp - _Ps1);
    h1 = find_hist_1D(std::to_string(user_histID + 30), m_hist_user_1D);
    h1->Fill(_Psfp - _Ps2);
    h1 = find_hist_1D(std::to_string(user_histID + 31), m_hist_user_1D);
    h1->Fill(_Ps1 - _Ps2);

    TProfile *h3;

    // test -----
    if (_par_sorter.switch_feret == 1) {
      // HFILL must be used since it is Profile histogram

      h3 = find_hist_Prof(std::to_string(user_histID + 232), m_hist_user_prof);
      h3->Fill(_feret[0] - _feret[1], _X1);

    } else {
      h3 = find_hist_Prof(std::to_string(user_histID + 232), m_hist_user_prof);
      h3->Fill(_feret[2] - _feret[3], _X1);
    }
    h2 = find_hist_2D(std::to_string(user_histID + 233), m_hist_user_2D);
    h2->Fill(_X1, _Xferet);
    // ----------

    h2 = find_hist_2D(std::to_string(user_histID + 42), m_hist_user_2D);
    h2->Fill(_Xfp, _tof);

    h2 = find_hist_2D(std::to_string(user_histID + 43), m_hist_user_2D);
    h2->Fill(_Thtgt, _tof);

    h2 = find_hist_2D(std::to_string(user_histID + 44), m_hist_user_2D);
    h2->Fill(_Xfp, _cor_tof);

    h2 = find_hist_2D(std::to_string(user_histID + 45), m_hist_user_2D);
    h2->Fill(_Thtgt, _cor_tof);

    h1 = find_hist_1D(std::to_string(user_histID + 47), m_hist_user_1D);
    h1->Fill(_Zttgt);

    h2 = find_hist_2D(std::to_string(user_histID + 104), m_hist_user_2D);
    h2->Fill(_X1, _Thfp);

    h2 = find_hist_2D(std::to_string(user_histID + 105), m_hist_user_2D);
    h2->Fill(_X2, _Thfp);

    h2 = find_hist_2D(std::to_string(user_histID + 106), m_hist_user_2D);
    h2->Fill(_Xfp, _Thfp);

    // Y gate to avoid the big hole
    if (_Yfp > 12. || _Yfp < -12.) {

      h2 = find_hist_2D(std::to_string(user_histID + 107), m_hist_user_2D);
      h2->Fill(_Xfp, _Thfp);

      h2 = find_hist_2D(std::to_string(user_histID + 110), m_hist_user_2D);
      h2->Fill(_Xfp, _Thtgt);
    }
    h2 = find_hist_2D(std::to_string(user_histID + 109), m_hist_user_2D);
    h2->Fill(_Xfp, _Thtgt);

    h2 = find_hist_2D(std::to_string(user_histID + 133), m_hist_user_2D);
    h2->Fill(_Xfp, _Phtgt);

    h2 = find_hist_2D(std::to_string(user_histID + 115), m_hist_user_2D);
    h2->Fill(_Xfp, _eventid);

    h2 = find_hist_2D(std::to_string(user_histID + 120), m_hist_user_2D);
    h2->Fill(_Thtgt, _Phtgt);

    h2 = find_hist_2D(std::to_string(user_histID + 132), m_hist_user_2D);
    h2->Fill(_Xfp, _Yfp);

    h1 = find_hist_1D(std::to_string(user_histID + 80), m_hist_user_1D);
    h1->Fill(_Eout);
  }
}

void Sorter_root::fill_hist_wire(
    std::array<int, 192> &_tdc_x1, std::array<int, 208> &_tdc_u1,
    std::array<int, 192> &_tdc_x2, std::array<int, 208> &_tdc_u2,
    std::array<int, 192> &_tdc_x1_cor, std::array<int, 208> &_tdc_u1_cor,
    std::array<int, 192> &_tdc_x2_cor, std::array<int, 208> &_tdc_u2_cor) {
  int i;
  TH1F *h1 = find_hist_1D(std::to_string(wire_histID), m_hist_wire_1D);
  TH2F *h2 = find_hist_2D(std::to_string(v3377_histID + 12), m_hist_v3377_2D);

  for (i = 0; i < 192; ++i) {
    if (_tdc_x1[i]) {
      h1->Fill(i);
      h2->Fill(_tdc_x1[i], i);
    }
  }
  h1 = find_hist_1D(std::to_string(v3377_histID), m_hist_v3377_1D);
  h2 = find_hist_2D(std::to_string(v3377_histID + 16), m_hist_v3377_2D);

  for (i = 0; i < 192; ++i) {
    if (_tdc_x1_cor[i]) {
      h1->Fill(_tdc_x1_cor[i]);
      h2->Fill(_tdc_x1_cor[i], i);
    }
  }
  h1 = find_hist_1D(std::to_string(wire_histID + 2), m_hist_wire_1D);
  h2 = find_hist_2D(std::to_string(v3377_histID + 14), m_hist_v3377_2D);

  for (i = 0; i < 192; ++i) {
    if (_tdc_x2[i]) {
      h1->Fill(i);
      h2->Fill(_tdc_x2[i], i);
    }
  }

  h1 = find_hist_1D(std::to_string(v3377_histID + 2), m_hist_v3377_1D);
  h2 = find_hist_2D(std::to_string(v3377_histID + 18), m_hist_v3377_2D);

  for (i = 0; i < 192; ++i) {
    if (_tdc_x2_cor[i]) {
      h1->Fill(_tdc_x2_cor[i]);
      h2->Fill(_tdc_x2_cor[i], i);
    }
  }
  h1 = find_hist_1D(std::to_string(wire_histID + 1), m_hist_wire_1D);
  h2 = find_hist_2D(std::to_string(v3377_histID + 13), m_hist_v3377_2D);

  for (i = 0; i < 208; ++i) {
    if (_tdc_u1[i]) {
      h1->Fill(i);
      h2->Fill(_tdc_u1[i], i);
    }
  }
  h1 = find_hist_1D(std::to_string(v3377_histID + 1), m_hist_v3377_1D);
  h2 = find_hist_2D(std::to_string(v3377_histID + 17), m_hist_v3377_2D);

  for (i = 0; i < 208; ++i) {
    if (_tdc_u1_cor[i]) {
      h1->Fill(_tdc_u1_cor[i]);
      h2->Fill(_tdc_u1_cor[i], i);
    }
  }
  h1 = find_hist_1D(std::to_string(wire_histID + 3), m_hist_wire_1D);
  h2 = find_hist_2D(std::to_string(v3377_histID + 15), m_hist_v3377_2D);

  for (i = 0; i < 208; ++i) {
    if (_tdc_u2[i]) {
      h1->Fill(i);
      h2->Fill(_tdc_u2[i], i);
    }
  }
  h1 = find_hist_1D(std::to_string(v3377_histID + 3), m_hist_v3377_1D);
  h2 = find_hist_2D(std::to_string(v3377_histID + 19), m_hist_v3377_2D);

  for (i = 0; i < 208; ++i) {
    if (_tdc_u2_cor[i]) {
      h1->Fill(_tdc_u2_cor[i]);
      h2->Fill(_tdc_u2_cor[i], i);
    }
  }
}

int Sorter_root::get_values_hist_config(
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
    std::string &par_name, double &par_double) {
  par_double = 0.0;

  // ÂçÊ¸»ú¤È¾®Ê¸»ú¤Î¶èÊÌ¤ò¤·¤Ê¤¤¤è¤¦¤Ë¤¹¤Ù¤­

  if (par_name == "X1") {
    par_double = _X1;
  } else if (par_name == "U1") {
    par_double = _U1;
  } else if (par_name == "Y1") {
    par_double = _Y1;
  } else if (par_name == "X2") {
    par_double = _X2;
  } else if (par_name == "U2") {
    par_double = _U2;
  } else if (par_name == "Y2") {
    par_double = _Y2;
  } else if (par_name == "Th1") {
    par_double = _Th1;
  } else if (par_name == "Ps1") {
    par_double = _Ps1;
  } else if (par_name == "Th2") {
    par_double = _Th2;
  } else if (par_name == "Ps2") {
    par_double = _Ps2;
  } else if (par_name == "Xfp") {
    par_double = _Xfp;
  } else if (par_name == "Yfp") {
    par_double = _Yfp;
  } else if (par_name == "Thfp") {
    par_double = _Thfp;
  } else if (par_name == "Psfp") {
    par_double = _Psfp;
  } else if (par_name == "Phfp") {
    par_double = _Phfp;
  } else if (par_name == "Thtgt") {
    par_double = _Thtgt;
  } else if (par_name == "Phtgt") {
    par_double = _Phtgt;
  } else if (par_name == "Zttgt") {
    par_double = _Zttgt;
  } else if (par_name == "Xferet") {
    par_double = _Xferet;
  }
  // fera/feret¤ÏËÜÅö¤ËÉ¬Í×¡©
  else if (par_name == "Fera1L") {
    par_double = (double)_fera[0];
  } else if (par_name == "Fera1R") {
    par_double = (double)_fera[1];
  } else if (par_name == "Fera2L") {
    par_double = (double)_fera[2];
  } else if (par_name == "Fera2R") {
    par_double = (double)_fera[3];
  } else if (par_name == "Feret1L") {
    par_double = (double)_feret[0];
  } else if (par_name == "Feret1R") {
    par_double = (double)_feret[1];
  } else if (par_name == "Feret2L") {
    par_double = (double)_feret[2];
  } else if (par_name == "Feret2R") {
    par_double = (double)_feret[3];
  }
  //
  else if (par_name == "Tof") {
    par_double = (double)_tof;
  } else if (par_name == "CorTof") {
    par_double = _cor_tof;
  } else if (par_name == "Plastic1") {
    par_double = _scintillator_ave_1;
  } else if (par_name == "Plastic2") {
    par_double = _scintillator_ave_2;
  } else if (par_name == "Chisqx1") {
    par_double = _chisq_x1;
  } else if (par_name == "Chisqu1") {
    par_double = _chisq_u1;
  } else if (par_name == "Chisqx2") {
    par_double = _chisq_x2;
  } else if (par_name == "Chisqu2") {
    par_double = _chisq_u2;
  } else if (par_name == "Eventid") {
    par_double = (double)_eventid;
  } else if (par_name == "Numwirex1") {
    par_double = (double)_num_wire_x1;
  } else if (par_name == "Numwireu1") {
    par_double = (double)_num_wire_u1;
  } else if (par_name == "Numwirex2") {
    par_double = (double)_num_wire_x2;
  } else if (par_name == "Numwireu2") {
    par_double = (double)_num_wire_u2;
  } else if (par_name == "Eout") {
    par_double = _Eout;
  } else if (par_name == "Successx1") {
    par_double = (double)_success_X1;
  } else if (par_name == "Successu1") {
    par_double = (double)_success_U1;
  } else if (par_name == "Successx2") {
    par_double = (double)_success_X2;
  } else if (par_name == "Successu2") {
    par_double = (double)_success_U2;
  } else {
    return 1;
  }

  return 0;
}

void Sorter_root::open_hist(struct parameters &_par_sorter,
                            struct hist_parameters &_par_hist) {

  if (_par_sorter.globalareaname == "OFF" ||
      _par_sorter.globalareaname.empty()) {
    std::cout << "Info : Global area is not defined." << std::endl;
    // Hope I dont need this
    // HLIMIT(PAWC_SIZE);

  } else {
    std::cout << "Info : Global area named \"" << _par_sorter.globalareaname
              << "\" defined." << std::endl;

    // Hope I dont need this either
    // HLIMAP(PAWC_SIZE, _par_sorter->globalareaname);
  }

  if (_par_sorter.switch_plot_dama != 0) {
    open_hist_dama(_par_sorter);
  } else if (_par_sorter.switch_plot_high_reso == TRUE) {
    // open_hist_high_reso(_par_sorter);
  } else {
    open_hist_scaler();
    if (_par_sorter.switch_plot_scinti_tof == TRUE) {
      open_hist_scintillator_tof(); // Histograms for Scintillator and TOF
    }
    if (_par_sorter.switch_plot_fera == TRUE) {
      open_hist_fera(); // Histograms for FERA module
    }
    if (_par_sorter.switch_plot_feret == TRUE) {
      open_hist_feret(); // Histograms for FERET module
    }
    if (_par_sorter.switch_plot_3377 == TRUE) {
      open_hist_wire(); // Histgrams for 3377 module
    }
    if (_par_sorter.switch_plot_system == TRUE) {
      open_hist_system();
    }
    if (_par_sorter.switch_plot_user == TRUE)
      open_hist_user(_par_sorter); // User defined histograms
  }

  if (_par_sorter.switch_histconfig == TRUE)
    open_hist_config(_par_hist); // User defined histograms
}

void Sorter_root::open_hist_config(struct hist_parameters &_par_hist) {
  std::cout << "Info : Open Hist Config!" << std::endl;

  int i = 0;
  while (_par_hist.hist_id[i] != 0) {
    if (_par_hist.hist_order[i] == 1) {
      m_hist_conf_1D.push_back(
          new TH1F(std::to_string(_par_hist.hist_id[i]).c_str(),
                   _par_hist.hist_name[i].c_str(), _par_hist.hist_numch1[i],
                   _par_hist.hist_min1[i], _par_hist.hist_max1[i]));
    } else if (_par_hist.hist_order[i] == 2) {
      m_hist_conf_2D.push_back(
          new TH2F(std::to_string(_par_hist.hist_id[i]).c_str(),
                   _par_hist.hist_name[i].c_str(), _par_hist.hist_numch1[i],
                   _par_hist.hist_min1[i], _par_hist.hist_max1[i],
                   _par_hist.hist_numch2[i], _par_hist.hist_min2[i],
                   _par_hist.hist_max2[i]));
    } else {
      std::cout << "ERROR : Unknown histgram order of "
                << _par_hist.hist_order[i] << ". (must be 1 or 2)\n"
                << std::endl;
    }
    ++i;
  }
}

void Sorter_root::open_hist_dama(struct parameters &_par_sorter) {
  std::cout << "Info : Open Hist Dama!" << std::endl;

  int i = 0;
  std::string name_tmp;

  if (_par_sorter.switch_plot_dama == 1) {
    for (i = 0; i < MAX_XGATE_SIEVESLIT; ++i) {
      if (_par_sorter.xgate_min_dama[i] != 99999.0 &&
          _par_sorter.xgate_max_dama[i] != 99999.0) {
        name_tmp = std::to_string(dama_histID + i * 6);

        m_hist_dama_2D.push_back(new TH2F(name_tmp.c_str(), "Thtgt vs Yfp", 128,
                                          -2., 2., 128, -50., 50.));
        name_tmp = std::to_string(dama_histID + i * 6 + 1);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Yfp (Thtgt=-1.0)", 200, -50., 50.));
        name_tmp = std::to_string(dama_histID + i * 6 + 2);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Yfp (Thtgt=-0.5)", 200, -50., 50.));
        name_tmp = std::to_string(dama_histID + i * 6 + 3);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Yfp (Thtgt= 0.0)", 200, -50., 50.));
        name_tmp = std::to_string(dama_histID + i * 6 + 4);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Yfp (Thtgt= 0.5)", 200, -50., 50.));
        name_tmp = std::to_string(dama_histID + i * 6 + 5);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Yfp (Thtgt= 1.0)", 200, -50., 50.));
      }
    }
  } else if (_par_sorter.switch_plot_dama == 2) {
    for (i = 0; i < MAX_XGATE_SIEVESLIT; ++i) {
      if (_par_sorter.xgate_min_dama[i] != 99999.0 &&
          _par_sorter.xgate_max_dama[i] != 99999.0) {
        name_tmp = std::to_string(dama_histID + i * 6);

        m_hist_dama_2D.push_back(new TH2F(name_tmp.c_str(), "Thtgt vs Phtgt",
                                          128, -3.5, 3.5, 128, -3.5, 3.5));
        name_tmp = std::to_string(dama_histID + i * 6 + 1);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Phtgt (Thtgt=-1.0)", 200, -60., 60.));
        name_tmp = std::to_string(dama_histID + i * 6 + 2);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Phtgt (Thtgt=-0.5)", 200, -60., 60.));
        name_tmp = std::to_string(dama_histID + i * 6 + 3);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Phtgt (Thtgt= 0.0)", 200, -60., 60.));
        name_tmp = std::to_string(dama_histID + i * 6 + 4);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Phtgt (Thtgt= 0.5)", 200, -60., 60.));
        name_tmp = std::to_string(dama_histID + i * 6 + 5);
        m_hist_dama_1D.push_back(
            new TH1F(name_tmp.c_str(), "Phtgt (Thtgt= 1.0)", 200, -60., 60.));
      }
    }
  }
}

void Sorter_root::open_hist_fera() {
  std::cout << "Info : Open Hist Fera!" << std::endl;

  std::string name_tmp;
  name_tmp = std::to_string(fera_histID);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 1/0", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 1);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 1/1", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 2);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 1/2", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 3);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 1/3", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 4);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 1/4", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 5);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 1/5", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 6);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 1/12", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 10);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 2/0", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 11);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 2/1", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 12);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 2/2", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 13);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 2/3", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 14);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 2/4", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 15);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 2/5", 2048, 0., 2048.));
  name_tmp = std::to_string(fera_histID + 16);
  m_hist_fera_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA Station/Channel 2/12", 2048, 0., 2048.));
}

void Sorter_root::open_hist_feret() {
  std::cout << "Info : Open Hist Feret!" << std::endl;
  std::string name_tmp;

  name_tmp = std::to_string(feret_histID);

  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/0 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 1);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/1 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 2);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/2 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 3);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/3 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 4);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/4 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 5);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/5 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 6);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/6 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 7);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/7 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 8);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/8 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 9);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/9 ", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 10);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/10", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 11);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/11", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 12);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/12", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 13);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/13", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 14);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/14", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 15);
  m_hist_feret_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET output vs/ch 81/15", 1024, 0., 1024.));
  name_tmp = std::to_string(feret_histID + 20);
  m_hist_feret_1D.push_back(new TH1F(
      name_tmp.c_str(), "FERET Virtual Station Number (must be 0x81=129?)", 256,
      -0.5, 255.5));
}

void Sorter_root::open_hist_scaler() {
  std::cout << "Info : Open Hist Scaler!" << std::endl;

  std::string name_tmp;

  name_tmp = std::to_string(scaler_histID);
  m_hist_scaler_1D.push_back(
      new TH1F(name_tmp.c_str(), "Scaler 0", 16, -0.5, 15.5));
  name_tmp = std::to_string(scaler_histID + 1);
  m_hist_scaler_1D.push_back(
      new TH1F(name_tmp.c_str(), "Scaler 1", 16, -0.5, 15.5));
  name_tmp = std::to_string(scaler_histID + 2);
  m_hist_scaler_1D.push_back(
      new TH1F(name_tmp.c_str(), "Scaler 2", 16, -0.5, 15.5));
  name_tmp = std::to_string(scaler_histID + 3);
  m_hist_scaler_1D.push_back(
      new TH1F(name_tmp.c_str(), "Scaler 3", 16, -0.5, 15.5));
  name_tmp = std::to_string(scaler_histID + 4);
  m_hist_scaler_1D.push_back(
      new TH1F(name_tmp.c_str(), "Scaler total", 16, -0.5, 15.5));
}

void Sorter_root::open_hist_scintillator_tof() {
  std::cout << "Info : Open Hist SCINTI-TOF!" << std::endl;
  std::string name_tmp;

  name_tmp = std::to_string(scinti_histID);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 1 Left", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 1);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 1 Right", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 2);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 2 Left", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 3);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 2 Right", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 4);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 1 L-R average", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 5);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 2 L-R average", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 6);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 1 L-R average gated FERA 1 L-R average",
               1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 7);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERA 2 L-R average gated FERA 2 L-R average",
               1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 8);
  m_hist_scintillator_tof_1D.push_back(new TH1F(
      name_tmp.c_str(), "FERA 1 L-R average (EventID=0)", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 9);
  m_hist_scintillator_tof_1D.push_back(new TH1F(
      name_tmp.c_str(), "FERA 2 L-R average (EventID=0)", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 10);
  m_hist_scintillator_tof_2D.push_back(new TH2F(
      name_tmp.c_str(), "FERA 1 vs FERA 2", 128, 0., 1024., 128, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 11);
  m_hist_scintillator_tof_2D.push_back(
      new TH2F(name_tmp.c_str(), "FERA 1 vs FERA 2 (EventID=0)", 128, 0., 1024.,
               128, 0., 1024.));

  name_tmp = std::to_string(scinti_histID + 16);
  m_hist_scintillator_tof_2D.push_back(
      new TH2F(name_tmp.c_str(), "FERET 1L vs 1R", 64, 0., 256., 64, 0., 256.));
  name_tmp = std::to_string(scinti_histID + 17);
  m_hist_scintillator_tof_2D.push_back(
      new TH2F(name_tmp.c_str(), "FERET 2L vs 2R", 64, 0., 256., 64, 0., 256.));

  name_tmp = std::to_string(scinti_histID + 20);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "FERET 4 TOF", 1024, 0., 1024.));
  name_tmp = std::to_string(scinti_histID + 21);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "cor-TOF", 300, 0., 300.));
  name_tmp = std::to_string(scinti_histID + 22);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "cor-TOF gated cor-tof", 300, 0., 300.));
  name_tmp = std::to_string(scinti_histID + 23);
  m_hist_scintillator_tof_1D.push_back(
      new TH1F(name_tmp.c_str(), "cor-TOF (EventID=0)", 300, 0., 300.));
}

void Sorter_root::open_hist_system() {

  std::cout << "Info : Open Hist SYSTEM!" << std::endl;
  std::string name_tmp;

  name_tmp = std::to_string(sys_histID);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(),
               "Field structure: IR1+1,FERA+2,FERET+4,IR2+8,3377+16,PCOS+32",
               64, -0.5, 63.5));
  name_tmp = std::to_string(sys_histID + 1);
  m_hist_system_1D.push_back(new TH1F(
      name_tmp.c_str(), "CI Range "
                        "1-15:20mA,6mA,2mA,600uA,200uA,60uA,20uA,6uA,2uA,"
                        "600nA,200nA,60nA,20nA,6nA,2nA",
      16, -0.5, 15.5));
  name_tmp = std::to_string(sys_histID + 10);
  m_hist_system_1D.push_back(new TH1F(
      name_tmp.c_str(), "Event-ID (bad X1/+1 U1/+2 X2/+4 U2/+8 cortof/+16 "
                        "NoWire/32 P1/-1 P2/-2 Xf/-4)",
      51, -10.5, 40.5));
  name_tmp = std::to_string(sys_histID + 11);
  m_hist_system_2D.push_back(new TH2F(name_tmp.c_str(), "TOF       vs Event-ID",
                                      128, 0., 256., 31, -10.5, 20.5));
  name_tmp = std::to_string(sys_histID + 12);
  m_hist_system_2D.push_back(new TH2F(name_tmp.c_str(), "Scinti 1  vs Event-ID",
                                      128, 0., 1024., 31, -10.5, 20.5));
  name_tmp = std::to_string(sys_histID + 13);
  m_hist_system_2D.push_back(new TH2F(name_tmp.c_str(), "Scinti 2  vs Event-ID",
                                      128, 0., 1024., 31, -10.5, 20.5));
  name_tmp = std::to_string(sys_histID + 14);
  m_hist_system_2D.push_back(new TH2F(name_tmp.c_str(), "Xferet vs Event-ID",
                                      64, -600., 600., 31, -10.5, 20.5));

  name_tmp = std::to_string(sys_histID + 17);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength-Estimated vs DriftLength X1 (mm vs mm)",
      100, -1., 1., 100, -6., 6.));
  name_tmp = std::to_string(sys_histID + 18);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength-Estimated vs DriftLength U1 (mm vs mm)",
      100, -1., 1., 100, -6., 6.));
  name_tmp = std::to_string(sys_histID + 19);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength-Estimated vs DriftLength X2 (mm vs mm)",
      100, -1., 1., 100, -6., 6.));
  name_tmp = std::to_string(sys_histID + 20);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength-Estimated vs DriftLength U2 (mm vs mm)",
      100, -1., 1., 100, -6., 6.));
  name_tmp = std::to_string(sys_histID + 21);
  m_hist_system_prof.push_back(new TProfile(
      name_tmp.c_str(), "DriftLength X1 (mm) vs 1-Estimated/DriftLength", 200,
      -10., 10., -1.0, 1.0, " "));
  name_tmp = std::to_string(sys_histID + 22);
  m_hist_system_prof.push_back(new TProfile(
      name_tmp.c_str(), "DriftLength U1 (mm) vs 1-Estimated/DriftLength", 200,
      -10., 10., -0.5, 1.0, " "));
  name_tmp = std::to_string(sys_histID + 23);
  m_hist_system_prof.push_back(new TProfile(
      name_tmp.c_str(), "DriftLength X2 (mm) vs 1-Estimated/DriftLength", 200,
      -10., 10., -0.5, 1.0, " "));
  name_tmp = std::to_string(sys_histID + 24);
  m_hist_system_prof.push_back(new TProfile(
      name_tmp.c_str(), "DriftLength U2 (mm) vs 1-Estimated/DriftLength", 200,
      -10., 10., -0.5, 1.0, " "));
  name_tmp = std::to_string(sys_histID + 25);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength X1 (mm) vs 1-Estimated/DriftLength", 200,
      -5., 5., 100, -0.2, 1.2));
  name_tmp = std::to_string(sys_histID + 26);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength U1 (mm) vs 1-Estimated/DriftLength", 200,
      -5., 5., 100, -0.2, 1.2));
  name_tmp = std::to_string(sys_histID + 27);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength X2 (mm) vs 1-Estimated/DriftLength", 200,
      -5., 5., 100, -0.2, 1.2));
  name_tmp = std::to_string(sys_histID + 28);
  m_hist_system_2D.push_back(new TH2F(
      name_tmp.c_str(), "DriftLength U2 (mm) vs 1-Estimated/DriftLength", 200,
      -5., 5., 100, -0.2, 1.2));

  name_tmp = std::to_string(sys_histID + 29);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "Cluster X1", 11, -0.5, 10.5));
  name_tmp = std::to_string(sys_histID + 30);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "Cluster U1", 11, -0.5, 10.5));
  name_tmp = std::to_string(sys_histID + 31);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "Cluster X2", 11, -0.5, 10.5));
  name_tmp = std::to_string(sys_histID + 32);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "Cluster U2", 11, -0.5, 10.5));
  name_tmp = std::to_string(sys_histID + 33);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "DriftLength-Estimated X1 (mm, only DL>2)",
               100, -1., 1.));
  name_tmp = std::to_string(sys_histID + 34);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "DriftLength-Estimated U1 (mm, only DL>2)",
               100, -1., 1.));
  name_tmp = std::to_string(sys_histID + 35);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "DriftLength-Estimated X2 (mm, only DL>2)",
               100, -1., 1.));
  name_tmp = std::to_string(sys_histID + 36);
  m_hist_system_1D.push_back(
      new TH1F(name_tmp.c_str(), "DriftLength-Estimated U2 (mm, only DL>2)",
               100, -1., 1.));
}

void Sorter_root::open_hist_user(struct parameters &_par_sorter) {
  std::cout << "Info : Open Hist USER!" << std::endl;
  std::string name_tmp;

  name_tmp = std::to_string(user_histID);

  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Chi square X1", 128, 0., 15.));
  name_tmp = std::to_string(user_histID + 1);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Chi square U1", 128, 0., 15.));
  name_tmp = std::to_string(user_histID + 2);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Chi square X2", 128, 0., 15.));
  name_tmp = std::to_string(user_histID + 3);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Chi square U2", 128, 0., 15.));

  name_tmp = std::to_string(user_histID + 10);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "X1    (mm)", 1200, -600., 600.));
  name_tmp = std::to_string(user_histID + 11);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Th1   (deg.)", 256, -20., 20.));
  name_tmp = std::to_string(user_histID + 12);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "U1    (mm)", 1000, -500., 500.));
  name_tmp = std::to_string(user_histID + 13);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Ps1   (deg.)", 256, -20., 20.));
  name_tmp = std::to_string(user_histID + 14);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Y1    (mm)", 200, -100., 100.));
  name_tmp = std::to_string(user_histID + 130);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "X1  vs Y1 (mm)", 1200,
                                    -600., 600., 200, -100., 100.));

  name_tmp = std::to_string(user_histID + 15);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "X2    (mm)", 1200, -600., 600.));
  name_tmp = std::to_string(user_histID + 16);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Th2   (deg.)", 256, -20., 20.));
  name_tmp = std::to_string(user_histID + 17);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "U2    (mm)", 1000, -500., 500.));
  name_tmp = std::to_string(user_histID + 18);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Ps2   (deg.)", 256, -20., 20.));
  name_tmp = std::to_string(user_histID + 19);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Y2    (mm)", 200, -100., 100.));
  name_tmp = std::to_string(user_histID + 131);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "X2  vs Y2 (mm)", 1200,
                                    -600., 600., 200, -100., 100.));

  name_tmp = std::to_string(user_histID + 20);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xfp   (mm)", 6000, -600., 600.));
  name_tmp = std::to_string(user_histID + 21);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Thfp  (deg.)", 256, -10., 10.));
  name_tmp = std::to_string(user_histID + 22);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Yfp   (mm)", 200, -100., 100.));
  name_tmp = std::to_string(user_histID + 23);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Phfp  (deg.)", 256, -10., 10.));

  name_tmp = std::to_string(user_histID + 24);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Thtgt (deg.)", 256, -5., 5.));
  name_tmp = std::to_string(user_histID + 25);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Phtgt (deg.)", 256, -5., 5.));

  name_tmp = std::to_string(user_histID + 26);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Thfp - Th1 (deg.)", 64, -5., 5.));
  name_tmp = std::to_string(user_histID + 27);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Thfp - Th2 (deg.)", 64, -5., 5.));

  name_tmp = std::to_string(user_histID + 28);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Th1  - Th2 (deg.)", 64, -5., 5.));

  name_tmp = std::to_string(user_histID + 29);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Psfp - Ps1 (deg.)", 64, -5., 5.));
  name_tmp = std::to_string(user_histID + 30);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Psfp - Ps2 (deg.)", 64, -5., 5.));
  name_tmp = std::to_string(user_histID + 31);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Ps1  - Ps2 (deg.)", 64, -5., 5.));
  name_tmp = std::to_string(user_histID + 32);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp  vs Chi square X1",
                                    1200, -600., 600., 128, 0., 15.));
  name_tmp = std::to_string(user_histID + 33);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp  vs Chi square U1",
                                    1200, -600., 600., 128, 0., 15.));
  name_tmp = std::to_string(user_histID + 34);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp  vs Chi square X2",
                                    1200, -600., 600., 128, 0., 15.));
  name_tmp = std::to_string(user_histID + 35);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp  vs Chi square U2",
                                    1200, -600., 600., 128, 0., 15.));

  name_tmp = std::to_string(user_histID + 232);
  m_hist_user_prof.push_back(new TProfile(name_tmp.c_str(), "FERET L-R vs X1",
                                          64, -100., 100., -600., 600., " "));

  name_tmp = std::to_string(user_histID + 233);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "X1 vs Xferet", 64, -600.,
                                    600., 64, -600., 600.));

  name_tmp = std::to_string(user_histID + 36);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xferet vs paddle 1L", 64,
                                    -600., 600., 128, 0., 1024.));
  name_tmp = std::to_string(user_histID + 37);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xferet vs paddle 1R", 64,
                                    -600., 600., 128, 0., 1024.));
  name_tmp = std::to_string(user_histID + 38);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xferet vs paddle 1", 64,
                                    -600., 600., 128, 0., 1024.));

  name_tmp = std::to_string(user_histID + 39);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xferet vs paddle 2L", 64,
                                    -600., 600., 128, 0., 1024.));
  name_tmp = std::to_string(user_histID + 40);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xferet vs paddle 2R", 64,
                                    -600., 600., 128, 0., 1024.));
  name_tmp = std::to_string(user_histID + 41);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xferet vs paddle 2", 64,
                                    -600., 600., 128, 0., 1024.));

  name_tmp = std::to_string(user_histID + 42);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp   vs TOF", 128,
                                    -600., 600., 128, 0., 300.));
  name_tmp = std::to_string(user_histID + 43);
  m_hist_user_2D.push_back(
      new TH2F(name_tmp.c_str(), "Thtgt vs TOF", 128, -2., 2., 128, 0., 300.));
  name_tmp = std::to_string(user_histID + 44);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp   vs cor-TOF", 128,
                                    -600., 600., 128, 0., 300.));
  name_tmp = std::to_string(user_histID + 45);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Thtgt vs cor-TOF", 128,
                                    -2., 2., 128, 0., 300.));
  name_tmp = std::to_string(user_histID + 46);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xfp gated", 6000, -600., 600.));

  name_tmp = std::to_string(user_histID + 47);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Scattering angle (deg)", 64, 0., 5.));

  name_tmp = std::to_string(user_histID + 48);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Thtgt gated (-1.5<Ph<1.5)", 256, -5., 5.));
  name_tmp = std::to_string(user_histID + 49);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Phtgt gated (-0.5<Th<0.5)", 256, -5., 5.));
  name_tmp = std::to_string(user_histID + 50);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet (mm)", 64, -600., 600.));

  name_tmp = std::to_string(user_histID + 60); // double name
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "X for Et calib. gated", 4000, -600., 600.));
  name_tmp = std::to_string(user_histID + 70); // double name
  m_hist_user_1D.push_back(new TH1F(
      name_tmp.c_str(), "Outgoing momentum (MeV/c)", 1000, 1500., 1600.));
  name_tmp = std::to_string(user_histID + 80);

  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Outgoing energy (MeV)", 1000, 380., 425.));
  name_tmp = std::to_string(user_histID + 81);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Ex gated (MeV)", 7200, -1., 35.));

  if (_par_sorter.ThGR == 0.0) {
    name_tmp = std::to_string(user_histID + 51);
    m_hist_user_1D.push_back(new TH1F(
        name_tmp.c_str(), "Xfp 0.0-0.5 (deg) gated", 9000, -600., 600.));
    name_tmp = std::to_string(user_histID + 52);
    m_hist_user_1D.push_back(new TH1F(
        name_tmp.c_str(), "Xfp 0.5-0.8 (deg) gated", 6000, -600., 600.));
    name_tmp = std::to_string(user_histID + 53);
    m_hist_user_1D.push_back(new TH1F(name_tmp.c_str(),
                                      "Xfp 0.8-1.2 (deg) (-0.8<th<0.8) gated",
                                      6000, -600., 600.));
    name_tmp = std::to_string(user_histID + 54);
    m_hist_user_1D.push_back(new TH1F(name_tmp.c_str(),
                                      "Xfp 1.2-1.6 (deg) (-0.8<th<0.8) gated",
                                      6000, -600., 600.));
    name_tmp = std::to_string(user_histID + 55);
    m_hist_user_1D.push_back(new TH1F(name_tmp.c_str(),
                                      "Xfp 1.6-2.0 (deg) (-0.8<th<0.8) gated",
                                      6000, -600., 600.));

    name_tmp = std::to_string(user_histID + 71); // double
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 0.0-0.5 (deg) gated", 7200, -1., 35.));
    name_tmp = std::to_string(user_histID + 72); // double
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 0.5-0.8 (deg) gated", 7200, -1., 35.));
    name_tmp = std::to_string(user_histID + 73); // double
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 0.8-1.2 (deg) gated", 7200, -1., 35.));
    name_tmp = std::to_string(user_histID + 74); // double
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 1.2-1.6 (deg) gated", 7200, -1., 35.));
    name_tmp = std::to_string(user_histID + 75); // double
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 1.6-2.0 (deg) gated", 7200, -1., 35.));

  } else if (_par_sorter.ThGR == 2.5) {

    name_tmp = std::to_string(user_histID + 56);
    m_hist_user_1D.push_back(new TH1F(name_tmp.c_str(),
                                      "Xfp 2.0-2.5 (deg) (-0.8<th<0.8) gated",
                                      6000, -600., 600.));
    name_tmp = std::to_string(user_histID + 57);
    m_hist_user_1D.push_back(new TH1F(name_tmp.c_str(),
                                      "Xfp 2.5-3.0 (deg) (-0.8<th<0.8) gated",
                                      6000, -600., 600.));
    name_tmp = std::to_string(user_histID + 58);
    m_hist_user_1D.push_back(new TH1F(name_tmp.c_str(),
                                      "Xfp 3.0-3.5 (deg) (-0.8<th<0.8) gated",
                                      6000, -600., 600.));

    name_tmp = std::to_string(user_histID + 76);
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 2.0-2.5 (deg) gated", 7200, -1., 35.));
    name_tmp = std::to_string(user_histID + 77);
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 2.5-3.0 (deg) gated", 7200, -1., 35.));
    name_tmp = std::to_string(user_histID + 78);
    m_hist_user_1D.push_back(
        new TH1F(name_tmp.c_str(), "Ex 3.0-3.5 (deg) gated", 7200, -1., 35.));
  }

  name_tmp = std::to_string(user_histID + 90);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "X1 gated", 4800, -600., 600.));
  name_tmp = std::to_string(user_histID + 91);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "U1 gated", 4800, -600., 600.));
  name_tmp = std::to_string(user_histID + 92);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "X2 gated", 4800, -600., 600.));
  name_tmp = std::to_string(user_histID + 93);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "U2 gated", 4800, -600., 600.));

  name_tmp = std::to_string(user_histID + 100);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "X1  vs Th1", 100, -600.,
                                    600., 64, -10., 10.));
  name_tmp = std::to_string(user_histID + 101);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "U1  vs Ps1", 100, -500.,
                                    500., 64, -10., 10.));
  name_tmp = std::to_string(user_histID + 102);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "X2  vs Th2", 100, -600.,
                                    600., 64, -10., 10.));
  name_tmp = std::to_string(user_histID + 103);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "U2  vs Ps2", 100, -500.,
                                    500., 64, -10., 10.));

  //  normal

  name_tmp = std::to_string(user_histID + 104);

  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "X1 vs Thfp", 300, -600.,
                                    600., 200, -5.,
                                    5.)); // high reso
  name_tmp = std::to_string(user_histID + 105);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "X2 vs Thfp", 300, -600.,
                                    600., 200, -5.,
                                    5.)); // high reso

  name_tmp = std::to_string(user_histID + 106);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs Thfp", 300, -600.,
                                    600., 200, -5.,
                                    5.)); // high reso
  name_tmp = std::to_string(user_histID + 107);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs Thfp Y gated",
                                    300, -600., 600., 200, -5.,
                                    5.)); // high reso
  name_tmp = std::to_string(user_histID + 109);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs Thtgt", 9000,
                                    -600., 600., 100, -2., 2.));
  name_tmp = std::to_string(user_histID + 110);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs Thtgt Y gated",
                                    300, -600., 600., 100, -1.5, 1.5));

  name_tmp = std::to_string(user_histID + 115);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs EventID", 100,
                                    -600., 600., 45, -5.5, 40.5));
  name_tmp = std::to_string(user_histID + 120);
  m_hist_user_2D.push_back(
      new TH2F(name_tmp.c_str(), "Thtgt vs Phtgt", 100, -3., 3., 100, -3., 3.));
  name_tmp = std::to_string(user_histID + 132);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs Yfp", 128, -600.,
                                    600., 64, -60., 60.)); // normal
  name_tmp = std::to_string(user_histID + 133);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs Phtgt", 9000,
                                    -600., 600., 100, -4., 4.));
  name_tmp = std::to_string(user_histID + 134);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Xfp vs Yfp gated ?", 256,
                                    -3., 3., 256, -3., 3.));
  name_tmp = std::to_string(user_histID + 135);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "Thtgt vs Phtgt gated",
                                    256, -3., 3., 256, -3., 3.));

  name_tmp = std::to_string(user_histID + 140);
  m_hist_user_2D.push_back(new TH2F(name_tmp.c_str(), "U1  vs Psfp", 100, -500.,
                                    500., 64, -10., 10.));

  name_tmp = std::to_string(user_histID + 150);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet X1 failed", 64, -600., 600.));
  name_tmp = std::to_string(user_histID + 151);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet U1 failed", 64, -600., 600.));
  name_tmp = std::to_string(user_histID + 152);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet X2 failed", 64, -600., 600.));
  name_tmp = std::to_string(user_histID + 153);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet U2 failed", 64, -600., 600.));

  // --- test for efficiency check
  name_tmp = std::to_string(user_histID + 154);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "X1 failed", 1200, -600., 600.));
  name_tmp = std::to_string(user_histID + 155);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "U1 failed", 1000, -500., 500.));
  name_tmp = std::to_string(user_histID + 156);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "X2 failed", 1200, -600., 600.));
  name_tmp = std::to_string(user_histID + 157);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "U2 failed", 1000, -500., 500.));

  // ---
  name_tmp = std::to_string(user_histID + 158);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet X1 failed", 12, -600., 600.));
  name_tmp = std::to_string(user_histID + 159);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet U1 failed", 12, -600., 600.));
  name_tmp = std::to_string(user_histID + 160);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet X2 failed", 12, -600., 600.));
  name_tmp = std::to_string(user_histID + 161);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet U2 failed", 12, -600., 600.));
  name_tmp = std::to_string(user_histID + 162);
  m_hist_user_1D.push_back(
      new TH1F(name_tmp.c_str(), "Xferet All good", 12, -600., 600.));
  // ---
}

void Sorter_root::open_hist_wire() {
  std::cout << "Info : Open Hist Wire!" << std::endl;
  std::string name_tmp;

  name_tmp = std::to_string(v3377_histID);

  m_hist_v3377_1D.push_back(new TH1F(
      name_tmp.c_str(), "3377 output X1 (corrected)", 1024, 0., 1024.));
  name_tmp = std::to_string(v3377_histID + 1);
  m_hist_v3377_1D.push_back(new TH1F(
      name_tmp.c_str(), "3377 output U1 (corrected)", 1024, 0., 1024.));
  name_tmp = std::to_string(v3377_histID + 2);
  m_hist_v3377_1D.push_back(new TH1F(
      name_tmp.c_str(), "3377 output X2 (corrected)", 1024, 0., 1024.));
  name_tmp = std::to_string(v3377_histID + 3);
  m_hist_v3377_1D.push_back(new TH1F(
      name_tmp.c_str(), "3377 output U2 (corrected)", 1024, 0., 1024.));
  name_tmp = std::to_string(v3377_histID + 4);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift length X1 (mm)", 56, -2., 12.));
  name_tmp = std::to_string(v3377_histID + 5);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift length U1 (mm)", 56, -2., 12.));
  name_tmp = std::to_string(v3377_histID + 6);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift length X2 (mm)", 56, -2., 12.));
  name_tmp = std::to_string(v3377_histID + 7);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift length U2 (mm)", 56, -2., 12.));
  name_tmp = std::to_string(v3377_histID + 8);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift table*1000 X1", 1024, 0., 1024.));
  name_tmp = std::to_string(v3377_histID + 9);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift table*1000 U1", 1024, 0., 1024.));
  name_tmp = std::to_string(v3377_histID + 10);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift table*1000 X2", 1024, 0., 1024.));
  name_tmp = std::to_string(v3377_histID + 11);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(), "Drift table*1000 U2", 1024, 0., 1024.));

  name_tmp = std::to_string(v3377_histID + 12);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "3377 output vs Wire X1",
                                     400, 0., 400., 192, -0.5, 191.5));
  name_tmp = std::to_string(v3377_histID + 13);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "3377 output vs Wire U1",
                                     400, 0., 400., 208, -0.5, 207.5));
  name_tmp = std::to_string(v3377_histID + 14);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "3377 output vs Wire X2",
                                     400, 0., 400., 192, -0.5, 191.5));
  name_tmp = std::to_string(v3377_histID + 15);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "3377 output vs Wire U2",
                                     400, 0., 400., 208, -0.5, 207.5));
  name_tmp = std::to_string(v3377_histID + 16);
  m_hist_v3377_2D.push_back(
      new TH2F(name_tmp.c_str(), "3377 output vs Wire X1 corrected", 400, 0.,
               400., 192, -0.5, 191.5)); // used to be +13
  name_tmp = std::to_string(v3377_histID + 17);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(),
                                     "3377 output vs Wire U1 corrected", 400,
                                     0., 400., 208, -0.5, 207.5)); // +15
  name_tmp = std::to_string(v3377_histID + 18);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(),
                                     "3377 output vs Wire X2 corrected", 400,
                                     0., 400., 192, -0.5, 191.5)); // +17
  name_tmp = std::to_string(v3377_histID + 19);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(),
                                     "3377 output vs Wire U2 corrected", 400,
                                     0., 400., 208, -0.5, 207.5)); // +19
                                                                   //  ----------------------------------------------------------------------------------------

  name_tmp = std::to_string(v3377_histID + 20);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "TDC i and i+1 X1", 300,
                                     50., 350., 301, 50., 350.));
  name_tmp = std::to_string(v3377_histID + 21);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "TDC i and i+1 U1", 300,
                                     50., 350., 301, 50., 350.));
  name_tmp = std::to_string(v3377_histID + 22);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "TDC i and i+1 X2", 300,
                                     50., 350., 301, 50., 350.));
  name_tmp = std::to_string(v3377_histID + 23);
  m_hist_v3377_2D.push_back(new TH2F(name_tmp.c_str(), "TDC i and i+1 U2", 300,
                                     50., 350., 301, 50., 350.));
  name_tmp = std::to_string(v3377_histID + 24);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(),
               "Drift length accuracy X1 : (1-2)-(2ndlast-last)", 64, -2., 2.));
  name_tmp = std::to_string(v3377_histID + 25);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(),
               "Drift length accuracy U1 : (1-2)-(2ndlast-last)", 64, -2., 2.));
  name_tmp = std::to_string(v3377_histID + 26);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(),
               "Drift length accuracy X2 : (1-2)-(2ndlast-last)", 64, -2., 2.));
  name_tmp = std::to_string(v3377_histID + 27);
  m_hist_v3377_1D.push_back(
      new TH1F(name_tmp.c_str(),
               "Drift length accuracy U2 : (1-2)-(2ndlast-last)", 64, -2., 2.));

  name_tmp = std::to_string(wire_histID);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "MWPC X1 All", 200, 0., 200.));
  name_tmp = std::to_string(wire_histID + 1);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "MWPC U1 All", 220, 0., 220.));
  name_tmp = std::to_string(wire_histID + 2);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "MWPC X2 All", 200, 0., 200.));
  name_tmp = std::to_string(wire_histID + 3);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "MWPC U2 All", 220, 0., 220.));
  name_tmp = std::to_string(wire_histID + 4);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Rubbish wire X1", 200, 0., 200.));
  name_tmp = std::to_string(wire_histID + 5);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Rubbish wire U1", 200, 0., 200.));
  name_tmp = std::to_string(wire_histID + 6);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Rubbish wire X2", 200, 0., 200.));
  name_tmp = std::to_string(wire_histID + 7);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Rubbish wire U2", 200, 0., 200.));

  name_tmp = std::to_string(wire_histID + 8);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire X1", 25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 9);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire X1 (paddle & tof gated)",
               25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 10);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire U1", 25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 11);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire U1 (paddle & tof gated)",
               25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 12);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire X2", 25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 13);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire X2 (paddle & tof gated)",
               25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 14);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire U2", 25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 15);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "Number of hit wire U2 (paddle & tof gated)",
               25, -0.5, 24.5));
  name_tmp = std::to_string(wire_histID + 16);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "RayID X1", 17, -0.5, 16.5));
  name_tmp = std::to_string(wire_histID + 17);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "RayID U1", 17, -0.5, 16.5));
  name_tmp = std::to_string(wire_histID + 18);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "RayID X2", 17, -0.5, 16.5));
  name_tmp = std::to_string(wire_histID + 19);
  m_hist_wire_1D.push_back(
      new TH1F(name_tmp.c_str(), "RayID U2", 17, -0.5, 16.5));
}

void Sorter_root::write_root(struct parameters &_par_sorter, TTree *tree) {

  TFile *outfile = new TFile(_par_sorter.rootfilename.c_str(), "recreate");
  TList *hList = new TList();

  tree->Write();

  for (auto &h : m_hist_conf_1D) {
    hList->Add(h);
  }

  for (auto &h : m_hist_conf_2D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_dama_1D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_dama_2D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_fera_1D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_feret_1D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_scaler_1D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_scintillator_tof_1D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_scintillator_tof_2D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_system_1D) {
    hList->Add(h);
  }

  for (auto &h : m_hist_system_2D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_system_prof) {
    hList->Add(h);
  }
  for (auto &h : m_hist_user_1D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_user_2D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_user_prof) {
    hList->Add(h);
  }
  for (auto &h : m_hist_v3377_1D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_v3377_2D) {
    hList->Add(h);
  }
  for (auto &h : m_hist_wire_1D) {
    hList->Add(h);
  }

  hList->Write();

  outfile->Close();

  //  HRPUT(0,_hbfile,"N");
}
