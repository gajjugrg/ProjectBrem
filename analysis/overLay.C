void overLay(){
	TH1F* Ana_slice[3];
	for(Int_t i = 0 ; i < 3 ; i++){
		TString name = Form("Ana_slice%d", i);
		Ana_slice[i] = new TH1F(name , "Track Length Distribution at given Energies #pm 10 MeV; Tracklength/X_{0}; Probability", 100, 0, 20);
		Ana_slice[i] -> SetLineColor(i+1);
	}
	Float_t binCen, TrkLen;
	for(Int_t i = 0; i < 3; i++)
	{
		Int_t count = 1;
		TString filename = Form("analyticalData/ana0%d.txt", i);
		ifstream in;
		in.open(filename);
		while(!in.eof())
		{
			in >> binCen >> TrkLen;
			Ana_slice[i] -> SetBinContent(count, TrkLen);
			Ana_slice[i]->SetBinError(count, 0);
			count ++;
		}
		in.close();
	}
	
	TFile* f = new TFile("slicesMC.root");
	TH1F* MC_slice0 = (TH1F*)f -> Get("slice0");
	MC_slice0->Sumw2();
	TH1F* MC_slice1 = (TH1F*)f -> Get("slice1");
	MC_slice1->Sumw2();
	TH1F* MC_slice2 = (TH1F*)f -> Get("slice2");
	MC_slice2->Sumw2();
	
	
	gStyle->SetLegendFont(80);

	TCanvas* c = new TCanvas("c", "Ratio of Probability distribution at 200 MeV");
	gStyle->SetOptStat(0);
	Ana_slice[0]->Scale(1./Ana_slice[0]->Integral("width"));
	MC_slice0->Scale(1./MC_slice0->Integral("width"));
	Ana_slice[0]->ResetStats();
	MC_slice0->ResetStats();
	auto rp = new TRatioPlot(Ana_slice[0], MC_slice0, "divsym");
//	c->SetTicks(0, 1);
	rp->Draw();
	rp->GetUpperPad()->cd();
	auto leg0 = new TLegend();
	leg0->SetHeader("Legend","C");
	leg0->AddEntry(Ana_slice[0],"200 MeV Ana","l");
	leg0->AddEntry(MC_slice0,"200 MeV MC","l");
	leg0->Draw();
	c->Update();

	TCanvas* c1 = new TCanvas("c1", "Ratio of Probability distribution at 1 GeV");
	gStyle->SetOptStat(0);
	Ana_slice[1]->Scale(1./Ana_slice[1]->Integral("width"));
	MC_slice1->Scale(1./MC_slice1->Integral("width"));
	Ana_slice[1]->ResetStats();
	MC_slice1->ResetStats();
	auto rp1 = new TRatioPlot(Ana_slice[1], MC_slice1, "divsym");
//	c1->SetTicks(0, 1);
	rp1->Draw();
	rp1->GetUpperPad()->cd();
	auto leg1 = new TLegend();
	leg1->SetHeader("Legend","C");
	leg1->AddEntry(Ana_slice[1],"1 GeV Ana","l");
	leg1->AddEntry(MC_slice1,"1 GeV MC","l");
	leg1->Draw();
	c1->Update();
	
	TCanvas* c2 = new TCanvas("c2", "Ratio of Probability distribution at 10 GeV");
	gStyle->SetOptStat(0);
	Ana_slice[2]->Scale(1./Ana_slice[2]->Integral("width"));
	MC_slice2->Scale(1./MC_slice2->Integral("width"));
	Int_t bin = 50;
	Ana_slice[2]->ResetStats();
	Double_t errorAna = Ana_slice[2]->GetBinError(bin);
	Double_t errorMC = MC_slice2->GetBinError(bin);
	cout << "Analytical Error : " << errorAna << " MC Error: " << errorMC << endl;
	MC_slice2->ResetStats();
	auto rp2 = new TRatioPlot(Ana_slice[2], MC_slice2, "divsym");
//	c2->SetTicks(0, 1);
	rp2->Draw();
	rp2->GetUpperPad()->cd();
	auto leg2 = new TLegend();
	leg2->SetHeader("Legend","C");
	leg2->AddEntry(Ana_slice[2],"10 GeV Ana","l");
	leg2->AddEntry(MC_slice2,"10 GeV MC","l");
	leg2->Draw();
	c2->Update();
	
}
