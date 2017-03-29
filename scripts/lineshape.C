#include <string>

#include "TMatrixD.h"

void line_shape(TTree *tree, std::string opt, std::string inp_f, int th_o,
                int x_o) {

  // double peak_pos = 448.0;
  // double peak_width = 2.0;

  // double lo_th = -1.9;
  // double hi_th = 1.9;
  // double steps = 100.0;

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

  std::string canvas_name;

  if (myfile.is_open()) {

    while (getline(myfile, line)) {

      std::vector<std::string> input;

      istringstream iss(line);

      copy(istream_iterator<std::string>(iss), istream_iterator<std::string>(),
           back_inserter(input));

      // double peakData[input.size() - 2];

      std::cout << "processing line" << std::endl;
      // shape(tree, cnt_l, opt, input, th_o,c1);

      peak_pos = stod(input[0]);
      peak_width = stod(input[1]);

      lo_th = stod(input[2]);
      hi_th = stod(input[3]);
      steps = stod(input[4]);

      canvas_name = "c" + to_string(cnt_l);

      TCanvas *c2 = new TCanvas(canvas_name.c_str(), "Test", 800, 600);

      c2->Update();
      tree->Draw("thetaSCAT:X1pos>>hThSCATvsX1", opt.c_str(), "col");

      hThSCATvsX1->Draw("colz");
      c2->Update();

      gStyle->SetPalette(55);
      c2->Show();
      c2->Update();
      c2->Divide(1, 2);
      c2->cd(1);

      gPad->Modified();
      hThSCATvsX1->Draw("COLZ");
      hThSCATvsX1->GetXaxis()->SetRangeUser(peak_pos - 20, peak_pos + 40);
      c2->Update();

      gSystem->ProcessEvents();

      c2->cd(2);

      TH1D *projX;

      TF1 *gaus = new TF1("func", "gaus(0)", 0, 10);
      gaus->SetParameters(1, peak_pos, peak_width);

      binMin = hThSCATvsX1->GetYaxis()->FindBin(lo_th);
      binMax = hThSCATvsX1->GetYaxis()->FindBin(hi_th);

      sliceBinWidth = (binMax - binMin) / steps;
      sliceUserWidth = (hi_th - lo_th) / steps;

      double x[(int)steps];
      double y[(int)steps];
      double height[(int)steps];

      for (int i = 0; i < steps; ++i) {
        projX = hThSCATvsX1->ProjectionX("px", i * sliceBinWidth + binMin,
                                         (i + 1) * sliceBinWidth + binMin, "");

        projX->GetXaxis()->SetRangeUser(peak_pos - 20, peak_pos + 40);
        projX->Draw();

        projX->Fit("func", "Q", "", gaus->GetParameter(1) - peak_width,
                   gaus->GetParameter(1) + peak_width);

        height[i] = gaus->GetParameter(0);

        // Sometimes errors happen!
        if ((gaus->GetParameter(1)) > -600) {

          projX->Draw("");
          c2->Update();

          x[i] = gaus->GetParameter(1);
          y[i] = lo_th + i * sliceUserWidth + sliceUserWidth / 2;

          gSystem->ProcessEvents();
          gaus->SetParameters(gaus->GetParameter(0), gaus->GetParameter(1),
                              gaus->GetParameter(2));
          // sleep(0.1);
        } else {
          c2->Update();
          x[i] = x[i - 1];
          y[i] = lo_th + i * sliceUserWidth + sliceUserWidth / 2;
          gSystem->ProcessEvents();
          gaus->SetParameters(height[i - 1], x[i], 2 * peak_width);
        }
        usleep(delay);
        if ((int)steps < 50) {
          usleep(delay);
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

      // string opt_corr = "thetaSCAT:X1pos-(";

      std::vector<double> out_par;

      for (int i = 0; i <= th_o; ++i) {
        // std::cout << "PAR: " <<   polN->GetParameter(i) << std::endl;
        out_par.push_back(polN->GetParameter(i));

        cout << out_par[i] << " ";
      }

      out_list.push_back(out_par);

      // opt_corr += ")>>hThSCATvsX1";
      /*
       cout << "" << endl;

       cout << opt_corr << endl;

       c1->cd(1);
       TGraph *gr2 = new TGraph(steps, x, y);
       gr2->SetLineWidth(2);
       gr2->SetLineColor(kRed);
       gr2->Draw("SAME");
       // gr2->Draw("SAME","AC*");
       c1->Update();

       // TCanvas *c2 = new TCanvas("c3", "Test", 800, 600);

       tree->Draw(opt_corr.c_str(), opt.c_str(), "col");
                */
      // out_list.push_back(output);

      input.clear();

      ++cnt_l;
    }
    myfile.close();
  }

  // generate the vector for position dependence calculation
  int line_points = 1002;
  // here for now
  double range = 1.1;

  double step_ang_width = 2 * range / line_points;
  double step_ang = -range;

  std::vector<double> xfp;
  std::vector<double> dxfp;
  std::vector<double> thtgt;

  // cout << range << endl;

  int data_cnt = 0;

  double xfp_tmp = 0.0;
  double dxfp_tmp = 0.0;

  for (unsigned i = 0; i < out_list.size(); ++i) {

    // ptr = (*lineData)[i];

    step_ang = -range;

    // cout << ptr[0] << endl;
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

      // std::cout << step_ang << " " << xfp_tmp << " " << dxfp_tmp <<
      // std::endl;

      xfp.push_back(xfp_tmp);
      dxfp.push_back(dxfp_tmp);
      thtgt.push_back(step_ang);

      ++data_cnt;
    }
  }

  std::cout << "DATA COUNT: " << data_cnt << std::endl;

  // calculate the parameters

  int ang_order = th_o;
  int x_order = x_o;

  int order_x2 = (ang_order + 1) * (x_order + 1);
  int order_x3 = (x_order + 1) * ang_order;

  std::cout << "TEST  " << order_x2 << " " << order_x3 << std::endl;

  TMatrixD param(order_x3, order_x3);
  //= new TMatrixD
  TMatrixD param_inv(order_x3, order_x3);
  ;
  //= new TMatrixD

  TMatrixD vec(order_x3, 1);   // = new TMatrixD
  TMatrixD par_v(order_x3, 1); // = new TMatrixD

  vec.Print();

  // std::cout << vec[0][0] << std::endl;

  // please dont use orders higher than 9

  std::vector<std::vector<double>> element;
  //[order_x3][order_x2] = {0.0};

  std::vector<double> tmp_row;

  for (int i = 0; i < order_x2; ++i) {
    tmp_row.push_back(0.0);
  }
  for (int i = 0; i < order_x3; ++i) {
    element.push_back(tmp_row);
  }

  std::array<double, 81> par = {0.0};
  // std::array<std::array<double, 81>, 81> element;
  // for (int dim = 0; dim < 81; ++dim) {
  // std::array<double, 81> tmp_arr = {0.0};
  // element[dim] = {0.0};
  //}

  // double element[order_x3][order_x2] = {0.0};

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

    // nt xo[order_x3][order_x3] = {0};
    // int tho[order_x3][order_x3] = {0};

    // std::cout << thtgt[i] << " " << xfp[i] << " " << dxfp[i] << endl;

    for (int c = 0; c <= x_order; ++c) {
      for (int b = 1; b <= ang_order; ++b) {
        m = 0;

        for (int c2 = 0; c2 <= x_order; ++c2) {
          for (int b2 = 1; b2 <= ang_order; ++b2) {
            xo[m][l] = c + c2;
            tho[m][l] = b + b2;
            element[m][l] += pow(thtgt[i], tho[m][l]) * pow(xfp[i], xo[m][l]);
            // std::cout << thtgt[i] << " " << tho[m][l] << " " << xfp[i] << " "
            //      << xo[m][l] << std::endl;

            // std::cout << m << " " << l << " " << xo[m][l] << " " << tho[m][l]
            //     << " " << element[m][l] << std::endl;
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
        cout << m << " " << dxfp[i] << " " << thtgt[i] << "" << b2 << " "
             << xfp[i] << " " << c2 << " " << vec[m][0] << std::endl;
        ++m;
      }
    }
  }

  for (int i = 0; i < order_x3; ++i) {
    for (int j = 0; j < order_x3; ++j) {
      param(i, j) = element[i][j];
      // cout << i << " " << j << " " << element[i][j] << endl;
      //      element[i][j]=0.0;
    }
  }

  param_inv = param.Invert();
  //  param_inv = param.inv2();

  /*if(!param_inv.zero_chk()){
          std::cerr << "ERROR : No inverse matrix" << std::endl; exit(1);
  }*/

  par_v.Mult(param_inv, vec);

  for (int i = 0; i < order_x3; ++i) {

    par[i] = par_v[i][0];
  }

  string opt_corr = "thetaSCAT:X1pos+(";

  std::vector<double> out_par;

  //%*s %d %d %lf",&global_xcor_th_tho,&global_xcor_th_xo,&global_xcor_th_par);

  for (int j = 0; j <= x_o; ++j) {
    for (int i = 1; i <= th_o; ++i) {
      // cout << i << " " << j << " " << par[j*ang_order + (i-1)]<< endl;
      // value += par[j*ang_order + (i-1)] * pow(x, i)
      //			  * pow(y, j);
      // std::ostringstream tmp_num;

      // tmp_num << std::setprecision(15) << par[j * ang_order + (i - 1)];

      std::cout << "XCOR_TH_PAR"
                << " " << i << " " << j << " " << par[j * ang_order + (i - 1)]
                << std::endl;

      opt_corr += "(" + to_string(par[j * ang_order + (i - 1)]) + ")*(X1pos**" +
                  to_string(j) + ")*(thetaSCAT**" + to_string(i) + ")";

      // tmp_num.flush();

      if (j < x_o || i < th_o) {
        opt_corr += " + ";
      }
    }
  }

  /*for (int i = 0; i <= x_o; ++i) {
    for (int j = 0; j < th_o; ++j) {
      // out_par.push_back(polN->GetParameter(i));
      // if (i > 0) {
      std::cout << j << " " << i << " " << i * th_o + j << " "
                << (*par_v)[i * th_o + j][0] << std::endl;


      // cout << polN->GetParameter(i) << " ";
    }
  }*/

  // out_list.push_back(out_par);

  opt_corr += ")>>hThSCATvsX1";

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

  // out_list.push_back(output);
}
