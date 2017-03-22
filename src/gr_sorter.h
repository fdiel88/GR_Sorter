#ifndef GR_Sorter_H_
#define GR_Sorter_H_

#include <fstream>
#include <string>
#include <vector>

#include <ctime>

#include "sorter_const.h"

class GR_Sorter {

public:
  int Run(std::string config_file_name, unsigned run_num);
  int switch_ntuple = FALSE;

private:
  int i, j;
  int switch_byteswap;
  std::string m_config_file_name = "Config.dat";
  unsigned m_run_num = 1;
  int BL_WORD = BL_WORD_32;
  int switch_stdin = FALSE;
  std::u16streampos bld_size_byte;
  unsigned bld_size_blk = 0;
  std::ifstream bld;
  std::ofstream scalerfile;

  unsigned int blk_id;
  unsigned int blk_header_size;

  std::array<uint16_t, 49152> buff_word,
      buff_word_swap; // larger area than expected just in case
  std::array<int, 1024> hist4dt_x1, hist4dt_u1, hist4dt_x2, hist4dt_u2;

  int runnumber_header = 0; // run number in header block
  int runnumber_footer = 0; // run number in footer block

  int block_number = 0, block_number_analysis = 0, start_blk = 0, stop_blk;

  std::time_t starttime;
  double esttime = 0.0; //,stdtime=0.0,totaltime=0.0;

  int swt_mesg = 0;
  unsigned int total_num_event;
  std::array<int, 16> scaler_0 = {0}, scaler_1 = {0}, scaler_2 = {0},
                      scaler_3 = {0};
  int CIrange = 0;
};

#endif
