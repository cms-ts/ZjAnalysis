#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <TH2.h>
#include "TF1.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include "TLatex.h"
#include <vector>
#include <iostream>
#include "tdrstyle.C"
#include <TROOT.h>
#include "TObject.h"
#include <iostream>
#include <sstream>
#include "TTree.h"
#include "TH2.h"
#include "THStack.h"
#include "TLatex.h"
#include "TColor.h"
#include <string.h>
#include <cmath>
#include <iomanip>

// INSTRUCTIONS:
// .L inclusiveMultStatistics.C++
// inclusiveMultStatistics()
// CONGRATULATIONS!

void computeCorr(TH2D * covMat, TH2D * corrMat) {

  int nx = covMat->GetNbinsX();
  int ny = covMat->GetNbinsY();

  if ( nx != ny ) {
    std::cout << "Non square covariance matrix, aborting" << std::endl;
    return;
  }

  //  covMat->Print("ALL");
  
  std::vector<double> sigma(nx,0.);

  for ( int k = 1; k <= nx ; k++ ) {
    for ( int l = 1; l <= ny; l++ ) {
      if ( k == l ) { 
        corrMat->SetBinContent(k,l,1.); 
        sigma[k] = std::sqrt(covMat->GetBinContent(k,l));
        //        std::cout << "Bin = " << k << " " << l << " sigma = " << sigma[k] << std::endl;
      }
    }
  }

  for ( int k = 1; k <= nx ; k++ ) {
    for ( int l = 1; l <= ny; l++ ) {
      if ( k != l ) { 
        if ( sigma[k] > 0. && sigma[l] > 0. ) {
          double corre = covMat->GetBinContent(k,l)/sigma[k]/sigma[l];
          if ( std::fabs(corre) > 1. ) {
            std::cout << "Warning: element " << k << " " << l << " with correlation > 1, rescaling" << std::endl;
            corre = ( (corre > 0. ) ? 1. : -1. );
          }
          corrMat->SetBinContent(k,l,corre); 
          //          std::cout << "Bin = " << k << " " << l << " Cov = " << covMat->GetBinContent(k,l) << " Corr = " << corrMat->GetBinContent(k,l)  << std::endl;
        }
      }
    }
  }
  
  return;

}

void FillInclusive( TH1D * exc , TH1D * inc , TH2D * corr) {

  int nx = exc->GetNbinsX();

  for ( int iMult = 1 ; iMult <= nx ; iMult++ ) {

    double sum = 0.;
    double errsum = 0.;
    double errsumNocorr = 0.;

    for ( int iBin = iMult; iBin <= nx; iBin++ ) {
      sum += exc->GetBinContent(iBin);
    }

    for ( int k = iMult; k <= nx ; k++ ) {
      for ( int l = iMult; l <= nx ; l++ ) {
          errsum += exc->GetBinError(k)*exc->GetBinError(l)*corr->GetBinContent(k,l);
          if ( l == k ) errsumNocorr += exc->GetBinError(k)*exc->GetBinError(l)*corr->GetBinContent(k,l);
      }
    }
    errsum = std::sqrt(errsum);
    errsumNocorr = std::sqrt(errsumNocorr);

    /* std::cout << "Sum i           = " << iMult << " " << sum << std::endl; */
    /* std::cout << "Sigma i         = " << iMult << " " << errsum << std::endl; */
    /* std::cout << "Sigma no corr i = " << iMult << " " << errsumNocorr << std::endl; */

    inc->SetBinContent(iMult,sum);
    inc->SetBinError(iMult,errsum);

  }

  return;

}

