void plotTrackLenVsEne(){


TFile* file = new TFile("bremOutput.root", "read");
TTree* ana = (TTree*)file->Get("brem");

Int_t           TrackID;
Double_t        fKineticEnergy;
Double_t        fTrackLength_X0;
Char_t          fProcess[16];
// List of branches
ana->SetBranchAddress("TrackID" , &TrackID);
ana->SetBranchAddress("fKineticEnergy", &fKineticEnergy);
ana->SetBranchAddress("fTrackLength_X0", &fTrackLength_X0);
ana->SetBranchAddress("fProcess", &fProcess);
		
		TH2D* TrkLenVsEne = new TH2D("TrkLenVsEne", "Track Length Vs. Energy; Energy GeV; Tracklength/X_{0}", 500, 0, 100100, 500, 0, 20);
		for(Int_t i = 0; i < ana->GetEntries(); i ++){
				ana->GetEntry(i);
				if( TrackID != 1) continue;
				else
				{ TrkLenVsEne->Fill(fKineticEnergy, fTrackLength_X0); }
		}
		
		TrkLenVsEne -> Draw("colz");
		TrkLenVsEne ->SetContour(99);
//    file->Close();
}

