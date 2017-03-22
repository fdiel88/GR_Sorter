
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "sorter_config.h"
#include "sorter_const.h"
#include "sorter_histpar.h"
#include "sorter_par.h"
#include "sorter_scaler.h"

int Sorter_config::init_parameters(struct parameters &_par_sorter) {
  unsigned i = 0;

  _par_sorter.globalareaname = "GLAR";
  _par_sorter.switch_online = FALSE;
  _par_sorter.online_host = "";
  _par_sorter.switch_byteswap =
      999; // <- default value is nor TRUE neither FALSE

  _par_sorter.start_block = 0;
  _par_sorter.stop_block = 0;
  _par_sorter.scinti_1_min = 0.0;
  _par_sorter.scinti_1_max = 0.0;
  _par_sorter.scinti_2_min = 0.0;
  _par_sorter.scinti_2_max = 0.0;
  _par_sorter.cortof_1_min = 0.0;
  _par_sorter.cortof_1_max = 0.0;
  _par_sorter.cortof_2_min = 0.0;
  _par_sorter.cortof_2_max = 0.0;

  for (i = 0; i < 12; ++i) {
    _par_sorter.tdcoffset16_x1[i] = 0;
    _par_sorter.tdcoffset16_x2[i] = 0;
  }
  for (i = 0; i < 13; ++i) {
    _par_sorter.tdcoffset16_u1[i] = 0;
    _par_sorter.tdcoffset16_u2[i] = 0;
  }
  for (i = 0; i < 192; ++i) {
    _par_sorter.tdcoffset_x1[i] = 0;
    _par_sorter.tdcoffset_x2[i] = 0;
  }
  for (i = 0; i < 208; ++i) {
    _par_sorter.tdcoffset_x1[i] = 0;
    _par_sorter.tdcoffset_x2[i] = 0;
  }

  _par_sorter.chisq_x1_max = 0.0;
  _par_sorter.chisq_u1_max = 0.0;
  _par_sorter.chisq_x2_max = 0.0;
  _par_sorter.chisq_u2_max = 0.0;
  _par_sorter.clustersize_x1_min = 0;
  _par_sorter.clustersize_x1_max = 0;
  _par_sorter.clustersize_u1_min = 0;
  _par_sorter.clustersize_u1_max = 0;
  _par_sorter.clustersize_x2_min = 0;
  _par_sorter.clustersize_x2_max = 0;
  _par_sorter.clustersize_u2_min = 0;
  _par_sorter.clustersize_u2_max = 0;
  _par_sorter.tdc_x1_min = 0;
  _par_sorter.tdc_x1_max = 1024;
  _par_sorter.tdc_u1_min = 0;
  _par_sorter.tdc_u1_max = 1024;
  _par_sorter.tdc_x2_min = 0;
  _par_sorter.tdc_x2_max = 1024;
  _par_sorter.tdc_u2_min = 0;
  _par_sorter.tdc_u2_max = 1024;

  for (i = 0; i < 3; ++i) {
    _par_sorter.drifttable1_x1_par[i] = 0;
    _par_sorter.drifttable1_u1_par[i] = 0;
    _par_sorter.drifttable1_x2_par[i] = 0;
    _par_sorter.drifttable1_u2_par[i] = 0;
  }
  for (i = 0; i < 4; ++i) {
    _par_sorter.drifttable2_x1_par[i] = 0;
    _par_sorter.drifttable2_u1_par[i] = 0;
    _par_sorter.drifttable2_x2_par[i] = 0;
    _par_sorter.drifttable2_u2_par[i] = 0;
  }
  for (i = 0; i < MAX_THTGT_PAR; ++i) {
    _par_sorter.thtgt_par_xorder[i] = 0;
    _par_sorter.thtgt_par_thorder[i] = 0;
    _par_sorter.thtgt_par[i] = 0.0;
  }
  _par_sorter.thtgt_offset = 0.0;
  _par_sorter.phtgt_offset = 0.0;
  _par_sorter.xfp_offset = 0.0;
  for (i = 0; i < MAX_PHTGT_PAR; ++i) {
    _par_sorter.phtgt_par_xorder[i] = 0;
    _par_sorter.phtgt_par_thorder[i] = 0;
    _par_sorter.phtgt_par_yorder[i] = 0;
    _par_sorter.phtgt_par[i] = 0.0;
  }
  /*for (i = 0; i < MAX_CORTOF_PAR; ++i) {
    
  }*/
  _par_sorter.cortof_par = {0.0};
  
  for (i = 0; i < MAX_FERETPOS_PAR; ++i) {
    _par_sorter.feretposi_par[i] = 0.0;
  }

  //_par_sorter.bldfilename = "";
  _par_sorter.hbfilename = "default.hb";
  _par_sorter.rootfilename = "default.root";
  _par_sorter.ntpfilename = "default_ntp.hb";
  _par_sorter.logfilename = "default.log";
  //_par_sorter.drifttablefilename = "";
  _par_sorter.scalerfilename = "default.sca";
  //_par_sorter.histconfigfilename = "";

  _par_sorter.ThGR = 0.0;
  _par_sorter.switch_feret = 1; // 1 or 2
  _par_sorter.switch_ntuple = FALSE;
  _par_sorter.switch_thtgt = FALSE;
  _par_sorter.switch_phtgt = FALSE;
  _par_sorter.switch_xcor_th = FALSE;
  _par_sorter.switch_xcor_ph = FALSE;
  _par_sorter.switch_global_xcor_th = FALSE;
  _par_sorter.switch_global_xcor_ph = FALSE;
  _par_sorter.switch_ex = FALSE;
  _par_sorter.switch_dl = 1;
  _par_sorter.switch_discard_shortdl = FALSE;
  _par_sorter.switch_pout = FALSE;
  _par_sorter.switch_recoil_cor = FALSE;
  //  _par_sorter.switch_tdc_optimize=FALSE;
  _par_sorter.switch_plot_fera = FALSE;
  _par_sorter.switch_plot_feret = FALSE;
  _par_sorter.switch_plot_3377 = FALSE;
  _par_sorter.switch_plot_system = FALSE;
  _par_sorter.switch_plot_vdc = FALSE;
  _par_sorter.switch_plot_scinti_tof = FALSE;
  _par_sorter.switch_plot_user =
      FALSE; //_par_sorter.switch_plot_user_gated=FALSE;
  _par_sorter.switch_plot_high_reso = FALSE;
  _par_sorter.switch_plot_dama = 0;
  _par_sorter.switch_histconfig = FALSE;
  for (i = 0; i < MAX_XGATE_SIEVESLIT; ++i) {
    _par_sorter.xgate_min_dama[i] = 99999.0;
    _par_sorter.xgate_max_dama[i] = 99999.0;
  }
  //_par_sorter.target = "";

  _par_sorter.ebeam = 0.0;
  _par_sorter.qvalue = 0.0;
  _par_sorter.mout = 0.0;
  for (i = 0; i < MAX_RECOIL_PAR; ++i) {
    _par_sorter.recoil_eorder[i] = 0;
    _par_sorter.recoil_ztorder[i] = 0;
    _par_sorter.recoil_par[i] = 0.0;
  }

  for (i = 0; i < MAX_POUT_PAR; ++i) {
    _par_sorter.pout_par[i] = 0.0;
    _par_sorter.pout_cor_par[i] = 0.0;
  }
  for (i = 0; i < MAX_EXCOR_PAR; ++i) {
    _par_sorter.ex_cor_par[i] = 0.0;
  }

  for (i = 0; i < MAX_GLOBAL_XCOR_TH_PAR; ++i) {
    _par_sorter.global_xcor_th_xorder[i] = 0;
    _par_sorter.global_xcor_th_thorder[i] = 0;
    _par_sorter.global_xcor_th_par[i] = 0.0;
  }
  for (i = 0; i < MAX_GLOBAL_XCOR_PH_PAR; ++i) {
    _par_sorter.global_xcor_ph_xorder[i] = 0;
    _par_sorter.global_xcor_ph_phorder[i] = 0;
    _par_sorter.global_xcor_ph_par[i] = 0.0;
  }
  for (i = 0; i < MAX_XCOR_TH_PAR; ++i) {
    _par_sorter.xcor_th_xorder[i] = 0;
    _par_sorter.xcor_th_thorder[i] = 0;
    _par_sorter.xcor_th_par[i] = 0.0;
  }
  for (i = 0; i < MAX_XCOR_PH_PAR; ++i) {
    _par_sorter.xcor_ph_xorder[i] = 0;
    _par_sorter.xcor_ph_phorder[i] = 0;
    _par_sorter.xcor_ph_par[i] = 0.0;
  }

  _par_sorter.num_discard_event = 0;
  _par_sorter.flg_discard_event = 0;

  return 0;
}