int inclusiveMultStatistics () {

  //  setTDRStyle ();

  string elePathFile;
  string muoPathFile;

  //  elePathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_finalCWR.root";
  //  muoPathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_finalCWRMu.root";

  elePathFile="ele1.root";
  muoPathFile="muo1.root";

  TFile output_file("inclusiveMultOfficialV58_finalCWR.root","RECREATE");

  // BEGIN COMBINATION:

  TFile *histofile1 = TFile::Open (elePathFile.c_str ());
  histofile1->cd ("");
  TDirectory *dir1 = gDirectory;
  TList *mylist1 = (TList *) dir1->GetListOfKeys ();
  TIter iter1 (mylist1);
  TObject *tobj1 = 0;

  TFile *histofile2 = TFile::Open (muoPathFile.c_str ());
  histofile2->cd ("");
  TDirectory *dir2 = gDirectory;
  TList *mylist2 = (TList *) dir2->GetListOfKeys ();
  TIter iter2 (mylist2);
  TObject *tobj2 = 0;

  string elename;
  string muoname;
  TH1D *elehisto;
  TH1D *muohisto;
  TH2D *elecov;
  TH2D *muocov;
  TH1D *combineinc;
        
  double wmean=0.;
  double wsigma=0.;

  while ((tobj1 = iter1.Next ())) {
    string name;
    name = tobj1->GetName ();
    histofile1->cd ("");
    if ( name != "JetMultiplicityUnfolded" && name != "jMatxCov" ) continue;
    if ( name == "JetMultiplicityUnfolded" ) { 
      gDirectory->GetObject (name.c_str (), elehisto); // Save ele histogram!
      elename = name;
    }
    else if ( name == "jMatxCov" ) {
      gDirectory->GetObject (name.c_str (), elecov); // Save ele covariance!
    }
    
  }

  iter2.Reset();
  while ((tobj2 = iter2.Next ())) {
    string name;
    name = tobj2->GetName ();
    if ( name != "JetMultiplicityUnfolded" && name != "jMatxCov" ) continue;
    histofile2->cd ("");
    if ( name == "JetMultiplicityUnfolded" ) { 
      gDirectory->GetObject (name.c_str (), muohisto); // Save muo histogram!
      muoname = name;
    }
    else if ( name == "jMatxCov" ) {
      gDirectory->GetObject (name.c_str (), muocov); // Save muo covariance!
    }
  }

  if ( elehisto == NULL || muohisto == NULL ) return 1;
  
  cout << "Combining " << elename << " for electrons with " << muoname << " for muons..."  << endl;
  
  int nbins_ele,nbins_muo;
  
  nbins_ele = elehisto->GetNbinsX();
  nbins_muo = muohisto->GetNbinsX();
  
  if (nbins_ele != nbins_muo) {cout << "ERROR: combining histos with different binning... exit." << endl; return 0;}

  TH2D tmpMat;
  elecov->Copy(tmpMat);

  //  elehisto->Print("ALL");
  //  elecov->Print("ALL");
  TH2D * elecorr(&tmpMat); elecorr->Reset();
  computeCorr(elecov,elecorr); 
  //  elecorr->Print("ALL");
  
  //  muohisto->Print("ALL");
  //  muocov->Print("ALL");
  TH2D * muocorr(&tmpMat); muocorr->Reset();
  computeCorr(muocov,muocorr); 
  //  muocorr->Print("ALL");

  TH1D * eleinc = (TH1D *) elehisto->Clone("elehisto");
  eleinc->Reset();
  FillInclusive( elehisto, eleinc, elecorr ) ;
  //  eleinc->Print("ALL");
  std::cout << "Electrons" << std::endl;
  for ( int iBin = 1 ; iBin <= eleinc->GetNbinsX() ; iBin++ ) {
    std::cout << "Bin " << iBin 
              << " cont = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << eleinc->GetBinContent(iBin) 
              << " sta% = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << eleinc->GetBinError(iBin)/eleinc->GetBinContent(iBin) 
              << " abs sta = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << eleinc->GetBinError(iBin) << std::endl;
  }

  TH1D * muoinc = (TH1D *) muohisto->Clone("muohisto");
  muoinc->Reset();
  FillInclusive( muohisto, muoinc, muocorr ) ;
  //  muoinc->Print("ALL");
  std::cout << "Muons" << std::endl;
  for ( int iBin = 1 ; iBin <= muoinc->GetNbinsX() ; iBin++ ) {
    std::cout << "Bin " << iBin 
              << " cont = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << muoinc->GetBinContent(iBin) 
              << " sta% = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << muoinc->GetBinError(iBin)/muoinc->GetBinContent(iBin) 
              << " abs sta = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << muoinc->GetBinError(iBin) << std::endl;
  }

  combineinc = (TH1D *) eleinc->Clone ("eleinc");
  combineinc->SetName(muoname.c_str ());
  combineinc->SetTitle(muoname.c_str ());
  
  // Compute weighted mean and sigma for every bin:
  std::cout << "Combined" << std::endl;
  for (int i=1; i<(eleinc->GetNbinsX()+1);i++) {
    wmean =   (eleinc->GetBinContent(i)/(eleinc->GetBinError(i)*eleinc->GetBinError(i))
               + muoinc->GetBinContent(i)/(muoinc->GetBinError(i)*muoinc->GetBinError(i)))
      / (1./(eleinc->GetBinError(i)*eleinc->GetBinError(i))
         + 1./(muoinc->GetBinError(i)*muoinc->GetBinError(i)));
    wsigma = 1./sqrt(1./(eleinc->GetBinError(i)*eleinc->GetBinError(i))
                     + 1./(muoinc->GetBinError(i)*muoinc->GetBinError(i)));
    combineinc->SetBinContent(i,wmean);
    combineinc->SetBinError(i,wsigma);
    std::cout << "Bin " << i 
              << " cont = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << combineinc->GetBinContent(i) 
              << " sta% = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << combineinc->GetBinError(i)/combineinc->GetBinContent(i) 
              << " abs sta = " << std::setfill(' ') << std::setw(9) << std::setprecision(5) << std::fixed << combineinc->GetBinError(i) << std::endl;
  }
  
  /* output_file.cd(); */
  /* combineinc->Write(); */
  
  
  histofile1->Close();
  histofile2->Close();
  //  output_file.Close();
  cout << "Congratulations, combination achieved!" << endl;
  return 0;
}
