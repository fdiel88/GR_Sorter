
#include <fstream>
#include <iostream>
#include <string>

#include <ctime>

#include "sorter_const.h"
#include "sorter_util.h"

std::u16streampos Sorter_util::get_filesize2(std::string bldfile) {

  std::u16streampos fpos;

  std::ifstream myfile(bldfile, std::ifstream::binary);

  if (!myfile.is_open()) {
    std::cout << "ERROR : Open BLD file (" << bldfile
              << ") failed in get_filesize()." << std::endl;
    exit(1);

  } else {

    // std::cout << std::ios::end << " " << myfile.seekg(0) << std::endl;

    if (!myfile.seekg(0, myfile.end)) {

      std::cout << "ERROR : fseek failed in get_filesize() orz" << std::endl;
      exit(0);
    }

    fpos = myfile.tellg();
    std::cout << fpos << std::endl;

    myfile.close();

    return fpos;
  }
  return 0;
}

/*std::time_t Sorter_util::getTime(std::time_t startTime){




        return gmtime(std::time(nullptr)-startTime):

        }*/