int Sorter_config::check_config(struct parameters &_par_sorter) {

  if ((_par_sorter.start_block && _par_sorter.stop_block) &&
      (_par_sorter.start_block < 0 || _par_sorter.stop_block < 0 ||
       _par_sorter.start_block >= _par_sorter.stop_block)) {
    std::cout << "ERROR : Invalid START_BLOCK and/or STOP_BLOCK ("
              << _par_sorter.start_block << "," << _par_sorter.stop_block << ")"
              << std::endl;

    exit(1);
  }

  // Drift table
  if (_par_sorter.switch_dl != 1 && _par_sorter.switch_dl != 2 &&
      _par_sorter.switch_dl != 3 && _par_sorter.switch_dl != 4) {
    std::cout << "ERROR : DRIFT_TABLE parameter must be 1, 2 or 3 (or 4). ("
              << _par_sorter.switch_dl << ", forced to be 1)" << std::endl;

    _par_sorter.switch_dl = 1;
  }

  if (_par_sorter.switch_dl == 1 && _par_sorter.drifttable1_x1_par[0] == 0.0) {
    std::cout << "ERROR : Parameter for Drift table mode 1, X1 not found. "
                 "(DRIFT_TABLE_1_X1_PAR)"
              << std::endl;
    exit(1);
  }
  if (_par_sorter.switch_dl == 1 && _par_sorter.drifttable1_u1_par[0] == 0.0) {
    std::cout << "ERROR : Parameter for Drift table mode 1, U1 not "
                 "found.(DRIFT_TABLE_1_U1_PAR)"
              << std::endl;
    exit(1);
  }
  if (_par_sorter.switch_dl == 1 && _par_sorter.drifttable1_x2_par[0] == 0.0) {
    std::cout << "ERROR : Parameter for Drift table mode 1, X2 not found. "
                 "(DRIFT_TABLE_1_X2_PAR)"
              << std::endl;
    exit(1);
  }
  if (_par_sorter.switch_dl == 1 && _par_sorter.drifttable1_u2_par[0] == 0.0) {
    std::cout << "ERROR : Parameter for Drift table mode 1, U2 not found. "
                 "(DRIFT_TABLE_1_U2_PAR)"
              << std::endl;
    exit(1);
  }

  if (_par_sorter.switch_dl == 4 && _par_sorter.drifttablefilename == "") {
    std::cout
        << "ERROR : External drift table file name not found. (DRIFT_TABLE)"
        << std::endl;
    exit(1);
  }
  
  
  
  return 1;
}

