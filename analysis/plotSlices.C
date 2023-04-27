void plotSlices(){
	TFile* file = new TFile("$HOME/projectBrem/outputfiles/bremOutput_100GeV_FTFP_BERT.root", "read");
	//TFile* file = new TFile("$HOME/projectBrem/outputfiles/bremOutput_100GeV_0.0009.root", "read");
	TTree* ana = (TTree*)file->Get("brem");

	Double_t nEntries = ana->GetEntries();

	cout << "The root file has : "<< nEntries << " Entries" << endl;
	Int_t           TrackID;
	Double_t        fKineticEnergy;
	Double_t        fTrackLength_X0;
	Char_t          fProcess[16];
	// List of branches
	ana->SetBranchAddress("TrackID" , &TrackID);
	ana->SetBranchAddress("fKineticEnergy", &fKineticEnergy);
	ana->SetBranchAddress("fTrackLength_X0", &fTrackLength_X0);
	ana->SetBranchAddress("fProcess", &fProcess);

	// Initialize the 1-D histogram for each slice of energy
	TH1D* slice0 = new TH1D("slice0", "10 GeV", 100, 0, 10);
	slice0 -> SetLineColor(8);
	TH1D* slice1 = new TH1D("slice1", "30 GeV", 100, 0, 10);
	slice1 -> SetLineColor(6);
	TH1D* slice2 = new TH1D("slice2", "45 GeV", 100, 0, 10);
	slice2 -> SetLineColor(4);
	
	// Filling the histograms
	for(Int_t i = 0; i < ana->GetEntries(); i ++){
		ana->GetEntry(i);
		if( TrackID != 1) continue;
		
//		TrkLenVsEne->Fill(fKineticEnergy, fTrackLength_X0);
// This is one way to fill the projection histograms, works well if you want to specify a different bin width than original 2D plot
		if(fKineticEnergy >= 9990 && fKineticEnergy < 10010){slice0->Fill(fTrackLength_X0);}
		if(fKineticEnergy >= 29990 && fKineticEnergy < 30010){slice1 ->Fill(fTrackLength_X0);}
		if(fKineticEnergy >= 44990 && fKineticEnergy < 45010){slice2 ->Fill(fTrackLength_X0);}
	}
	auto c = new TCanvas("c","c");
	slice0->DrawNormalized("e1p");
	slice1->DrawNormalized("e1p same");
	slice2->DrawNormalized("e1p same");
	c->SetLogy(1);
	gStyle->SetOptStat(0); //this removes the Statbox
	auto legend = new TLegend();
	legend->SetHeader("Legend","C");
	legend->AddEntry(slice0,"10 GeV","l");
	legend->AddEntry(slice1,"30 GeV","l");
	legend->AddEntry(slice2,"45 GeV", "l");
	legend->Draw();
	
	TFile f("slicesG4.root","recreate");
	slice0->Write();
	slice1->Write();
	slice2->Write();
}

