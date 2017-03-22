#ifndef SORTER_INIT_H_
#define SORTER_INIT_H_

#include <string>

#include "sorter_par.h"

class Sorter_init {

public:
  int get_blocksize_check_byteswap(std::string bldfile, int &_switch_byteswap,
                                   struct parameters &_par_sorter);
};

#endif