int Sorter_config::get_config(double KEY, std::string config_file_name,
                              struct parameters &_par_sorter) {

  std::ifstream config_f(config_file_name);

  std::string buff, tmp, configname, KEY_configfile_char;

  double KEY_configfile_double = -1.0;
  int KEY_region = FALSE;

  int thtgt_par_i = 0, xo_thtgt = 0, tho_thtgt = 0, phtgt_par_i = 0,
      xo_phtgt = 0, tho_phtgt = 0, yo_phtgt = 0;
  double par_thtgt = 0.0, par_phtgt = 0.0;

  int global_xcor_th_xo = 0, global_xcor_th_tho = 0, global_xcor_ph_xo = 0,
      global_xcor_ph_pho = 0, global_xcor_th_i = 0, global_xcor_ph_i = 0;
  double global_xcor_th_par = 0.0, global_xcor_ph_par = 0.0;
  int xcor_th_xo = 0, xcor_th_tho = 0, xcor_ph_xo = 0, xcor_ph_pho = 0,
      xcor_th_i = 0, xcor_ph_i = 0;
  double xcor_th_par = 0.0, xcor_ph_par = 0.0;

  int dummy_int_1 = 0, dummy_int_2 = 0, dummy_int_3 = 0;
  double dummy_double_1 = 0.0;

  std::vector<std::vector<std::string>> conf;
  std::string line;

  if (config_f.is_open()) {

    while (getline(config_f, line)) {
      std::stringstream iss(line);

      // istringstream iss(sentence);
      std::vector<std::string> line_entries;

      copy(std::istream_iterator<std::string>(iss),
           std::istream_iterator<std::string>(), back_inserter(line_entries));

      if (line_entries.size() > 0) {
        conf.push_back(line_entries);
      }
    }

  } else
    std::cout << "Unable to open file" << std::endl;

  for (unsigned l = 0; l < conf.size(); ++l) {
    // std::cout << conf[l][0] << std::endl;
    if (conf[l][0].at(0) == '#') { // comment (#)
    } else {                       // data line
      if (conf[l][0] == "KEY") {
        if (KEY_region == TRUE) {
          std::cout << "WARNING : KEY line without KEYEND found. -> "
                    << std::endl;
        }

        KEY_configfile_char = conf[l][1];
        if (conf[l][1] == "COMMON") {
          KEY_region = TRUE;
        } else {
          KEY_configfile_double = stof(conf[l][1]);

          if (KEY_configfile_double == KEY) {
            KEY_region = TRUE;
          }
        }
      } else if (conf[l][0] == "KEYEND") {
        KEY_region = FALSE;
      } else if (conf[l][0] == "GLOBALAREA" && KEY_region == TRUE) {
        _par_sorter.globalareaname = conf[l][1];
      } else if (conf[l][0] == "ONLINE" && KEY_region == TRUE) {
        _par_sorter.online_host = conf[l][2];

        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_online = TRUE;
        } else {
          _par_sorter.switch_online = FALSE;
          _par_sorter.online_host = " ";
        }

      } else if (conf[l][0] == "BYTESWAP" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_byteswap = TRUE;
        } else if (conf[l][1] == "FALSE") {
          _par_sorter.switch_byteswap = FALSE;
        } else {
          _par_sorter.switch_byteswap = 999;
        }

      } else if (conf[l][0] == "START_BLOCK" && KEY_region == TRUE) {
        _par_sorter.start_block = stoi(conf[l][1]);
      } else if (conf[l][0] == "STOP_BLOCK" && KEY_region == TRUE) {
        _par_sorter.stop_block = stoi(conf[l][1]);
      } else if (conf[l][0] == "THTGT_PAR" && KEY_region == TRUE) {
        xo_thtgt = stoi(conf[l][1]);
        tho_thtgt = stoi(conf[l][2]);
        par_thtgt = stof(conf[l][3]);

        if (thtgt_par_i >= MAX_THTGT_PAR) {
          std::cout << "ERROR : Number of THTGT_PAR must be less than "
                    << MAX_THTGT_PAR << ". (xo/tho/par=" << xo_thtgt << "/"
                    << tho_thtgt << "/" << par_thtgt << " ignored)"
                    << std::endl;

        } else {
          if (_par_sorter.thtgt_par[thtgt_par_i] != 0) {
            std::cout << "WARNING : THTGT_PAR overwritten " << MAX_THTGT_PAR
                      << ". (xo/tho/par=" << xo_thtgt << "/" << tho_thtgt << "/"
                      << par_thtgt << ")" << std::endl;
          }

          _par_sorter.thtgt_par_xorder[thtgt_par_i] = xo_thtgt;
          _par_sorter.thtgt_par_thorder[thtgt_par_i] = tho_thtgt;
          _par_sorter.thtgt_par[thtgt_par_i] = par_thtgt;
          ++thtgt_par_i;
        }
      } else if (conf[l][0] == "PHTGT_PAR" && KEY_region == TRUE) {
        xo_phtgt = stoi(conf[l][1]);
        tho_phtgt = stoi(conf[l][2]);
        yo_phtgt = stoi(conf[l][3]);
        par_phtgt = stof(conf[l][4]);

        if (phtgt_par_i >= MAX_PHTGT_PAR) {
          std::cout << "ERROR : Number of PHTGT_PAR must be less than "
                    << MAX_PHTGT_PAR << ". (xo/tho/yo/par= " << xo_phtgt << "/"
                    << tho_phtgt << "/" << yo_phtgt << "/" << par_phtgt
                    << " ignored)" << std::endl;

        } else {
          if (_par_sorter.phtgt_par[phtgt_par_i] != 0) {
            std::cout << "WARNING : PHTGT_PAR overwritten " << MAX_PHTGT_PAR
                      << ". (xo/tho/yo/par= " << xo_thtgt << "/" << tho_thtgt
                      << "/" << yo_phtgt << "/" << par_thtgt << ")"
                      << std::endl;
          }
          _par_sorter.phtgt_par_xorder[phtgt_par_i] = xo_phtgt;
          _par_sorter.phtgt_par_thorder[phtgt_par_i] = tho_phtgt;
          _par_sorter.phtgt_par_yorder[phtgt_par_i] = yo_phtgt;
          _par_sorter.phtgt_par[phtgt_par_i] = par_phtgt;
          ++phtgt_par_i;
        }

      } else if (conf[l][0] == "THTGT_OFFSET" && KEY_region == TRUE) {
	     
        _par_sorter.thtgt_offset = stof(conf[l][1]);
      } else if (conf[l][0] == "PHTGT_OFFSET" && KEY_region == TRUE) {
        _par_sorter.phtgt_offset = stof(conf[l][1]);
      } else if (conf[l][0] == "XFP_OFFSET" && KEY_region == TRUE) {
        _par_sorter.xfp_offset = stof(conf[l][1]);
      } else if (conf[l][0] == "GATE_SCINTI_1" && KEY_region == TRUE) {
        _par_sorter.scinti_1_min = stof(conf[l][1]);
        _par_sorter.scinti_1_max = stof(conf[l][2]);
      } else if (conf[l][0] == "GATE_SCINTI_2" && KEY_region == TRUE) {
        _par_sorter.scinti_2_min = stof(conf[l][1]);
        _par_sorter.scinti_2_max = stof(conf[l][2]);
      } else if (conf[l][0] == "GATE_CORTOF_1" && KEY_region == TRUE) {
        _par_sorter.cortof_1_min = stof(conf[l][1]);
        _par_sorter.cortof_1_max = stof(conf[l][2]);
      } else if (conf[l][0] == "GATE_CORTOF_2" && KEY_region == TRUE) {
        _par_sorter.cortof_2_min = stof(conf[l][1]);
        _par_sorter.cortof_2_max = stof(conf[l][2]);
      } else if (conf[l][0] == "TDC_OFFSET" && KEY_region == TRUE) {
        if (conf[l][1] == "A") {
          _par_sorter.tdcoffset16_x1[0] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[0] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[0] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[0] = stoi(conf[l][5]);
        } else if (conf[l][1] == "B") {
          _par_sorter.tdcoffset16_x1[1] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[1] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[1] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[1] = stoi(conf[l][5]);
        } else if (conf[l][1] == "C") {
          _par_sorter.tdcoffset16_x1[2] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[2] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[2] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[2] = stoi(conf[l][5]);
        } else if (conf[l][1] == "D") {
          _par_sorter.tdcoffset16_x1[3] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[3] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[3] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[3] = stoi(conf[l][5]);
        } else if (conf[l][1] == "E") {
          _par_sorter.tdcoffset16_x1[4] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[4] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[4] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[4] = stoi(conf[l][5]);
        } else if (conf[l][1] == "F") {
          _par_sorter.tdcoffset16_x1[5] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[5] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[5] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[5] = stoi(conf[l][5]);
        } else if (conf[l][1] == "G") {
          _par_sorter.tdcoffset16_x1[6] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[6] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[6] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[6] = stoi(conf[l][5]);
        } else if (conf[l][1] == "H") {
          _par_sorter.tdcoffset16_x1[7] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[7] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[7] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[7] = stoi(conf[l][5]);
        } else if (conf[l][1] == "I") {
          _par_sorter.tdcoffset16_x1[8] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[8] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[8] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[8] = stoi(conf[l][5]);
        } else if (conf[l][1] == "J") {
          _par_sorter.tdcoffset16_x1[9] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[9] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[9] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[9] = stoi(conf[l][5]);
        } else if (conf[l][1] == "K") {
          _par_sorter.tdcoffset16_x1[10] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[10] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[10] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[10] = stoi(conf[l][5]);
        } else if (conf[l][1] == "L") {
          _par_sorter.tdcoffset16_x1[11] = stoi(conf[l][2]);
          _par_sorter.tdcoffset16_u1[11] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_x2[11] = stoi(conf[l][4]);
          _par_sorter.tdcoffset16_u2[11] = stoi(conf[l][5]);
        } else if (conf[l][1] == "M") {
          _par_sorter.tdcoffset16_u1[12] = stoi(conf[l][3]);
          _par_sorter.tdcoffset16_u2[12] = stoi(conf[l][5]);
        } else {
          std::cout << "ERROR : Unknown region in TDC_OFFSET parameter "
                    << conf[l][1] << " will be ignored.\n"
                    << std::endl;
        }
      } else if (conf[l][0] == "TDC_OFFSET_WIRE" && KEY_region == TRUE) {
        if (conf[l][1] == "X1") {
          _par_sorter.tdcoffset_x1[stoi(conf[l][2])] = stoi(conf[l][3]);
        } else if (conf[l][1] == "U1") {
          _par_sorter.tdcoffset_u1[stoi(conf[l][2])] = stoi(conf[l][3]);
        } else if (conf[l][1] == "X2") {
          _par_sorter.tdcoffset_x2[stoi(conf[l][2])] = stoi(conf[l][3]);
        } else if (conf[l][1] == "U2") {
          _par_sorter.tdcoffset_u2[stoi(conf[l][2])] = stoi(conf[l][3]);
        } else {
          std::cout << "ERROR : Unknown Wire plane name (" << conf[l][1]
                    << "in TDC_OFFSET_WIRE : Not implemented" << std::endl;
          exit(1);
        }

        if ((((conf[l][1] == "X1") || (conf[l][1] == "X2")) &&
             dummy_int_1 > 192) ||
            (((conf[l][1] == "U1") || (conf[l][1] == "U2")) &&
             dummy_int_1 > 208)) {
          std::cout
              << "ERROR : Invalid wire id in TDC_OFFSET_WIRE : Not implemented"
              << std::endl;
          exit(1);
        }
      } else if (conf[l][0] == "CHISQ_X1_MAX" && KEY_region == TRUE) {
        _par_sorter.chisq_x1_max = stof(conf[l][1]);
        if (_par_sorter.chisq_x1_max <= 0) {
          std::cout
              << "WARNING : CHISQ_X1_MAX less than 0 found (9999 will be used)."
              << std::endl;
          _par_sorter.chisq_x1_max = 9999.0;
        }
      } else if (conf[l][0] == "CHISQ_U1_MAX" && KEY_region == TRUE) {
        _par_sorter.chisq_u1_max = stof(conf[l][1]);
        if (_par_sorter.chisq_u1_max <= 0) {
          std::cout
              << "WARNING : CHISQ_U1_MAX less than 0 found (9999 will be used)."
              << std::endl;
          _par_sorter.chisq_u1_max = 9999.0;
        }
      } else if (conf[l][0] == "CHISQ_X2_MAX" && KEY_region == TRUE) {
        _par_sorter.chisq_x2_max = stof(conf[l][1]);
        if (_par_sorter.chisq_x2_max <= 0) {
          std::cout
              << "WARNING : CHISQ_X2_MAX less than 0 found (9999 will be used)."
              << std::endl;
          _par_sorter.chisq_x2_max = 9999.0;
        }
      } else if (conf[l][0] == "CHISQ_U2_MAX" && KEY_region == TRUE) {
        _par_sorter.chisq_u2_max = stof(conf[l][1]);
        if (_par_sorter.chisq_u2_max <= 0) {
          std::cout
              << "WARNING : CHISQ_U2_MAX less than 0 found (9999 will be used)."
              << std::endl;
          _par_sorter.chisq_u2_max = 9999.0;
        }
      } else if (conf[l][0] == "CLUSTERSIZE_X1" && KEY_region == TRUE) {
        _par_sorter.clustersize_x1_min = stoi(conf[l][1]);
        _par_sorter.clustersize_x1_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "CLUSTERSIZE_U1" && KEY_region == TRUE) {
        _par_sorter.clustersize_u1_min = stoi(conf[l][1]);
        _par_sorter.clustersize_u1_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "CLUSTERSIZE_X2" && KEY_region == TRUE) {
        _par_sorter.clustersize_x2_min = stoi(conf[l][1]);
        _par_sorter.clustersize_x2_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "CLUSTERSIZE_U2" && KEY_region == TRUE) {
        _par_sorter.clustersize_u2_min = stoi(conf[l][1]);
        _par_sorter.clustersize_u2_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "TDC_X1" && KEY_region == TRUE) {
        _par_sorter.tdc_x1_min = stoi(conf[l][1]);
        _par_sorter.tdc_x1_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "TDC_U1" && KEY_region == TRUE) {
        _par_sorter.tdc_u1_min = stoi(conf[l][1]);
        _par_sorter.tdc_u1_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "TDC_X2" && KEY_region == TRUE) {
        _par_sorter.tdc_x2_min = stoi(conf[l][1]);
        _par_sorter.tdc_x2_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "TDC_U2" && KEY_region == TRUE) {
        _par_sorter.tdc_u2_min = stoi(conf[l][1]);
        _par_sorter.tdc_u2_max = stoi(conf[l][2]);
      } else if (conf[l][0] == "CORTOF_PAR" && KEY_region == TRUE) {
	      
	   
	      
        _par_sorter.cortof_par[0] = stof(conf[l][1]);
        _par_sorter.cortof_par[1] = stof(conf[l][2]);
        _par_sorter.cortof_par[2] = stof(conf[l][3]);
        _par_sorter.cortof_par[3] = stof(conf[l][4]);
        _par_sorter.cortof_par[4] = stof(conf[l][5]);
        
        
        
        
      } else if (conf[l][0] == "FERET_ID" && KEY_region == TRUE) {
        _par_sorter.switch_feret = stoi(conf[l][1]);
        if (_par_sorter.switch_feret != 1 && _par_sorter.switch_feret != 2) {
          std::cout << "WARNING : Invalid FERET_ID of "
                    << _par_sorter.switch_feret << " -> 1" << std::endl;
          _par_sorter.switch_feret = 1;
        }
      } else if (conf[l][0] == "FERETPOSI_PAR" && KEY_region == TRUE) {
	    
	      
        _par_sorter.feretposi_par[0] = stof(conf[l][1]);
        _par_sorter.feretposi_par[1] = stof(conf[l][2]);
        _par_sorter.feretposi_par[2] = stof(conf[l][3]);
        
        
	      
      } else if (conf[l][0] == "GET_NTUPLE" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_ntuple = TRUE;
        } else {
          _par_sorter.switch_ntuple = FALSE;
        }
      } else if (conf[l][0] == "BLDFILE" && KEY_region == TRUE) {
        _par_sorter.bldfilename = conf[l][1];
      } else if (conf[l][0] == "NTPFILE" && KEY_region == TRUE) {
        _par_sorter.ntpfilename = conf[l][1];
      } else if (conf[l][0] == "HBFILE" && KEY_region == TRUE) {
        _par_sorter.hbfilename = conf[l][1];
      } else if (conf[l][0] == "ROOTFILE" && KEY_region == TRUE) {
        _par_sorter.rootfilename = conf[l][1];
      } else if (conf[l][0] == "LOGFILE" && KEY_region == TRUE) {
        _par_sorter.logfilename = conf[l][1];
      } else if (conf[l][0] == "SCALERFILE" && KEY_region == TRUE) {
        _par_sorter.scalerfilename = conf[l][1];
      } else if (conf[l][0] == "HISTCONFIGFILE" && KEY_region == TRUE) {
        _par_sorter.histconfigfilename = conf[l][1];
        //?
        if (_par_sorter.histconfigfilename.empty()) {
          _par_sorter.switch_histconfig = TRUE;
        }

      } else if (conf[l][0] == "GR_ANGLE" && KEY_region == TRUE) {
	  
        _par_sorter.ThGR = stof(conf[l][1]);
      } else if (conf[l][0] == "GET_THTGT" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_thtgt = TRUE;
        } else {
          _par_sorter.switch_thtgt = FALSE;
        }
      } else if (conf[l][0] == "GET_PHTGT" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_phtgt = TRUE;
        } else {
          _par_sorter.switch_phtgt = FALSE;
        }
      } else if (conf[l][0] == "XCOR_TH" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_xcor_th = TRUE;
        } else {
          _par_sorter.switch_xcor_th = FALSE;
        }
      } else if (conf[l][0] == "XCOR_PH" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_xcor_ph = TRUE;
        } else {
          _par_sorter.switch_xcor_ph = FALSE;
        }
      } else if (conf[l][0] == "GLOBAL_XCOR_TH" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_global_xcor_th = TRUE;
        } else {
          _par_sorter.switch_global_xcor_th = FALSE;
        }
      } else if (conf[l][0] == "GLOBAL_XCOR_PH" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_global_xcor_ph = TRUE;
        } else {
          _par_sorter.switch_global_xcor_ph = FALSE;
        }
      } else if (conf[l][0] == "GLOBAL_XCOR_TH_PAR" && KEY_region == TRUE) {
        global_xcor_th_tho = stoi(conf[l][1]);
        global_xcor_th_xo = stoi(conf[l][2]);
        global_xcor_th_par = stof(conf[l][3]);
        if (global_xcor_th_i >= MAX_GLOBAL_XCOR_TH_PAR) {
          std::cout << "ERROR : Number of GLOBAL_XCOR_TH_PAR must be less than "
                    << MAX_GLOBAL_XCOR_TH_PAR
                    << ". (xo/tho/par=" << global_xcor_th_xo << "/"
                    << global_xcor_th_tho << "/" << global_xcor_th_par
                    << " ignored)" << std::endl;
        } else {
          if (_par_sorter.global_xcor_th_par[global_xcor_th_i] != 0.0) {
            std::cout << "WARNING : GLOBAL_XCOR_TH_PAR overwritten (xo/tho/par="
                      << global_xcor_th_xo << "/" << global_xcor_th_tho << "/"
                      << global_xcor_th_par << ")" << std::endl;
          }

          _par_sorter.global_xcor_th_xorder[global_xcor_th_i] =
              global_xcor_th_xo;
          _par_sorter.global_xcor_th_thorder[global_xcor_th_i] =
              global_xcor_th_tho;
          _par_sorter.global_xcor_th_par[global_xcor_th_i] = global_xcor_th_par;
          ++global_xcor_th_i;
        }
      } else if (conf[l][0] == "GLOBAL_XCOR_PH_PAR" && KEY_region == TRUE) {
        global_xcor_ph_pho = stoi(conf[l][1]);
        global_xcor_ph_xo = stoi(conf[l][2]);
        global_xcor_ph_par = stof(conf[l][3]);
        if (global_xcor_ph_i >= MAX_GLOBAL_XCOR_PH_PAR) {
          std::cout << "ERROR : Number of GLOBAL_XCOR_PH_PAR must be less than "
                    << MAX_GLOBAL_XCOR_PH_PAR
                    << ". (xo/tho/par=" << global_xcor_ph_xo << "/"
                    << global_xcor_ph_pho << "/" << global_xcor_ph_par
                    << " ignored)" << std::endl;
        } else {
          if (_par_sorter.global_xcor_ph_par[global_xcor_ph_i] != 0.0) {
            std::cout << "WARNING : GLOBAL_XCOR_PH_PAR overwritten (xo/pho/par="
                      << global_xcor_ph_xo << "/" << global_xcor_ph_pho << "/"
                      << global_xcor_ph_par << ")" << std::endl;
          }

          _par_sorter.global_xcor_ph_xorder[global_xcor_ph_i] =
              global_xcor_ph_xo;
          _par_sorter.global_xcor_ph_phorder[global_xcor_ph_i] =
              global_xcor_ph_pho;
          _par_sorter.global_xcor_ph_par[global_xcor_ph_i] = global_xcor_ph_par;
          ++global_xcor_ph_i;
        }
      } else if (conf[l][0] == "XCOR_TH_PAR" && KEY_region == TRUE) {
        xcor_th_tho = stoi(conf[l][1]);
        xcor_th_xo = stoi(conf[l][2]);
        xcor_th_par = stof(conf[l][3]);
        if (xcor_th_i >= MAX_XCOR_TH_PAR) {
          std::cout << "ERROR : Number of XCOR_TH_PAR must be less than "
                    << MAX_XCOR_TH_PAR << ". (xo/tho/par=" << xcor_th_xo << "/"
                    << xcor_th_tho << "/" << xcor_th_par << " ignored)"
                    << std::endl;
        } else {
          if (_par_sorter.xcor_th_par[xcor_th_i] != 0.0) {
            std::cout << "WARNING : XCOR_TH_PAR overwritten (xo/pho/par="
                      << xcor_th_xo << "/" << xcor_th_tho << "/" << xcor_th_par
                      << ")" << std::endl;
          }

          _par_sorter.xcor_th_xorder[xcor_th_i] = xcor_th_xo;
          _par_sorter.xcor_th_thorder[xcor_th_i] = xcor_th_tho;
          _par_sorter.xcor_th_par[xcor_th_i] = xcor_th_par;
          ++xcor_th_i;
        }
      } else if (conf[l][0] == "XCOR_PH_PAR" && KEY_region == TRUE) {
        xcor_ph_pho = stoi(conf[l][1]);
        xcor_ph_xo = stoi(conf[l][2]);
        xcor_ph_par = stof(conf[l][3]);
        if (xcor_ph_i >= MAX_XCOR_PH_PAR) {
          std::cout << "ERROR : Number of XCOR_PH_PAR must be less than "
                    << MAX_XCOR_PH_PAR << ". (xo/tho/par=" << xcor_ph_xo << "/"
                    << xcor_ph_pho << "/" << xcor_ph_par << " ignored)"
                    << std::endl;
        } else {
          if (_par_sorter.xcor_ph_par[xcor_ph_i] != 0.0) {
            std::cout << "WARNING : XCOR_PH_PAR overwritten (xo/pho/par="
                      << xcor_ph_xo << "/" << xcor_ph_pho << "/" << xcor_ph_par
                      << ")" << std::endl;
          }

          _par_sorter.xcor_ph_xorder[xcor_ph_i] = xcor_ph_xo;
          _par_sorter.xcor_ph_phorder[xcor_ph_i] = xcor_ph_pho;
          _par_sorter.xcor_ph_par[xcor_ph_i] = xcor_ph_par;
          ++xcor_ph_i;
        }
      } else if (conf[l][0] == "GET_EX" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_ex = TRUE;
        } else {
          _par_sorter.switch_ex = FALSE;
        }
      } else if (conf[l][0] == "DRIFT_TABLE" && KEY_region == TRUE) {
        _par_sorter.switch_dl = stoi(conf[l][1]);
        if (_par_sorter.switch_dl == 4) {
          _par_sorter.drifttablefilename = conf[l][2];
        }

      } else if (conf[l][0] == "DISCARD_SHORT_DRIFT_LENGTH" &&
                 KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_discard_shortdl = TRUE;
        } else {
          _par_sorter.switch_discard_shortdl = FALSE;
        }
      } else if (conf[l][0] == "GET_POUT" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_pout = TRUE;
        } else {
          _par_sorter.switch_pout = FALSE;
        }
      } else if (conf[l][0] == "RECOIL_COR" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_recoil_cor = TRUE;
        } else {
          _par_sorter.switch_recoil_cor = FALSE;
        }
      } else if (conf[l][0] == "DRIFT_TABLE_1_X1_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable1_x1_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable1_x1_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable1_x1_par[2] = stof(conf[l][3]);
      } else if (conf[l][0] == "DRIFT_TABLE_1_U1_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable1_u1_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable1_u1_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable1_u1_par[2] = stof(conf[l][3]);
      } else if (conf[l][0] == "DRIFT_TABLE_1_X2_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable1_x2_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable1_x2_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable1_x2_par[2] = stof(conf[l][3]);
      } else if (conf[l][0] == "DRIFT_TABLE_1_U2_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable1_u2_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable1_u2_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable1_u2_par[2] = stof(conf[l][3]);
      } else if (conf[l][0] == "DRIFT_TABLE_2_X1_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable2_x1_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable2_x1_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable2_x1_par[2] = stof(conf[l][3]);
        _par_sorter.drifttable2_x1_par[3] = stof(conf[l][4]);
      } else if (conf[l][0] == "DRIFT_TABLE_2_U1_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable2_u1_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable2_u1_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable2_u1_par[2] = stof(conf[l][3]);
        _par_sorter.drifttable2_u1_par[3] = stof(conf[l][4]);
      } else if (conf[l][0] == "DRIFT_TABLE_2_X2_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable2_x2_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable2_x2_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable2_x2_par[2] = stof(conf[l][3]);
        _par_sorter.drifttable2_x2_par[3] = stof(conf[l][4]);
      } else if (conf[l][0] == "DRIFT_TABLE_2_U2_PAR" && KEY_region == TRUE) {
        _par_sorter.drifttable2_u2_par[0] = stof(conf[l][1]);
        _par_sorter.drifttable2_u2_par[1] = stof(conf[l][2]);
        _par_sorter.drifttable2_u2_par[2] = stof(conf[l][3]);
        _par_sorter.drifttable2_u2_par[3] = stof(conf[l][4]);
      } else if (conf[l][0] == "PLOT_FERA" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_fera = TRUE;
        } else {
          _par_sorter.switch_plot_fera = FALSE;
        }
      } else if (conf[l][0] == "PLOT_FERET" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_feret = TRUE;
        } else {
          _par_sorter.switch_plot_feret = FALSE;
        }
      } else if (conf[l][0] == "PLOT_3377" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_3377 = TRUE;
        } else {
          _par_sorter.switch_plot_3377 = FALSE;
        }
      } else if (conf[l][0] == "PLOT_SYSTEM" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_system = TRUE;
        } else {
          _par_sorter.switch_plot_system = FALSE;
        }
      } else if (conf[l][0] == "PLOT_VDC" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_vdc = TRUE;
        } else {
          _par_sorter.switch_plot_vdc = FALSE;
        }
      } else if (conf[l][0] == "PLOT_SCINTI_TOF" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_scinti_tof = TRUE;
        } else {
          _par_sorter.switch_plot_scinti_tof = FALSE;
        }
      } else if (conf[l][0] == "PLOT_USER" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_user = TRUE;
        } else {
          _par_sorter.switch_plot_user = FALSE;
        }
      } else if (conf[l][0] == "PLOT_HIGH_RESO" && KEY_region == TRUE) {
        if (conf[l][1] == "TRUE") {
          _par_sorter.switch_plot_high_reso = TRUE;
        } else {
          _par_sorter.switch_plot_high_reso = FALSE;
        }
      } else if (conf[l][0] == "PLOT_SIEVESLIT" && KEY_region == TRUE) {
        if (conf[l][1] == "YFP") {
          _par_sorter.switch_plot_dama = 1;
        } else if (conf[l][1] == "PHTGT") {
          _par_sorter.switch_plot_dama = 2;
        } else if (conf[l][1] == "FALSE") {
          _par_sorter.switch_plot_dama = 0;
        } else {
          std::cout << "WARNING : PLOT_SIEVESLIT must be YFP or PHTGT or FALSE "
                       "(forced to be FALSE)\n"
                    << std::endl;
          _par_sorter.switch_plot_dama = 0;
        }
      } else if (conf[l][0] == "XGATE_SIEVESLIT" && KEY_region == TRUE) {
        // FOR NOW NOT IMPLEMENTED! STRINGS SHOULD BE SPLIT AT '/'
        _par_sorter.xgate_min_dama[0] = stof(conf[l][1]);
        _par_sorter.xgate_max_dama[0] = stof(conf[l][2]);
        _par_sorter.xgate_min_dama[1] = stof(conf[l][3]);
        _par_sorter.xgate_max_dama[1] = stof(conf[l][4]);
        _par_sorter.xgate_min_dama[2] = stof(conf[l][5]);
        _par_sorter.xgate_max_dama[2] = stof(conf[l][6]);
        _par_sorter.xgate_min_dama[3] = stof(conf[l][7]);
        _par_sorter.xgate_max_dama[3] = stof(conf[l][8]);
        _par_sorter.xgate_min_dama[4] = stof(conf[l][9]);
        _par_sorter.xgate_max_dama[4] = stof(conf[l][10]);
        _par_sorter.xgate_min_dama[5] = stof(conf[l][11]);
        _par_sorter.xgate_max_dama[5] = stof(conf[l][12]);
        _par_sorter.xgate_min_dama[6] = stof(conf[l][13]);
        _par_sorter.xgate_max_dama[6] = stof(conf[l][14]);
        _par_sorter.xgate_min_dama[7] = stof(conf[l][15]);
        _par_sorter.xgate_max_dama[7] = stof(conf[l][16]);
        _par_sorter.xgate_min_dama[8] = stof(conf[l][17]);
        _par_sorter.xgate_max_dama[8] = stof(conf[l][18]);
        _par_sorter.xgate_min_dama[9] = stof(conf[l][19]);
        _par_sorter.xgate_max_dama[9] = stof(conf[l][20]);
        _par_sorter.xgate_min_dama[10] = stof(conf[l][21]);
        _par_sorter.xgate_max_dama[10] = stof(conf[l][22]);
        _par_sorter.xgate_min_dama[11] = stof(conf[l][23]);
        _par_sorter.xgate_max_dama[11] = stof(conf[l][24]);
        _par_sorter.xgate_min_dama[12] = stof(conf[l][25]);
        _par_sorter.xgate_max_dama[12] = stof(conf[l][26]);
        _par_sorter.xgate_min_dama[13] = stof(conf[l][27]);
        _par_sorter.xgate_max_dama[13] = stof(conf[l][28]);
        _par_sorter.xgate_min_dama[14] = stof(conf[l][29]);
        _par_sorter.xgate_max_dama[14] = stof(conf[l][30]);
        _par_sorter.xgate_min_dama[15] = stof(conf[l][31]);
        _par_sorter.xgate_max_dama[15] = stof(conf[l][32]);
        _par_sorter.xgate_min_dama[16] = stof(conf[l][33]);
        _par_sorter.xgate_max_dama[16] = stof(conf[l][34]);
        _par_sorter.xgate_min_dama[17] = stof(conf[l][35]);
        _par_sorter.xgate_max_dama[17] = stof(conf[l][36]);
        _par_sorter.xgate_min_dama[18] = stof(conf[l][37]);
        _par_sorter.xgate_max_dama[18] = stof(conf[l][38]);
        _par_sorter.xgate_min_dama[19] = stof(conf[l][39]);
        _par_sorter.xgate_max_dama[19] = stof(conf[l][40]);
      } else if (conf[l][0] == "TARGET" && KEY_region == TRUE) {
        _par_sorter.target = conf[l][1];
      } else if (conf[l][0] == "E_BEAM" && KEY_region == TRUE) {
        _par_sorter.ebeam = stof(conf[l][1]);
      } else if (conf[l][0] == "QVALUE" && KEY_region == TRUE) {
        _par_sorter.qvalue = stof(conf[l][1]);
      } else if (conf[l][0] == "MASS_OUT" && KEY_region == TRUE) {
        _par_sorter.mout = stof(conf[l][1]);
      } else if (conf[l][0] == "RECOIL_PAR" && KEY_region == TRUE) {
        dummy_int_1 = stoi(conf[l][1]);
        dummy_int_2 = stoi(conf[l][1]);
        dummy_double_1 = stof(conf[l][1]);

        if (dummy_int_3 >= MAX_RECOIL_PAR) {
          std::cout << "ERROR : Number of RECOIL_PAR must be less than "
                    << MAX_RECOIL_PAR << ". (xo/zto/par=" << dummy_int_1 << "/"
                    << dummy_int_2 << "/" << dummy_double_1 << " ignored)"
                    << std::endl;
        } else {
          if (_par_sorter.recoil_par[dummy_int_3] != 0.0) {
            std::cout << "WARNING : RECOIL_PAR overwritten (xo/zto/par="
                      << dummy_int_1 << "/" << dummy_int_2 << "/"
                      << dummy_double_1 << ")" << std::endl;
          }
          _par_sorter.recoil_eorder[dummy_int_3] = dummy_int_1;
          _par_sorter.recoil_ztorder[dummy_int_3] = dummy_int_2;
          _par_sorter.recoil_par[dummy_int_3] = dummy_double_1;
          ++dummy_int_3;
        }

      } else if (conf[l][0] == "POUT_PAR" && KEY_region == TRUE) {
        dummy_int_1 = stoi(conf[l][1]);

        if (dummy_int_1 >= MAX_POUT_PAR) {
          std::cout << "ERROR : Number of POUT_PAR (" << dummy_int_1
                    << ") must be less than " << MAX_POUT_PAR << "."
                    << std::endl;
        } else {
          if (_par_sorter.pout_par[dummy_int_1] != 0.0) {
            std::cout << "WARNING : POUT_PAR(" << dummy_int_1
                      << ") overwritten." << std::endl;
          }
          _par_sorter.pout_par[dummy_int_1] = stof(conf[l][2]);
        }

      } else if (conf[l][0] == "POUT_COR_PAR" && KEY_region == TRUE) {
        dummy_int_1 = stoi(conf[l][1]);

        if (dummy_int_1 >= MAX_POUT_PAR) {
          std::cout << "ERROR : Number of POUT_COR_PAR (" << dummy_int_1
                    << ") must be less than " << MAX_POUT_PAR << "."
                    << std::endl;
        } else {
          if (_par_sorter.pout_cor_par[dummy_int_1] != 0.0) {
            std::cout << "WARNING : POUT_COR_PAR(" << dummy_int_1
                      << ") overwritten." << std::endl;
          }
          _par_sorter.pout_cor_par[dummy_int_1] = stof(conf[l][2]);
        }

      } else if (conf[l][0] == "EX_COR_PAR" && KEY_region == TRUE) {
        dummy_int_1 = stoi(conf[l][1]);

        if (dummy_int_1 >= MAX_EXCOR_PAR) {
          std::cout << "ERROR : Number of EX_COR_PAR (" << dummy_int_1
                    << ") must be less than " << MAX_EXCOR_PAR << "."
                    << std::endl;
        } else {
          if (_par_sorter.ex_cor_par[dummy_int_1] != 0.0) {
            std::cout << "WARNING : EX_COR_PAR(" << dummy_int_1
                      << ") overwritten." << std::endl;
          }
          _par_sorter.ex_cor_par[dummy_int_1] = stof(conf[l][2]);
        }
      }
    }
  }
 std::cout <<"TEST" << _par_sorter.cortof_par[0] << std::endl;
	      std::cout <<_par_sorter.cortof_par[1] << std::endl;
	      std::cout <<_par_sorter.cortof_par[2] << std::endl;
	      std::cout <<_par_sorter.cortof_par[3] << std::endl;
	      std::cout <<_par_sorter.cortof_par[4] << std::endl;


  return 1.0;
}

