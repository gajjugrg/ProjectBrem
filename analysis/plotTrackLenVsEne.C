void plotTrackLenVsEne(){
	TFile* file = new TFile("../1GeV_10MillEvnts.root", "read");
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
	TH1D* slice1 = new TH1D("slice1", "200 MeV", 100, 0, 20);
	TH1D* slice3 = new TH1D("slice3", "600 MeV", 100, 0, 20);
	TH1D* slice2 = new TH1D("slice2", "800 MeV", 100, 0, 20);

	// Initialize the 2-D histogram for plotting Track length Vs. Energy distribution
	TH2F* TrkLenVsEne = new TH2F("TrkLenVsEne", "Track Length Vs. Energy; Energy MeV; Tracklength/X_{0}", 50, 0, 1000, 100, 0, 20);
	TrkLenVsEne->Sumw2();
	
	// Filling the histograms
	for(Int_t i = 0; i < ana->GetEntries(); i ++){
		ana->GetEntry(i);
		if( TrackID != 1) continue;
		
		TrkLenVsEne->Fill(fKineticEnergy, fTrackLength_X0);
	/* // This is one way to fill the projection histograms, works well if you want to specify a different bin width than original 2D plot
		if(fKineticEnergy > 190 && fKineticEnergy < 210){slice1->Fill(fTrackLength_X0);}
		if(fKineticEnergy > 990 && fKineticEnergy < 1010){slice2 ->Fill(fTrackLength_X0);}
		if(fKineticEnergy > 9990 && fKineticEnergy < 10010){slice3 ->Fill(fTrackLength_X0);} */
	}

	// Here we normalize the 2-D histogram
	TH2F* TrkLenVsEne_norm = (TH2F*)TrkLenVsEne->Clone("norm");
	TrkLenVsEne_norm->SetTitle("Normalized: Track Length Vs. Energy");
	TrkLenVsEne_norm->Scale(1./TrkLenVsEne_norm->Integral(), "width");

	// Taking the slice at Energy of Interest (eoi)
	double eoi = 200;
	int pbin = TrkLenVsEne_norm->GetXaxis()->FindBin(eoi); //get the bin the energy is in
	slice1 = TrkLenVsEne_norm->ProjectionY("slice1", pbin, pbin+1); //fill in the projection data
	slice1->SetLineColor(3);
	slice1->SetTitle("Tracklength Distribution for the given energies #pm 10 MeV; Tracklength/X_{0}; Counts / NbEntries");
	
	eoi = 600;
	pbin = TrkLenVsEne_norm->GetXaxis()->FindBin(eoi);
	slice2 = TrkLenVsEne_norm->ProjectionY("slice2", pbin, pbin+1);
	slice2->SetLineColor(4);
	
	eoi = 800;
	pbin = TrkLenVsEne_norm->GetXaxis()->FindBin(eoi);
	slice3 = TrkLenVsEne_norm->ProjectionY("slice3", pbin, pbin+1);
	slice3->SetLineColor(7);

	auto c = new TCanvas("c","c");
	TrkLenVsEne -> DrawNormalized("colz");
	TrkLenVsEne ->SetContour(99);
	c->SetLogx(1); //set the logarithmic scale on the X axis
	c->SetLogy(1);
	c->SetLogz(1);

	auto c1 = new TCanvas("c1","c1");
	TrkLenVsEne_norm -> Draw("colz");
	TrkLenVsEne_norm ->SetContour(99);
	c1->SetLogx(1); //set the logarithmic scale on the X axis
	c1->SetLogy(1);
	c1->SetLogz(1);
	TrkLenVsEne_norm->SetMinimum(1e-10);

	auto c2 = new TCanvas("c2","c2");
	slice1->Draw("");
	slice2->Draw("same");
	slice3->Draw("same");
	c2->SetLogy(1);
	gStyle->SetOptStat(0); //this removes the Statbox
	auto legend = new TLegend();
	legend->SetHeader("Legend","C");
	legend->AddEntry(slice1,"200 MeV","l");
	legend->AddEntry(slice2,"600 MeV","l");
	legend->AddEntry(slice3,"800 MeV", "l");
	legend->Draw();
	//    file->Close();
	
	TFile f("slicesMC.root","recreate");
	slice1->Write();
	slice2->Write();
	slice3->Write();
}

