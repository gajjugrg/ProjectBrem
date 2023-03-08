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
	
	TH1D* slice1= new TH1D("slice1", "200 MeV", 100, 0, 18);
//	slice1->SetFillColor(3);
//	slice1->SetFillStyle(3004);
	slice1->SetLineColor(3);
	
	TH1D* Slice3 = new TH1D("Slice3", "1 GeV", 100, 0, 18);
//	Slice3->SetFillColor(4);
//	Slice3->SetFillStyle(3006);
	Slice3->SetLineColor(4);
	
	TH1D* Slice2 = new TH1D("Slice2", "10 GeV", 100, 0, 18);
//	Slice2->SetFillColor(7);
//	Slice2->SetFillStyle(3007);
	Slice2->SetLineColor(7);
	
	
		
		TH2D* TrkLenVsEne = new TH2D("TrkLenVsEne", "Track Length Vs. Energy; Energy MeV; Tracklength/X_{0}", 1000, 0, 100100, 1000, 0, 20);
		for(Int_t i = 0; i < ana->GetEntries(); i ++){
				ana->GetEntry(i);
				if( TrackID != 1) continue;
				else
				{
					TrkLenVsEne->Fill(fKineticEnergy, fTrackLength_X0);
					if(fKineticEnergy > 190 && fKineticEnergy < 210){slice1->Fill(fTrackLength_X0);};
					if(fKineticEnergy > 990 && fKineticEnergy < 1010){Slice2 ->Fill(fTrackLength_X0);};
					if(fKineticEnergy > 9990 && fKineticEnergy < 10010){Slice3 ->Fill(fTrackLength_X0);}

				}
		}
	
	
	
	
	
	
	auto c = new TCanvas("c","c");
	TrkLenVsEne -> Draw("colz");
	TrkLenVsEne ->SetContour(99);
	c->SetLogx(1); //set the logarithmic scale on the X axis
	c->SetLogy(1);
	c->SetLogz(1);
	
	
	auto c1 = new TCanvas("c1","c1");
	
	slice1->Draw();
	Slice2->Draw("same");
	Slice3->Draw("same");
	c1->SetLogy(1);
	gStyle->SetOptStat(0); //this removes the Statbox
	auto legend = new TLegend();
	legend->SetHeader("Legend","C");
	legend->AddEntry(slice1,"200 MeV","l");
	legend->AddEntry(Slice2,"1 GeV","l");
	legend->AddEntry(Slice3,"10 GeV", "l");
	legend->Draw();
//    file->Close();
}

