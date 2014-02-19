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

void
scorporateStat(int whichobservable, int whichjet, int lepton)
{

  string fileSystematics; 
  string suffix="/gpfs/cms/data/2011/Systematics/postApproval/";
  if (lepton==1) suffix=suffix+"ele/";
  if (lepton==2) suffix=suffix+"muo/";

  gStyle->SetErrorX(0);

  int use_case = whichobservable;

  string version = "_v2_32";
  //string s = "/home/schizzi/CMSSW_4_4_2/src/Histo/HistoAnalyzer/macros/plotArticleEle" + version + "/";
  string s = "/tmp/";
  string plotpath = "/gpfs/cms/data/2011/Systematics/postApproval/";
  if (lepton == 1) plotpath = "/gpfs/cms/data/2011/Systematics/ele/";
  if (lepton == 2) plotpath = "/gpfs/cms/data/2011/Systematics/muo/";
  if (lepton == 3) plotpath = "/gpfs/cms/data/2011/Systematics/combination/";

  string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3NewUnfSystNoProtectionNoToy.root";
  string pathFilea2="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3NewUnfSystNoProtectionYesToy.root";

  if (lepton ==2){
  pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3NewUnfSystNoProtectionNoToyMu.root";
  pathFilea2="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3NewUnfSystNoProtectionYesToyMu.root";
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
      systPathFile = plotpath + "systematicsUnfMCToy_jetMult" + version + ".txt";
      fileSystematics = suffix+"systematicsUnf_jetMult" + version + ".txt"; 
    }

  if (use_case == 2) 
    { // Jet Pt
      if (whichjet == 1)
	{
	  stringmatch = "jReco_leading";
	  systPathFile = plotpath + "systematicsUnfMCToy_jet1Pt" + version + ".txt";
	  fileSystematics = suffix+"systematicsUnf_jet1Pt" + version + ".txt"; 
	}
      
      if (whichjet == 2)
	{
	  stringmatch = "jReco_subleading";
	  systPathFile = plotpath + "systematicsUnfMCToy_jet2Pt" + version + ".txt";
	  fileSystematics = suffix+"systematicsUnf_jet2Pt" + version + ".txt"; 
	}
      
      if (whichjet == 3)
	{
	  stringmatch = "jReco_subsubleading";
	  systPathFile = plotpath + "systematicsUnfMCToy_jet3Pt" + version + ".txt";
	  fileSystematics = suffix+"systematicsUnf_jet3Pt" + version + ".txt"; 
	}
      
      if (whichjet == 4)
	{
	  stringmatch = "jReco_subsubsubleading";
	  systPathFile = plotpath + "systematicsUnfMCToy_jet4Pt" + version + ".txt";
	  fileSystematics = suffix+"systematicsUnf_jet4Pt" + version + ".txt"; 
	}
    }
  
  if (use_case == 3) { // Jet Eta
    if (whichjet == 1)
      {
	stringmatch = "jReco_leadingeta";
	systPathFile = plotpath + "systematicsUnfMCToy_jet1Eta" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet1Eta" + version + ".txt"; 
      }
    
    if (whichjet == 2)
      {
	stringmatch = "jReco_subleadingeta";
	systPathFile = plotpath + "systematicsUnfMCToy_jet2Eta" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet2Eta" + version + ".txt"; 
      }
    
    if (whichjet == 3)
      {
	stringmatch = "jReco_subsubleadingeta";
	systPathFile = plotpath + "systematicsUnfMCToy_jet3Eta" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet3Eta" + version + ".txt"; 
      }
    
    if (whichjet == 4)
      {
	stringmatch = "jReco_subsubsubleadingeta";
	systPathFile = plotpath + "systematicsUnfMCToy_jet4Eta" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet4Eta" + version + ".txt"; 
      }
  }
  
  if (use_case == 4) { // Ht
    if (whichjet == 1)
      {
	stringmatch = "HReco_leading";
	systPathFile = plotpath + "systematicsUnfMCToy_jet1Ht" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet1Ht" + version + ".txt"; 
      }
    
    if (whichjet == 2)
      {
	stringmatch = "HReco_subleading";
	systPathFile = plotpath + "systematicsUnfMCToy_jet2Ht" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet2Ht" + version + ".txt"; 
      }
    
    if (whichjet == 3)
      {
	stringmatch = "HReco_subsubleading";
	systPathFile = plotpath + "systematicsUnfMCToy_jet3Ht" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet3Ht" + version + ".txt"; 
      }
    
    if (whichjet == 4)
      {
	stringmatch = "HReco_subsubsubleading";
	systPathFile = plotpath + "systematicsUnfMCToy_jet4Ht" + version + ".txt";
	fileSystematics = suffix+"systematicsUnf_jet4Ht" + version + ".txt"; 
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

  myfile.open (fileSystematics.c_str());
  cout<<"TXT file saved in "<<fileSystematics<<endl;

  for (int j=0; j<systTmpM.size(); j++){
    double erroreToy=fabs(1-leading2->GetBinError(j+1)/leading->GetBinError(j+1));
    double extraMCerror=systTmpM[j];
    double quadratureSum=sqrt( pow(erroreToy,2)+ pow(extraMCerror,2));
      cout<<"Bin 1 errore MC toy "<<erroreToy<<" extra MC generators error "<<extraMCerror<<" quadarture sum "<<quadratureSum<<endl;
      myfile<<quadratureSum<<endl;
  }
  myfile.close();
  
}
