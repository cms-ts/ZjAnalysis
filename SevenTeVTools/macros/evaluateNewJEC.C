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

ofstream myfile;

TH1D* turnExclusiveHistoInInclusive(TH1D* exclusive){
  TH1D *auxPlot = (TH1D *) exclusive->Clone ("exclusive");

  for (int nnbins=1;nnbins<=exclusive->GetNbinsX ();nnbins++) {
    double value=0;
    for (int nnbins2=nnbins;nnbins2<=exclusive->GetNbinsX (); nnbins2++){
      value+=exclusive->GetBinContent(nnbins2);
    }
    auxPlot->SetBinContent(nnbins,value);  
  }
  return auxPlot;
}


void
evaluateNewJEC(int whichobservable, int whichjet, int lepton, int inclusive)
{

  string fileSystematics; 
  string suffix="/gpfs/cms/data/2011/Systematics/postApproval_v58_Journal/";
  if (lepton==1) suffix=suffix+"ele/";
  if (lepton==2) suffix=suffix+"muo/";

  gStyle->SetErrorX(0);

  int use_case = whichobservable;

  string version = "_v2_32";
  //string s = "/home/schizzi/CMSSW_4_4_2/src/Histo/HistoAnalyzer/macros/plotArticleEle" + version + "/";
  string s = "/tmp/";
  string plotpath = "/gpfs/cms/data/2011/Systematics/";
  if (lepton == 1) plotpath = "/gpfs/cms/data/2011/Systematics/ele/";
  if (lepton == 2) plotpath = "/gpfs/cms/data/2011/Systematics/muo/";
  if (lepton == 3) plotpath = "/gpfs/cms/data/2011/Systematics/combination/";

  string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58.root";
  string pathFilea2="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_JECUP.root";
  string pathFilea3="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_JECDOWN.root";
  if (lepton ==2){
    string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58Mu.root";
    string pathFilea2="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_JECUPMu.root";
    string pathFilea3="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_JECDOWNMu.root";
  }

  gStyle->SetOptStat (0);

  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 800);

  stringstream oss;

  TFile *histof = TFile::Open (pathFile.c_str ());
  histof->cd ("");
  TDirectory *dir = gDirectory;
  TList *mylist = (TList *) dir->GetListOfKeys ();
  TIter iter (mylist);
  TObject *tobj = 0;
  string tmpname;
  string stringmatch;
  string systPathFile;
  string rivet_data;
  string rivet_dataMG;
  
  int i = 0;			// solo di servizio quando debuggo...
  while ((tobj = iter.Next ()))
    {
      string name = tobj->GetName ();

  if (use_case == 1) 
    { // Jet Multiplicity
      stringmatch = "JetMultiplicityUnfolded";
      systPathFile = plotpath + "systematicsJECMCToy_jetMult" + version + ".txt";
      fileSystematics = suffix+"systematicsJEC_jetMult" + version + ".txt"; 
    }

  if (use_case == 2) 
    { // Jet Pt
      if (whichjet == 1)
	{
	  stringmatch = "jReco_leading";
	  fileSystematics = suffix+"systematicsJEC_jet1Pt" + version + ".txt"; 
	}
      
      if (whichjet == 2)
	{
	  stringmatch = "jReco_subleading";
	  fileSystematics = suffix+"systematicsJEC_jet2Pt" + version + ".txt"; 
	}
      
      if (whichjet == 3)
	{
	  stringmatch = "jReco_subsubleading";
	  fileSystematics = suffix+"systematicsJEC_jet3Pt" + version + ".txt"; 
	}
      
      if (whichjet == 4)
	{
	  stringmatch = "jReco_subsubsubleading";
	  fileSystematics = suffix+"systematicsJEC_jet4Pt" + version + ".txt"; 
	}
    }
  
  if (use_case == 3) { // Jet Eta
    if (whichjet == 1)
      {
	stringmatch = "jReco_leadingeta";
	fileSystematics = suffix+"systematicsJEC_jet1Eta" + version + ".txt"; 
      }
    
    if (whichjet == 2)
      {
	stringmatch = "jReco_subleadingeta";
	fileSystematics = suffix+"systematicsJEC_jet2Eta" + version + ".txt"; 
      }
    
    if (whichjet == 3)
      {
	stringmatch = "jReco_subsubleadingeta";
	fileSystematics = suffix+"systematicsJEC_jet3Eta" + version + ".txt"; 
      }
    
    if (whichjet == 4)
      {
	stringmatch = "jReco_subsubsubleadingeta";
	fileSystematics = suffix+"systematicsJEC_jet4Eta" + version + ".txt"; 
      }
  }
  
  if (use_case == 4) { // Ht
    if (whichjet == 1)
      {
	stringmatch = "HReco_leading";
	fileSystematics = suffix+"systematicsJEC_jet1Ht" + version + ".txt"; 
      }
    
    if (whichjet == 2)
      {
	stringmatch = "HReco_subleading";
	fileSystematics = suffix+"systematicsJEC_jet2Ht" + version + ".txt"; 
      }
    
    if (whichjet == 3)
      {
	stringmatch = "HReco_subsubleading";
	fileSystematics = suffix+"systematicsJEC_jet3Ht" + version + ".txt"; 
      }
    
    if (whichjet == 4)
      {
	stringmatch = "HReco_subsubsubleading";
	fileSystematics = suffix+"systematicsJEC_jet4Ht" + version + ".txt"; 
      }
  }
  
   TH1D *leading;
   cout<<name<<endl;
   if (name == stringmatch) {
     gDirectory->GetObject (name.c_str (), leading);
   }

   TH1D *leading2;   

   if (name == stringmatch) {
     TFile *histof2 = TFile::Open (pathFilea2.c_str());
     histof2->cd ();
     gDirectory->GetObject (name.c_str (), leading2);
   }

   TH1D *leading3;   
   
   if (name == stringmatch) {
     TFile *histof3 = TFile::Open (pathFilea3.c_str());
     histof3->cd ();
     gDirectory->GetObject(name.c_str (), leading3);
   }
   

    }

  if (inclusive==1){
    TH1D* leadingIncl=turnExclusiveHistoInInclusive(leading);
    TH1D* leadingmuoIncl=turnExclusiveHistoInInclusive(leading2);
    TH1D* leadingthirdIncl=turnExclusiveHistoInInclusive(leading3);
    leading=leadingIncl;
    leading2=leadingmuoIncl;
    leading3=leadingthirdIncl;
  }


  
  myfile.open (fileSystematics.c_str());
  cout<<"TXT file saved in "<<fileSystematics<<endl;

  //Dividing plots
  TH1D *leadingRatioUp = (TH1D *) leading2->Clone ("leading2");
  leadingRatioUp->Divide(leading);

  TH1D *leadingRatioDown = (TH1D *) leading3->Clone ("leading3");
  leadingRatioDown->Divide(leading);
  
  for (int j=1; j<=leading->GetNbinsX(); j++){
    cout<<"central "<<leading->GetBinContent(j)<<" up "<<leading2->GetBinContent(j)<<" down "<<leading3->GetBinContent(j)<<endl;
    double syst=TMath::Max(leadingRatioUp->GetBinContent(j),1-leadingRatioDown->GetBinContent(j));
    cout<<syst<<endl;
    myfile<<syst<<endl;
  }
  myfile.close();
}
