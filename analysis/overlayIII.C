void overlayIII(){
	TH1F* Ana_slice[3];
	TFile* g = new TFile("slicesAna.root");
	Ana_slice[0] = (TH1F*)g -> Get("slice0"); Ana_slice[0] -> SetLineColor(7);
	Ana_slice[1] = (TH1F*)g -> Get("slice1"); Ana_slice[1] -> SetLineColor(7);
	Ana_slice[2] = (TH1F*)g -> Get("slice2"); Ana_slice[2] -> SetLineColor(7);

	TH1F* MC_slice[3];
	TFile* f = new TFile("slicesG4.root");
	MC_slice[0] = (TH1F*)f -> Get("slice0"); MC_slice[0] -> SetLineColor(9); MC_slice[0] -> Sumw2();
	MC_slice[1] = (TH1F*)f -> Get("slice1"); MC_slice[1] -> SetLineColor(9); MC_slice[1] -> Sumw2();
	MC_slice[2] = (TH1F*)f -> Get("slice2"); MC_slice[2] -> SetLineColor(9); MC_slice[2] -> Sumw2();
	
	TH1F* DMG4_e3_slice[3];
	TFile* h = new TFile("slicesDMG4_0.010_Bias1e3.root");
	DMG4_e3_slice[0] = (TH1F*)h -> Get("slice0"); DMG4_e3_slice[0] -> SetLineColor(1);
	DMG4_e3_slice[1] = (TH1F*)h -> Get("slice1"); DMG4_e3_slice[1] -> SetLineColor(1);
	DMG4_e3_slice[2] = (TH1F*)h -> Get("slice2"); DMG4_e3_slice[2] -> SetLineColor(1);
	
	TH1F* DMG4_e4_slice[3];
	TFile* i = new TFile("slicesDMG4_0.010_Bias1e4.root");
	DMG4_e4_slice[0] = (TH1F*)i -> Get("slice0"); DMG4_e4_slice[0] -> SetLineColor(2);
	DMG4_e4_slice[1] = (TH1F*)i -> Get("slice1"); DMG4_e4_slice[1] -> SetLineColor(2);
	DMG4_e4_slice[2] = (TH1F*)i -> Get("slice2"); DMG4_e4_slice[2] -> SetLineColor(2);
	
	TH1F* DMG4_e5_slice[3];
	TFile* j = new TFile("slicesDMG4_0.010_Bias1e5.root");
	DMG4_e5_slice[0] = (TH1F*)j -> Get("slice0"); DMG4_e5_slice[0] -> SetLineColor(3);
	DMG4_e5_slice[1] = (TH1F*)j -> Get("slice1"); DMG4_e5_slice[1] -> SetLineColor(3);
	DMG4_e5_slice[2] = (TH1F*)j -> Get("slice2"); DMG4_e5_slice[2] -> SetLineColor(3);

	TH1F* DMG4_e6_slice[3];
	TFile* k = new TFile("slicesDMG4_0.010_Bias1e6.root");
	DMG4_e6_slice[0] = (TH1F*)k -> Get("slice0"); DMG4_e6_slice[0] -> SetLineColor(4);
	DMG4_e6_slice[1] = (TH1F*)k -> Get("slice1"); DMG4_e6_slice[1] -> SetLineColor(4);
	DMG4_e6_slice[2] = (TH1F*)k -> Get("slice2"); DMG4_e6_slice[2] -> SetLineColor(4);

	TH1F* DMG4_e7_slice[3];
	TFile* l = new TFile("slicesDMG4_0.010_Bias1e7.root");
	DMG4_e7_slice[0] = (TH1F*)k -> Get("slice0"); DMG4_e7_slice[0] -> SetLineColor(48);
	DMG4_e7_slice[1] = (TH1F*)k -> Get("slice1"); DMG4_e7_slice[1] -> SetLineColor(48);
	DMG4_e7_slice[2] = (TH1F*)k -> Get("slice2"); DMG4_e7_slice[2] -> SetLineColor(48);
	
	gStyle->SetOptStat(0);
	gStyle->SetLegendFont(80);

	TCanvas* c = new TCanvas("c", "Ratio of Probability distribution at 10 GeV");
	Ana_slice[0]->Scale(.1/Ana_slice[0]->Integral("width"));
	MC_slice[0]->Scale(.1/MC_slice[0]->Integral(), "width");
	DMG4_e3_slice[0]->Scale(.1/DMG4_e3_slice[0]->Integral(), "width");
	DMG4_e4_slice[0]->Scale(.1/DMG4_e4_slice[0]->Integral(), "width");
	DMG4_e5_slice[0]->Scale(.1/DMG4_e5_slice[0]->Integral(), "width");
	DMG4_e6_slice[0]->Scale(.1/DMG4_e6_slice[0]->Integral(), "width");
	DMG4_e7_slice[0]->Scale(.1/DMG4_e7_slice[0]->Integral(), "width");
	
	Ana_slice[0]->Draw("hist");
	MC_slice[0]->Draw("same");
	DMG4_e3_slice[0]->Draw("hist same");
//	DMG4_e4_slice[0]->Draw("hist same");
//	DMG4_e5_slice[0]->Draw("hist same");
//	DMG4_e6_slice[0]->Draw("hist same");
	DMG4_e7_slice[0]->Draw("hist same");
	
	auto leg = new TLegend();
	leg->SetHeader("Legend","C");
	leg->AddEntry(Ana_slice[0],"10 GeV/ Ana","le");
	leg->AddEntry(MC_slice[0],"10 GeV/ G4","le");
	leg->AddEntry(DMG4_e3_slice[0],"10 GeV/ DMG4 bais e3","le");
//	leg->AddEntry(DMG4_e4_slice[0],"10 GeV/ DMG4 bais e4","le");
//	leg->AddEntry(DMG4_e5_slice[0],"10 GeV/ DMG4 bais e5","le");
//	leg->AddEntry(DMG4_e6_slice[0],"10 GeV/ DMG4 bais e6","le");
	leg->AddEntry(DMG4_e7_slice[0],"10 GeV/ DMG4 bais e7","le");
	leg->Draw();
	
	
	TCanvas* c1 = new TCanvas("c1", "Ratio of Probability distribution at 30 GeV");
	Ana_slice[1]->Scale(.1/Ana_slice[1]->Integral("width"));
	MC_slice[1]->Scale(.1/MC_slice[1]->Integral(), "width");
	DMG4_e3_slice[1]->Scale(.1/DMG4_e3_slice[1]->Integral(), "width");
	DMG4_e4_slice[1]->Scale(.1/DMG4_e4_slice[1]->Integral(), "width");
	DMG4_e5_slice[1]->Scale(.1/DMG4_e5_slice[1]->Integral(), "width");
	DMG4_e6_slice[1]->Scale(.1/DMG4_e6_slice[1]->Integral(), "width");
	DMG4_e7_slice[1]->Scale(.1/DMG4_e7_slice[1]->Integral(), "width");
	
	Ana_slice[1]->Draw("hist");
	MC_slice[1]->Draw("same");
	DMG4_e3_slice[1]->Draw("hist same");
	DMG4_e4_slice[1]->Draw("hist same");
	DMG4_e5_slice[1]->Draw("hist same");
	DMG4_e6_slice[1]->Draw("hist same");
	DMG4_e7_slice[1]->Draw("hist same");
	
	auto leg1 = new TLegend();
	leg1->SetHeader("Legend","C");
	leg1->AddEntry(Ana_slice[1],"30 GeV/ Ana","le");
	leg1->AddEntry(MC_slice[1],"30 GeV/ G4","le");
	leg1->AddEntry(DMG4_e3_slice[1],"30 GeV/ DMG4 bais e3","le");
	leg1->AddEntry(DMG4_e4_slice[1],"30 GeV/ DMG4 bais e4","le");
	leg1->AddEntry(DMG4_e5_slice[1],"30 GeV/ DMG4 bais e5","le");
	leg1->AddEntry(DMG4_e6_slice[1],"30 GeV/ DMG4 bais e6","le");
	leg1->AddEntry(DMG4_e7_slice[1],"30 GeV/ DMG4 bais e7","le");
	leg1->Draw();
	
	
	TCanvas* c2 = new TCanvas("c2", "Ratio of Probability distribution at 45 GeV");
	Ana_slice[2]->Scale(.1/Ana_slice[2]->Integral("width"));
	MC_slice[2]->Scale(.1/MC_slice[2]->Integral(), "width");
	DMG4_e3_slice[2]->Scale(.1/DMG4_e3_slice[2]->Integral(), "width");
	DMG4_e4_slice[2]->Scale(.1/DMG4_e4_slice[2]->Integral(), "width");
	cout << DMG4_e5_slice[2] ->Integral() << endl;
	DMG4_e5_slice[2]->Scale(.1/DMG4_e5_slice[2]->Integral(), "width");
	cout << DMG4_e5_slice[2] ->Integral() << endl;
	DMG4_e6_slice[2]->Scale(.1/DMG4_e6_slice[2]->Integral(), "width");
	DMG4_e7_slice[2]->Scale(.1/DMG4_e7_slice[2]->Integral(), "width");
	
	Ana_slice[2]->Draw("hist");
	MC_slice[2]->Draw("same");
	DMG4_e3_slice[2]->Draw("hist same");
	DMG4_e4_slice[2]->Draw("hist same");
	DMG4_e5_slice[2]->Draw("hist same");
	DMG4_e6_slice[2]->Draw("hist same");
	DMG4_e7_slice[2]->Draw("hist same");
	
	auto leg2 = new TLegend();
	leg2->SetHeader("Legend","C");
	leg2->AddEntry(Ana_slice[2],"45 GeV/ Ana","le");
	leg2->AddEntry(MC_slice[2],"45 GeV/ G4","le");
	leg2->AddEntry(DMG4_e3_slice[2],"45 GeV/ DMG4 bais e3","le");
	leg2->AddEntry(DMG4_e4_slice[2],"45 GeV/ DMG4 bais e4","le");
	leg2->AddEntry(DMG4_e5_slice[2],"45 GeV/ DMG4 bais e5","le");
	leg2->AddEntry(DMG4_e6_slice[2],"45 GeV/ DMG4 bais e6","le");
	leg2->AddEntry(DMG4_e7_slice[2],"45 GeV/ DMG4 bais e7","le");
	leg2->Draw();
	
}
