

#include <array>
#include <iomanip>
#include <iostream>

#include <cmath>

#include "sorter_const.h"
#include "sorter_histpar.h"
#include "sorter_par.h"
#include "sorter_read.h"
#include "sorter_scaler.h"
#include "sorter_treedata.h"
#include "sorter_user.h"

int Sorter_read::get_fera_virtualstation_number(uint16_t word) {
  // 0:FERA, 1:FERET
  if (0x0080 & word) {
    std::cout << "WARNING : FERET Virtual station number in FERA Region?"
              << std::endl;
    exit(1);
  }
  if (0x0060 & word) {
    std::cout
        << "WARNING : Inconsistent FERA Virtual station number -> Accepted"
        << std::endl;
  }
  // 0:GR, 1:LAS
  if (0x0010 & word) {
    std::cout << "WARNING : Seems to be LAS-FERA data -> treated as GR"
              << std::endl;
    //    exit(1);
  }
  return 0x000f & word;
}

Sorter_read::Sorter_read(int swt_mesg_in, unsigned int BL_WORD_in) {
  swt_mesg = swt_mesg_in;
  BL_WORD = BL_WORD_in;
}

void Sorter_read::read_1storlast_blk(std::array<uint16_t, 49152> &buff,
                                     int &_runnumber,
                                     struct scalers &_sca_sorter) {

  unsigned i = 0;
  // time_t time_read;
  // struct tm *t_read;

  if (swt_mesg)
    std::cout << "----------------------------------------------" << std::endl;

  // 1st word (should be Block Header ID:0xffff)
  if (buff[0] == 0xffff) {
    if (swt_mesg) {
      std::cout << "Block Header 0xffff found." << std::endl;
    }
  } else {
    std::cout << "ERROR : Inconsistent Block Header ID in block "
              << _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt << " : "
              << buff[0] << " (should be 0xffff)" << std::endl;
    exit(1);
  }

  // 3rd word (Block ID)
  if (swt_mesg) {
    if (buff[2] == 0x0f01) {
      std::cout << "Header Block" << std::endl;
    } else if (buff[2] == 0x0f02) {
      std::cout << "Footer Block" << std::endl;
    }
  }

  // 4th word (Block Size - Block Header Size)

  // 5th word (Block Number) <- always this seems to be ZERO... does not work?
  if (buff[4]) {
    std::cout << "WARNING: Block Number buff[4] in Header/Footer Block?"
              << std::endl;
    exit(1);
  }

  // 6th word (Number of Events) 1st/last blockなので0のハズ
  if (buff[5]) {
    std::cout << "WARNING: NON-ZERO Number of Events in Header Block : "
              << buff[5] << std::endl;
    exit(1);
  }
  // 7th word (Reserved word, should be zero for GR single)
  if (buff[6]) {
    std::cout << "WARNING: 7th Word should be ZERO (reserved) : " << buff[6]
              << std::endl;
    exit(1);
  }
  if (swt_mesg) {
    uint16_t tmp1 = 0xff00 & buff[7] >> 8;
    uint16_t tmp2 = 0x00ff & buff[7];

    std::cout << "Data format\t: ver. " << tmp1 << "." << tmp2 << "(?)"
              << std::endl;
  }
  // 9th word (Byte Order) ?imi wakaran, Do nothing
  // 10,11,12th word of 1st block (Time (the num. of secs since the Epoch,
  // 00:00:00 GMT 1 Jan 1970))
  // (Note that above two words are in the big endian byte order)
  // ----------------------------------------------------------

  // time_read = buff[9];
  // t_read = localtime(&time_read);
  std::cout << "Info : Experiment date\t-> "
            << std::endl; // t_read->tm_year+1970<<
                          // "/"<<t_read->tm_mon+1<<"/"<<t_read->tm_mday <<" "<<
                          // t_read->tm_hour<<":"
                          // <<t_read->tm_min<<":"<<t_read->tm_sec<<"
                          // (wrong?)\n",

  if (swt_mesg) {
    if (buff[2] == 0x0f01) {
      std::cout << "Run started time\t: ";
    } else {
      std::cout << "Run halted  time\t: ";
    }
  }

  if (buff[2] == 0x0f01) {
    // 13th of 1st block word (Run number)
    std::cout << "Info : Run num. in data\t-> " << buff[12] << std::endl;
    _runnumber = buff[12];
    // Comments
    std::cout << "Info : Comments\t\t-> ";
    for (i = 13; i <= buff[3]; ++i) {
      if (buff[i]) {
        std::cout << buff[i];
      }
    }
    std::cout << std::endl;
  } else {
    // -----
    std::cout << "Footer block found." << std::endl;
    // -----
    i = buff[3] + 1;
  }
  while (i < BL_WORD) {
    if (buff[i]) {
      if (buff[i] == 0xffef && i == 8190) {
        if (swt_mesg) {
          std::cout << "Block Trailer ID  (word" << i << ") : " << buff[i]
                    << std::endl;
        }
      } else if (buff[i] == 0x0002 && i == 8191) {
        if (swt_mesg) {
          std::cout << "Block Trailer size (word " << i << ") : " << buff[i]
                    << std::endl;
        }
      } else {
        std::cout << "WARNING : something not zero (" << i
                  << "th) : " << buff[i] << std::endl;
      }
    }
    ++i;
  }

  //  ++total_num_block;
  ++_sca_sorter.hf_block_cnt;
}

