void overLay(){
//	TH1F* Ana_slice[3];
//	for(Int_t i = 0 ; i < 3 ; i++){
//		TString name = Form("Ana_slice%d", i);
//		Ana_slice[i] = new TH1F(name , "Track Length Distribution at given Energies #pm 10 MeV; Tracklength/X_{0}; Probability", 100, 0, 20);
//		Ana_slice[i] -> SetLineColor(i+1);
//	}
//	Float_t binCen, TrkLen;
//	for(Int_t i = 0; i < 3; i++)
//	{
//		Int_t count = 1;
//		TString filename = Form("analyticalData/ana0%d.txt", i);
//		ifstream in;
//		in.open(filename);
//		while(!in.eof())
//		{
//			in >> binCen >> TrkLen;
//			Ana_slice[i] -> SetBinContent(count, TrkLen);
//			Ana_slice[i] -> SetBinError(count, 0);
//			count ++;
//		}
//		in.close();
//	}
	TH1F* Ana_slice[3];
	TFile* g = new TFile("slicesAna.root");
	Ana_slice[0] = (TH1F*)g -> Get("slice0");
	Ana_slice[1] = (TH1F*)g -> Get("slice1");
	Ana_slice[2] = (TH1F*)g -> Get("slice2");

	TH1F* MC_slice[3];
	TFile* f = new TFile("slicesMC.root");
	MC_slice[0] = (TH1F*)f -> Get("slice0"); MC_slice[0] -> SetLineColor(7); MC_slice[0] -> Sumw2();
	MC_slice[1] = (TH1F*)f -> Get("slice1"); MC_slice[1] -> SetLineColor(9); MC_slice[1] -> Sumw2();
	MC_slice[2] = (TH1F*)f -> Get("slice2"); MC_slice[2] -> SetLineColor(11); MC_slice[2] -> Sumw2();


	gStyle->SetOptStat(0);
	gStyle->SetLegendFont(80);

	TCanvas* c = new TCanvas("c", "Ratio of Probability distribution at 50 GeV");
	Ana_slice[0]->Scale(1./Ana_slice[0]->Integral("width"));
	MC_slice[0]->Scale(1./MC_slice[0]->Integral(), "width");
//	Ana_slice[0]->ResetStats();
//	MC_slice[0]->ResetStats();
	auto rp = new TRatioPlot(Ana_slice[0], MC_slice[0], "divsym");
	c->SetTicks(0, 1);
	rp->Draw();
	rp->GetUpperPad()->cd();

	auto leg = new TLegend();
	leg->SetHeader("Legend","C");
	leg->AddEntry(Ana_slice[0],"1 GeV/ A","l");
	leg->AddEntry(MC_slice[0],"1 GeV/ MC","l");
	leg->Draw();
	c->Update();

	TCanvas* c1 = new TCanvas("c1", "Ratio of Probability distribution at 1 GeV");
	Ana_slice[1]->Scale(1./Ana_slice[1]->Integral("width"));
	MC_slice[1]->Scale(1./MC_slice[1]->Integral("width"));
	auto rp1 = new TRatioPlot(Ana_slice[1], MC_slice[1], "divsym");
	c1->SetTicks(0, 1);
	rp1->Draw();
	rp1->GetUpperPad()->cd();
	auto leg1 = new TLegend();
	leg1->SetHeader("Legend","C");
	leg1->AddEntry(Ana_slice[1],"25 GeV/ A","l");
	leg1->AddEntry(MC_slice[1],"25 GeV/ MC","l");
	leg1->Draw();
	c1->Update();

	TCanvas* c2 = new TCanvas("c2", "Ratio of Probability distribution at 10 GeV");
	Ana_slice[2]->Scale(1./Ana_slice[2]->Integral("width"));
//	MC_slice[2]->Draw();
//	cout << MC_slice[2]->Integral() << endl;
	MC_slice[2]->Scale(1./MC_slice[2]->Integral("width"));
//	MC_slice[2]->ResetStats();
//	MC_slice[2]->Draw("same");
	Int_t bin = 50;
	Double_t errorAna = Ana_slice[2]->GetBinError(bin);
	Double_t errorMC = MC_slice[2]->GetBinError(bin);
	cout << "Analytical Error : " << errorAna << " MC Error: " << errorMC << endl;
	Ana_slice[2]->ResetStats();
	MC_slice[2]->ResetStats();
	auto rp2 = new TRatioPlot(Ana_slice[2],MC_slice[2], "divsym");
	c2->SetTicks(0, 1);
	rp2->Draw();
	rp2->GetUpperPad()->cd();
	auto leg2 = new TLegend();
	leg2->SetHeader("Legend","C");
	leg2->AddEntry(Ana_slice[2],"55 GeV/ A","l");
	leg2->AddEntry(MC_slice[2],"55 GeV/ MC","l");
	leg2->Draw();
	c2->Update();
	
}
