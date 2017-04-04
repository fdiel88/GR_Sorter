#include <iostream>

void h12ascii(TTree *tree, std::string opt, std::string out_f) {

  std::ofstream output_file;
  output_file.open(out_f);

  tree->Draw("X1posC>>hX1pos", opt.c_str());

  for (int i = 0; i < hX1pos->GetNbinsX(); ++i) {
    output_file << i << " " << hX1pos->GetBinContent(i) << endl;
  }
  output_file.close();
}
