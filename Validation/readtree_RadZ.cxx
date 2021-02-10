#include "TTree.h"

Bool_t CNNTight(Double_t eta, Double_t p, Double_t cov);

Bool_t CNNLoose(Double_t eta, Double_t p, Double_t cov);

void readtree_RadZ(TString Tree_name, TString path, TString filename){

TFile* input  = new TFile(path+"/"+filename+".root","READ");
TFile* output = new TFile(path+"/Histo_"+filename+".root", "RECREATE");

TTree* tree = (TTree*)input->Get(Tree_name);

Int_t        Event;
Int_t          Truth;
Float_t         ETA;
Float_t         PT;
Float_t         E;
Int_t           Cov;
Float_t         MU;
Bool_t          EdepWP;
Bool_t          EindWP;
Float_t         CNN;
Bool_t          Loose;


tree->SetBranchAddress("evntN", &Event);
tree->SetBranchAddress("PDG", &Truth);
tree->SetBranchAddress("eta", &ETA);
tree->SetBranchAddress("pt", &PT);
tree->SetBranchAddress("e", &E);
tree->SetBranchAddress("Conversion", &Cov);
tree->SetBranchAddress("mu", &MU);
tree->SetBranchAddress("isEMTightDepOff", &EdepWP);
tree->SetBranchAddress("isEMTightIncOff", &EindWP);
tree->SetBranchAddress("isEMLooseOff", &Loose);
tree->SetBranchAddress("CNN", &CNN);

//Double_t bins [] = {0,15,20,25,30,35,40,45,50,60,70,80,100,125,150};
//Int_t nbins = 15;

Double_t bins [] = {10,15,20,25,30,35,40,45,50,60,80,100,150};
Int_t nbins = 12;

Double_t etabins [] = {0,0.2,0.4,0.6,0.8,1.,1.2,1.3,1.5,1.8,2.,2.2,2.4};
Int_t netabins = 13;

Double_t mubins [] = {0,10,20,30,40,50,60,70,80,100};
Int_t nmubins = 10;

std::string Type[3] = {"Inclusive", "UnConverted", "Converted"};

Double_t eta [] = {0,0.6,0.8,1.37,1.52,1.81,2.01,2.37};

TH1F* E_Truth[3];
TH1F* E_EdepWP[3];
TH1F* E_EindWP[3];
TH1F* E_Loose[3];
TH1F* E_CNN_Tight[3];
TH1F* E_CNN_Loose[3];

TH1F* ETA_Truth[3];
TH1F* ETA_EdepWP[3];
TH1F* ETA_EindWP[3];
TH1F* ETA_Loose[3];
TH1F* ETA_CNN_Tight[3];
TH1F* ETA_CNN_Loose[3];

TH1F* MU_Truth[3];
TH1F* MU_EdepWP[3];
TH1F* MU_EindWP[3];
TH1F* MU_Loose[3];
TH1F* MU_CNN_Tight[3];
TH1F* MU_CNN_Loose[3];

TH1F* E_ETA_Truth[3][7];
TH1F* E_ETA_EdepWP[3][7];
TH1F* E_ETA_EindWP[3][7];
TH1F* E_ETA_Loose[3][7];
TH1F* E_ETA_CNN_Tight[3][7];
TH1F* E_ETA_CNN_Loose[3][7];

for(Int_t i = 0; i<3; i++) {
for(Int_t j = 0; j<7; j++)
{
	if(j == 3)continue;
	E_ETA_Truth[i][j]  = new TH1F(Form("E_Truth_%s_ETA_%.2f_%.2f",Type[i].c_str(),eta[j],eta[j+1]) , Form(" E Truth Photon %s ETA [%.2f,%.2f]",Type[i].c_str(),eta[j],eta[j+1]), nbins-1, bins);
	E_ETA_EdepWP[i][j] = new TH1F(Form("E_EdepWP_%s_ETA_%.2f_%.2f",Type[i].c_str(),eta[j],eta[j+1]), Form(" E EdepWP Photon %s ETA [%.2f,%.2f]",Type[i].c_str(),eta[j],eta[j+1]), nbins-1, bins);
	E_ETA_EindWP[i][j] = new TH1F(Form("E_EindWP_%s_ETA_%.2f_%.2f",Type[i].c_str(),eta[j],eta[j+1]), Form(" E EindWP Photon %s ETA [%.2f,%.2f]",Type[i].c_str(),eta[j],eta[j+1]), nbins-1, bins);
	E_ETA_Loose[i][j] = new TH1F(Form("E_Loose_%s_ETA_%.2f_%.2f",Type[i].c_str(),eta[j],eta[j+1]), Form(" E Loose Photon %s ETA [%.2f,%.2f]",Type[i].c_str(),eta[j],eta[j+1]), nbins-1, bins);
	E_ETA_CNN_Tight[i][j]    = new TH1F(Form("E_CNN_Tight_%s_ETA_%.2f_%.2f",Type[i].c_str(),eta[j],eta[j+1]),    Form(" E CNN Photon  %s  ETA [%.2f,%.2f] ",Type[i].c_str(),eta[j],eta[j+1]),
 nbins-1, bins);
	E_ETA_CNN_Loose[i][j]    = new TH1F(Form("E_CNN_Loose_%s_ETA_%.2f_%.2f",Type[i].c_str(),eta[j],eta[j+1]),    Form(" E CNN Photon  %s  ETA [%.2f,%.2f] ",Type[i].c_str(),eta[j],eta[j+1]),
 nbins-1, bins);


	E_ETA_Truth[i][j]->Sumw2();
	E_ETA_EdepWP[i][j]->Sumw2();
	E_ETA_EindWP[i][j]->Sumw2();
	E_ETA_Loose[i][j]->Sumw2();
	E_ETA_CNN_Tight[i][j]->Sumw2();
	E_ETA_CNN_Loose[i][j]->Sumw2();

	E_ETA_Truth[i][j]->SetStats(0);
	E_ETA_EdepWP[i][j]->SetStats(0);
	E_ETA_EindWP[i][j]->SetStats(0);
	E_ETA_Loose[i][j]->SetStats(0);
	E_ETA_CNN_Tight[i][j]->SetStats(0);
	E_ETA_CNN_Loose[i][j]->SetStats(0);

	E_ETA_Truth[i][j]->SetMarkerStyle(8);
	E_ETA_EdepWP[i][j]->SetMarkerStyle(8);
	E_ETA_EindWP[i][j]->SetMarkerStyle(22);
	E_ETA_Loose[i][j]->SetMarkerStyle(22);
	E_ETA_CNN_Tight[i][j]->SetMarkerStyle(21);
	E_ETA_CNN_Loose[i][j]->SetMarkerStyle(21);

	E_ETA_EdepWP[i][j]->SetMarkerColor(1);
	E_ETA_EindWP[i][j]->SetMarkerColor(4);
	E_ETA_Loose[i][j]->SetMarkerColor(4);
	E_ETA_CNN_Tight[i][j]->SetMarkerColor(2);
	E_ETA_CNN_Loose[i][j]->SetMarkerColor(2);
	
	E_ETA_Truth[i][j]->GetYaxis()->SetRangeUser(0.,1.05);
	E_ETA_EdepWP[i][j]->GetYaxis()->SetRangeUser(0.,1.05);
	E_ETA_EindWP[i][j]->GetYaxis()->SetRangeUser(0.,1.05);
	E_ETA_Loose[i][j]->GetYaxis()->SetRangeUser(0.,1.05);
	E_ETA_CNN_Tight[i][j]->GetYaxis()->SetRangeUser(0.,1.05);
	E_ETA_CNN_Loose[i][j]->GetYaxis()->SetRangeUser(0.,1.05);
	
	

	E_ETA_Truth[i][j]->GetYaxis()->SetTitle("Tight Eff.");
	E_ETA_EdepWP[i][j]->GetYaxis()->SetTitle("Tight Eff.");
	E_ETA_EindWP[i][j]->GetYaxis()->SetTitle("Tight Eff.");
	E_ETA_Loose[i][j]->GetYaxis()->SetTitle("Loose Eff.");
	E_ETA_CNN_Tight[i][j]->GetYaxis()->SetTitle("Tight Eff.");
	E_ETA_CNN_Loose[i][j]->GetYaxis()->SetTitle("Loose Eff.");

	E_ETA_Truth[i][j]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_ETA_EdepWP[i][j]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_ETA_EindWP[i][j]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_ETA_Loose[i][j]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_ETA_CNN_Tight[i][j]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_ETA_CNN_Loose[i][j]->GetXaxis()->SetTitle("Photon E[GeV]");
}
}
for(Int_t i = 0; i<3; i++)
{
	E_Truth[i]  = new TH1F(Form("E_Truth_%s",Type[i].c_str()) , Form(" E Truth Photon %s ",Type[i].c_str()), nbins-1, bins);
	E_EdepWP[i] = new TH1F(Form("E_EdepWP_%s",Type[i].c_str()), Form(" E EdepWP Photon %s",Type[i].c_str()), nbins-1, bins);
	E_EindWP[i] = new TH1F(Form("E_EindWP_%s",Type[i].c_str()), Form(" E EindWP Photon %s",Type[i].c_str()), nbins-1, bins);
	E_Loose[i] = new TH1F(Form("E_Loose_%s",Type[i].c_str()), Form(" E Loose Photon %s",Type[i].c_str()), nbins-1, bins);
	E_CNN_Tight[i]    = new TH1F(Form("E_CNN_Tight_%s",Type[i].c_str()),    Form(" E CNN Photon  %s  ",Type[i].c_str()), nbins-1, bins);
	E_CNN_Loose[i]    = new TH1F(Form("E_CNN_Loose_%s",Type[i].c_str()),    Form(" E CNN Photon  %s  ",Type[i].c_str()), nbins-1, bins);

	ETA_Truth[i]  = new TH1F(Form("ETA_Truth_%s",Type[i].c_str()) , Form(" ETA Truth Photon %s ",Type[i].c_str()), netabins-1, etabins);
	ETA_EdepWP[i] = new TH1F(Form("ETA_EdepWP_%s",Type[i].c_str()), Form(" ETA EdepWP Photon %s",Type[i].c_str()), netabins-1, etabins);
	ETA_EindWP[i] = new TH1F(Form("ETA_EindWP_%s",Type[i].c_str()), Form(" ETA EindWP Photon %s",Type[i].c_str()), netabins-1, etabins);
	ETA_Loose[i] = new TH1F(Form("ETA_Loose_%s",Type[i].c_str()), Form(" ETA Loose Photon %s",Type[i].c_str()), netabins-1, etabins);
	ETA_CNN_Tight[i]    = new TH1F(Form("ETA_CNN_Tight_%s",Type[i].c_str()),    Form(" ETA CNN Photon  %s  ",Type[i].c_str()), netabins-1, etabins);
	ETA_CNN_Loose[i]    = new TH1F(Form("ETA_CNN_Loose_%s",Type[i].c_str()),    Form(" ETA CNN Photon  %s  ",Type[i].c_str()), netabins-1, etabins);

	MU_Truth[i]  = new TH1F(Form("MU_Truth_%s",Type[i].c_str()) , Form(" PileUp Truth Photon %s ",Type[i].c_str()), nmubins-1, mubins);
	MU_EdepWP[i] = new TH1F(Form("MU_EdepWP_%s",Type[i].c_str()), Form(" PileUp EdepWP Photon %s",Type[i].c_str()), nmubins-1, mubins);
	MU_EindWP[i] = new TH1F(Form("MU_EindWP_%s",Type[i].c_str()), Form(" PileUP EindWP Photon %s",Type[i].c_str()), nmubins-1, mubins);
	MU_Loose[i] = new TH1F(Form("MU_Loose_%s",Type[i].c_str()), Form(" MU Loose Photon %s",Type[i].c_str()), nmubins-1, mubins);
	MU_CNN_Tight[i]    = new TH1F(Form("MU_CNN_Tight_%s",Type[i].c_str()),    Form(" PileUP CNN Photon  %s  ",Type[i].c_str()), nmubins-1, mubins);
	MU_CNN_Loose[i]    = new TH1F(Form("MU_CNN_Loose_%s",Type[i].c_str()),    Form(" PileUP CNN Photon  %s  ",Type[i].c_str()), nmubins-1, mubins);
	
	E_Truth[i]->Sumw2();
	E_EdepWP[i]->Sumw2();
	E_EindWP[i]->Sumw2();
	E_Loose[i]->Sumw2();
	E_CNN_Tight[i]->Sumw2();
	E_CNN_Loose[i]->Sumw2();

	E_Truth[i]->SetStats(0);
	E_EdepWP[i]->SetStats(0);
	E_EindWP[i]->SetStats(0);
	E_Loose[i]->SetStats(0);
	E_CNN_Tight[i]->SetStats(0);
	E_CNN_Loose[i]->SetStats(0);

	E_Truth[i]->SetMarkerStyle(8);
	E_EdepWP[i]->SetMarkerStyle(8);
	E_EindWP[i]->SetMarkerStyle(22);
	E_Loose[i]->SetMarkerStyle(22);
	E_CNN_Tight[i]->SetMarkerStyle(21);
	E_CNN_Loose[i]->SetMarkerStyle(21);

	E_EdepWP[i]->SetMarkerColor(1);
	E_EindWP[i]->SetMarkerColor(4);
	E_Loose[i]->SetMarkerColor(4);
	E_CNN_Tight[i]->SetMarkerColor(2);
	E_CNN_Loose[i]->SetMarkerColor(2);

	E_Truth[i]->GetYaxis()->SetRangeUser(0.,1.05);
	E_EdepWP[i]->GetYaxis()->SetRangeUser(0.,1.05);
	E_EindWP[i]->GetYaxis()->SetRangeUser(0.,1.05);
	E_Loose[i]->GetYaxis()->SetRangeUser(0.,1.05);
	E_CNN_Tight[i]->GetYaxis()->SetRangeUser(0.,1.05);
	E_CNN_Loose[i]->GetYaxis()->SetRangeUser(0.,1.05);	
	

	E_Truth[i]->GetYaxis()->SetTitle("Tight Eff.");
	E_EdepWP[i]->GetYaxis()->SetTitle("Tight Eff.");
	E_EindWP[i]->GetYaxis()->SetTitle("Tight Eff.");
	E_Loose[i]->GetYaxis()->SetTitle("Loose Eff.");
	E_CNN_Tight[i]->GetYaxis()->SetTitle("Tight Eff.");
	E_CNN_Loose[i]->GetYaxis()->SetTitle("Loose Eff.");

	E_Truth[i]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_EdepWP[i]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_EindWP[i]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_Loose[i]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_CNN_Tight[i]->GetXaxis()->SetTitle("Photon E[GeV]");
	E_CNN_Loose[i]->GetXaxis()->SetTitle("Photon E[GeV]");

	ETA_Truth[i]->Sumw2();
	ETA_EdepWP[i]->Sumw2();
	ETA_EindWP[i]->Sumw2();
	ETA_Loose[i]->Sumw2();
	ETA_CNN_Tight[i]->Sumw2();
	ETA_CNN_Loose[i]->Sumw2();

	ETA_Truth[i]->SetStats(0);
	ETA_EdepWP[i]->SetStats(0);
	ETA_EindWP[i]->SetStats(0);
	ETA_Loose[i]->SetStats(0);
	ETA_CNN_Tight[i]->SetStats(0);
	ETA_CNN_Loose[i]->SetStats(0);

	ETA_Truth[i]->SetMarkerStyle(8);
	ETA_EdepWP[i]->SetMarkerStyle(8);
	ETA_EindWP[i]->SetMarkerStyle(22);
	ETA_Loose[i]->SetMarkerStyle(22);
	ETA_CNN_Tight[i]->SetMarkerStyle(21);
	ETA_CNN_Loose[i]->SetMarkerStyle(21);

	ETA_EdepWP[i]->SetMarkerColor(1);
	ETA_EindWP[i]->SetMarkerColor(4);
	ETA_Loose[i]->SetMarkerColor(4);
	ETA_CNN_Tight[i]->SetMarkerColor(2);
	ETA_CNN_Loose[i]->SetMarkerColor(2);

	ETA_Truth[i]->GetYaxis()->SetRangeUser(0.,1.05);
	ETA_EdepWP[i]->GetYaxis()->SetRangeUser(0.,1.05);
	ETA_EindWP[i]->GetYaxis()->SetRangeUser(0.,1.05);
	ETA_Loose[i]->GetYaxis()->SetRangeUser(0.,1.05);
	ETA_CNN_Tight[i]->GetYaxis()->SetRangeUser(0.,1.05);
	ETA_CNN_Loose[i]->GetYaxis()->SetRangeUser(0.,1.05);

	ETA_Truth[i]->GetYaxis()->SetTitle("Tight Eff.");
	ETA_EdepWP[i]->GetYaxis()->SetTitle("Tight Eff.");
	ETA_EindWP[i]->GetYaxis()->SetTitle("Tight Eff.");
	ETA_Loose[i]->GetYaxis()->SetTitle("Tight Eff.");
	ETA_CNN_Tight[i]->GetYaxis()->SetTitle("Tight Eff.");
	ETA_CNN_Loose[i]->GetYaxis()->SetTitle("Loose Eff.");

	ETA_Truth[i]->GetXaxis()->SetTitle("Photon | #eta |");
	ETA_EdepWP[i]->GetXaxis()->SetTitle("Photon | #eta |");
	ETA_EindWP[i]->GetXaxis()->SetTitle("Photon | #eta |");
	ETA_Loose[i]->GetXaxis()->SetTitle("Photon | #eta |");
	ETA_CNN_Tight[i]->GetXaxis()->SetTitle("Photon | #eta |");
	ETA_CNN_Loose[i]->GetXaxis()->SetTitle("Photon | #eta |");

	MU_Truth[i]->Sumw2();
	MU_EdepWP[i]->Sumw2();
	MU_EindWP[i]->Sumw2();
	MU_Loose[i]->Sumw2();
	MU_CNN_Tight[i]->Sumw2();
	MU_CNN_Loose[i]->Sumw2();

	MU_Truth[i]->SetStats(0);
	MU_EdepWP[i]->SetStats(0);
	MU_EindWP[i]->SetStats(0);
	MU_Loose[i]->SetStats(0);
	MU_CNN_Tight[i]->SetStats(0);
	MU_CNN_Loose[i]->SetStats(0);

	MU_Truth[i]->SetMarkerStyle(8);
	MU_EdepWP[i]->SetMarkerStyle(8);
	MU_EindWP[i]->SetMarkerStyle(22);
	MU_Loose[i]->SetMarkerStyle(22);
	MU_CNN_Tight[i]->SetMarkerStyle(21);
	MU_CNN_Loose[i]->SetMarkerStyle(21);

	MU_EdepWP[i]->SetMarkerColor(1);
	MU_EindWP[i]->SetMarkerColor(4);
	MU_Loose[i]->SetMarkerColor(4);
	MU_CNN_Tight[i]->SetMarkerColor(2);
	MU_CNN_Loose[i]->SetMarkerColor(2);
	
	MU_Truth[i]->GetYaxis()->SetRangeUser(0.,1.05);
	MU_EdepWP[i]->GetYaxis()->SetRangeUser(0.,1.05);
	MU_EindWP[i]->GetYaxis()->SetRangeUser(0.,1.05);
	MU_Loose[i]->GetYaxis()->SetRangeUser(0.,1.05);
	MU_CNN_Tight[i]->GetYaxis()->SetRangeUser(0.,1.05);
	MU_CNN_Loose[i]->GetYaxis()->SetRangeUser(0.,1.05);

	MU_Truth[i]->GetYaxis()->SetTitle("Tight Eff.");
	MU_EdepWP[i]->GetYaxis()->SetTitle("Tight Eff.");
	MU_EindWP[i]->GetYaxis()->SetTitle("Tight Eff.");
	MU_Loose[i]->GetYaxis()->SetTitle("Loose Eff.");
	MU_CNN_Tight[i]->GetYaxis()->SetTitle("Tight Eff.");
	MU_CNN_Loose[i]->GetYaxis()->SetTitle("Tight Eff.");

	MU_Truth[i]->GetXaxis()->SetTitle("#mu");
	MU_EdepWP[i]->GetXaxis()->SetTitle("#mu");
	MU_EindWP[i]->GetXaxis()->SetTitle("#mu");
	MU_Loose[i]->GetXaxis()->SetTitle("#mu");
	MU_CNN_Tight[i]->GetXaxis()->SetTitle("#mu");
	MU_CNN_Loose[i]->GetXaxis()->SetTitle("#mu");
}

for(Int_t i = 0; i<tree->GetEntriesFast(); i++)
{
	tree->GetEntry(i);

	

	if(Truth != 22) continue;

	bool isCNNTight = CNNTight(fabs(ETA), CNN, Cov);
	bool isCNNLoose = CNNLoose(fabs(ETA), CNN, Cov);

	if(Truth) E_Truth[0]->Fill(E*1e-3);
	if(EdepWP) E_EdepWP[0]->Fill(E*1e-3);
	if(EindWP) E_EindWP[0]->Fill(E*1e-3);
	if(isCNNTight) E_CNN_Tight[0]->Fill(E*1e-3);
	if(isCNNLoose) E_CNN_Loose[0]->Fill(E*1e-3);
	if(Loose) E_Loose[0]->Fill(E*1e-3);

	for(Int_t j = 0; j<7 ; j++) {
			if( j == 3) continue;
			if(fabs(ETA) < eta[j+1] && fabs(ETA) > eta[j])
			{
				if(Truth) E_ETA_Truth[0][j]->Fill(E*1e-3);
				if(EdepWP) E_ETA_EdepWP[0][j]->Fill(E*1e-3);
				if(EindWP) E_ETA_EindWP[0][j]->Fill(E*1e-3);
				if(isCNNTight) E_ETA_CNN_Tight[0][j]->Fill(E*1e-3);
				if(isCNNLoose) E_ETA_CNN_Loose[0][j]->Fill(E*1e-3);
				if(Loose) E_ETA_Loose[0][j]->Fill(E*1e-3);
			}
		}

	if(Truth) ETA_Truth[0]->Fill(fabs(ETA));
	if(EdepWP) ETA_EdepWP[0]->Fill(fabs(ETA));
	if(EindWP) ETA_EindWP[0]->Fill(fabs(ETA));
	if(isCNNTight) ETA_CNN_Tight[0]->Fill(fabs(ETA));
	if(isCNNLoose) ETA_CNN_Loose[0]->Fill(fabs(ETA));
	if(Loose) ETA_Loose[0]->Fill(fabs(ETA));

	if(Truth) MU_Truth[0]->Fill(MU);
	if(EdepWP) MU_EdepWP[0]->Fill(MU);
	if(EindWP) MU_EindWP[0]->Fill(MU);
	if(isCNNTight) MU_CNN_Tight[0]->Fill(MU);
	if(isCNNLoose) MU_CNN_Loose[0]->Fill(MU);
	if(Loose) MU_Loose[0]->Fill(MU);

	if(Cov == 0)
	{
		if(Truth) E_Truth[1]->Fill(E*1e-3);
		if(EdepWP) E_EdepWP[1]->Fill(E*1e-3);
		if(EindWP) E_EindWP[1]->Fill(E*1e-3);
		if(isCNNTight) E_CNN_Tight[1]->Fill(E*1e-3);
		if(isCNNLoose) E_CNN_Loose[1]->Fill(E*1e-3);
		if(Loose) E_Loose[1]->Fill(E*1e-3);

		for(Int_t j = 0; j<7 ; j++) {
			if( j == 3) continue;
			if(fabs(ETA) < eta[j+1] && fabs(ETA) > eta[j])
			{
				if(Truth) E_ETA_Truth[1][j]->Fill(E*1e-3);
				if(EdepWP) E_ETA_EdepWP[1][j]->Fill(E*1e-3);
				if(EindWP) E_ETA_EindWP[1][j]->Fill(E*1e-3);
				if(isCNNTight) E_ETA_CNN_Tight[1][j]->Fill(E*1e-3);
				if(isCNNLoose) E_ETA_CNN_Loose[1][j]->Fill(E*1e-3);
				if(Loose) E_ETA_Loose[1][j]->Fill(E*1e-3);
			}
		}

		if(Truth) ETA_Truth[1]->Fill(fabs(ETA));
		if(EdepWP) ETA_EdepWP[1]->Fill(fabs(ETA));
		if(EindWP) ETA_EindWP[1]->Fill(fabs(ETA));
		if(isCNNTight) ETA_CNN_Tight[1]->Fill(fabs(ETA));
		if(isCNNLoose) ETA_CNN_Loose[1]->Fill(fabs(ETA));
		if(Loose) ETA_Loose[1]->Fill(fabs(ETA));

		if(Truth) MU_Truth[1]->Fill(MU);
		if(EdepWP) MU_EdepWP[1]->Fill(MU);
		if(EindWP) MU_EindWP[1]->Fill(MU);
		if(isCNNTight) MU_CNN_Tight[1]->Fill(MU);
		if(isCNNLoose) MU_CNN_Loose[1]->Fill(MU);
		if(Loose) MU_Loose[1]->Fill(MU);
	}else{

		if(Truth) E_Truth[2]->Fill(E*1e-3);
		if(EdepWP) E_EdepWP[2]->Fill(E*1e-3);
		if(EindWP) E_EindWP[2]->Fill(E*1e-3);
		if(isCNNTight) E_CNN_Tight[2]->Fill(E*1e-3);
		if(isCNNLoose) E_CNN_Loose[2]->Fill(E*1e-3);
		if(Loose) E_Loose[2]->Fill(E*1e-3);

		for(Int_t j = 0; j<7 ; j++) {
			if( j == 3) continue;
			if(fabs(ETA) < eta[j+1] && fabs(ETA) > eta[j])
			{
				if(Truth) E_ETA_Truth[2][j]->Fill(E*1e-3);
				if(EdepWP) E_ETA_EdepWP[2][j]->Fill(E*1e-3);
				if(EindWP) E_ETA_EindWP[2][j]->Fill(E*1e-3);
				if(isCNNTight) E_ETA_CNN_Tight[2][j]->Fill(E*1e-3);
				if(isCNNLoose) E_ETA_CNN_Loose[2][j]->Fill(E*1e-3);
				if(Loose) E_ETA_Loose[2][j]->Fill(E*1e-3);
			}
		}

		if(Truth) ETA_Truth[2]->Fill(fabs(ETA));
		if(EdepWP) ETA_EdepWP[2]->Fill(fabs(ETA));
		if(EindWP) ETA_EindWP[2]->Fill(fabs(ETA));
		if(isCNNTight) ETA_CNN_Tight[2]->Fill(fabs(ETA));
		if(isCNNLoose) ETA_CNN_Loose[2]->Fill(fabs(ETA));
		if(Loose) ETA_Loose[2]->Fill(fabs(ETA));

		if(Truth) MU_Truth[2]->Fill(MU);
		if(EdepWP) MU_EdepWP[2]->Fill(MU);
		if(EindWP) MU_EindWP[2]->Fill(MU);
		if(isCNNTight) MU_CNN_Tight[2]->Fill(MU);
		if(isCNNLoose) MU_CNN_Loose[2]->Fill(MU);
		if(Loose) MU_Loose[2]->Fill(MU);

	}
	

}

for(Int_t i = 0; i<3; i++)
{

E_EdepWP[i]->Divide(E_Truth[i]);
E_EindWP[i]->Divide(E_Truth[i]);
E_CNN_Tight[i]->Divide(E_Truth[i]);
E_CNN_Loose[i]->Divide(E_Truth[i]);
E_Loose[i]->Divide(E_Truth[i]);

for(Int_t j = 0; j<7; j++)
{
	if( j==3) continue;
	
	E_ETA_EdepWP[i][j]->Divide(E_ETA_Truth[i][j]);
	E_ETA_EindWP[i][j]->Divide(E_ETA_Truth[i][j]);
	E_ETA_CNN_Tight[i][j]->Divide(E_ETA_Truth[i][j]);	
	E_ETA_CNN_Loose[i][j]->Divide(E_ETA_Truth[i][j]);
	E_ETA_Loose[i][j]->Divide(E_ETA_Truth[i][j]);
}

E_Truth[i]->SetDirectory(output);
E_EdepWP[i]->SetDirectory(output);
E_EindWP[i]->SetDirectory(output);
E_CNN_Tight[i]->SetDirectory(output);
E_CNN_Loose[i]->SetDirectory(output);
E_Loose[i]->SetDirectory(output);

ETA_EdepWP[i]->Divide(ETA_Truth[i]);
ETA_EindWP[i]->Divide(ETA_Truth[i]);
ETA_CNN_Tight[i]->Divide(ETA_Truth[i]);
ETA_CNN_Loose[i]->Divide(ETA_Truth[i]);
ETA_Loose[i]->Divide(ETA_Truth[i]);

ETA_Truth[i]->SetDirectory(output);
ETA_EdepWP[i]->SetDirectory(output);
ETA_EindWP[i]->SetDirectory(output);
ETA_CNN_Tight[i]->SetDirectory(output);
ETA_CNN_Loose[i]->SetDirectory(output);
ETA_Loose[i]->SetDirectory(output);

MU_EdepWP[i]->Divide(MU_Truth[i]);
MU_EindWP[i]->Divide(MU_Truth[i]);
MU_CNN_Tight[i]->Divide(MU_Truth[i]);
MU_CNN_Loose[i]->Divide(MU_Truth[i]);
MU_Loose[i]->Divide(MU_Truth[i]);

MU_Truth[i]->SetDirectory(output);
MU_EdepWP[i]->SetDirectory(output);
MU_EindWP[i]->SetDirectory(output);
MU_CNN_Tight[i]->SetDirectory(output);
MU_CNN_Loose[i]->SetDirectory(output);
MU_Loose[i]->SetDirectory(output);

}
output->Write();
//output->Close();
}

