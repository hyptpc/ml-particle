#include <TRandom3.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <cmath>

void mkrootfile()
{
    gRandom->SetSeed(time(NULL));
    TFile *fout = new TFile("/home/had/kohki/work/ML/Likelihood/buf/train_10000.root", "RECREATE");
    //TFile *fout = new TFile("/home/had/kohki/work/ML/Likelihood/buf/test.root", "RECREATE");
    // // TFile *fout = new TFile("train_Kppi_TofMom.root", "RECREATE");
    // // TFile *fout = new TFile("test_Kppi_TofMom.root", "RECREATE");

    const double PDG_code[3] = {2212, 211, 321};               // proton, pi+, K+
    const double Mass[3] = {0.93827203, 0.13957018, 0.493677}; // GeV
    // const double Mass[3] = {938.27203, 139.57018, 493.677};//MeV
    const double Charge[3] = {1, 1, 1};

    double particle;
    double mom;
    double tof, tofres10, tofres100, tofres500, tofres1000;                               // tof of 40cm distance
    double EnergyLoss, EnergyLossres1, EnergyLossres10, EnergyLossres30, EnergyLoss_rate; // energy loss of 40cm distance
    double right_velocity = 0.299792458;                                                  // m/ns
    double beta;

    TTree *tree = new TTree("tree", "tree of data");
    tree->Branch("particle", &particle, "particle/D");
    tree->Branch("mom", &mom, "mom/D");
    tree->Branch("beta", &beta, "beta/D");
    tree->Branch("tofres0", &tof, "tof/D");
    tree->Branch("tofres10", &tofres10, "tofres10/D");
    tree->Branch("tofres100", &tofres100, "tofres100/D");
    tree->Branch("tofres500", &tofres500, "tofres500/D");
    tree->Branch("tofres1000", &tofres1000, "tofres1000/D");
    tree->Branch("energy_lossres0", &EnergyLoss, "energy_loss/D");
    tree->Branch("energy_lossres1", &EnergyLossres1, "energy_lossres1/D");
    tree->Branch("energy_lossres10", &EnergyLossres10, "energy_lossres2/D");
    tree->Branch("energy_lossres30", &EnergyLossres30, "energy_lossres5/D");
    tree->Branch("energy_loss_rate", &EnergyLoss_rate, "energy_loss_rate/D");

    for (int i = 0; i < 10000; ++i)
    {
        // for (int i = 0; i < 10000; ++i) {
        if (i % 100000 == 0)
            std::cout << "event: " << i << std::endl;
        double rand = gRandom->Uniform(0, 1);
        int id = 0;
        if (rand < 0.33)
            id = 0;
        else if (rand < 0.66)
            id = 1;
        else
            id = 2;

        // particle = PDG_code[id];
        particle = id;
        // mom = gRandom->Uniform(0.1, 1)*1000.;//MeV/c
        mom = gRandom->Uniform(0.3, 0.8); // GeV/c

        double E = sqrt(Mass[id] * Mass[id] + mom * mom);
        beta = mom / E;
        double velocity = right_velocity * beta;
        // tof = 1.0 / velocity; // tof of 1m [ns]
        tof = 0.4 / (velocity * 10);          // tof of 40cm [10ns]
        // tof = 1.0*1000. / velocity; // tof of 1m [ps]
        tofres10 = gRandom->Gaus(tof, 0.001); // 10ps resolution
        tofres100 = gRandom->Gaus(tof, 0.01); // 100ps resolution
        tofres500 = gRandom->Gaus(tof, 0.05); // 500ps resolution
        tofres1000 = gRandom->Gaus(tof, 0.1); // 1ns resolution

        double gamma = 1 / sqrt(1 - pow(beta, 2));
        double meM = 0.000511 / Mass[id];                                                                                                                                // me/M
        double Tmax = 1.02 * pow(gamma, 2) * pow(beta, 2) / (1 + 2 * gamma * meM + pow(meM, 2));                                                                         // [MeV]
        EnergyLoss_rate = (2.46 * pow(10, -4) * pow(Charge[id] / beta, 2)) * (0.5 * (std::log(1.27 * pow(10, 7) * pow(gamma, 2) * pow(beta, 2) * Tmax)) - pow(beta, 2)); // MeV/cm
        EnergyLoss = 40 * EnergyLoss_rate;                                                                                                                               // energy loss of 40cm
        EnergyLossres1 = gRandom->Gaus(EnergyLoss, EnergyLoss * 0.01);                                                                                                   // 1% resolution
        EnergyLossres10 = gRandom->Gaus(EnergyLoss, EnergyLoss * 0.10);                                                                                                  // 10% resolution
        EnergyLossres30 = gRandom->Gaus(EnergyLoss, EnergyLoss * 0.30);                                                                                                  // 30% resolution

        tree->Fill();
    }

    fout->Write();
    fout->Close();
    delete fout;
}

int main()
{
    mkrootfile();
    return 0;
}
