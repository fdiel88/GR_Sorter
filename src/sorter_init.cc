#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "sorter_const.h"
#include "sorter_histpar.h"
#include "sorter_init.h"
#include "sorter_par.h"
#include "sorter_scaler.h"
#include "sorter_user.h"

int Sorter_init::get_blocksize_check_byteswap(std::string bldfile,
                                              int &_switch_byteswap,
                                              struct parameters &_par_sorter) {

  int blocksize = 0;

  std::vector<std::uint16_t> words;
  std::vector<std::uint16_t> words_size;

  words_size.push_back(BL_WORD_16);
  words_size.push_back(BL_WORD_24);
  words_size.push_back(BL_WORD_32);
  words_size.push_back(BL_WORD_40);
  words_size.push_back(BL_WORD_48);
  words_size.push_back(9999);

  std::ifstream myfile(bldfile, std::ifstream::binary);
  std::uint16_t n;
  std::uint16_t n_2;

  if (myfile.is_open()) {

    myfile.seekg(0);
    myfile.seekg(BL_WORD_16 * 2);
    myfile.read(reinterpret_cast<char *>(&n), sizeof n);
    words.push_back(n);

    myfile.seekg(0);
    myfile.seekg(BL_WORD_24 * 2);
    myfile.read(reinterpret_cast<char *>(&n), sizeof n);
    words.push_back(n);

    myfile.seekg(0);
    myfile.seekg(BL_WORD_32 * 2);
    myfile.read(reinterpret_cast<char *>(&n), sizeof n);
    words.push_back(n);

    myfile.seekg(0);
    myfile.seekg(BL_WORD_40 * 2);
    myfile.read(reinterpret_cast<char *>(&n), sizeof n);
    words.push_back(n);

    myfile.seekg(0);
    myfile.seekg(BL_WORD_48 * 2);
    myfile.read(reinterpret_cast<char *>(&n), sizeof n);
    words.push_back(n);

    myfile.seekg(0);
    myfile.seekg(16);
    myfile.read(reinterpret_cast<char *>(&n), sizeof n);
    words.push_back(n);

    for (unsigned i = 0; i < words.size(); ++i) {

      // std::cout << words[i] << std::endl;
      if (words[i] == 0xffff) {
        blocksize = words_size[i];
        break;
      }
    }

    std::cout << "Blocksize: " << blocksize << std::endl;

    //=============================================
    // check if byteswap is needed

    myfile.seekg(0);
    myfile.seekg(2);

    myfile.read(reinterpret_cast<char *>(&n), sizeof n);

    myfile.seekg(0);
    myfile.seekg(4);

    myfile.read(reinterpret_cast<char *>(&n_2), sizeof n_2);

    if (n == 0x0600)
      _switch_byteswap = TRUE; // byteswap needed
    else if (n == 0x0006)
      _switch_byteswap = FALSE;
    else if (n == 0x0000) {
      std::cout << " unknown buff_word[1] of " << n_2
                << " in get_blocksize_check_byteswap() "
                   "found. Variable block size?\n"
                << std::endl;
    } else {
      std::cout << " unknown buff_word[1] of " << n_2
                << " in get_blocksize_check_byteswap()." << std::endl;

      exit(1);
    }

    myfile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return blocksize;
}