Bool_t CNNTight(Double_t eta, Double_t p, Double_t cov)
{

	if(eta < .6 && eta > 0.0){
		if(p > .715 && cov==0)
			return true;
		if(p > .662 && cov!=0)
			return true;
	}
	if(eta < .8 && eta > .6){
		if(p > 0.756 && cov==0)
			return true;
		if(p > 0.477 && cov!=0)
			return true;
	}
	if(eta < 1.15 && eta > .8){
		if(p > 0.795 && cov==0)
			return true;
		if(p > 0.578 && cov!=0)
			return true;
	}
	if(eta < 1.37 && eta > 1.15){
		if(p > 0.81 && cov==0)
			return true;
		if(p > 0.49 && cov!=0)
			return true;
	}
	if(eta < 1.81 && eta > 1.52){
		if(p > 0.875 && cov==0)
			return true;
		if(p > 0.742 && cov!=0)
			return true;
	}
	if(eta < 2.01 && eta > 1.81){
		if(p > 0.93 && cov==0)
			return true;
		if(p > 0.626 && cov!=0)
			return true;
	}
	if(eta > 2.01){
		if(p > 0.892 && cov==0)
			return true;
		if(p > 0.722 && cov!=0)
			return true;
	}
	//return false;

return false;
	
}


Bool_t CNNLoose(Double_t eta, Double_t p, Double_t cov)
{

	if(eta < .6 && eta > 0.0){
		if(p > .033 && cov==0)
			return true;
		if(p > .025 && cov!=0)
			return true;
	}
	if(eta < .8 && eta > .6){
		if(p > 0.027 && cov==0)
			return true;
		if(p > 0.022 && cov!=0)
			return true;
	}
	if(eta < 1.15 && eta > .8){
		if(p > 0.044 && cov==0)
			return true;
		if(p > 0.023 && cov!=0)
			return true;
	}
	if(eta < 1.37 && eta > 1.15){
		if(p > 0.04 && cov==0)
			return true;
		if(p > 0.027 && cov!=0)
			return true;
	}
	if(eta < 1.81 && eta > 1.52){
		if(p > 0.187 && cov==0)
			return true;
		if(p > 0.081 && cov!=0)
			return true;
	}
	if(eta < 2.01 && eta > 1.81){
		if(p > 0.62 && cov==0)
			return true;
		if(p > 0.125 && cov!=0)
			return true;
	}
	if(eta > 2.01){
		if(p > 0.132 && cov==0)
			return true;
		if(p > 0.578 && cov!=0)
			return true;
	}
	//return false;

return false;
	
}
