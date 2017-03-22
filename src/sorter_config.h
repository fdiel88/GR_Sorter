#ifndef SORTER_CONFIG_H_
#define SORTER_CONFIG_H_

#include <string>

#include "sorter_par.h"

class Sorter_config {

public:
  int init_parameters(struct parameters &_par_sorter);
  int show_parameters(struct parameters &_par_sorter);
  int get_config(double _KEY, std::string config_file_name,
                 struct parameters &_par_sorter);
  int get_hist_config(std::string _histconfigfilename,
                      struct hist_parameters &_par_hist);

  int check_config(struct parameters &_par_sorter);
  int init_hist_parameters(struct hist_parameters &_par_hist);
  int show_hist_config(struct hist_parameters &_par_hist);
  int init_scalers(struct scalers &_sca_sorter);
};

#endif
