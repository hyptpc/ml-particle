#include <TRandom3.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TH2D.h>
#include <cmath>

void mkrootfile_pdf(int tof_option, int energy_option, int run)
{
  gRandom->SetSeed(time(NULL));
  // TFile *fout = new TFile("train_Kppi_TofMom.root", "RECREATE");
  TFile *fout = new TFile(Form("/group/had/sks/Users/Amemiya/Likelihood/pdf_tof%dene%d_run%d.root", tof_option, energy_option, run), "RECREATE");

  const double PDG_code[3] = {2212, 211, 321};               // proton, pi+, K+
  const double Mass[3] = {0.93827203, 0.13957018, 0.493677}; // GeV
  // const double Mass[3] = {938.27203, 139.57018, 493.677};//MeV
  const double Charge[3] = {1, 1, 1};

  double particle;
  double mom;
  double tofres;  // tof of 40cm distance
  double EnergyLossres; // energy loss of 40cm distance
  double right_velocity = 0.299792458; // m/ns
  double beta;

  TH2D *hpdf[3][500]; //[3]:particle, [500]:mom
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 500; ++j)
    {
      hpdf[i][j] = new TH2D(Form("hpdf%d_%d", i, j),
                            Form("hpdf%d_%d", i, j),
                            500, 0.1, 0.5, 500, 0, 0.9);
    }
  }

  //  for (int i = 0; i < 30000000; ++i)
  for (int i = 0; i < 200000; ++i)
  {

    if (i % 10000 == 0)
      std::cout << "event: " << i << std::endl;
    double rand = gRandom->Uniform(0, 1);
    int id = 0;
    if (rand < 0.33)
      id = 0;
    else if (rand < 0.66)
      id = 1;
    else
      id = 2;

    particle = id;
    mom = gRandom->Uniform(0.3, 0.8); // GeV/c
    int mom_id = (int)((mom - 0.3) * 1000.);

    double E = sqrt(Mass[id] * Mass[id] + mom * mom);
    beta = mom / E;
    double velocity = right_velocity * beta;
    double tof = 0.4 / (velocity * 10); // tof of 40cm [10ns]
    if (tof_option == 0)
    tofres = tof;
    else
    tofres = gRandom->Gaus(tof, 0.1 * tof_option*0.001);//tof resolution [ps]

    double gamma = 1 / sqrt(1 - pow(beta, 2));
    double meM = 0.000511 / Mass[id];                                                                                                                                // m_e/M
    double Tmax = 1.02 * pow(gamma, 2) * pow(beta, 2) / (1 + 2 * gamma * meM + pow(meM, 2));                                                                         // [MeV]
    double EnergyLoss_rate = (2.46 * pow(10, -4) * pow(Charge[id] / beta, 2)) * (0.5 * (std::log(1.27 * pow(10, 7) * pow(gamma, 2) * pow(beta, 2) * Tmax)) - pow(beta, 2)); // MeV/cm
    double EnergyLoss = 40 * EnergyLoss_rate;                                                                                                                         // energy loss of 40cm
    if (energy_option == 0)
    EnergyLossres = EnergyLoss;
    else
    EnergyLossres = gRandom->Gaus(EnergyLoss, EnergyLoss * energy_option*0.01);  // energy loss of 40cm
    hpdf[id][mom_id]->Fill(tofres, EnergyLossres);
  }

  // for(int i=0; i<3; ++i){
  //   for(int j=0; j<500; ++j){
  //     double Norm_factor = 1./hpdf[i][j]->GetEntries();
  //      hpdf[i][j]->Scale(Norm_factor);
  //   }
  // }

  fout->Write();
  fout->Close();
  delete fout;
  std::cout << "run "<< run << "finished" << std::endl;
}

// int main()
// {
//   mkrootfile();
//   return 0;
// }
