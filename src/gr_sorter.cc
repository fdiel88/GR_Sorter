
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <cstring>
#include <ctime>

#include "gr_sorter.h"
#include "sorter_config.h"
#include "sorter_const.h"
#include "sorter_histpar.h"
#include "sorter_init.h"
#include "sorter_par.h"
#include "sorter_read.h"
#include "sorter_root.h"
#include "sorter_scaler.h"
#include "sorter_treedata.h"
#include "sorter_user.h"
#include "sorter_util.h"

// using namespace std;

std::string version = "0.1";
// TODO: unsigned int -> uint
//	scaler output

int GR_Sorter::Run(std::string config_file_name, unsigned run_num) {

  std::cout << "Info: VERSION: " << version << std::endl;

  // config file name
  m_config_file_name = config_file_name;
  std::cout << "Info: Config file: " << m_config_file_name << std::endl;

  // run number (KEY Parameter)
  m_run_num = run_num;
  std::cout << "Info: Run num: " << m_run_num << std::endl;

  // Define variables

  std::array<double, 1024> drifttable_x1 = {0.0}, drifttable_u1 = {0.0},
                           drifttable_x2 = {0.0}, drifttable_u2 = {0.0};

  // initialize the parameter struct;

  Sorter_config s_conf;

  struct parameters par_sorter;

  s_conf.init_parameters(par_sorter);
  std::cout << "Parameters initialized!" << std::endl;

  // s_conf.show_parameters(par_sorter);
  // std::cout << "Parameters shown!" << std::endl;

  // initialize the parameter struct;
  struct hist_parameters par_hist;

  s_conf.init_hist_parameters(par_hist);
  std::cout << "Hist Parameters initialized!" << std::endl;

  s_conf.show_hist_config(par_hist);
  std::cout << "Hist Config shown!" << std::endl;

  // initialize the scalar struct;
  struct scalers sca_sorter;

  s_conf.init_scalers(sca_sorter);
  std::cout << "Scaler initialized!" << std::endl;

  std::cout << par_sorter.cortof_par[0] << std::endl;
  std::cout << par_sorter.cortof_par[1] << std::endl;
  std::cout << par_sorter.cortof_par[2] << std::endl;
  std::cout << par_sorter.cortof_par[3] << std::endl;
  std::cout << par_sorter.cortof_par[4] << std::endl;

  // get config file
  s_conf.get_config(m_run_num, m_config_file_name, par_sorter);
  std::cout << "Configfile read!" << std::endl;

  // s_conf.check_config(par_sorter);
  // std::cout << "Configfile Checked!" << std::endl;

  std::cout << par_sorter.cortof_par[0] << std::endl;
  std::cout << par_sorter.cortof_par[1] << std::endl;
  std::cout << par_sorter.cortof_par[2] << std::endl;
  std::cout << par_sorter.cortof_par[3] << std::endl;
  std::cout << par_sorter.cortof_par[4] << std::endl;

  s_conf.show_parameters(par_sorter);
  std::cout << "Parameters shown!" << std::endl;

  // get hist config
  if (par_sorter.switch_histconfig == TRUE) {
    s_conf.get_hist_config(par_sorter.histconfigfilename, par_hist);
    // show_hist_config(&par_hist);
  }

  //==============================================
  // DRIFTTABLE

  Sorter_user s_user;

  if (par_sorter.switch_dl == 1) {
    s_user.get_drifttable1(drifttable_x1, drifttable_u1, drifttable_x2,
                           drifttable_u2, par_sorter);
  } else if (par_sorter.switch_dl == 2) {
    s_user.get_drifttable2(drifttable_x1, drifttable_u1, drifttable_x2,
                           drifttable_u2, par_sorter);
  } else if (par_sorter.switch_dl == 3) {
    s_user.get_drifttable3(drifttable_x1, drifttable_u1, drifttable_x2,
                           drifttable_u2, par_sorter);
  } else if (par_sorter.switch_dl == 4) {
    s_user.get_drifttable4(drifttable_x1, drifttable_u1, drifttable_x2,
                           drifttable_u2, par_sorter);
  } else {
    std::cout << "ERROR : Unknown DRIFT_TABLE parameter ("
              << par_sorter.switch_dl << ")" << std::endl;

    exit(1);
  }

  //==============================================
  // ONLINE?

  std::cout << "Info : Analysis Key\t-> " << m_run_num << std::endl;
  if (par_sorter.switch_online == TRUE) {
    std::cout << "Info : Online mode\t-> TRUE" << std::endl;
    std::cout << "Info : Online host\t-> " << par_sorter.online_host
              << std::endl;
  } else {
    std::cout << "Info : Online mode\t-> FALSE" << std::endl;
  }
  if (par_sorter.switch_ntuple != TRUE) {
    std::cout << "Info : Global Area\t-> " << par_sorter.globalareaname
              << std::endl;
    std::cout << "Info : Output Hbook\t-> " << par_sorter.hbfilename
              << " (Histogram)" << std::endl;
    std::cout << "Info : Output ROOT\t-> " << par_sorter.rootfilename
              << " (Histogram)" << std::endl;
  } else {
    std::cout << "Info : Global Area\t-> Not allocated in Ntuple mode"
              << std::endl;
    std::cout << "Info : Output Hbook\t-> " << par_sorter.ntpfilename
              << " (Ntuple)" << std::endl;
  }
  std::cout << "Info : Log file\t\t-> " << par_sorter.logfilename << std::endl;

  //==============================================
  // check Plastic and TOF gates

  if (par_sorter.scinti_1_min >= par_sorter.scinti_1_max) {
    std::cout << "ERROR : Invalid Plastic Scintillator 1 gate -> "
              << par_sorter.scinti_1_min << " < P1 < "
              << par_sorter.scinti_1_max << std::endl;
    exit(1);
  }

  if (par_sorter.scinti_2_min >= par_sorter.scinti_2_max) {
    std::cout << "ERROR : Invalid Plastic Scintillator 2 gate -> "
              << par_sorter.scinti_2_min << " < P1 < "
              << par_sorter.scinti_2_max << std::endl;
    exit(1);
  }

  //==============================================
  // Initialize Histogramms

  Sorter_root s_root;

  if (par_sorter.switch_ntuple != TRUE) {
    s_root.open_hist(par_sorter, par_hist); // Open histgrams
    // s_root.write_root(par_sorter);
  } else {

    // NTUPLE MODE  is not implemented yet. Might be usefull using ROOT trees
    // open_ntp(&par_sorter);
  }

  //==============================================
  // Drift table plot (originally in get_drifttable())

  s_root.fill_hist_drifttable(drifttable_x1, drifttable_u1, drifttable_x2,
                              drifttable_u2);
  // s_root.write_root(par_sorter);

  //==============================================
  // Check Blocksize and byte swap
  Sorter_init s_init;

  if (switch_stdin == FALSE && par_sorter.switch_online == FALSE) {
    if (switch_stdin == FALSE && par_sorter.switch_online == FALSE) {
      std::cout << "Info : BLD data file\t-> " << par_sorter.bldfilename
                << std::endl;
    } else {
      std::cout << "ERROR : BLD file name is not given." << std::endl;
      exit(1);
    }
    switch_byteswap = TRUE;
    BL_WORD = s_init.get_blocksize_check_byteswap(par_sorter.bldfilename,
                                                  switch_byteswap, par_sorter);

    if (BL_WORD == 9999) {
      std::cout << "ERROR : Variable block size? Cannot analyze." << std::endl;
      exit(1);
    } else if (!BL_WORD) {
      std::cout << "ERROR : Block size estimation failed." << std::endl;
      exit(1);
    }
    std::cout << "Info : Block size\t-> " << BL_WORD * 2 / 1024 << " KB"
              << std::endl;
    if (par_sorter.switch_byteswap == 999) {
      if (switch_byteswap == TRUE) {
        std::cout << "Info : Byte swap\t-> TRUE (Automatically detected)"
                  << std::endl;
      } else {
        std::cout << "Info : Byte swap\t-> FALSE (Automatically detecteed)"
                  << std::endl;
      }
    }

    //==============================================
    // Check BLD Filesize

    Sorter_util s_util;

    bld_size_byte = s_util.get_filesize2(par_sorter.bldfilename);
    bld_size_blk = bld_size_byte / (BL_WORD * 2);

    if (bld_size_byte % (BL_WORD * 2)) {
      std::cout << "WARNING : Inconsistent file/block size? (" << bld_size_byte
                << "/" << BL_WORD * 2 << " B/B)" << std::endl;
    }
    std::cout << "Info : BLD filesize\t->" << bld_size_blk << " ("
              << bld_size_byte << " Byte)" << std::endl;
    bld.open(par_sorter.bldfilename, std::ifstream::binary);

    // bld=fopen(par_sorter.bldfilename,"r"); // <-
    // ¥Õ¥¡¥¤¥ë¤ÎÍ­Ìµ¤Ïget_filesize¤Ç¥Á¥§¥Ã¥¯ºÑ

  } else if (switch_stdin == TRUE) {
    std::cout << "Info : Standard input mode is not supported yet."
              << std::endl;
    exit(0);
  } else if (par_sorter.switch_online == TRUE) {
  }

  //==============================================
  // Open Scaler file
  scalerfile.open(par_sorter.scalerfilename, std::ifstream::binary);
  if (!scalerfile.is_open()) {
    std::cout << "ERROR : Open " << par_sorter.scalerfilename
              << " (scaler output file) failed." << std::endl;
    exit(1);
  }

  total_num_event = 0;

  // Buffer initialize
  buff_word = {};
  buff_word_swap = {};
  // TDC output histogram initialize
  hist4dt_x1 = {};
  hist4dt_u1 = {};
  hist4dt_x2 = {};
  hist4dt_u2 = {};

  TTree *tree = new TTree("DATA", "Grand Raiden data");
  Sorter_treedata s_treedata;
  s_treedata.init_tree(tree);

  //==============================================
  // for online mode
  if (par_sorter.switch_online == TRUE) {
    std::cout << "ERROR : ONLINE MODE IS NOT SUPPORTED YET" << std::endl;
  } else {
    // number of block which will be analyzed (block number starts from zero)
    if (!par_sorter.start_block && !par_sorter.stop_block) {
      start_blk = 0;
      stop_blk = bld_size_blk;
      block_number_analysis = bld_size_blk;
    } else if (par_sorter.start_block && !par_sorter.stop_block) {
      start_blk = par_sorter.start_block;
      stop_blk = bld_size_blk;
      block_number_analysis = bld_size_blk - par_sorter.start_block;
    } else if (!par_sorter.start_block && par_sorter.stop_block) {
      start_blk = 0;
      stop_blk = par_sorter.stop_block;
      block_number_analysis = par_sorter.stop_block + 1;
    } else if (par_sorter.start_block && par_sorter.stop_block) {
      start_blk = par_sorter.start_block;
      stop_blk = par_sorter.stop_block;
      block_number_analysis =
          par_sorter.stop_block - (par_sorter.start_block - 1);
    }
    if (bld.is_open()) {

      // std::string buf_tmp;

      Sorter_read s_read(swt_mesg, BL_WORD);

      while (bld.read(reinterpret_cast<char *>(&buff_word), BL_WORD * 2)) {

        block_number =
            ((0xff00 & buff_word[4]) >> 8) | ((0x00ff & buff_word[4]) << 8);

        if (block_number < start_blk)
          continue;
        else if (block_number > stop_blk)
          break;

        if (block_number == start_blk) {
          starttime = std::time(nullptr);
          std::cout << "Info : Analysis started -> " << time(&starttime)
                    << std::endl;
        }

        // std::cout << "\r" << time(nullptr) - starttime << std::flush;

        if (switch_byteswap == TRUE) {
          for (i = 0; i < BL_WORD; ++i) {
            buff_word_swap[i] =
                ((0xff00 & buff_word[i]) >> 8) | ((0x00ff & buff_word[i]) << 8);

            // std::cout << std::hex << std::showbase << buff_word[i] << " " <<
            // buff_word_swap[i] << std::endl;
          }
        } else {
          for (i = 0; i < BL_WORD; ++i) {
            buff_word_swap[i] = buff_word[i];
          } // address¤Ç´ÖÃ±¤Ë¤«¤±¤ë¤Ï¤º
        }

        switch (buff_word_swap[2]) {
        //      case 0x0f01: read_1storlast_blk(buff_word_swap);
        case 0x0f01:
          // std::cout <<
          // "read_1storlast_blk(buff_word_swap,&runnumber_header,&sca_sorter)"
          // << std::endl;
          s_read.read_1storlast_blk(buff_word_swap, runnumber_header,
                                    sca_sorter);
          break;
        case 0x0000:
          par_sorter.flg_discard_event = 0;
          // std::cout <<
          // "read_data_blk(buff_word_swap,drifttable_x1,drifttable_u1,drifttable_x2,drifttable_u2,
          // scaler_0,scaler_1,scaler_2,scaler_3,
          // &CIrange,&par_sorter,&sca_sorter,&par_hist)" << std::endl;
          s_read.read_data_blk(buff_word_swap, drifttable_x1, drifttable_u1,
                               drifttable_x2, drifttable_u2, scaler_0, scaler_1,
                               scaler_2, scaler_3, CIrange, par_sorter,
                               sca_sorter, par_hist, total_num_event, s_user,
                               s_root, s_treedata);

          // std::cout << scalerfile<< std::endl;
          for (j = 0; j < 16; ++j) {
            // scaler output for each block
            // fprintf(scalerfile,"%d\t%d\t%d\t%d\t%d\t%d\n",sca_sorter.data_block_cnt,j,scaler_0[j],scaler_1[j],scaler_2[j],scaler_3[j]);
          }

          break;
        //      case 0x0f02: read_1storlast_blk(buff_word_swap);
        case 0x0f02:
          // std::cout <<
          // "read_1storlast_blk(buff_word_swap,&runnumber_footer,&sca_sorter)"
          // << std::endl;
          s_read.read_1storlast_blk(buff_word_swap, runnumber_header,
                                    sca_sorter);

          break;
        default:
          std::cout << "ERROR : Unknown Block ID : " << blk_id << std::endl;
          exit(1);
        }

        if (bld_size_blk) {
          //	if(total_num_block%50==0){
          if (sca_sorter.data_block_cnt % 50 == 0 &&
              sca_sorter.data_block_cnt != 0) {
            // time(&tmptime);	ctime(&tmptime);
            // stdtime = difftime(tmptime,starttime);
            //	  esttime =
            //(double)block_number_analysis/(double)total_num_block*stdtime -
            // stdtime;
            // esttime =
            // (double)block_number_analysis/(double)sca_sorter.data_block_cnt*stdtime
            // - stdtime;
          }

          // if (esttime) {
          //	  printf("Info : Processed block\t-> %d/%d %d/%d\t(Remain
          //%02d:%02d:%02d)\n",
          //		 sca_sorter.data_block_cnt+sca_sorter.hf_block_cnt,block_number_analysis,
          //		 block_number,bld_size_blk,
          //		 (int)(esttime/3600),
          //		 ( (int)(esttime/60) - (int)(esttime/3600)*60 ),
          //		 (int)esttime%60);
          std::cout << "\r"
                    << "Info : Block count\t-> Total/Header/Data/Present "
                    << bld_size_blk << "/" << sca_sorter.hf_block_cnt << "/"
                    << sca_sorter.data_block_cnt << "/" << block_number
                    << std::flush;

          // std::cout << "/r" << "Info : Remaining time\t-> "<<
          // (int)(esttime/3600)<<":"<<((int)(esttime/60)-(int)(esttime/3600)*60)<<":"<<(int)esttime%60)<<
          // std::flush;;
          // } else {
          //	  printf("Info : Processed block\t-> %d/%d %d/%d\t(Remain
          //--:--:--) \n",
          //		 sca_sorter.data_block_cnt+sca_sorter.hf_block_cnt,block_number_analysis,block_number,bld_size_blk);
          /* printf("Info : Block count\t-> Total/Header/Data/Present "
                  "%d/%d/%d/%d\n",
                  bld_size_blk, sca_sorter.hf_block_cnt,
                  sca_sorter.data_block_cnt, block_number);
           printf("Info : Remaining time\t-> --:--:--\n");*/
          // }
        } else {
          // get_filesize()¤ò»È¤¦¤Èfilesize¤¬¤Ê¤¤¾õ¶·¤Ï¤¢¤ê¤¨¤Ê¤¤¤¬¡Ä¤È¤ê¤¢¤¨¤º¤ª¤¤¤È¤¯
          std::cout << "Info : Processed block\t-> "
                    << sca_sorter.data_block_cnt << "/BLD file size unknown"
                    << std::endl;
        }
        buff_word = {0};
        buff_word_swap = {0};
      }
      bld.close();
    } else {
      std::cout << "ERROR : BLD file does not exist!" << std::endl;
      exit(1);
    }
  }

  if (par_sorter.switch_ntuple != TRUE) {
    s_root.write_root(par_sorter, s_treedata.tree);
  } else {
    // write_ntp(par_sorter.ntpfilename);
  }
  // quit_sorter(CIrange,par_sorter.switch_ntuple,runnumber_header,runnumber_footer,&par_sorter,sca_sorter);

  return 1;
}

int main(int argc, char **argv) {

  GR_Sorter sorter;

  if (argc != 3) {
    std::cout << "gr_sorter, Software to analyze Grand Raiden single "
                 "measurement data."
              << std::endl;
    std::cout << "Usage   : " << argv[0] << " <config file> <KEY parameter>"
              << std::endl;
    std::cout << "Version : " << version << std::endl;
    std::cout << "Build   : " << __DATE__ << " " << __TIME__ << std::endl;
    exit(0);
  } else {

    sorter.Run(argv[1], atoi(argv[2]));
  }
}