void Sorter_read::read_data_blk(
    std::array<uint16_t, 49152> &buff, std::array<double, 1024> &_drifttable_x1,
    std::array<double, 1024> &_drifttable_u1,
    std::array<double, 1024> &_drifttable_x2,
    std::array<double, 1024> &_drifttable_u2, std::array<int, 16> &_scaler_0,
    std::array<int, 16> &_scaler_1, std::array<int, 16> &_scaler_2,
    std::array<int, 16> &_scaler_3, int &_CIrange,
    struct parameters &_par_sorter, struct scalers &_sca_sorter,
    struct hist_parameters &_par_hist, unsigned int &total_num_event,
    Sorter_user &s_user, Sorter_root &s_root, Sorter_treedata &s_treedata) {

  int i, j;
  unsigned int word_num_eventhead = 6;
  unsigned int num_event = 0;
  unsigned int field_size;
  // unsigned int field_size_chk;
  unsigned short region_header, region_size;
  unsigned int tot_blk_num_word, blk_num_events, event_size, present_word_num;
  std::array<unsigned int, 16> InputRegister_data; // present_num_word;

  int flg_field_structure;
  unsigned int flg_InputRegister_1st, flg_InputRegister_2nd, flg_FERA,
      flg_FERET, flg_v3377, flg_PCOS;
  int wirechamber_ID = -1; // 1:X1, 2:U1, 3:X2, 4:U2

  // int event_num = 0;
  // int event_num_pre = -1;

  int fera_word_count, fera_virtualstation_number;
  std::array<int, 16> fera_data_channel = {0}, fera_data_adc = {0};
  int feret_word_count, feret_virtualstation_number;
  std::array<int, 16> feret_data_channel = {0}, feret_data_tdc = {0};
  std::array<int, 4> feret_offset = {0};
  std::array<unsigned int, 4> plastic_scintillator = {0};
  std::array<unsigned int, 5> tof = {0};
  unsigned int v3377_event_number, v3377_module_ID, v3377_channel;
  int v3377_tdc_out = 0;
  std::array<int, 192> v3377_tdc_X1 = {0}, v3377_tdc_X2 = {0};
  std::array<int, 208> v3377_tdc_U1 = {0}, v3377_tdc_U2 = {0};
  int wireID;

  int num_wire_x1 = 0, num_wire_u1 = 0, num_wire_x2 = 0, num_wire_u2 = 0;
  int sca_num;
  // std::array<std::array<unsigned int, 16>, 4> scaler = {0};

  // int pre_wirechamber_ID = 0, pre_wireID = 999;

  // int tmp_int = 0;

  if (swt_mesg) {
    std::cout << "----------------------------------------------" << std::endl;
  }
  // address=0 wo uketoru? inchiki kusai ga korede sinogu (11/09/02)
  // NOT SURE IF THIS IS NESSECARY
  /*if (&_scaler_1 == nullptr) {
    &_scaler_1 = &_scaler_0 + 64;
  }
  if (&_scaler_2 == nullptr) {
    &_scaler_2 = &_scaler_1 + 64;
  }
  if (&_scaler_3 == nullptr) {
    &_scaler_3 = &_scaler_2 + 64;
  }*/

  // 1st word (should be Block Header ID:0xffff)
  if (buff[0] == 0xffff) {
    if (swt_mesg) {
      std::cout << "Block Header 0xffff found\n" << std::endl;
    }
  } else {
    std::cout << "ERROR : Inconsistent Block Header ID in block"
              << _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt << " : "
              << buff[0] << " (should be 0xffff) -> Accepted" << std::endl;

    //    exit(1);
  }
  // 2nd word of Data block ( Block Header Size, should be 6 )
  if (buff[1] != 6) {
    std::cout << "ERROR : Block Header Size != 6 (" << buff[1] << ")"
              << std::endl;
    exit(1);
  }

  // 4th word of Data block ( BlockSize - BlockHeaderSize )
  tot_blk_num_word = buff[3] + buff[1];
  if (swt_mesg) {
    std::cout << "Data Block Size : " << buff[1] << " + " << buff[3] << " = "
              << tot_blk_num_word << "words" << std::endl;
  }

  // 5th word of Data block ( Block Number )
  if ((buff[4] != _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt) &&
      (_par_sorter.start_block)) {
    if (_par_sorter.switch_online == FALSE) {
      //      std::cout << "WARNING: Inconsistent Block Number : %d (should be
      //      %d)\n",buff[4],total_num_block);
      std::cout << "WARNING: Inconsistent Block Number : " << buff[4]
                << "(should be "
                << _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt
                << std::endl;
      _sca_sorter.data_block_cnt =
          buff[4] - 1; // header blockがあることを勝手に仮定
    }
  } else {
    if (swt_mesg) {
      std::cout << "Data Block, Block Number : " << buff[4] << "(" << buff[4]
                << ")" << std::endl;
    }
  }

  // 6th word of Data block ( Number of Events )
  blk_num_events = buff[5];
  if (swt_mesg) {
    std::cout << "Number of events in this Block :" << blk_num_events << "("
              << blk_num_events << ")" << std::endl;
  }

  // pre_wirechamber_ID = 0;
  // pre_wireID = 0;
  // hfnew -----

  // - - - - - event part - - - - -
  while (!buff[word_num_eventhead + 2]) {

    // event_num = 0;
    // event_num_pre = -1;

    flg_InputRegister_1st = 0;
    flg_InputRegister_2nd = 0;
    flg_FERA = 0;
    flg_FERET = 0;
    flg_v3377 = 0;
    flg_PCOS = 0;
    _CIrange = 0;

    // should be 1st word of event (Event Header ID)
    if (buff[word_num_eventhead] != 0xffdf) {
      std::cout << "Unknown event header ID  " << buff[word_num_eventhead]
                << "  (should be 0xffdf)" << std::endl;
      exit(1);
    } else {
      if (swt_mesg) {
        std::cout << "Event Header ID 0xffdf found." << std::endl;
      }
    }
    // 2nd word of event (Event Header Size)
    if (buff[word_num_eventhead + 1] != 6) {
      std::cout << "WARNING : Unknown Event header size : "
                << buff[word_num_eventhead + 1] << std::endl;
      exit(1);
    }
    // 3rd word of event (Event ID, should be 0x0000)
    if (buff[word_num_eventhead + 2]) {
      std::cout << "WARNING : Unknown Event ID (in BLD file) : "
                << buff[word_num_eventhead + 2] << std::endl;
      exit(1);
    }
    // 4th word of event (Event Size)
    event_size = buff[word_num_eventhead + 3];
    if (swt_mesg) {
      std::cout << "Event size :  "
                << "0x" << std::hex << event_size << " (" << std::dec
                << event_size << ")" << std::endl;
    }
    // 5th word of event (Event Number)
    if (buff[word_num_eventhead + 4] != num_event) {
      std::cout << "Inconsistent Event Number : " << num_event << " (should be "
                << buff[word_num_eventhead + 4] << ")" << std::endl;
      exit(1);
    }
    // 6th word of event (Number of Fields in This Event GRS->1 assumed)
    if (buff[word_num_eventhead + 5] != 1) {
      std::cout << "WARNING : Number of Fields > 1 :  "
                << buff[word_num_eventhead + 5] << " " << std::endl;
      exit(1);
    }

    // - - - - - Data Field - - - - -
    // 1st word of field (Field Header ID)
    if (buff[word_num_eventhead + 6] != 0xffcf) {
      std::cout << "Unknown event header ID " << buff[word_num_eventhead + 6]
                << " (should be 0xffcf)" << std::endl;
      exit(1);
    }
    // 2nd word of field (Field Header Size)
    if (buff[word_num_eventhead + 7] != 4) {
      std::cout << "WARNING : Unknown Event header size : "
                << buff[word_num_eventhead + 7] << std::endl;
      exit(1);
    }
    // 3rd word of field (Field ID) 0を仮定
    if (buff[word_num_eventhead + 8]) {
      std::cout << "WARNING : Unknown Field ID (in BLD file) : "
                << buff[word_num_eventhead + 8] << std::endl;
      exit(1);
    }
    // 4th word of field (Field Size)
    field_size = buff[word_num_eventhead + 9];
    if (swt_mesg) {
      std::cout << "Field size :  "
                << "0x" << std::hex << field_size << "  (" << std::dec
                << field_size << ")" << std::endl;
    }
    // field_size_chk = 0;
    if (!field_size) {
      std::cout << "orz " << field_size << std::endl;
      exit(1);
    }

    //  scaler only mode nara kokokara comment out?
    //  ======================================
    present_word_num = word_num_eventhead + 9;

    plastic_scintillator = {0};
    tof = {0};
    feret_data_channel = {0};
    feret_data_tdc = {0};
    fera_data_channel = {0};
    fera_data_adc = {0};
    v3377_tdc_X1 = {0};
    v3377_tdc_U1 = {0};
    v3377_tdc_X2 = {0};
    v3377_tdc_U2 = {0};

    while (present_word_num - (word_num_eventhead + 9) < field_size - 1) {

      if (swt_mesg) {
        std::cout << " Present Word Num " << present_word_num << "("
                  << word_num_eventhead << ")" << std::endl;
      }
      ++present_word_num;
      region_header = buff[present_word_num] >> 12;  // アタマ4bit
      region_size = 0x0fff & buff[present_word_num]; // 残り12bit

      if (region_header == 0x2) {

        if (!flg_InputRegister_1st) {
          flg_InputRegister_1st = 1;
        } else if (!flg_InputRegister_2nd) {
          flg_InputRegister_2nd = 1;
        }

        if (swt_mesg) {
          std::cout << "  Input Register Region header 0x2 found" << std::endl;
          std::cout << "  Input Register Region Size : " << region_size
                    << std::endl;
        }
        // Input Register Data
        ++present_word_num;
        if (flg_InputRegister_2nd) {
          _CIrange = buff[present_word_num] & 0x000f; // CI range?
          // fill_hist_CIrange(*_CIrange);
        }

        if (swt_mesg) {

          std::cout << "  Input Register data ("
                    << "0x" << std::hex << buff[present_word_num] << "("
                    << std::dec << buff[present_word_num] << ") ) [0-15]   :";
        }

        for (i = 0; i < 16; ++i) {
          InputRegister_data[i] = 0x01 & (buff[present_word_num] >> i);
          // CIrange
          if (swt_mesg) {
            std::cout << InputRegister_data[i];
          }
        }
        if (swt_mesg) {
          std::cout << std::endl;
        }
      } // - - - - - FERA part (ADC) (region header:0xd) - - - - -
      else if (region_header == 0xd) {
        if (!flg_FERA)
          flg_FERA = 1;

        if (swt_mesg) {
          std::cout << "  FERA Region header 0xd found" << std::endl;
          std::cout << "  FERA Region Size :" << region_size << std::endl;
        }
        // Initialize
        for (i = 0; i < 16; ++i) {
          fera_data_channel[i] = 0;
          fera_data_adc[i] = 0;
        }
        // 2nd word of FERA data part (FERA Header)
        ++present_word_num;
        if (!(0x8000 & buff[present_word_num])) { // アタマ1bit
          std::cout << "WARNING : Inconsistent FERA Header (1st bit is 0) "
                    << (buff[present_word_num] >> 15) << " -> Accepted"
                    << std::endl;
          // exit(1);
        }
        fera_word_count =
            (0x7800 & buff[present_word_num]) >> 11; // 2-5の4bit
        if (!fera_word_count) {
          fera_word_count = 16;
        }
        fera_virtualstation_number =
            get_fera_virtualstation_number(buff[present_word_num]);
        if (0x0700 & buff[present_word_num]) { // 6-8の3bit
          std::cout << "WARNING : Inconsistent FERA Header (6-8bit != 000) "
                    << (buff[present_word_num] >> 15) << " -> Accepted"
                    << std::endl;
          // exit(1);
        }
        if (swt_mesg) {
          std::cout << "  FERA Word Count    : " << fera_word_count
                    << std::endl;
          std::cout << "  FERA Virtual Station Number : "
                    << fera_virtualstation_number << std::endl;
        }
        // fera_word_countはregion_size-1に等しいはず
        if (fera_word_count != region_size - 1) {
          std::cout << "WARNING : Inconsistent FERA word count : "
                    << fera_word_count << " (should be " << region_size - 1
                    << ") -> Accepted" << std::endl;
        }

        //	for(i=0;i<fera_word_count;++i){
        for (i = 0; i < region_size - 1; ++i) {
          ++present_word_num;
          if (0x8000 & buff[present_word_num]) {
            std::cout << "WARNING : Inconsistent FERA DATA : "
                      << (buff[present_word_num] >> 15) << " (should be "
                                                           "0) -> Accepted"
                      << std::endl;
            // exit(1);
          }
          fera_data_channel[i] =
              (0x7800 & buff[present_word_num]) >> 11;        // 2-5の4bit
          fera_data_adc[i] = 0x07ff & buff[present_word_num]; // 以下11bit
          //	  fill_hist_fera(fera_data_adc[i],fera_data_channel[i],fera_virtualstation_number);
          if (swt_mesg) {
            std::cout << "  FERA Data Channel/ADC" << i << "  : "
                      << fera_data_channel[i] << "/" << fera_data_adc[i]
                      << std::endl;
          }
          if (fera_virtualstation_number == FERA_PS_VS &&
              fera_data_channel[i] == FERA_PS_CH_1L) {
            plastic_scintillator[0] = fera_data_adc[i];
          } else if (fera_virtualstation_number == FERA_PS_VS &&
                     fera_data_channel[i] == FERA_PS_CH_1R) {
            plastic_scintillator[1] = fera_data_adc[i];
          } else if (fera_virtualstation_number == FERA_PS_VS &&
                     fera_data_channel[i] == FERA_PS_CH_2L) {
            plastic_scintillator[2] = fera_data_adc[i];
          } else if (fera_virtualstation_number == FERA_PS_VS &&
                     fera_data_channel[i] == FERA_PS_CH_2R) {
            plastic_scintillator[3] = fera_data_adc[i];
          }
        }
      }

      // - - - - - FERET part (TDC) (region header:0xe) - - - - -
      else if (region_header == 0xe) {
        if (!flg_FERET)
          flg_FERET = 1;

        if (swt_mesg) {
          std::cout << "  FERET Region header 0xe found" << std::endl;
          std::cout << "  FERET Region Size : " << region_size << std::endl;
        }
        // 2nd word of FERET data part (FERET Header)
        ++present_word_num;
        if (!(0x8000 & buff[present_word_num])) {
          std::cout << "WARNING : Inconsistent FERET Header (1st bit is 0) -> "
                    << (buff[present_word_num] >> 15) << std::endl;
          exit(1);
        }
        feret_word_count = (0x7800 & buff[present_word_num]) >> 11;
        if (!feret_word_count)
          feret_word_count = 16;
        feret_virtualstation_number = 0x00ff & buff[present_word_num];

        if ((feret_virtualstation_number != 0x81) &&
            (feret_virtualstation_number != 0xb1) &&
            (feret_virtualstation_number != 0xb2)) {
          std::cout << "WARNING : FERET Virtual Station Number should be 0x81, "
                       "82 or 91."
                    << feret_virtualstation_number << std::endl;
          std::cout << "          (Ignored)" << std::endl; // exit(1);
        }
        if (0x0700 & buff[present_word_num]) { // 6-8の3bit
          std::cout << "WARNING : Inconsistent FERET Header (6-8bit != 000) "
                    << (buff[present_word_num] >> 15) << " -> Accepted"
                    << std::endl;
          // exit(1);
        }
        if (swt_mesg) {
          std::cout << "  FERET Word Count    : " << feret_word_count
                    << std::endl;
          std::cout << "  FERET Virtual Station Number : "
                    << feret_virtualstation_number << std::endl;
        }
        // feret_word_countはregion_size-1に等しいはず
        if (feret_word_count != region_size - 1) {
          std::cout << "WARNING : Inconsistent FERET word count : "
                    << feret_word_count << " (should be " << region_size - 1
                    << " -> Accepted" << std::endl;
        }

        //	for(i=0;i<feret_word_count;++i){
        for (i = 0; i < region_size - 1; ++i) {
          ++present_word_num;
          if (0x8000 & buff[present_word_num]) {
            std::cout << "WARNING : Inconsistent FERET DATA : "
                      << (buff[present_word_num] >> 15) << " (should be 0)"
                      << std::endl;
            std::cout << "          (Anyway accepted)" << std::endl; // exit(1);
          }
          feret_data_channel[i] =
              (0x7800 & buff[present_word_num]) >> 11; // 2-5の4bit
          feret_data_tdc[i] = 0x00ff & buff[present_word_num]; // 下8bit

          // offset
          feret_offset[0] = 81;
          feret_offset[1] = 151;
          feret_offset[2] = 110;
          feret_offset[3] = 83;
          for (j = 0; j <= 3; ++j) {
            feret_data_tdc[j] += feret_offset[j];
            if (feret_data_tdc[j] > 256)
              feret_data_tdc[j] -= 256;
          }

          if (feret_virtualstation_number == FERET_PS_VS &&
              feret_data_channel[i] == FERET_PS_CH_1L)
            tof[0] = feret_data_tdc[i]; // Plastic 1L (low momentum side)
          else if (feret_virtualstation_number == FERET_PS_VS &&
                   feret_data_channel[i] == FERET_PS_CH_1R)
            tof[1] = feret_data_tdc[i]; // Plastic 1R
          else if (feret_virtualstation_number == FERET_PS_VS &&
                   feret_data_channel[i] == FERET_PS_CH_2L)
            tof[2] = feret_data_tdc[i]; // Plastic 2L
          else if (feret_virtualstation_number == FERET_PS_VS &&
                   feret_data_channel[i] == FERET_PS_CH_2R)
            tof[3] = feret_data_tdc[i]; // Plastic 2R
          else if (feret_virtualstation_number == FERET_PS_VS &&
                   feret_data_channel[i] == FERET_PS_CH_RF)
            tof[4] = feret_data_tdc[i]; // TOF

          if (swt_mesg) {
            std::cout << "  FERET Data Channel/TDC  " << i << " : "
                      << feret_data_channel[i] << "/" << feret_data_tdc[i]
                      << std::endl;
          }
          /*fill_hist_feret(feret_data_tdc[i], feret_data_channel[i],
                          feret_virtualstation_number);*/
        }
      }

      else if (region_header == 0x7) {
        if (!flg_v3377)
          flg_v3377 = 1;

        v3377_module_ID = 0xffff; // チェック用ありえない初期値
        if (swt_mesg) {
          std::cout << "  VDC Region header 0x7 found" << std::endl;
          std::cout << "  VDC Region Size : " << region_size << std::endl;
        }
        for (i = 0; i < region_size; ++i) {

          // 2nd word of VDC data part (3377 Header)
          ++present_word_num;
          if ((0x8000 & buff[present_word_num])) {
            // 2bit目 0:Single Word Format,1:Double Word Format ->
            // 0を仮定
            if (!(0x4000 & buff[present_word_num]) >> 14) {
              std::cout << "WARNING : 3377 Word Format should be single -> "
                           "Accepted"
                        << std::endl;
              //	      exit(1);
            } else {
              if (swt_mesg) {
                std::cout << "  3377 Word format   : Single" << std::endl;
              }
            } // 3-5の3bit Event number
            v3377_event_number = (0x3800 & buff[present_word_num]) >> 11;
            if (swt_mesg)
              std::cout << "  3377 Event Number    : " << v3377_event_number
                        << std::endl;
            // 6bit目 0:Leading Edge only, 1:Both Leading and Trailing
            // Edge 意味は知らない -> 0を仮定
            if (((0x0400 & buff[present_word_num]) >> 10)) {
              std::cout << "WARNING : 3377 Both Leading and Trailing Edge mode "
                           "found -> Accepted"
                        << std::endl;
              //	      exit(1);
            } else {
              if (swt_mesg)
                std::cout << "  3377 Leading/Trailing Edge mode    : Leading "
                             "Edge Only"
                          << std::endl;
            }
            // 7,8の2bit 0:0.5ns,1:1.0ns,2:2.0ns,3:4.0ns -> 1を仮定
            if (((0x0300 & buff[present_word_num]) >> 8) != 1) {
              std::cout << "WARNING : 3377 Time resolution should be 1.0ns. ("
                        << pow(2, ((0x0300 & buff[present_word_num]) >> 8) - 1)
                        << "ns found)" << std::endl;
              //	      exit(1);
            } else {
              if (swt_mesg)
                std::cout << "  3377 Time Resolution    : 1.0ns" << std::endl;
            }
            // 9-12bit -> 0000:GR-Front-X, 0010:GR-Front-U, 0100:GR-Rear-X,
            // 0110:GR-Rear-U
            // hfnew (for multihit) -----
            // if (wirechamber_ID)
            // pre_wirechamber_ID = wirechamber_ID;
            // hfnew (for multihit) -----
            if ((0x00f0 & buff[present_word_num]) == 0x00) {
              wirechamber_ID = 1;
            } else if ((0x00f0 & buff[present_word_num]) == 0x20) {
              wirechamber_ID = 2;
            } else if ((0x00f0 & buff[present_word_num]) == 0x40) {
              wirechamber_ID = 3;
            } else if ((0x00f0 & buff[present_word_num]) == 0x60) {
              wirechamber_ID = 4;
            } else {
              std::cout << "WARNING : Invalid Wirechamber ID : "
                        << (0x00f0 & buff[present_word_num]) << " -> Discarded"
                        << std::endl;
              ++_par_sorter.flg_discard_event;
              //	      exit(1);
            }
            // 最後の4bit module ID
            v3377_module_ID = 0x000f & buff[present_word_num];
            // hfchk -----
            //	    std::cout << "chamber %d, module ID
            //%d\n",wirechamber_ID,v3377_module_ID);
            // std::cout << "orz 3377 wirechamber / module ID -> %d /
            // %d\n",wirechamber_ID,v3377_module_ID);
            // hfchk -----

            if (wirechamber_ID == 1 || wirechamber_ID == 3) {
              if (v3377_module_ID < 0 || v3377_module_ID >= 6) {
                std::cout << "ERROR : Invalid 3377 module ID "
                          << v3377_module_ID
                          << " (Wirechamber ID : " << wirechamber_ID
                          << ") -> Discarded" << std::endl;
                ++_par_sorter.flg_discard_event;
                //		exit(1);
              }
            } else if (wirechamber_ID == 2 || wirechamber_ID == 4) {
              if (v3377_module_ID < 0 || v3377_module_ID >= 7) {
                std::cout << "ERROR : Invalid 3377 module ID "
                          << v3377_module_ID
                          << " (Wirechamber ID : " << wirechamber_ID
                          << ") -> Discarded" << std::endl;
                ++_par_sorter.flg_discard_event;
                //		exit(1);
              }
            }

            if (swt_mesg)
              std::cout << "  3377 Module ID : " << v3377_module_ID
                        << std::endl;

          } else {
            // Data part
            if (v3377_module_ID == 0xffff) {
              std::cout
                  << "ERROR : 3377 Data Word without 3377 Header -> Discarded"
                  << std::endl;
              ++_par_sorter.flg_discard_event;
              //	      exit(1);
            }

            v3377_channel = (0x7c00 & buff[present_word_num]) >> 10;
            if (v3377_channel < 0 || v3377_channel >= 32) {
              std::cout << "ERROR : Invalid 3377 channel " << v3377_channel
                        << " (should be 0-31 ) -> Discarded" << std::endl;
              ++_par_sorter.flg_discard_event;
              //	      exit(1);
            }
            v3377_tdc_out = 0x03ff & buff[present_word_num];
            if (v3377_tdc_out < 0 || v3377_tdc_out >= 1024) {
              std::cout << "ERROR : Invalid 3377 output " << v3377_tdc_out
                        << " (should be 0-1023) -> Discarded" << std::endl;
              exit(1);
            }

            // hfnew (for multihit) -----
            // pre_wireID = wireID;
            // hfnew (for multihit) -----
            wireID = v3377_module_ID * 32 + v3377_channel;
            if ((wirechamber_ID == 1 || wirechamber_ID == 3) &&
                (wireID < 0 || wireID >= 192)) {
              std::cout << "ERROR : Inconsistent 3377 wire ID " << wireID
                        << " (wirechamber_ID: " << wirechamber_ID
                        << ") -> Discarded" << std::endl;
              ++_par_sorter.flg_discard_event;
              //	      exit(1);
            } else if ((wirechamber_ID == 2 || wirechamber_ID == 4) &&
                       (wireID < 0 || wireID >= 208)) {
              std::cout << "ERROR : Inconsistent 3377 wire ID " << wireID
                        << " (wirechamber_ID: " << wirechamber_ID
                        << ") -> Discarded" << std::endl;
              ++_par_sorter.flg_discard_event;
              //	      exit(1);
            }
            // ----- wireID<150 は3He+を省くため -----
            if (wirechamber_ID == 1) {
              v3377_tdc_X1[wireID] = v3377_tdc_out;
            } // GR X1
            else if (wirechamber_ID == 2) {
              v3377_tdc_U1[wireID] = v3377_tdc_out;
            } // GR U1
            else if (wirechamber_ID == 3) {
              v3377_tdc_X2[wireID] = v3377_tdc_out;
            } // GR X2
            else if (wirechamber_ID == 4) {
              v3377_tdc_U2[wireID] = v3377_tdc_out;
            } // GR U2

            if (swt_mesg)
              std::cout << "  3377 Channel : " << v3377_channel << std::endl;
            if (swt_mesg)
              std::cout << "  3377 TDC out : " << v3377_tdc_out << std::endl;
          }
        }
      }

      // - - - - - PCOS part (region header:0xa) - - - - -
      else if (region_header == 0xa) {
        std::cout << "WARNING : PCOS region found. -> Ignored" << std::endl;
        // exit(1);

        std::cout << "orz -> " << buff[present_word_num] << std::endl;

        //	present_word_num += region_size+1;
        if (!flg_PCOS)
          flg_PCOS = 1;
      }

      else {
        std::cout << "ERROR : Unknown Region header ID " << region_header
                  << std::endl;

        // for test of online mode ---------
        for (unsigned k = present_word_num; k < present_word_num + 5; ++k) {
          std::cout << buff[k * 8] << " " << buff[k * 8 + 1] << " "
                    << buff[k * 8 + 2] << " " << buff[k * 8 + 3] << " "
                    << buff[k * 8 + 4] << " " << buff[k * 8 + 5] << " "
                    << buff[k * 8 + 6] << " " << buff[k * 8 + 7] << std::endl;
        }
        // ---------------------------------

        exit(1);
      }
    }

    // --- moved to user_analysis() ---
    // Plot wire information histograms
    // (Because of multi-hit events, "read-one-wire->plot" procedure is not
    // proper)
    //    fill_hist_wire(v3377_tdc_X1,v3377_tdc_U1,v3377_tdc_X2,v3377_tdc_U2);

    // Data field structure check
    flg_field_structure = flg_InputRegister_1st + 2 * flg_FERA + 4 * flg_FERET +
                          8 * flg_InputRegister_2nd + 16 * flg_v3377 +
                          32 * flg_PCOS;
    /*fill_hist_system(flg_field_structure);*/

    // ----- flg_field_structure ----
    //	 1st Input Regst. -> +1
    //	 FERA             -> +2
    //	 FERET            -> +4
    //	 2nd Input Regst. -> +8
    //	 VDC 3377         -> +16
    //	 PCOS             -> +32
    //  (GR single data should be +31)
    // ---------------------------------

    /* fill_hist_scintillator_tof(plastic_scintillator, tof);*/

    // 鳴ったwire数を数える
    num_wire_x1 = 0;
    num_wire_u1 = 0;
    num_wire_x2 = 0;
    num_wire_u2 = 0;

    for (i = 0; i < 192; ++i) {
      if (v3377_tdc_X1[i])
        ++num_wire_x1;
      if (v3377_tdc_X2[i])
        ++num_wire_x2;
    }
    for (i = 0; i < 208; ++i) {
      if (v3377_tdc_U1[i])
        ++num_wire_u1;
      if (v3377_tdc_U2[i])
        ++num_wire_u2;
    }

    /*fill_hist_numwire(num_wire_x1, num_wire_u1, num_wire_x2, num_wire_u2);*/

    // for switch_tdc_optimize test --------------------------------------
    //    if(_par_sorter->switch_tdc_optimize==TRUE){
    //      for(i=0;i<192;++i){ _wiretdc_x1[i]=v3377_tdc_X1[i];
    //      _wiretdc_x2[i]=v3377_tdc_X2[i]; }
    //      for(i=0;i<208;++i){ _wiretdc_u1[i]=v3377_tdc_U1[i];
    //      _wiretdc_u2[i]=v3377_tdc_U2[i]; }
    //    }
    // -------------------------------------------------------------------

    if (flg_field_structure == 31 && !_par_sorter.flg_discard_event) {

      // std::cout << "user Analysis" << std::endl;
      s_user.user_analysis(
          v3377_tdc_X1, v3377_tdc_U1, v3377_tdc_X2, v3377_tdc_U2,
          plastic_scintillator, tof, _drifttable_x1, _drifttable_u1,
          _drifttable_x2, _drifttable_u2, num_wire_x1, num_wire_u1, num_wire_x2,
          num_wire_u2, _par_sorter, _sca_sorter, _par_hist, s_root, s_treedata);

      // std::cout << s_treedata.t_eventID << std::endl;

    } else if (_par_sorter.flg_discard_event) {
      ++_par_sorter.num_discard_event;
      std::cout << "Info : Event discarded, block "
                << _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt
                << std::endl;
    }

    // hfnew -----
    // 読んだword数とfield_sizeをチェキ
    if (present_word_num + 1 != word_num_eventhead + field_size + 10) {
      std::cout << "ERROR : All data were not read? (read : "
                << present_word_num + 1
                << " <-> field size : " << word_num_eventhead + field_size + 10
                << std::endl;
      exit(1);
    }
    // hfnew -----

    //  scaler only mode nara kokomade comment out?
    //  ======================================

    ++num_event;
    word_num_eventhead += field_size + 10;

    ++_sca_sorter.event_cnt;
  }
  total_num_event += num_event;

  // ----------------------------------------------------
  // Block end event (Scaler block)
  // should be 1st word of event (Event Header ID)
  if (buff[word_num_eventhead] != 0xffdf) {
    std::cout << "Unknown event header ID " << buff[word_num_eventhead]
              << " (should be 0xffdf) in Block End event." << std::endl;
    exit(1);
  } else {
    if (swt_mesg)
      std::cout << "Event Header ID 0xffdf found in Block End event."
                << std::endl;
  }
  // 2nd word of event (Event Header Size) -> 6を仮定
  if (buff[word_num_eventhead + 1] != 6) {
    std::cout << "WARNING : Unknown Event header size : "
              << buff[word_num_eventhead + 1] << std::endl;
    exit(1);
  }
  // 3rd word of event (Event ID, should be 0x0001)
  if (buff[word_num_eventhead + 2] != 0x0001) {
    std::cout << "WARNING : Unknown Event ID (in Block End event) : "
              << buff[word_num_eventhead + 2] << std::endl;
    exit(1);
  }
  // 4th word of event (Event Size)
  event_size = buff[word_num_eventhead + 3];
  if (swt_mesg)
    std::cout << "Event size : " << event_size << " (" << event_size << ")"
              << std::endl;
  // 5th word of event (Event Number)
  if (buff[word_num_eventhead + 4] != num_event) {
    std::cout << "Inconsistent Event Number : " << num_event << " (should be "
              << buff[word_num_eventhead + 4] << ")" << std::endl;
    exit(1);
  }
  // 6th word of event (Number of Fields in This Event GRS->1 assumed)
  if (buff[word_num_eventhead + 5] != 1) {
    std::cout << "WARNING : Number of Fields > 1 : "
              << buff[word_num_eventhead + 5] << std::endl;
    exit(1);
  }
  // 1st word of field (Field Header ID)
  if (buff[word_num_eventhead + 6] != 0xffcf) {
    std::cout << "Unknown event header ID " << buff[word_num_eventhead + 6]
              << "(should be 0xffcf)" << std::endl;
    exit(1);
  }
  // 2nd word of field (Field Header Size) -> 4を仮定
  if (buff[word_num_eventhead + 7] != 4) {
    std::cout << "WARNING : Unknown Event header size : "
              << buff[word_num_eventhead + 7] << std::endl;
    exit(1);
  }
  // 3rd word of field (Field ID) -> 0を仮定
  if (buff[word_num_eventhead + 8]) {
    std::cout << "WARNING : Unknown Field ID (in BLD file) : "
              << buff[word_num_eventhead + 8] << std::endl;
    exit(1);
  }
  // 4th word of field (Field Size)
  field_size = buff[word_num_eventhead + 9];
  if (swt_mesg)
    std::cout << "Field size : " << field_size << " (" << field_size << ")"
              << std::endl;
  ;
  // field_size_chk = 0;

  // -----------------------
  /*
  if(!field_size){ std::cout << "orz ZERO field size! %04x\n",field_size);
  exit(1); }
  if(field_size!=0x0088){
    std::cout << "orz block %d\n",total_num_block);
    exit(1);
  }
  */
  if (field_size != 0x0088) {
    std::cout << "WARNING : Inconistent field size of " << field_size
              << " (blk "
              << _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt
              << "), 0x0088 assumed." << std::endl;

    field_size = 0x0088;
  }
  // -----------------------

  // present...は現在読んでるword番号(0から始まる)ループに入ってすぐに++するので+9
  present_word_num = word_num_eventhead + 9;

  sca_num = 0;
  while (present_word_num - (word_num_eventhead + 9) < field_size - 1) {
    ++present_word_num;
    region_header = buff[present_word_num] >> 12;  // アタマ4bit
    region_size = 0x0fff & buff[present_word_num]; // 残り12bit

    // - - - - - Input Register part (region header:0x2) - - - - -
    if (region_header == 0x2) {
      if (swt_mesg) {
        std::cout << "  Input Register Region header (0x2) found" << std::endl;
        std::cout << "  Input Register Region Size : " << region_size
                  << std::endl;
      }
      // Input Register Data (0x8000を仮定)
      ++present_word_num;
      if (buff[present_word_num] != 0x8000) {
        if (swt_mesg) {
          std::cout << "WARNING : Unexpected Input Register data in Block End "
                       "Event : "
                    << buff[present_word_num] << std::endl;
        }
        exit(1);
      }
    }
    // - - - - - Scaler part (region header:0x6) - - - - -
    else if (region_header == 0x6) {
      if (swt_mesg) {
        std::cout << "  SCALER Region header 0x6 found" << std::endl;
        std::cout << "  SCALER Region Size : " << region_size << std::endl;
      }
      for (i = 0; i < 16; ++i) {
        //	scaler[sca_num][i] =
        // buff[present_word_num+(2*i-1)]|(buff[present_word_num+(2*i)]<<16);
        //	scaler[sca_num][i] =
        // buff[present_word_num+(2*i+1)]|(buff[present_word_num+(2*i+2)]<<16);
        //	total_scaler[sca_num][i] += scaler[sca_num][i];

        if (swt_mesg) {
          std::cout << "  Scaler/Ch=" << sca_num << "/" << i << " "
                    << buff[present_word_num + (2 * i + 1)] << " "
                    << buff[present_word_num + (2 * i + 2)] << "(" << &_scaler_0
                    << "," << &_scaler_1 << "," << &_scaler_2 << ","
                    << &_scaler_3 << ")" << std::endl;
        }

        if (sca_num == 0) {
          _scaler_0[i] = buff[present_word_num + (2 * i + 1)] |
                         (buff[present_word_num + (2 * i + 2)] << 16);
          //	  total_scaler[sca_num][i] += _scaler_0[i];
          _sca_sorter.data_scaler[sca_num][i] += _scaler_0[i];
        } else if (sca_num == 1) {
          _scaler_1[i] = buff[present_word_num + (2 * i + 1)] |
                         (buff[present_word_num + (2 * i + 2)] << 16);
          //	  total_scaler[sca_num][i] += _scaler_1[i];
          _sca_sorter.data_scaler[sca_num][i] += _scaler_1[i];
        } else if (sca_num == 2) {
          _scaler_2[i] = buff[present_word_num + (2 * i + 1)] |
                         (buff[present_word_num + (2 * i + 2)] << 16);
          //	  total_scaler[sca_num][i] += _scaler_2[i];
          _sca_sorter.data_scaler[sca_num][i] += _scaler_2[i];
        } else if (sca_num == 3) {
          _scaler_3[i] = buff[present_word_num + (2 * i + 1)] |
                         (buff[present_word_num + (2 * i + 2)] << 16);
          //	  total_scaler[sca_num][i] += _scaler_3[i];
          _sca_sorter.data_scaler[sca_num][i] += _scaler_3[i];
        }
      }
      ++sca_num;

      if (sca_num == 4) {
        /*fill_hist_scaler(
            _scaler_0, _scaler_1, _scaler_2,
            _scaler_3);*/ // after reading all 4 scalers, histogram will be
                            // filled
      }
      if (swt_mesg) {
        std::cout << "Region size: " << present_word_num << std::endl;
      }

      present_word_num += region_size;
    }
    // - - - - - Check-sum part (region header:0xf) 現状チェックしていない
    // - - - - -
    else if (region_header == 0xf) {
      if (swt_mesg) {
        std::cout << "  Check-Sum Region header 0xf found" << std::endl;
        std::cout << "  Check-Sum Region Size : " << region_size << std::endl;
      }
    } else {
      if (_par_sorter.switch_online == FALSE) {
        std::cout << "WARNING : Unknown Region header ID " << region_header
                  << " in "
                  << _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt
                  << "th Block End Event" << std::endl;

        //      exit(1);
      }
    }
  }
  ++num_event;
  // end of scaler event  ----------------------------------------------------

  if (swt_mesg) {
    std::cout << "Scaler output Block "
              << _sca_sorter.data_block_cnt + _sca_sorter.hf_block_cnt
              << std::endl;
    for (i = 0; i < 16; ++i) {
      std::cout << " " << i << " : " << std::endl;
      for (j = 0; j < 4; ++j) {
        //	std::cout << "%06d ",total_scaler[j][i]);
        std::cout << _sca_sorter.data_scaler[j][i] << " ";
      }
      std::cout << std::endl;
    }
  }

  if (num_event != buff[5]) {
    std::cout
        << "WARNING : Number of events is not consistent with Block Header. "
        << num_event << " " << buff[5] << std::endl;
  } else {
    if (swt_mesg) {
      std::cout << "  " << num_event << " Events found" << std::endl;
    }

    ++_sca_sorter.data_block_cnt;
  }
}
