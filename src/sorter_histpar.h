#ifndef SORTER_HIST_PAR_H_
#define SORTER_HIST_PAR_H_

#include <array>
#include <string>

#define MAX_GATE 100
#define MAX_HIST 200

#define SHT_LENGTH 16
#define MDL_LENGTH 64
#define LNG_LENGTH 256

// For par_hist.gate_type (0->initial value)
#define G_EQUAL 1
#define G_MINMAX 2

struct hist_parameters {
  std::array<int, MAX_GATE> gate_id= {0}; // <- starts from 1, not 0
  std::array<int, MAX_GATE> gate_type= {0};
  std::array<std::string, MAX_GATE> gate_name = {" "}, gate_param = {" "};
  std::array<double, MAX_GATE> gate_min= {0.0}, gate_max= {0.0};

  std::array<std::string, MAX_HIST> hist_name = {" "}, hist_param1 = {" "}, hist_param2 = {" "},
      hist_gate01 = {" "}, hist_gate02 = {" "}, hist_gate03 = {" "}, hist_gate04 = {" "}, hist_gate05 = {" "};
  std::array<std::array<int, MAX_GATE>, MAX_HIST> hist_gate  = {0} ; // ためしにいれてみる。gate01-05のかわり
  std::array<double, MAX_HIST> hist_min1= {0.0}, hist_max1= {0.0}, hist_min2= {0.0}, hist_max2= {0.0};
  std::array<int, MAX_HIST> hist_id= {0}, hist_numch1= {0}, hist_numch2= {0}, hist_order= {0};
};
#endif
