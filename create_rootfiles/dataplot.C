#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>

void dataplot()
{
    // Open the ROOT file containing the generated data
    TFile *file = new TFile("train_Kppi_TofMom.root", "READ");
    TTree *tree = (TTree *)file->Get("tree");

    // Declare variables to store data
    double EnergyLoss, EnergyLossres1, EnergyLossres10, EnergyLossres30;
    double mom, tof, tofres10, tofres100, tofres500, tofres1000;
    double particle;

    // Set the branch addresses
    tree->SetBranchAddress("energy_loss", &EnergyLoss);
    tree->SetBranchAddress("energy_lossres1", &EnergyLossres1);
    tree->SetBranchAddress("energy_lossres10", &EnergyLossres10);
    tree->SetBranchAddress("energy_lossres30", &EnergyLossres30);
    tree->SetBranchAddress("mom", &mom);
    tree->SetBranchAddress("tof", &tof);
    tree->SetBranchAddress("tofres10", &tofres10);
    tree->SetBranchAddress("tofres100", &tofres100);
    tree->SetBranchAddress("tofres500", &tofres500);
    tree->SetBranchAddress("tofres1000", &tofres1000);
    tree->SetBranchAddress("particle", &particle);

    // Create a canvas and a legend
    TCanvas *canvas = new TCanvas("canvas", "ToF data", 800, 600);
    //////////////////////////////////////////////////////////////////////////////////
    TMultiGraph *mg = new TMultiGraph();
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);

    // Create separate TGraphs for each particle
    TGraph *graphProton = new TGraph();
    TGraph *graphPiPlus = new TGraph();
    TGraph *graphKPlus = new TGraph();

    // Loop over the events in the tree and fill the graphs
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i)
    {
        tree->GetEntry(i);
        double xValue = mom;
        //------------------------------------------------
        double yValue = tof;
        //------------------------------------------------

        // Fill the appropriate TGraph based on particle id
        if (particle == 0)
        {
            graphProton->SetPoint(graphProton->GetN(), xValue, yValue);
        }
        else if (particle == 1)
        {
            graphPiPlus->SetPoint(graphPiPlus->GetN(), xValue, yValue);
        }
        else if (particle == 2)
        {
            graphKPlus->SetPoint(graphKPlus->GetN(), xValue, yValue);
        }
    }

    // Set the point color and add to the multigraph and legend
    graphProton->SetMarkerColor(kRed);
    graphProton->SetMarkerStyle(50);
    graphPiPlus->SetMarkerColor(kBlue);
    graphPiPlus->SetMarkerStyle(50);
    graphKPlus->SetMarkerColor(kGreen);
    graphKPlus->SetMarkerStyle(50);

    mg->Add(graphProton);
    mg->Add(graphPiPlus);
    mg->Add(graphKPlus);

    legend->AddEntry(graphProton, "Proton", "P");
    legend->AddEntry(graphPiPlus, "Pi+", "P");
    legend->AddEntry(graphKPlus, "K+", "P");

    mg->SetTitle("created ToF data (Resolution 0ps); momentum (GeV/c); ToF (ps)");
    mg->Draw("AP");
    mg->GetYaxis()->SetTitleOffset(1.2);
    mg->GetYaxis()->SetRangeUser(-2.0, 3.0); // Set the y-axis range
    legend->Draw();
    canvas->SetGrid();
    canvas->Draw();
    canvas->SaveAs("../figures/ToFres0_dataplot.png");
    //////////////////////////////////////////////////////////////////////////////////
    TCanvas *canvas2 = new TCanvas("canvas2", "EnergyLoss data", 800, 600);
    TMultiGraph *mg2 = new TMultiGraph();
    TLegend *legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);

    // Create separate TGraphs for each particle
    TGraph *graphProton2 = new TGraph();
    TGraph *graphPiPlus2 = new TGraph();
    TGraph *graphKPlus2 = new TGraph();

    // Loop over the events in the tree and fill the graphs
    for (Long64_t i = 0; i < nEntries; ++i)
    {
        tree->GetEntry(i);
        double xValue2 = mom;
        //------------------------------------------------
        double yValue2 = EnergyLoss;//CHANGE HERE
        //------------------------------------------------
        // Fill the appropriate TGraph based on particle id
        if (particle == 0)
        {
            graphProton2->SetPoint(graphProton2->GetN(), xValue2, yValue2);
        }
        else if (particle == 1)
        {
            graphPiPlus2->SetPoint(graphPiPlus2->GetN(), xValue2, yValue2);
        }
        else if (particle == 2)
        {
            graphKPlus2->SetPoint(graphKPlus2->GetN(), xValue2, yValue2);
        }
    }

    // Set the point color and add to the multigraph and legend
    graphProton2->SetMarkerColor(kRed);
    graphProton2->SetMarkerStyle(50);
    graphPiPlus2->SetMarkerColor(kBlue);
    graphPiPlus2->SetMarkerStyle(50);
    graphKPlus2->SetMarkerColor(kGreen);
    graphKPlus2->SetMarkerStyle(50);

    mg2->Add(graphProton2);
    mg2->Add(graphPiPlus2);
    mg2->Add(graphKPlus2);

    legend2->AddEntry(graphProton2, "Proton", "P");
    legend2->AddEntry(graphPiPlus2, "Pi+", "P");
    legend2->AddEntry(graphKPlus2, "K+", "P");

    mg2->SetTitle("created Energy-Loss (Resolution 0%) data; momentum (GeV/c); Energy-Loss (MeV)");
    mg2->Draw("AP");
    mg2->GetYaxis()->SetTitleOffset(1.2);
    mg2->GetYaxis()->SetRangeUser(0, 1.5);
    legend2->Draw();

    canvas2->SetGrid();
    canvas2->Draw();
    canvas2->SaveAs("../figures/EnergyLossres0_dataplot.png");
}
