#ifndef SORTER_SCALER_H_
#define SORTER_SCALER_H_

struct scalers {
  std::array<std::array<int, 16>, 4> data_scaler= {0};

  int data_block_cnt, hf_block_cnt, event_cnt; // hf_block <- header or footer
  int eventID0_cnt, eventID1_cnt, eventID2_cnt, eventID4_cnt, eventID8_cnt;
  int x1_cnt, u1_cnt, x2_cnt, u2_cnt, xferet_cnt;
  int p1r_cnt, p1l_cnt, p2r_cnt, p2l_cnt;
};

#endif
