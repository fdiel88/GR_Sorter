#ifndef SORTER_READ_H_
#define SORTER_READ_H_

#include <array>

#include "sorter_histpar.h"
#include "sorter_par.h"
#include "sorter_root.h"
#include "sorter_scaler.h"
#include "sorter_user.h"

class Sorter_read {

public:
  Sorter_read(int swt_mesg_in, unsigned int BL_WORD_in);

  int get_fera_virtualstation_number(uint16_t word);
  void read_1storlast_blk(std::array<uint16_t, 49152> &buff, int &_runnumber,
                          struct scalers &_sca_sorter);
  void read_data_blk(
      std::array<uint16_t, 49152> &buff,
      std::array<double, 1024> &_drifttable_x1,
      std::array<double, 1024> &_drifttable_u1,
      std::array<double, 1024> &_drifttable_x2,
      std::array<double, 1024> &_drifttable_u2, std::array<int, 16> &_scaler_0,
      std::array<int, 16> &_scaler_1, std::array<int, 16> &_scaler_2,
      std::array<int, 16> &_scaler_3, int &_CIrange,
      struct parameters &_par_sorter, struct scalers &_sca_sorter,
      struct hist_parameters &_par_hist, unsigned int &total_num_event,
      Sorter_user &s_user, Sorter_root &s_root);

private:
  int swt_mesg;
  unsigned int BL_WORD;
};

#endif
