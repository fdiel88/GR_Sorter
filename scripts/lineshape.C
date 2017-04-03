#include <string>

#include "TMatrixD.h"

void line_shape(TTree *tree, std::string b_opt, std::string opt,
                std::string inp_f, int th_o, int x_o) {

  TCanvas *c1 = new TCanvas("c2", "Test", 800, 600);

  vector<string> input;
  string line;

  // open input file
  ifstream myfile(inp_f);

  vector<vector<double>> out_list;
  int cnt_l = 0;

  double peak_pos = 0;
  double peak_width = 0;

  double lo_th = 0;
  double hi_th = 0;
  double steps = 0;

  int binMin = 0;
  int binMax = 0;

  double sliceBinWidth = 0;
  double sliceUserWidth = 0;

  double delay = 100000;

  double hist_ang_lo;
  double hist_ang_hi;
  std::string par_name;
  std::string conf_par_name;
  std::string hist_name;

  TH2F *hist;

  if (b_opt == "-th") {

    hist_ang_lo = -1.1;
    hist_ang_hi = 1.1;
    par_name = "thetaSCAT";
    conf_par_name = "XCOR_TH_PAR";
    hist_name = "hThSCATvsX1";

    if (hThSCATvsX1) {
      hist = hThSCATvsX1;
    } else {
      hist = new TH2F("hThSCATvsX1", "SCATTERING Theta vs X position", 3200,
                      -600., 600., 600, -3., 3.);
    }

  } else if (b_opt == "-ph") {
    hist_ang_lo = -3.0;
    hist_ang_hi = 3.0;
    par_name = "phiSCAT";
    conf_par_name = "XCOR_PH_PAR";
    hist_name = "hPhSCATvsX1";
    if (hPhSCATvsX1) {
      hist = hPhSCATvsX1;
    } else {
      hist = new TH2F("hPhSCATvsX1", "SCATTERING Phi vs X position", 3200,
                      -600., 600., 600, -4., 4.);
    }
  } else {
    std::cout << "Option not defined: killing process." << std::endl;
    return;
  }

  std::string canvas_name;

  if (myfile.is_open()) {

    while (getline(myfile, line)) {

      std::vector<std::string> input;

      istringstream iss(line);

      copy(istream_iterator<std::string>(iss), istream_iterator<std::string>(),
           back_inserter(input));

      // std::cout << "processing line" << std::endl;

      peak_pos = stod(input[0]);
      peak_width = stod(input[1]);

      lo_th = stod(input[2]);
      hi_th = stod(input[3]);
      steps = stod(input[4]);

      canvas_name = "c" + to_string(cnt_l);

      TCanvas *c2 = new TCanvas(canvas_name.c_str(), "Test", 800, 600);

      c2->Update();
      tree->Draw((par_name + ":X1pos>>" + hist_name).c_str(), opt.c_str(),
                 "col");

      hist->Draw("colz");
      c2->Update();

      gStyle->SetPalette(55);
      c2->Show();
      c2->Update();
      c2->Divide(1, 2);
      c2->cd(1);

      gPad->Modified();
      hist->Draw("COLZ");
      hist->GetXaxis()->SetRangeUser(peak_pos - 20, peak_pos + 40);
      c2->Update();

      gSystem->ProcessEvents();

      c2->cd(2);

      TH1D *projX;

      TF1 *gaus = new TF1("func", "gaus(0)", 0, 10);
      gaus->SetParameters(1, peak_pos, peak_width);

      binMin = hist->GetYaxis()->FindBin(lo_th);
      binMax = hist->GetYaxis()->FindBin(hi_th);

      sliceBinWidth = (binMax - binMin) / steps;
      sliceUserWidth = (hi_th - lo_th) / steps;

      double x[(int)steps];
      double y[(int)steps];
      double height[(int)steps];

      for (int i = 0; i < steps; ++i) {
        projX = hist->ProjectionX("px", i * sliceBinWidth + binMin,
                                  (i + 1) * sliceBinWidth + binMin, "");

        projX->GetXaxis()->SetRangeUser(peak_pos - 20, peak_pos + 40);
        projX->Draw();

        projX->Fit("func", "Q", "", gaus->GetParameter(1) - peak_width,
                   gaus->GetParameter(1) + peak_width);

        height[i] = gaus->GetParameter(0);

        if ((gaus->GetParameter(1)) > -600) {

          projX->Draw("");
          c2->Update();

          x[i] = gaus->GetParameter(1);
          y[i] = lo_th + i * sliceUserWidth + sliceUserWidth / 2;

          gSystem->ProcessEvents();
          gaus->SetParameters(gaus->GetParameter(0), gaus->GetParameter(1),
                              gaus->GetParameter(2));

        } else {
          c2->Update();
          x[i] = x[i - 1];
          y[i] = lo_th + i * sliceUserWidth + sliceUserWidth / 2;
          gSystem->ProcessEvents();
          gaus->SetParameters(height[i - 1], x[i], 2 * peak_width);
        }

        // projX->Delete();
      }

      TGraph *gr1 = new TGraph(steps, y, x);

      gr1->Draw("AC*");

      stringstream sstm;
      sstm << "pol" << th_o;
      string polS = sstm.str();

      stringstream sstm2;
      sstm2 << "Peak at x = " << peak_pos << " fitted with Pol " << 6;
      string graphTitle = sstm2.str();

      gr1->SetTitle(graphTitle.c_str());

      TF1 *polN = new TF1("pol", polS.c_str(), 0, 10);
      gr1->Fit("pol", "Q");

      TSpline3 *s = new TSpline3("grs", gr1);
      s->SetLineColor(kGreen);
      s->Draw("SAME");

      std::vector<double> out_par;

      for (int i = 0; i <= th_o; ++i) {
        out_par.push_back(polN->GetParameter(i));

        cout << out_par[i] << " ";
      }
      std::cout << std::endl;
      out_list.push_back(out_par);

      input.clear();

      ++cnt_l;
    }
    myfile.close();
  }

  // generate the vector for position dependence calculation
  int line_points = 3001;
  // here for now
  double range = hist_ang_hi;

  double step_ang_width = 2 * range / line_points;
  double step_ang = hist_ang_lo;

  std::vector<double> xfp;
  std::vector<double> dxfp;
  std::vector<double> thtgt;

  int data_cnt = 0;

  double xfp_tmp = 0.0;
  double dxfp_tmp = 0.0;

  for (unsigned i = 0; i < out_list.size(); ++i) {

    step_ang = -range;

    for (int j = 0; j < line_points; ++j) {

      step_ang += step_ang_width;

      xfp_tmp = 0.0;
      dxfp_tmp = 0.0;

      for (unsigned k = 0; k < out_list[i].size(); ++k) {

        xfp_tmp += out_list[i][k] * pow(step_ang, k);

        if (k > 0) {
          dxfp_tmp += out_list[i][k] * pow(step_ang, k);
        }
      }
      dxfp_tmp *= (-1);

      xfp.push_back(xfp_tmp);
      dxfp.push_back(dxfp_tmp);
      thtgt.push_back(step_ang);

      ++data_cnt;
    }
  }

  // std::cout << "DATA COUNT: " << data_cnt << std::endl;

  // calculate the parameters

  int ang_order = th_o;
  int x_order = x_o;

  int order_x2 = (ang_order + 1) * (x_order + 1);
  int order_x3 = (x_order + 1) * ang_order;

  // std::cout << "TEST  " << order_x2 << " " << order_x3 << std::endl;

  TMatrixD param(order_x3, order_x3);

  TMatrixD param_inv(order_x3, order_x3);

  TMatrixD vec(order_x3, 1);
  TMatrixD par_v(order_x3, 1);

  // vec.Print();
  std::vector<std::vector<double>> element;

  std::vector<double> tmp_row;

  for (int i = 0; i < order_x2; ++i) {
    tmp_row.push_back(0.0);
  }
  for (int i = 0; i < order_x3; ++i) {
    element.push_back(tmp_row);
  }

  std::array<double, 81> par = {0.0};

  int l = 0;
  int m = 0;

  for (int i = 0; i < data_cnt; ++i) {
    l = 0;
    m = 0;

    std::vector<std::vector<int>> xo;
    std::vector<std::vector<int>> tho;

    std::vector<int> tmp_row_2;
    for (int k = 0; k < order_x3; ++k) {
      tmp_row_2.push_back(0);
    }

    for (int k = 0; k < order_x3; ++k) {
      xo.push_back(tmp_row_2);
      tho.push_back(tmp_row_2);
    }

    for (int c = 0; c <= x_order; ++c) {
      for (int b = 1; b <= ang_order; ++b) {
        m = 0;

        for (int c2 = 0; c2 <= x_order; ++c2) {
          for (int b2 = 1; b2 <= ang_order; ++b2) {
            xo[m][l] = c + c2;
            tho[m][l] = b + b2;
            element[m][l] += pow(thtgt[i], tho[m][l]) * pow(xfp[i], xo[m][l]);
            ++m;
          }
        }
        ++l;
      }
    }

    m = 0;

    for (int c2 = 0; c2 <= x_order; ++c2) {
      for (int b2 = 1; b2 <= ang_order; ++b2) {
        vec[m] += dxfp[i] * pow(thtgt[i], b2) * pow(xfp[i], c2);
        // cout << m << " " << dxfp[i] << " " << thtgt[i] << "" << b2 << " "
        //     << xfp[i] << " " << c2 << " " << vec[m][0] << std::endl;
        ++m;
      }
    }
  }

  for (int i = 0; i < order_x3; ++i) {
    for (int j = 0; j < order_x3; ++j) {
      param(i, j) = element[i][j];
    }
  }

  param_inv = param.Invert();

  par_v.Mult(param_inv, vec);

  for (int i = 0; i < order_x3; ++i) {

    par[i] = par_v[i][0];
  }

  string opt_corr = par_name + ":X1pos+(";

  std::vector<double> out_par;

  for (int j = 0; j <= x_o; ++j) {
    for (int i = 1; i <= th_o; ++i) {

      std::cout << conf_par_name << " " << i << " " << j << " "
                << par[j * ang_order + (i - 1)] << std::endl;

      opt_corr += "(" + to_string(par[j * ang_order + (i - 1)]) + ")*(X1pos**" +
                  to_string(j) + ")*(" + par_name + "**" + to_string(i) + ")";

      if (j < x_o || i < th_o) {
        opt_corr += " + ";
      }
    }
  }

  opt_corr += ")>>" + hist_name;

  cout << "" << endl;

  cout << opt_corr << endl;

  // c1->cd(1);
  // TGraph *gr2 = new TGraph(steps, x, y);
  // gr2->SetLineWidth(2);
  // gr2->SetLineColor(kRed);
  // gr2->Draw("SAME");
  // gr2->Draw("SAME","AC*");
  // c1->Update();

  TCanvas *c0 = new TCanvas("c0", "Test", 800, 600);

  tree->Draw(opt_corr.c_str(), opt.c_str(), "col");
}
