// This is the function to plot the analytical Data equation 22 from https://doi.org/10.1103/PhysRev.149.1248

Double_t Intensity(Double_t E_0, Double_t E, Double_t t){
	return (1/E_0)*(1/tgamma(4*t/3))*pow(log(E_0/E),4*t/3-1);
}
void analytical(){
	
	Int_t N = 20000;
	Double_t E_0 = 1e11 ;
	Double_t E_i[3] = {0.99e9, 24.99e9, 54.99e9};
	Double_t delta_t = 0.001;
	Double_t delta_E = 0.001;
	Double_t t = 0.0;
	Double_t Prob;
  
	TH1F* slice[3];
		for(Int_t i = 0 ; i < 3 ; i++){
			TString name = Form("slice%d", i);
			slice[i] = new TH1F(name , "Track Length Distribution at given Energies #pm 10 MeV; Tracklength/X_{0}; Probability", 100, 0, 20);
			slice[i] -> SetLineColor(i+1);
		}

	for (Int_t g = 0; g < 3; g++) {
		for (Int_t i = 0; i < N; i++) {
			Double_t Ei = E_i[g];
			Prob = 0.;
			t = i*delta_t;
			for (Int_t j = 0; j < N; j++) {
				Ei = Ei + j*delta_E;
				Prob = Prob + Intensity(E_0, Ei, t);
			}
			slice[g] -> Fill(t,Prob);
		}
	}
	
	TCanvas* c = new TCanvas("c", "Ratio of Probability distribution at 200 MeV");
	slice[0] -> Draw();
	slice[1] -> Draw("same");
	slice[2] -> Draw("same");
	for (Int_t Bin = 0; Bin < 100; Bin++) {
		cout << "Bin Center : " << slice[2]->GetBinCenter(Bin+1)<< " bincontent : " << slice[2]->GetBinContent(Bin+1) << endl;
	}
	
	TFile f("slicesAna.root","recreate");
	slice[0]->Write();
	slice[1]->Write();
	slice[2]->Write();

}
