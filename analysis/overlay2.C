void overlay2(){
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
	
	TH1F* DMG4_1000_slice[3];
	TFile* h = new TFile("slicesDMG4_0.1000.root");
	DMG4_1000_slice[0] = (TH1F*)h -> Get("slice0"); DMG4_1000_slice[0] -> SetLineColor(11); DMG4_1000_slice[0] -> Sumw2();
	DMG4_1000_slice[1] = (TH1F*)h -> Get("slice1"); DMG4_1000_slice[1] -> SetLineColor(11); DMG4_1000_slice[1] -> Sumw2();
	DMG4_1000_slice[2] = (TH1F*)h -> Get("slice2"); DMG4_1000_slice[2] -> SetLineColor(11); DMG4_1000_slice[2] -> Sumw2();
	
	TH1F* DMG4_0100_slice[3];
	TFile* i = new TFile("slicesDMG4_0.0100.root");
	DMG4_0100_slice[0] = (TH1F*)i -> Get("slice0"); DMG4_0100_slice[0] -> SetLineColor(24); DMG4_0100_slice[0] -> Sumw2();
	DMG4_0100_slice[1] = (TH1F*)i -> Get("slice1"); DMG4_0100_slice[1] -> SetLineColor(24); DMG4_0100_slice[1] -> Sumw2();
	DMG4_0100_slice[2] = (TH1F*)i -> Get("slice2"); DMG4_0100_slice[2] -> SetLineColor(24); DMG4_0100_slice[2] -> Sumw2();
	
	TH1F* DMG4_0010_slice[3];
	TFile* j = new TFile("slicesDMG4_0.0010.root");
	DMG4_0010_slice[0] = (TH1F*)j -> Get("slice0"); DMG4_0010_slice[0] -> SetLineColor(27); DMG4_0010_slice[0] -> Sumw2();
	DMG4_0010_slice[1] = (TH1F*)j -> Get("slice1"); DMG4_0010_slice[1] -> SetLineColor(27); DMG4_0010_slice[1] -> Sumw2();
	DMG4_0010_slice[2] = (TH1F*)j -> Get("slice2"); DMG4_0010_slice[2] -> SetLineColor(27); DMG4_0010_slice[2] -> Sumw2();

	TH1F* DMG4_0001_slice[3];
	TFile* k = new TFile("slicesDMG4_0.0001.root");
	DMG4_0001_slice[0] = (TH1F*)k -> Get("slice0"); DMG4_0001_slice[0] -> SetLineColor(34); DMG4_0001_slice[0] -> Sumw2();
	DMG4_0001_slice[1] = (TH1F*)k -> Get("slice1"); DMG4_0001_slice[1] -> SetLineColor(34); DMG4_0001_slice[1] -> Sumw2();
	DMG4_0001_slice[2] = (TH1F*)k -> Get("slice2"); DMG4_0001_slice[2] -> SetLineColor(34); DMG4_0001_slice[2] -> Sumw2();

	gStyle->SetOptStat(0);
	gStyle->SetLegendFont(80);

	TCanvas* c = new TCanvas("c", "Ratio of Probability distribution at 10 GeV");
	cout << Ana_slice[0]->Integral() << endl;
	Ana_slice[0]->Scale(.1/Ana_slice[0]->Integral("width"));
	cout << Ana_slice[0]->Integral() << endl;
	MC_slice[0]->Scale(.1/MC_slice[0]->Integral(), "width");
	DMG4_1000_slice[0]->Scale(.1/DMG4_1000_slice[0]->Integral(), "width");
	cout << DMG4_1000_slice[0]->Integral() << endl;
	DMG4_0100_slice[0]->Scale(.1/DMG4_0100_slice[0]->Integral(), "width");
	cout << DMG4_0100_slice[0]->Integral() << endl;
	DMG4_0010_slice[0]->Scale(.1/DMG4_0010_slice[0]->Integral(), "width");
	cout << DMG4_0010_slice[0]->Integral() << endl;
	DMG4_0001_slice[0]->Scale(.1/DMG4_0001_slice[0]->Integral(), "width");
	cout << DMG4_0001_slice[0]->Integral() << endl;

	Ana_slice[0]->Draw("hist");
	MC_slice[0]->Draw("same");
	DMG4_1000_slice[0]->Draw("same");
	DMG4_0100_slice[0]->Draw("same");
	DMG4_0010_slice[0]->Draw("same");
	DMG4_0001_slice[0]->Draw("same");

	auto leg = new TLegend();
	leg->SetHeader("Legend","C");
	leg->AddEntry(Ana_slice[0],"10 GeV/ Ana","l");
	leg->AddEntry(MC_slice[0],"10 GeV/ G4","l");
	leg->AddEntry(DMG4_1000_slice[0],"10 GeV/ DMG4 0.1000","l");
	leg->AddEntry(DMG4_0100_slice[0],"10 GeV/ DMG4 0.0100","l");
	leg->AddEntry(DMG4_0010_slice[0],"10 GeV/ DMG4 0.0010","l");
	leg->AddEntry(DMG4_0001_slice[0],"10 GeV/ DMG4 0.0001","l");
	leg->Draw();
	c->Update();
	
/*

auto rp = new TRatioPlot(Ana_slice[0], MC_slice[0], "divsym");
c->SetTicks(0, 1);
rp->Draw();
rp->GetUpperPad()->cd();

auto leg = new TLegend();
leg->SetHeader("Legend","C");
leg->AddEntry(Ana_slice[0],"10 GeV/ DMG4","l");
leg->AddEntry(MC_slice[0],"10 GeV/ G4","l");
leg->Draw();
c->Update();

TCanvas* c1 = new TCanvas("c1", "Ratio of Probability distribution at 30 GeV");
TPad *pad10 = new TPad("pad10","This is pad10",0.02, //Lower x value (0,1) [as a percentage of the whole canvas]
						0.27, //lower y value
						0.98, //upper x value
						0.97); //upper y value
TPad *pad11 = new TPad("pad11","This is pad11",0.02,0.02,0.98,0.26);
pad10->Draw();
pad11->Draw();
pad10->cd();
	cout << Ana_slice[1]->Integral() << endl;
	Ana_slice[1]->Scale(.1/Ana_slice[1]->Integral("width"));
	cout << Ana_slice[1]->Integral() << endl;
	MC_slice[1]->Scale(.1/MC_slice[1]->Integral(), "width");
	DMG4_slice[1]->Scale(.1/DMG4_slice[1]->Integral(), "width");

	DMG4_slice[1]->Draw();
	Ana_slice[1]->Draw("same hist");
	MC_slice[1]->Draw("same");

	auto leg1 = new TLegend();
	leg1->SetHeader("Legend","C");
	leg1->AddEntry(Ana_slice[1],"30 GeV/ Ana","l");
	leg1->AddEntry(MC_slice[1],"30 GeV/ G4","le");
	leg1->AddEntry(DMG4_slice[1],"30 GeV/ DMG4","le");
	leg1->Draw();
	
pad11->cd();

	// Define the ratio plot
TH1F *G4Div10 = (TH1F*)MC_slice[1]->Clone("G4Div10");
G4Div10->Divide(Ana_slice[1]);
G4Div10->Draw("ep");
	
TH1F *G4Div11 = (TH1F*)DMG4_slice[1]->Clone("G4Div11");
G4Div11->Divide(Ana_slice[1]);
G4Div11->Draw("ep same");
G4Div10->GetXaxis()->SetLabelSize(15);
G4Div10->GetYaxis()->SetLabelSize(15);
G4Div10->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
G4Div10->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
c1->Update();
	
	
TCanvas* c2 = new TCanvas("c2", "Ratio of Probability distribution at 45 GeV");
TPad *pad20 = new TPad("pad10","This is pad20",0.02, //Lower x value (0,1) [as a percentage of the whole canvas]
						0.27, //lower y value
						0.98, //upper x value
						0.97); //upper y value
TPad *pad21 = new TPad("pad11","This is pad21",0.02,0.02,0.98,0.26);
pad20->Draw();
pad21->Draw();
pad20->cd();
	cout << Ana_slice[2]->Integral() << endl;
	Ana_slice[2]->Scale(.1/Ana_slice[2]->Integral("width"));
	cout << Ana_slice[2]->Integral() << endl;
	MC_slice[2]->Scale(.1/MC_slice[2]->Integral(), "width");
	DMG4_slice[2]->Scale(.1/DMG4_slice[2]->Integral(), "width");

	
	DMG4_slice[2]->Draw();
	Ana_slice[2]->Draw("same hist");
	MC_slice[2]->Draw("same");
	auto leg2 = new TLegend();
	leg2->SetHeader("Legend","C");
	leg2->AddEntry(Ana_slice[2],"45 GeV/ Ana","l");
	leg2->AddEntry(MC_slice[2],"45 GeV/ G4","le");
	leg2->AddEntry(DMG4_slice[2],"45 GeV/ DMG4","le");
	leg2->Draw();
	
pad21->cd();

	// Define the ratio plot
TH1F *G4Div20 = (TH1F*)MC_slice[2]->Clone("G4Div20");
G4Div20->Divide(Ana_slice[2]);
G4Div20->Draw("ep");
	
TH1F *G4Div21 = (TH1F*)DMG4_slice[2]->Clone("G4Div21");
G4Div21->Divide(Ana_slice[2]);
G4Div21->Draw("ep same");
G4Div20->GetXaxis()->SetLabelSize(15);
G4Div20->GetYaxis()->SetLabelSize(15);
G4Div20->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
G4Div20->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
c2->Update();
 
 */
}
