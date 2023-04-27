void comparePlot(){
	TFile* file = new TFile("../../outputfiles/bremOutput_1GeV_10MillEvnts.root", "read");
	TTree* ana = (TTree*)file->Get("brem");

	Double_t nEntries = ana->GetEntries();

	cout << "The root file has : "<< nEntries << " Entries" << endl;
	Int_t      TrackID;
	Double_t   fKineticEnergy;
	Double_t   fTrackLength_X0;
	Char_t     fProcess[16];
	// List of branches
	ana->SetBranchAddress("TrackID" , &TrackID);
	ana->SetBranchAddress("fKineticEnergy", &fKineticEnergy);
	ana->SetBranchAddress("fTrackLength_X0", &fTrackLength_X0);
	ana->SetBranchAddress("fProcess", &fProcess);

	// Initialize the 2-D histogram for plotting Track length Vs. Energy distribution
	TH2D* TrkLenVsEne = new TH2D("TrkLenVsEne", "Track Length Vs. Energy; Energy MeV; Tracklength/X_{0}", 500, 0, 5, 500, 0, 5);
	TrkLenVsEne->Sumw2();
	
	// Filling the histograms
	for(Int_t i = 0; i < ana->GetEntries(); i ++){
		ana->GetEntry(i);
		if( TrackID != 1) continue;
		TrkLenVsEne->Fill(TMath::Log10(fKineticEnergy), fTrackLength_X0);
	}
	// Here we normalize the 2-D histogram
	TH2D* TrkLenVsEne_norm = (TH2D*)TrkLenVsEne->Clone("norm");
	TrkLenVsEne_norm->SetTitle("Normalized: Track Length Vs. Energy");
	TrkLenVsEne_norm->Scale(1./TrkLenVsEne_norm->Integral(), "width");

	auto c = new TCanvas("c","c");
	TrkLenVsEne -> Draw("colz");
	TrkLenVsEne ->SetContour(99);
	c->SetLogz(1);

	auto c1 = new TCanvas("c1","c1");
	TrkLenVsEne_norm -> Draw("colz");
	TrkLenVsEne_norm ->SetContour(99);
	c1->SetLogz(1);
	TrkLenVsEne_norm->SetMinimum(1e-6);

}