// Not tested!
int Sorter_config::get_hist_config(std::string _histconfigfilename,
                                   struct hist_parameters &_par_hist) {

  std::ifstream hist_f(_histconfigfilename);

  std::string buff, tmp, configname, HIST_configfile_char;
  std::string hist_groupname;

  std::string g_name, g_param_name, g_chk01 = "", g_chk02 = "", g_chk03 = "",
                                    g_chk04 = "", g_chk05 = "";
  double g_min = 0.0, g_max = 0.0;

  std::string h_name, h_param1, h_param2;
  double h_min1, h_max1, h_min2, h_max2;
  int h_id, h_numch1, h_numch2;

  int g_count = 0, h_count = 0;

  int i = 0;

  std::vector<std::vector<std::string>> conf;
  std::string line;

  if (hist_f.is_open()) {

    while (getline(hist_f, line)) {
      std::stringstream iss(line);

      // istringstream iss(sentence);
      std::vector<std::string> line_entries;

      copy(std::istream_iterator<std::string>(iss),
           std::istream_iterator<std::string>(), back_inserter(line_entries));

      if (line_entries.size() > 0) {
        conf.push_back(line_entries);
      }
    }

  } else {
    std::cout << "ERROR : Open " << _histconfigfilename
              << " (histogram config file) failed." << std::endl;

    exit(1);
  }

  for (unsigned l = 0; l < conf.size(); ++l) {
    // std::cout << conf[l][0] << std::endl;
    if (conf[l][0].at(0) == '#') {
      // comment (#)
    } else {
      h_id = 0;
      h_numch1 = 0;
      h_numch2 = 0;
      h_min1 = 0.0;
      h_max1 = 0.0;
      h_min2 = 0.0;
      h_max2 = 0.0;
      h_name = "";
      h_param1 = "";
      h_param2 = "";
      g_chk01 = "";
      g_chk02 = "";
      g_chk03 = "";
      g_chk04 = "";
      g_chk05 = "";
      configname = "";
      tmp = "";
      if (conf[l][0] == "GATE") {
        if (conf[l].size() < 5) {
          g_name = conf[l][1];
          g_param_name = conf[l][2];
          g_min = stof(conf[l][3]);

          _par_hist.gate_name[g_count] = g_name;
          _par_hist.gate_param[g_count] = g_param_name;

          _par_hist.gate_min[g_count] = g_min;
          _par_hist.gate_type[g_count] = G_EQUAL;
          _par_hist.gate_id[g_count] = g_count;
        } else {
          g_name = conf[l][1];
          g_param_name = conf[l][2];
          g_min = stof(conf[l][3]);
          g_max = stof(conf[l][4]);

          _par_hist.gate_name[g_count] = g_name;
          _par_hist.gate_param[g_count] = g_param_name;
          _par_hist.gate_min[g_count] = g_min;
          _par_hist.gate_max[g_count] = g_max;
          _par_hist.gate_type[g_count] = G_MINMAX;
          _par_hist.gate_id[g_count] = g_count;
        }
        ++g_count;

      } else if (conf[l][0] == "TH1") {
        _par_hist.hist_order[h_count] = 1;
        h_id = stoi(conf[l][1]);
        h_param1 = conf[l][2];
        h_min1 = stof(conf[l][3]);
        h_max1 = stof(conf[l][4]);
        h_numch1 = stoi(conf[l][5]);
        h_name = conf[l][6];
        // g_chk01 = conf[l][7];;
        // g_chk02 = conf[l][8];;
        // g_chk03 = conf[l][9];;
        // g_chk04 = conf[l][10];;
        // g_chk05 = conf[l][11];;

        _par_hist.hist_name[h_count] = h_name;
        _par_hist.hist_param1[h_count] = h_param1;
        _par_hist.hist_id[h_count] = h_id;
        _par_hist.hist_min1[h_count] = h_min1;
        _par_hist.hist_max1[h_count] = h_max1;
        _par_hist.hist_numch1[h_count] = h_numch1;

        if (conf[l].size() > 7) {
          _par_hist.hist_gate01[h_count] = conf[l][7];
        }
        if (conf[l].size() > 8) {
          _par_hist.hist_gate02[h_count] = conf[l][8];
        }
        if (conf[l].size() > 9) {
          _par_hist.hist_gate03[h_count] = conf[l][9];
        }
        if (conf[l].size() > 10) {
          _par_hist.hist_gate04[h_count] = conf[l][9];
        }
        if (conf[l].size() > 11) {
          _par_hist.hist_gate05[h_count] = conf[l][10];
        }

        // not so sure here
        for (i = 0; i < MAX_GATE && _par_hist.gate_id[i] >= 0; ++i) {

          if ((_par_hist.hist_gate01[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate01[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate02[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate02[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate03[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate03[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate04[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate04[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate05[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate05[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
        }

        ++h_count;

      } else if (conf[l][0] == "TH2") {

        _par_hist.hist_order[h_count] = 2;
        h_id = stoi(conf[l][1]);
        h_param1 = conf[l][2];
        h_min1 = stof(conf[l][3]);
        h_max1 = stof(conf[l][4]);
        h_numch1 = stoi(conf[l][5]);
        h_param2 = conf[l][6];
        h_min2 = stof(conf[l][7]);
        h_max2 = stof(conf[l][8]);
        h_numch2 = stoi(conf[l][9]);
        h_name = conf[l][10];

        _par_hist.hist_name[h_count] = h_name;
        _par_hist.hist_param1[h_count] = h_param1;
        _par_hist.hist_param2[h_count] = h_param2;
        _par_hist.hist_id[h_count] = h_id;
        _par_hist.hist_min1[h_count] = h_min1;
        _par_hist.hist_max1[h_count] = h_max1;
        _par_hist.hist_numch1[h_count] = h_numch1;
        _par_hist.hist_min2[h_count] = h_min2;
        _par_hist.hist_max2[h_count] = h_max2;
        _par_hist.hist_numch2[h_count] = h_numch2;

        if (conf[l].size() > 11) {
          _par_hist.hist_gate01[h_count] = conf[l][11];
        }
        if (conf[l].size() > 12) {
          _par_hist.hist_gate02[h_count] = conf[l][12];
        }
        if (conf[l].size() > 13) {
          _par_hist.hist_gate03[h_count] = conf[l][13];
        }
        if (conf[l].size() > 14) {
          _par_hist.hist_gate04[h_count] = conf[l][14];
        }
        if (conf[l].size() > 15) {
          _par_hist.hist_gate05[h_count] = conf[l][15];
        }

        // not so sure here
        for (i = 0; i < MAX_GATE && _par_hist.gate_id[i] >= 0; ++i) {

          if ((_par_hist.hist_gate01[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate01[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate02[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate02[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate03[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate03[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate04[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate04[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
          if ((_par_hist.hist_gate05[h_count] == _par_hist.gate_name[i]) &&
              !_par_hist.hist_gate05[h_count].empty()) {
            _par_hist.hist_gate[h_count][i] = TRUE;
          }
        }

        ++h_count;
      }
    }
  }
  return 1;
}

int Sorter_config::show_parameters(struct parameters &_par_sorter) {
  int i = 0;

  std::cout << "Info : Global area name\t\t\t-> " << _par_sorter.globalareaname
            << std::endl;
  ;
  if (_par_sorter.switch_online == TRUE) {
    std::cout << "Info : Online mode\t\t\t-> TRUE" << std::endl;
    ;
    std::cout << "Info : Online host\t\t\t-> " << _par_sorter.online_host
              << std::endl;
    ;
  } else
    std::cout << "Info : Online mode\t\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_byteswap == TRUE)
    std::cout << "Info : Byte swap\t\t\t-> TRUE" << std::endl;
  else if (_par_sorter.switch_byteswap == FALSE)
    std::cout << "Info : Byte swap\t\t\t-> FALSE" << std::endl;
  else
    std::cout << "Info : Byte swap\t\t\t-> NOT SPECIFIED" << std::endl;
  std::cout << "Info : Start Block\t\t\t-> " << _par_sorter.start_block
            << std::endl;
  if (_par_sorter.start_block)
    std::cout << "" << std::endl;
  else
    std::cout << " (from the 1st block)" << std::endl;
  std::cout << "Info : Stop Block\t\t\t-> " << _par_sorter.stop_block
            << std::endl;
  if (_par_sorter.stop_block)
    std::cout << "" << std::endl;
  else
    std::cout << " (till the last block)" << std::endl;

  std::cout << "Info : Scintilator gate 1,2 min/max\t-> "
            << _par_sorter.scinti_1_min << "/" << _par_sorter.scinti_1_max
            << "," << _par_sorter.scinti_2_min << "/"
            << _par_sorter.scinti_2_max << std::endl;

  // MAX_CORTOF_PAR made ni subeki...
  std::cout << "Info : Cor-TOF gate 1,2 min/max\t\t-> "
            << _par_sorter.cortof_1_min << "/" << _par_sorter.cortof_1_max
            << "," << _par_sorter.cortof_2_min << "/"
            << _par_sorter.cortof_2_max << std::endl;

  std::cout << "Info : Maximum chi square x1,u1,x2,u2\t-> "
            << _par_sorter.chisq_x1_max << "," << _par_sorter.chisq_u1_max
            << "," << _par_sorter.chisq_x2_max << ","
            << _par_sorter.chisq_u2_max << std::endl;

  std::cout << "Info : Cluster size x1,u1,x2,u2 min/max\t-> "
            << _par_sorter.clustersize_x1_min << "/"
            << _par_sorter.clustersize_x1_max << ","
            << _par_sorter.clustersize_u1_min << "/"
            << _par_sorter.clustersize_u1_max << ","
            << _par_sorter.clustersize_x2_min << "/"
            << _par_sorter.clustersize_x2_max << ","
            << _par_sorter.clustersize_u2_min << "/"
            << _par_sorter.clustersize_u2_max << std::endl;

  std::cout << "Info : TDC range x1,u1,x2,u2 min/max\t-> "
            << _par_sorter.tdc_x1_min << "/" << _par_sorter.tdc_x1_max << ","
            << _par_sorter.tdc_u1_min << "/" << _par_sorter.tdc_u1_max << ","
            << _par_sorter.tdc_x2_min << "/" << _par_sorter.tdc_x2_max << ","
            << _par_sorter.tdc_u2_min << "/" << _par_sorter.tdc_u2_max
            << std::endl;

  std::cout << "Info : Thtgt offset\t\t\t-> " << _par_sorter.thtgt_offset
            << std::endl;
  std::cout << "Info : Phtgt offset\t\t\t->  " << _par_sorter.phtgt_offset
            << std::endl;
  std::cout << "Info : Xfp offset\t\t\t-> " << _par_sorter.xfp_offset
            << std::endl;

  // MAX_CORTOF_PAR made ni subeki...
  std::cout << "Info : TOF-correction parameters\t-> "
            << _par_sorter.cortof_par[0] << "," << _par_sorter.cortof_par[1]
            << "," << _par_sorter.cortof_par[2] << ","
            << _par_sorter.cortof_par[3] << "," << _par_sorter.cortof_par[4]
            << std::endl;

  std::cout << "Info : FERET on plastic\t\t\t-> " << _par_sorter.switch_feret
            << std::endl;
  std::cout << "Info : FERET-position parameters\t-> "
            << _par_sorter.feretposi_par[0] << ","
            << _par_sorter.feretposi_par[1] << ","
            << _par_sorter.feretposi_par[2] << std::endl;

  std::cout << "Info : BLD data file\t\t\t-> " << _par_sorter.bldfilename
            << std::endl;
  std::cout << "Info : output  HB file name\t\t-> " << _par_sorter.hbfilename
            << std::endl;
  std::cout << "Info : output  ROOT file name\t\t-> "
            << _par_sorter.rootfilename << std::endl;
  if (_par_sorter.switch_ntuple == TRUE)
    std::cout << "Info : output NTP file name\t\t-> " << _par_sorter.ntpfilename
              << std::endl;
  std::cout << "Info : output LOG file name\t\t-> " << _par_sorter.logfilename
            << std::endl;
  std::cout << "Info : output Scaler file name\t\t-> "
            << _par_sorter.scalerfilename << std::endl;
  std::cout << "Info : Histogram config file name\t-> "
            << _par_sorter.histconfigfilename << std::endl;

  std::cout << "Info : GR angle\t\t\t\t-> " << _par_sorter.ThGR << "[deg]"
            << std::endl;

  if (_par_sorter.switch_thtgt == TRUE)
    std::cout << "Info : get Th_tgt\t\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : get Th_tgt\t\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_phtgt == TRUE)
    std::cout << "Info : get Ph_tgt\t\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : get Ph_tgt\t\t\t-> FALSE" << std::endl;

  if (_par_sorter.switch_xcor_th == TRUE) {
    if (_par_sorter.switch_thtgt != TRUE) {
      std::cout << "WARNING : XCOR_TH->TRUE will be neglected since "
                   "GET_THTGT->FALSE"
                << std::endl;
      _par_sorter.switch_thtgt = FALSE;
    } else {
      std::cout << "Info : X-Th correction\t\t\t-> TRUE" << std::endl;
    }
  } else
    std::cout << "Info : X-Th correction\t\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_xcor_ph == TRUE) {
    if (_par_sorter.switch_phtgt != TRUE) {
      std::cout << "WARNING : XCOR_PH->TRUE will be neglected since "
                   "GET_PHTGT->FALSE"
                << std::endl;
      _par_sorter.switch_phtgt = FALSE;
    } else {
      std::cout << "Info : X-Ph correction\t\t\t-> TRUE" << std::endl;
    }
  } else
    std::cout << "Info : X-Ph correction\t\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_global_xcor_th == TRUE) {
    if (_par_sorter.switch_thtgt != TRUE) {
      std::cout << "WARNING : GLOBAL_XCOR_TH->TRUE will be neglected since "
                   "GET_THTGT->FALSE"
                << std::endl;
      _par_sorter.switch_global_xcor_th = FALSE;
    } else {
      std::cout << "Info : Global X-Th correction\t\t-> TRUE" << std::endl;
    }
  } else
    std::cout << "Info : Global X-Th correction\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_global_xcor_ph == TRUE) {
    if (_par_sorter.switch_phtgt != TRUE) {
      std::cout << "WARNING : GLOBAL_XCOR_PH->TRUE will be neglected since "
                   "GET_PHTGT->FALSE"
                << std::endl;
      _par_sorter.switch_global_xcor_ph = FALSE;
    } else {
      std::cout << "Info : Global X-Ph correction\t\t-> TRUE" << std::endl;
    }
  } else
    std::cout << "Info : Global X-Ph correction\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_ex == TRUE)
    std::cout << "Info : Calculate Excitation energy\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Calculate Excitation energy\t-> FALSE" << std::endl;
  if (_par_sorter.switch_dl == 1) {
    std::cout << "Info : Drift length mode\t\t-> 1 (simple drift table)"
              << std::endl;
    std::cout << "Info :  Parameters for X1\t\t-> "
              << (int)_par_sorter.drifttable1_x1_par[0] << "/"
              << _par_sorter.drifttable1_x1_par[1] << "/"
              << _par_sorter.drifttable1_x1_par[2] << std::endl;
    std::cout << "Info :  Parameters for U1\t\t-> "
              << (int)_par_sorter.drifttable1_u1_par[0] << "/"
              << _par_sorter.drifttable1_u1_par[1] << "/"
              << _par_sorter.drifttable1_x1_par[2] << std::endl;
    std::cout << "Info :  Parameters for X2\t\t-> "
              << (int)_par_sorter.drifttable1_x2_par[0] << "/"
              << _par_sorter.drifttable1_x2_par[1] << "/"
              << _par_sorter.drifttable1_x1_par[2] << std::endl;
    std::cout << "Info :  Parameters for U2\t\t-> "
              << (int)_par_sorter.drifttable1_u2_par[0] << "/"
              << _par_sorter.drifttable1_u2_par[1] << "/"
              << _par_sorter.drifttable1_x1_par[2] << std::endl;
  } else if (_par_sorter.switch_dl == 2) {
    std::cout << "Info : Drift length mode\t\t-> 2 (linear function)"
              << std::endl;
    std::cout << "Info :  Parameters for X1\t\t-> "
              << _par_sorter.drifttable2_x1_par[0] << "/"
              << _par_sorter.drifttable2_x1_par[1] << "/"
              << _par_sorter.drifttable2_x1_par[2] << "/"
              << _par_sorter.drifttable2_x1_par[3] << std::endl;
    std::cout << "Info :  Parameters for U1\t\t-> "
              << _par_sorter.drifttable2_u1_par[0] << "/"
              << _par_sorter.drifttable2_u1_par[1] << "/"
              << _par_sorter.drifttable2_u1_par[2] << "/"
              << _par_sorter.drifttable2_u1_par[3] << std::endl;
    std::cout << "Info :  Parameters for X2\t\t-> "
              << _par_sorter.drifttable2_x2_par[0] << "/"
              << _par_sorter.drifttable2_x2_par[1] << "/"
              << _par_sorter.drifttable2_x2_par[2] << "/"
              << _par_sorter.drifttable2_x2_par[3] << std::endl;
    std::cout << "Info :  Parameters for U2\t\t-> "
              << _par_sorter.drifttable2_u2_par[0] << "/"
              << _par_sorter.drifttable2_u2_par[1] << "/"
              << _par_sorter.drifttable2_u2_par[2] << "/"
              << _par_sorter.drifttable2_u2_par[3] << std::endl;
  } else if (_par_sorter.switch_dl == 3)
    std::cout
        << "Info : Drift length mode\t\t-> 3 (drift table fitted function)"
        << std::endl;
  else if (_par_sorter.switch_dl == 4) {
    std::cout << "Info : Drift length mode\t\t-> 4 (external drift table)"
              << std::endl;
    std::cout << "       External Drift table file\t-> "
              << _par_sorter.drifttablefilename << std::endl;
  }

  else
    std::cout << "Info : Unknown switch_dl value\t\t-> "
              << _par_sorter.switch_dl << "(drift table will be used)"
              << std::endl;

  if (_par_sorter.switch_discard_shortdl == TRUE) {
    std::cout << "Info : Discard shortest drift length\t-> TRUE" << std::endl;
  } else {
    std::cout << "Info : Discard shortest drift length\t-> FALSE" << std::endl;
  }

  if (_par_sorter.switch_pout == TRUE)
    std::cout << "Info : get outgoing momentum\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : get outgoing momentum\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_recoil_cor == TRUE)
    std::cout << "Info : Kinematic correction\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Kinematic correction\t\t-> FALSE" << std::endl;
  //  if(_par_sorter->switch_tdc_optimize==TRUE) std::cout << "Info : TDC
  //  optimize
  //  mode\t\t-> TRUE" << std::endl;
  //  else                                       std::cout << "Info : TDC
  //  optimize
  //  mode\t\t-> FALSE" << std::endl;

  if (_par_sorter.switch_plot_fera == TRUE)
    std::cout << "Info : Plot FERA histograms\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Plot FERA histograms\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_plot_feret == TRUE)
    std::cout << "Info : Plot FERET histograms\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Plot FERET histograms\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_plot_3377 == TRUE)
    std::cout << "Info : Plot 3377 histograms\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Plot 3377 histograms\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_plot_system == TRUE)
    std::cout << "Info : Plot SYSTEM histograms\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Plot SYSTEM histograms\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_plot_vdc == TRUE)
    std::cout << "Info : Plot VDC histograms\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Plot VDC histograms\t\t-> FALSE" << std::endl;
  if (_par_sorter.switch_plot_scinti_tof == TRUE)
    std::cout << "Info : Plot SCINTILLATOR-TOF histograms\t-> TRUE"
              << std::endl;
  else
    std::cout << "Info : Plot SCINTILLATOR-TOF histograms\t-> FALSE"
              << std::endl;
  if (_par_sorter.switch_plot_user == TRUE)
    std::cout << "Info : Plot USER histograms\t\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Plot USER histograms\t\t-> FALSE" << std::endl;
  //  if(_par_sorter->switch_plot_user_gated==TRUE) std::cout << "Info : Plot
  //  USER
  //  GATED histograms\t-> TRUE" << std::endl;
  //  else                                          std::cout << "Info : Plot
  //  USER
  //  GATED histograms\t-> FALSE" << std::endl;
  if (_par_sorter.switch_plot_high_reso == TRUE)
    std::cout << "Info : Plot HIGH-RESO 2D histograms\t-> TRUE" << std::endl;
  else
    std::cout << "Info : Plot HIGH-RESO 2D histograms\t-> FALSE" << std::endl;
  if (_par_sorter.switch_plot_dama == 0)
    std::cout << "Info : Plot Sieve-slit 2D histograms\t-> FALSE" << std::endl;
  else if (_par_sorter.switch_plot_dama == 1)
    std::cout << "Info : Plot Sieve-slit 2D histograms\t-> Thtgt-Yfp"
              << std::endl;
  else if (_par_sorter.switch_plot_dama == 2)
    std::cout << "Info : Plot Sieve-slit 2D histograms\t-> Thtgt-Phtgt"
              << std::endl;

  std::cout << "Info : X gate for Sieve-slit data" << std::endl;
  for (i = 0; i < MAX_XGATE_SIEVESLIT; ++i) {
    if (_par_sorter.xgate_min_dama[i] != 99999.0 &&
        _par_sorter.xgate_max_dama[i] != 99999.0) {
      std::cout << "       " << i << " -> " << _par_sorter.xgate_min_dama[i]
                << " < Xfp < " << _par_sorter.xgate_max_dama[i] << std::endl;
    }
  }

  std::cout << "Info : Target\t\t\t\t-> " << _par_sorter.target << std::endl;
  std::cout << "Info : Incident beam energy\t\t-> " << _par_sorter.ebeam
            << std::endl;
  std::cout << "Info : Reaction Q-value\t\t\t-> " << _par_sorter.qvalue
            << std::endl;
  std::cout << "Info : Outgoing Mass\t\t\t-> " << _par_sorter.mout << std::endl;
  //  std::cout << "Info : keV per mm\t\t\t-> %5.2f\n",_par_sorter->keVpermm);

  // must be corrected
  //  std::cout << "Info : Pout -> Pout@center parameter\t->");
  //  for(i=0;i<MAX_RECOIL_PAR;++i){ std::cout << "
  //  %6.2e",_par_sorter->recoil_par[i]); }
  //  std::cout << "" << std::endl;

  std::cout << "Info : Posi -> Pout parameter\t\t->";
  for (i = 0; i < MAX_POUT_PAR; ++i) {
    std::cout << " " << _par_sorter.pout_par[i];
  }
  std::cout << std::endl;

  std::cout << "Info : Pout correction parameter\t->";
  for (i = 0; i < MAX_POUT_PAR; ++i) {
    std::cout << " " << _par_sorter.pout_cor_par[i];
  }
  std::cout << std::endl;

  std::cout << "Info : Ex correction parameter\t\t->";
  for (i = 0; i < MAX_EXCOR_PAR; ++i) {
    std::cout << " " << _par_sorter.ex_cor_par[i];
  }
  std::cout << std::endl;

  return 0;
}

int Sorter_config::init_hist_parameters(struct hist_parameters &_par_hist) {
  unsigned i = 0, j = 0;

  for (i = 0; i < MAX_GATE; ++i) {
    _par_hist.gate_name[i] = "";
    _par_hist.gate_param[i] = "";
    _par_hist.gate_id[i] = -1; // Initial value is -1, not 0
    _par_hist.gate_type[i] = 0;
    _par_hist.gate_min[i] = 0.0;
    _par_hist.gate_max[i] = 0.0;
  }

  for (i = 0; i < MAX_HIST; ++i) {
    _par_hist.hist_order[i] = 0;

    _par_hist.hist_min1[i] = 0.0;
    _par_hist.hist_max1[i] = 0.0;
    _par_hist.hist_min2[i] = 0.0;
    _par_hist.hist_max2[i] = 0.0;
    _par_hist.hist_id[i] = 0;
    _par_hist.hist_numch1[i] = 0;
    _par_hist.hist_numch2[i] = 0;

    for (j = 0; j < MAX_GATE; ++j) {
      _par_hist.hist_gate[i][j] = FALSE;
    }
  }
  return 1;
}

int Sorter_config::show_hist_config(struct hist_parameters &_par_hist) {
  unsigned i = 0, j = 0;

  for (i = 0; i < MAX_GATE && _par_hist.gate_id[i] >= 0; ++i) {
    std::cout << i << " : Gate " << _par_hist.gate_id[i] << "/"
              << _par_hist.gate_name[i] << "/" << _par_hist.gate_param[i] << "/"
              << _par_hist.gate_type[i] << "/" << _par_hist.gate_min[i] << "/"
              << _par_hist.gate_max[i] << std::endl;
  }

  for (i = 0; i < MAX_HIST && _par_hist.hist_order[i] > 0; ++i) {
    if (_par_hist.hist_order[i] == 1) {
      std::cout << i << " : 1D-hist " << _par_hist.hist_id[i] << "/"
                << _par_hist.hist_name[i] << "/" << _par_hist.hist_numch1[i]
                << "/" << _par_hist.hist_min1[i] << "/"
                << _par_hist.hist_max1[i];
      for (j = 0; j < MAX_GATE && _par_hist.gate_id[j] >= 0; ++j) {
        if (_par_hist.hist_gate[i][j] == TRUE) {
          std::cout << " " << _par_hist.gate_name[j];
        }
      }
      std::cout << std::endl;
    } else if (_par_hist.hist_order[i] == 2) {
      std::cout << i << " 2D-hist " << _par_hist.hist_id[i] << "/"
                << _par_hist.hist_name[i] << "/" << _par_hist.hist_numch1[i]
                << "/" << _par_hist.hist_min1[i] << "/"
                << _par_hist.hist_max1[i] << "/" << _par_hist.hist_numch2[i]
                << "/" << _par_hist.hist_min2[i] << "/"
                << _par_hist.hist_max2[i] << std::endl;
      for (j = 0; j < MAX_GATE && _par_hist.gate_id[j] >= 0; ++j) {
        if (_par_hist.hist_gate[i][j] == TRUE) {
          std::cout << " " << _par_hist.gate_name[j];
        }
      }
      std::cout << std::endl;
    }
  }

  return 1;
}

int Sorter_config::init_scalers(struct scalers &_sca_sorter) {
  // Is that right?
  /*std::memset((void *)(&(_sca_sorter.data_scaler)), 0,
              sizeof(_sca_sorter.data_scaler));*/
  _sca_sorter.data_scaler = {};
  _sca_sorter.data_block_cnt = 0;
  _sca_sorter.hf_block_cnt = 0;
  _sca_sorter.event_cnt = 0;
  _sca_sorter.eventID0_cnt = 0;
  _sca_sorter.eventID1_cnt = 0;
  _sca_sorter.eventID2_cnt = 0;
  _sca_sorter.eventID4_cnt = 0;
  _sca_sorter.eventID8_cnt = 0;
  _sca_sorter.x1_cnt = 0;
  _sca_sorter.u1_cnt = 0;
  _sca_sorter.x2_cnt = 0;
  _sca_sorter.u2_cnt = 0;
  _sca_sorter.xferet_cnt = 0;
  _sca_sorter.p1r_cnt = 0;
  _sca_sorter.p1l_cnt = 0;
  _sca_sorter.p2r_cnt = 0;
  _sca_sorter.p2l_cnt = 0;

  return 1;
}
