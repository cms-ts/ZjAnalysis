#include "Unfolding/tdrstyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include "Unfolding/MakePlotLumiLabel.C"
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
#include "tdrStyle.C"
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

void
flattenJECsystematics(int whichobservable, int whichjet, int lepton)
{

  setTDRStyle ();
  gStyle->SetErrorX(0);

  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";
  //string s = "/home/schizzi/CMSSW_4_4_2/src/Histo/HistoAnalyzer/macros/plotArticleEle" + version + "/";
  string s = "/tmp/";
  string plotpath = "/gpfs/cms/data/2011/Uncertainties/";
  if (lepton == 1) plotpath = "/gpfs/cms/users/schizzi/Systematics/ele/old_PtJECJER/";
  if (lepton == 2) plotpath = "/gpfs/cms/users/schizzi/Systematics/muo/old_PtJECJER/";
  if (lepton == 3) plotpath = "/gpfs/cms/users/schizzi/Systematics/combination/";

  if (lepton == 1) string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3.root";
  if (lepton == 2) string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3Mu.root";

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
      stringstream oss;

  if (use_case == 1) 
    { // Jet Multiplicity
      stringmatch = "jMultiplicity";
      systPathFile = plotpath + "systematicsJEC_jetMult" + version + ".txt";
    }

  if (use_case == 2) 
    { // Jet Pt
      if (whichjet == 1)
	{
	  stringmatch = "jReco_leading";
	  systPathFile = plotpath + "systematicsJEC_jet1Pt" + version + ".txt";
	}
      
      if (whichjet == 2)
	{
	  stringmatch = "jReco_subleading";
	  systPathFile = plotpath + "systematicsJEC_jet2Pt" + version + ".txt";
	}
      
      if (whichjet == 3)
	{
	  stringmatch = "jReco_subsubleading";
	  systPathFile = plotpath + "systematicsJEC_jet3Pt" + version + ".txt";
	}
      
      if (whichjet == 4)
	{
	  stringmatch = "jReco_subsubsubleading";
	  systPathFile = plotpath + "systematicsJEC_jet4Pt" + version + ".txt";
	}
    }
  
  if (use_case == 3) { // Jet Eta
    if (whichjet == 1)
      {
	stringmatch = "jReco_leadingeta";
	systPathFile = plotpath + "systematicsJEC_jet1Eta" + version + ".txt";
      }
    
    if (whichjet == 2)
      {
	stringmatch = "jReco_subleadingeta";
	systPathFile = plotpath + "systematicsJEC_jet2Eta" + version + ".txt";
      }
    
    if (whichjet == 3)
      {
	stringmatch = "jReco_subsubleadingeta";
	systPathFile = plotpath + "systematicsJEC_jet3Eta" + version + ".txt";
      }
    
    if (whichjet == 4)
      {
	stringmatch = "jReco_subsubsubleadingeta";
	systPathFile = plotpath + "systematicsJEC_jet4Eta" + version + ".txt";
      }
  }
  
  if (use_case == 4) { // Ht
    if (whichjet == 1)
      {
	stringmatch = "HReco_leading";
	systPathFile = plotpath + "systematicsJEC_jet1Ht" + version + ".txt";
      }
    
    if (whichjet == 2)
      {
	stringmatch = "HReco_subleading";
	systPathFile = plotpath + "systematicsJEC_jet2Ht" + version + ".txt";
      }
    
    if (whichjet == 3)
      {
	stringmatch = "HReco_subsubleading";
	systPathFile = plotpath + "systematicsJEC_jet3Ht" + version + ".txt";
      }
    
    if (whichjet == 4)
      {
	stringmatch = "HReco_subsubsubleading";
	systPathFile = plotpath + "systematicsJEC_jet4Ht" + version + ".txt";
      }
  }
  
  
  //Open histo to access the statistics
   TH1D *leading;
   
   if (name == stringmatch) {
     gDirectory->GetObject (name.c_str (), leading);
   }
    }
  
  // read from file ---------------------------------------------
  double dat;
  ifstream inM;
  cout << "reading ...  " << systPathFile << endl;
  inM.open (systPathFile.c_str ());
  std::vector < double >systTmpM;
  while (1)
    {
      inM >> dat;
      if (!inM.good ())
	break;
      systTmpM.push_back (dat);
    }
  inM.close ();
  // ------------------------------------------------------------
  
  TH1F *systToBeFlatten=new TH1F("systToBeFlatten","systToBeFlatten",systTmpM.size(),0,systTmpM.size());
  systToBeFlatten->Sumw2();

  double area=0;
  for (int i=0; i<systTmpM.size(); i++){
    cout<<systTmpM[i]<<endl;
    double value=systTmpM[i]*leading->GetBinContent(i+1);
    systToBeFlatten->Fill(i,value);
    area+=value;
  }
  //  area=area/leading->Integral();
  systToBeFlatten->SetLineColor(kBlack);
  systToBeFlatten->Draw("HIST");

  TH1F * FlattenSys =  (TH1F*) systToBeFlatten->Clone();
  FlattenSys->Sumw2();
    
  //FlattenSys->Smooth(1000);

  FlattenSys->SetLineColor(kRed);
  FlattenSys->Draw("HISTSAME");

  cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;

  for (int j=0; j<systTmpM.size(); j++){
    cout<<area/(leading->Integral())<<endl;

  }
}
