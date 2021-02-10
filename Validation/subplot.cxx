#include "TTree.h"
#include "AtlasStyle.h"
#include "AtlasLabels.h"
#include "TText.h"
#include "TPaveText.h"
#include "TCut.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TROOT.h"

void subplot(TString file, TString name, std::string cnn, std::string stg, std::string iso){

	gStyle->SetOptStat("");
  	gStyle->SetPalette(1);
	TColor *color = gROOT->GetColor(5);
  	color->SetRGB(1., 0.8, 0.);
  	gStyle->SetPaintTextFormat("2.1f");

	TFile* _input = new TFile(file+name,"READ");

	std::string Type[3] = {"Inclusive", "UnConverted", "Converted"};
	std::string Var[3] = {"E", "ETA", "MU"};
        Double_t eta [] = {0,0.6,0.8,1.37,1.52,1.81,2.01,2.37};

	for(int i = 0; i<3; i++)
	{
	for(int j = 0; j<3; j++)
	{
	
		TCanvas* c = new TCanvas(Form("Canvas_%s_%s",Var[j].c_str(),Type[i].c_str())," ", 850, 850);
		TH1F* h_inc = (TH1F*)_input->Get(Form("%s_EindWP_%s", Var[j].c_str(), Type[i].c_str()));
		TH1F* h_dep = (TH1F*)_input->Get(Form("%s_EdepWP_%s", Var[j].c_str(), Type[i].c_str()));
		TH1F* h_cnn = (TH1F*)_input->Get(Form("%s_CNN_Tight_%s", Var[j].c_str(), Type[i].c_str()));

		
		h_inc->SetLineColor(1);
		h_dep->SetLineColor(4);
		h_cnn->SetLineColor(2);

		h_dep->SetMarkerStyle(8);
		h_inc->SetMarkerStyle(22);
		h_cnn->SetMarkerStyle(21);

		h_dep->SetMarkerColor(4);
		h_inc->SetMarkerColor(1);
		h_cnn->SetMarkerColor(2);

		h_inc->Draw();
		h_dep->Draw("same");
		h_cnn->Draw("same");

		TLegend* legend = new TLegend(0.9,0.2,0.2,0.3);
		legend->SetBorderSize(0);
		legend->AddEntry(h_dep,"E-dependent ATLAS ID");
		legend->AddEntry(h_inc,"E-independent ATLAS ID");
		legend->AddEntry(h_cnn,"CNN ID");
		legend->SetHeader(Form("%s %s : %s #gamma RadiativeZ, | #eta |<2.37, Isolation %s", cnn.c_str(), stg.c_str(), Type[i].c_str(), iso.c_str()),"C");
		legend->Draw("same");
		TPaveText* pavelumi = new TPaveText(0.17,0.4,0.5,0.3,"BRNDC");
		pavelumi->AddText("Tight ID");  
		pavelumi->SetFillColor(0);
		pavelumi->SetFillStyle(0);
		pavelumi->SetBorderSize(0);
		pavelumi->SetTextSize(0.03);
		pavelumi->SetTextAlign(11);
		pavelumi->Draw("same");
		TString ATLASText = "Simulation Internal";
  		SetAtlasStyle();
  		ATLASLabel(0.17, 0.4, ATLASText);

		c->SaveAs(file+Form("/%s_%s_%s_%s_%s_TightEff.png", cnn.c_str(), stg.c_str(), Type[i].c_str(), iso.c_str(), Var[j].c_str()));
		
		delete c;
	}
	}

	for(int i = 0; i<3; i++)
	{
	for(int j = 0; j<3; j++)
	{
	
		TCanvas* c = new TCanvas(Form("Canvas_%s_%s",Var[j].c_str(),Type[i].c_str())," ", 850, 850);
		TH1F* h_inc = (TH1F*)_input->Get(Form("%s_Loose_%s", Var[j].c_str(), Type[i].c_str()));
		TH1F* h_cnn = (TH1F*)_input->Get(Form("%s_CNN_Loose_%s", Var[j].c_str(), Type[i].c_str()));

		
		h_inc->SetLineColor(4);
		h_cnn->SetLineColor(2);

		h_inc->SetMarkerStyle(22);
		h_cnn->SetMarkerStyle(21);

		h_inc->SetMarkerColor(4);
		h_cnn->SetMarkerColor(2);

		h_inc->Draw();
		h_cnn->Draw("same");

		TLegend* legend = new TLegend(0.9,0.2,0.2,0.3);
		legend->SetBorderSize(0);
		legend->AddEntry(h_inc,"ATLAS ID");
		legend->AddEntry(h_cnn,"CNN ID");
		legend->SetHeader(Form("%s %s : %s #gamma RadiativeZ, | #eta |<2.37, Isolation %s", cnn.c_str(), stg.c_str(), Type[i].c_str(), iso.c_str()),"C");
		legend->Draw("same");
		TPaveText* pavelumi = new TPaveText(0.17,0.4,0.5,0.3,"BRNDC");
		pavelumi->AddText("Loose ID");  
		pavelumi->SetFillColor(0);
		pavelumi->SetFillStyle(0);
		pavelumi->SetBorderSize(0);
		pavelumi->SetTextSize(0.03);
		pavelumi->SetTextAlign(11);
		pavelumi->Draw("same");
		TString ATLASText = "Simulation Internal";
  		SetAtlasStyle();
  		ATLASLabel(0.17, 0.4, ATLASText);

		c->SaveAs(file+Form("/%s_%s_%s_%s_%s_LooseEff.png", cnn.c_str(), stg.c_str(), Type[i].c_str(), iso.c_str(), Var[j].c_str()));
		
		delete c;
	}
	}
	
	for(int i = 0; i<3; i++) {
	for(int e = 0; e<7; e++) {
		Int_t j = 0;
		if(e == 3) continue;

		TCanvas* c = new TCanvas(Form("Canvas_%s_%s_ETA_%.2f_%.2f ",Var[j].c_str(),Type[i].c_str(),eta[e],eta[e+1])," ", 850, 850);
		TH1F* h_inc = (TH1F*)_input->Get(Form("%s_EindWP_%s_ETA_%.2f_%.2f", Var[j].c_str(), Type[i].c_str(),eta[e],eta[e+1]));
		TH1F* h_dep = (TH1F*)_input->Get(Form("%s_EdepWP_%s_ETA_%.2f_%.2f", Var[j].c_str(), Type[i].c_str(),eta[e],eta[e+1]));
		TH1F* h_cnn = (TH1F*)_input->Get(Form("%s_CNN_Tight_%s_ETA_%.2f_%.2f", Var[j].c_str(), Type[i].c_str(),eta[e],eta[e+1]));
		
		h_inc->SetLineColor(1);
		h_dep->SetLineColor(4);
		h_cnn->SetLineColor(2);

		h_dep->SetMarkerStyle(8);
		h_inc->SetMarkerStyle(22);
		h_cnn->SetMarkerStyle(21);

		h_dep->SetMarkerColor(4);
		h_inc->SetMarkerColor(1);
		h_cnn->SetMarkerColor(2);

		h_inc->Draw();
		h_dep->Draw("same");
		h_cnn->Draw("same");

		TLegend* legend = new TLegend(0.9,0.2,0.2,0.3);
		legend->SetBorderSize(0);
		legend->AddEntry(h_dep,"E-dependent ATLAS ID");
		legend->AddEntry(h_inc,"E-independent ATLAS ID");
		legend->AddEntry(h_cnn,"CNN ID");
		legend->SetHeader(Form("%s %s : %s #gamma RadiativeZ, %.2f <|#eta|< %.2f, Isolation %s", cnn.c_str(), stg.c_str(), Type[i].c_str(), eta[e], eta[e+1], iso.c_str()),"C");
		legend->Draw("same");
		TPaveText* pavelumi = new TPaveText(0.17,0.4,0.5,0.3,"BRNDC");
		pavelumi->AddText("Tight ID");  
		pavelumi->SetFillColor(0);
		pavelumi->SetFillStyle(0);
		pavelumi->SetBorderSize(0);
		pavelumi->SetTextSize(0.03);
		pavelumi->SetTextAlign(11);
		pavelumi->Draw("same");
		TString ATLASText = "Simulation Internal";
  		SetAtlasStyle();
  		ATLASLabel(0.17, 0.4, ATLASText);

		c->SaveAs(file+Form("/%s_%s_%s_%s_%s_ETA_%.2f_%.2f_TightEff.png", cnn.c_str(), stg.c_str(), Type[i].c_str(), iso.c_str(), Var[j].c_str(), eta[e], eta[e+1]));
		
		delete c;
	
	} }

	for(int i = 0; i<3; i++) {
	for(int e = 0; e<7; e++) {
		Int_t j = 0;
		if(e == 3) continue;

		TCanvas* c = new TCanvas(Form("Canvas_%s_%s_ETA_%.2f_%.2f ",Var[j].c_str(),Type[i].c_str(),eta[e],eta[e+1])," ", 850, 850);
		TH1F* h_inc = (TH1F*)_input->Get(Form("%s_Loose_%s_ETA_%.2f_%.2f", Var[j].c_str(), Type[i].c_str(),eta[e],eta[e+1]));
		TH1F* h_cnn = (TH1F*)_input->Get(Form("%s_CNN_Loose_%s_ETA_%.2f_%.2f", Var[j].c_str(), Type[i].c_str(),eta[e],eta[e+1]));
		
		h_inc->SetLineColor(4);
		h_cnn->SetLineColor(2);


		h_inc->SetMarkerStyle(22);
		h_cnn->SetMarkerStyle(21);

		h_inc->SetMarkerColor(4);
		h_cnn->SetMarkerColor(2);

		h_inc->Draw();
		h_cnn->Draw("same");

		TLegend* legend = new TLegend(0.9,0.2,0.2,0.3);
		legend->SetBorderSize(0);
		legend->AddEntry(h_inc,"ATLAS ID");
		legend->AddEntry(h_cnn,"CNN ID");
		legend->SetHeader(Form("%s %s : %s #gamma RadiativeZ, %.2f <|#eta|< %.2f, Isolation %s", cnn.c_str(), stg.c_str(), Type[i].c_str(), eta[e], eta[e+1], iso.c_str()),"C");
		legend->Draw("same");
		TPaveText* pavelumi = new TPaveText(0.17,0.4,0.5,0.3,"BRNDC");
		pavelumi->AddText("Loose ID");  
		pavelumi->SetFillColor(0);
		pavelumi->SetFillStyle(0);
		pavelumi->SetBorderSize(0);
		pavelumi->SetTextSize(0.03);
		pavelumi->SetTextAlign(11);
		pavelumi->Draw("same");
		TString ATLASText = "Simulation Internal";
  		SetAtlasStyle();
  		ATLASLabel(0.17, 0.4, ATLASText);

		c->SaveAs(file+Form("/%s_%s_%s_%s_%s_ETA_%.2f_%.2f_LooseEff.png", cnn.c_str(), stg.c_str(), Type[i].c_str(), iso.c_str(), Var[j].c_str(), eta[e], eta[e+1]));
		
		delete c;
	
	} }
	
}

int main(int argc, char* argv[]){

	subplot(argv[1], argv[2], argv[3], argv[4], argv[5]);
}
