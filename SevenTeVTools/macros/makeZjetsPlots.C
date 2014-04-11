#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TDirectory.h"
#include "TLine.h"
#include "MakePlotLumiLabel.C"
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
#include <string.h>


void
makeZjetsPlots (int whichobservable, int whichjet, int whichlepton, bool inclusiveMultiplicity, bool isPDFComparison)
{

  bool addPlot1EnvelopSherpa=true;
  bool addPlot2EnvelopSherpa=true;
  bool addPlot3EnvelopSherpa=true;

  bool addPlot1EnvelopPowheg=true;

  bool verboseSherpa=true;
  bool verbosePowheg=false;
  bool verboseMadGraph=false;

  setTDRStyle ();
  gStyle->SetErrorX(0.5);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);

  bool suppressContributionFromDatasetStatistics=false;

  bool absoluteNormalization=true;
  int lepton=whichlepton; //1 -> electron,  2-> muon , 3 -> combined reults!
  bool addLumiUncertainties=true; double lumiError=0.025;
  bool incMultiplicity = inclusiveMultiplicity;
  bool etaFolded = true;

  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";

  /* string s                = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v58/FinalPlotsArticle_27022014/Ele/"; */
  /* if (lepton==2) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v58/FinalPlotsArticle_27022014/Mu/"; */
  /* if (lepton==3) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v58/FinalPlotsArticle_27022014/Combined/"; */

  /* if (isPDFComparison) { */
  /*   string s                = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v58/FinalPlotsArticle_27022014/Ele/PDF/"; */
  /*   if (lepton==2) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v58/FinalPlotsArticle_27022014/Mu/PDF/"; */
  /*   if (lepton==3) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v58/FinalPlotsArticle_27022014/Combined/PDF/"; */
  /* } */

  string s                = "Ele/";
  if (lepton==2) string s = "Mu/";
  if (lepton==3) string s = "Combined/";

  if (isPDFComparison) {
    string s                = "Ele/PDF/";
    if (lepton==2) string s = "Mu/PDF/";
    if (lepton==3) string s = "Combined/PDF/";
  }

  string plotpath           = "/gpfs/cms/users/schizzi/Systematics/ele/";
  if (lepton == 2) plotpath = "/gpfs/cms/users/schizzi/Systematics/muo/";
  if (lepton == 3) plotpath = "/gpfs/cms/users/schizzi/Systematics/combination/";

  gStyle->SetOptStat (0);

  //  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 800);
  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 850);

  TFile dumphistos_file("data_rivet_histos.root","UPDATE");

  //DATA:
  string           pathFile ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_BinWidth.root";
  if (lepton == 2) pathFile ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_BinWidthMu.root";
  if (lepton == 3) pathFile ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV58_BinWidthCombined.root";

  //RIVET:
  /* string rivetPathPlot1           ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/CentralSherpa/out.root"; */

  /* string rivetPathPlot1UP         ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/FRUp/out.root"; */
  /* string rivetPathPlot1DOWN       ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/FRDown/out.root"; */

  /* string  rivetPathPlot1QUP        ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/QUp/out.root"; */
  /* string  rivetPathPlot1QDOWN      ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/QDown/out.root"; */
  /* string  rivetPathPlot1QcutUP     ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/QCutUp/out.root"; */
  /* string  rivetPathPlot1QcutDOWN   ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/QCutDown/out.root"; */
  
  /* string  rivetPathPlot1MSTW       ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/MSTW/out.root"; */
  /* string  rivetPathPlot1NNPDF      ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/NNPDF/out.root"; */
  
  /* string rivetPathPlot3         ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Madgraph/CentralMadgraph/DYToLL.root"; */
  /* string rivetPathPlot3UP       ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Madgraph/CentralMadgraph/DYToLL.root"; */
  /* string rivetPathPlot3DOWN     ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Madgraph/CentralMadgraph/DYToLL.root"; */

  /* string rivetPathPlot2           ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Powheg/CentralPowheg/scaleorig.root"; */
  /* string rivetPathPlot2UP         ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Powheg/PowhegScaleUp/scaleup.root"; */
  /* string rivetPathPlot2DOWN       ="/gpfs/cms/data/2011/Rivet/FinalDatasets/Powheg/PowhegScaleDown/scaledown.root";   */

  /* string rivetPathAlphaStrongUpVersusCT10="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/AsUp/out.root"; */
  /* string rivetPathAlphaStrongDownVersusCT10="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/AsDown/out.root"; */

  /* string rivetPathVariationPDF_CT10_down="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/CT10/CT10DownUp/Observables_CT10_down.root"; */
  /* string rivetPathVariationPDF_CT10_up="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/CT10/CT10DownUp/Observables_CT10_up.root"; */

  /* string rivetPathVariationPDF_MSTW_down="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/MSTW/MSTWDownUp/Observables_MSTW2008_down.root"; */
  /* string rivetPathVariationPDF_MSTW_up="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/MSTW/MSTWDownUp/Observables_MSTW2008_up.root"; */

  /* string rivetPathVariationPDF_NNPDF_down="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/NNPDF/NNPDFDownUp/Observables_NNPDF21_down.root"; */
  /* string rivetPathVariationPDF_NNPDF_up="/gpfs/cms/data/2011/Rivet/FinalDatasets/Sherpa/NNPDF/NNPDFDownUp/Observables_NNPDF21_up.root"; */


  string rivetPathPlot1           ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/CentralSherpa/out.root";

  string rivetPathPlot1UP         ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/FRUp/out.root";
  string rivetPathPlot1DOWN       ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/FRDown/out.root";

  string  rivetPathPlot1QUP        ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/QUp/out.root";
  string  rivetPathPlot1QDOWN      ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/QDown/out.root";
  string  rivetPathPlot1QcutUP     ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/QCutUp/out.root";
  string  rivetPathPlot1QcutDOWN   ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/QCutDown/out.root";
  
  string  rivetPathPlot1MSTW       ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/MSTW/out.root";
  string  rivetPathPlot1NNPDF      ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/NNPDF/out.root";
  
  string rivetPathPlot3         ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Madgraph/CentralMadgraph/DYToLL.root";
  string rivetPathPlot3UP       ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Madgraph/CentralMadgraph/DYToLL.root";
  string rivetPathPlot3DOWN     ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Madgraph/CentralMadgraph/DYToLL.root";

  string rivetPathPlot2           ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Powheg/CentralPowheg/scaleorig.root";
  string rivetPathPlot2UP         ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Powheg/PowhegScaleUp/scaleup.root";
  string rivetPathPlot2DOWN       ="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Powheg/PowhegScaleDown/scaledown.root";  

  string rivetPathAlphaStrongUpVersusCT10="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/AsUp/out.root";
  string rivetPathAlphaStrongDownVersusCT10="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/AsDown/out.root";

  string rivetPathVariationPDF_CT10_down="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/CT10/CT10DownUp/Observables_CT10_down.root";
  string rivetPathVariationPDF_CT10_up="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/CT10/CT10DownUp/Observables_CT10_up.root";

  string rivetPathVariationPDF_MSTW_down="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/MSTW/MSTWDownUp/Observables_MSTW2008_down.root";
  string rivetPathVariationPDF_MSTW_up="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/MSTW/MSTWDownUp/Observables_MSTW2008_up.root";

  string rivetPathVariationPDF_NNPDF_down="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/NNPDF/NNPDFDownUp/Observables_NNPDF21_down.root";
  string rivetPathVariationPDF_NNPDF_up="/gpfs/cms/users/cossutti/ZjAnalysis/2011/Rivet/20140306/Sherpa/NNPDF/NNPDFDownUp/Observables_NNPDF21_up.root";

  //Switchjing paths when we compare PDFs
  if (isPDFComparison){
    rivetPathPlot2=rivetPathPlot1MSTW;
    rivetPathPlot3=rivetPathPlot1NNPDF;

    rivetPathPlot1UP=rivetPathAlphaStrongUpVersusCT10;
    rivetPathPlot1DOWN=rivetPathAlphaStrongDownVersusCT10;
    rivetPathPlot1QUP=rivetPathVariationPDF_CT10_up;
    rivetPathPlot1QDOWN=rivetPathVariationPDF_CT10_down;

    rivetPathPlot2UP=rivetPathVariationPDF_MSTW_up;         
    rivetPathPlot2DOWN=rivetPathVariationPDF_MSTW_down;       

    rivetPathPlot3UP=rivetPathVariationPDF_NNPDF_up;         
    rivetPathPlot3DOWN=rivetPathVariationPDF_NNPDF_down;         
  }


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
  string rivet_data_minus;
  string rivet_dataMG;

  int i = 0;			// solo di servizio quando debuggo...
  while ((tobj = iter.Next ()))
    {
      string name = tobj->GetName ();
      stringstream oss;
      stringstream ossInc;

      //////////////////////////////////
      //
      //  Data - Rivet Histogram  Name Matching
      //
      //////////////////////////////////


      if (use_case == 1) 
        { // Jet Multiplicity
          stringmatch = "JetMultiplicityUnfolded";
          systPathFile = plotpath + "jetMultFinalSyst" + version + ".txt";
          if (lepton == 1) { oss<<"01"; ossInc<<"02"; }
          if (lepton == 2) { oss<<"15"; ossInc<<"16"; }
          if (lepton == 3) { oss<<"29"; ossInc<<"30"; }
        } 	   
      
      if (use_case == 2) 
        { // Jet Pt
          if (whichjet == 1)
            {
              stringmatch = "jReco_leading";
              systPathFile = plotpath + "jet1PtFinalSyst" + version + ".txt";
              if (lepton == 1 ) oss<<"03"; 
              if (lepton == 2 ) oss<<"17";
              if (lepton == 3 ) oss<<"31";
            }
          if (whichjet == 2)
            {
              stringmatch = "jReco_subleading";
              systPathFile = plotpath + "jet2PtFinalSyst" + version + ".txt";
              if (lepton == 1 ) oss<<"04"; 
              if (lepton == 2 ) oss<<"18";
              if (lepton == 3 ) oss<<"32";
            }
          if (whichjet == 3)
            {
              stringmatch = "jReco_subsubleading";
              systPathFile = plotpath + "jet3PtFinalSyst" + version + ".txt";
              if (lepton == 1 ) oss<<"05"; 
              if (lepton == 2 ) oss<<"19";
              if (lepton == 3 ) oss<<"33";
            }
          if (whichjet == 4)
            {
              stringmatch = "jReco_subsubsubleading";
              systPathFile = plotpath + "jet4PtFinalSyst" + version + ".txt";
              if (lepton == 1 ) oss<<"06"; 
              if (lepton == 2 ) oss<<"20";
              if (lepton == 3 ) oss<<"34";
            }
        }
      if (use_case == 3) { // Jet Eta
        if (whichjet == 1)
          {
            stringmatch = "jReco_leadingeta";
            systPathFile = plotpath + "jet1EtaFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"07"; 
            if (lepton == 2 ) oss<<"21";
            if (lepton == 3 ) oss<<"35";
          }
        if (whichjet == 2)
          {
            stringmatch = "jReco_subleadingeta";
            systPathFile = plotpath + "jet2EtaFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"08"; 
            if (lepton == 2 ) oss<<"22";
            if (lepton == 3 ) oss<<"36";
          }
        if (whichjet == 3)
          {
            stringmatch = "jReco_subsubleadingeta";
            systPathFile = plotpath + "jet3EtaFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"09"; 
            if (lepton == 2 ) oss<<"23";
            if (lepton == 3 ) oss<<"37";
          }
        if (whichjet == 4)
          {
            stringmatch = "jReco_subsubsubleadingeta";
            systPathFile = plotpath + "jet4EtaFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"10"; 
            if (lepton == 2 ) oss<<"24";
            if (lepton == 3 ) oss<<"38";
          }
      }
      if (use_case == 4) { // Ht
        if (whichjet == 1)
          {
            stringmatch = "HReco_leading";
            systPathFile = plotpath + "jet1HtFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"11"; 
            if (lepton == 2 ) oss<<"25";
            if (lepton == 3 ) oss<<"39";
          }
        if (whichjet == 2)
          {
            stringmatch = "HReco_subleading";
            systPathFile = plotpath + "jet2HtFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"12"; 
            if (lepton == 2 ) oss<<"26";
            if (lepton == 3 ) oss<<"40";
          }
        if (whichjet == 3)
          {
            stringmatch = "HReco_subsubleading";
            systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"13"; 
            if (lepton == 2 ) oss<<"27";
            if (lepton == 3 ) oss<<"41";
          }
        if (whichjet == 4)
          {
            stringmatch = "HReco_subsubsubleading";
            systPathFile = plotpath + "jet4HtFinalSyst" + version + ".txt";
            if (lepton == 1 ) oss<<"14"; 
            if (lepton == 2 ) oss<<"28";
            if (lepton == 3 ) oss<<"42";
          }
      }

      string rivetname="d"+oss.str()+"_x01_y01";
      string rivetnameMG="d"+oss.str()+"_x01_y01";
      rivet_data_minus="d"+oss.str()+"-x01-y01";
      if (incMultiplicity) {
        rivetname="d"+ossInc.str()+"_x01_y01";
        rivetnameMG="d"+ossInc.str()+"-x01-y01";
        rivet_data_minus="d"+ossInc.str()+"-x01-y01";
      }


      rivet_data    = rivetname;
      rivet_dataMG    = rivetnameMG;
      
      if (name == stringmatch) {

        cout << "CONFIGURATION:" << endl;
        cout << "stringmatch: " <<stringmatch<< endl;
        cout << "systPathFile: " <<systPathFile<< endl;
        cout << "rivet_data: " <<rivet_data<< endl;

        gPad->SetLogy (1);
        TH1D *leading;
        gDirectory->GetObject (name.c_str (), leading);
        if (incMultiplicity) {
          for (int dd=1; dd<=leading->GetNbinsX(); dd++) {
            double inclusiveYield=0.0;
            double inclusiveYieldUnc=0.0;
            for (int ff=dd; ff<=leading->GetNbinsX(); ff++) {
              inclusiveYield=inclusiveYield + leading->GetBinContent(ff);
              inclusiveYieldUnc=sqrt(inclusiveYieldUnc*inclusiveYieldUnc + leading->GetBinError(ff)*leading->GetBinError(ff));
            }
            leading->SetBinContent(dd,inclusiveYield);
          }
        }


        // CIUSKI in order to fold ETA distributions
        if (etaFolded && use_case==3) {
          double wmean, wsigma;
          for (int mdm=(leading->GetNbinsX()/2)+1; mdm<=leading->GetNbinsX(); mdm++) {
            wmean =   leading->GetBinContent(mdm) + leading->GetBinContent(leading->GetNbinsX()-mdm+1);
            wsigma = sqrt((leading->GetBinError(mdm)*leading->GetBinError(mdm)) 
                          + (leading->GetBinError(leading->GetNbinsX()-mdm+1)*leading->GetBinError(leading->GetNbinsX()-mdm+1)));
            leading->SetBinContent(mdm,wmean);
            leading->SetBinError(mdm,wsigma);
          }
        }

        TH1D *leadingEta;
        leadingEta = (TH1D *) leading->Clone ("leading");
        if (etaFolded && use_case==3) {
          leadingEta->SetBins(leading->GetNbinsX()/2,0.0,2.4);
          for (int mdn=1; mdn<=leadingEta->GetNbinsX(); mdn++) {
            leadingEta->SetBinContent(mdn,leading->GetBinContent((leading->GetNbinsX()/2)+mdn));
            leadingEta->SetBinError(mdn,leading->GetBinError((leading->GetNbinsX()/2)+mdn));
          }
        }

        TH1D *leadingSystematics;
        leadingSystematics = (TH1D *) leading->Clone ("leading");

        leadingSystematics->SetMarkerSize(0.9);
        leading->SetMarkerSize(0.9);

        // read from file ---------------------------------------------
        double dat;
        ifstream inM;
        inM.open (systPathFile.c_str ());
        //int l2 =0;
        std::vector < double >systTmpM;
        while (1)
          {
            inM >> dat;
            if (!inM.good ())
              break;
            if (addLumiUncertainties) {
              dat=pow(dat*dat+lumiError*lumiError,0.5);
            }
            systTmpM.push_back (dat);
            //l2++;  
          }
        inM.close ();



        // ------------------------------------------------------------
        // ------------------------------------------------------------
        // Get RIVET data: --------------------------------------------
        // ------------------------------------------------------------
        // ------------------------------------------------------------
        // ------------------------------------------------------------

        ////////////
        //Plot1
        ////////////

        TGraphAsymmErrors *leadingRivetPlot1=returnTGraphFromFile(rivetPathPlot1, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case, true);
        TGraphAsymmErrors *leadingRivetPlot1Stat;
        leadingRivetPlot1Stat = (TGraphAsymmErrors *) leadingRivetPlot1->Clone ("");
        TGraphAsymmErrors *leadingRatioPlot1Stat;
        leadingRatioPlot1Stat = (TGraphAsymmErrors *) leadingRivetPlot1->Clone ("");
        TGraphAsymmErrors *leadingRatioPlot1;
        leadingRatioPlot1 = (TGraphAsymmErrors *) leadingRivetPlot1->Clone ("");
 
        TGraphAsymmErrors *leadingRivetPlot1UP=returnTGraphFromFile(rivetPathPlot1UP, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
        TGraphAsymmErrors *leadingRivetPlot1DOWN=returnTGraphFromFile(rivetPathPlot1DOWN, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);

        TGraphAsymmErrors *leadingRivetPlot1QcutUP=returnTGraphFromFile(rivetPathPlot1QcutUP, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
        TGraphAsymmErrors *leadingRivetPlot1QcutDOWN=returnTGraphFromFile(rivetPathPlot1QcutDOWN, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);

        TGraphAsymmErrors *leadingRivetPlot1QUP=returnTGraphFromFile(rivetPathPlot1QUP, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
        TGraphAsymmErrors *leadingRivetPlot1QDOWN=returnTGraphFromFile(rivetPathPlot1QDOWN, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);


        /////////////
        // Plot2
        /////////////

        TGraphAsymmErrors *leadingRivetPlot2=returnTGraphFromFile(rivetPathPlot2, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
        TGraphAsymmErrors *leadingRivetPlot2Stat;
        leadingRivetPlot2Stat = (TGraphAsymmErrors *) leadingRivetPlot2->Clone ("");
        TGraphAsymmErrors *leadingRatioPlot2Stat;
        leadingRatioPlot2Stat = (TGraphAsymmErrors *) leadingRivetPlot2->Clone ("");
        TGraphAsymmErrors *leadingRatioPlot2;
        leadingRatioPlot2 = (TGraphAsymmErrors *) leadingRivetPlot2->Clone ("");

        TGraphAsymmErrors *leadingRivetPlot2UP=returnTGraphFromFile(rivetPathPlot2UP, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
        TGraphAsymmErrors *leadingRivetPlot2DOWN=returnTGraphFromFile(rivetPathPlot2DOWN, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
	

        /////////////////
        // Madgraph
        /////////////////

        //Central value

        TGraphAsymmErrors *leadingRivetPlot3=returnTGraphFromFile(rivetPathPlot3, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
        TGraphAsymmErrors *leadingRatioPlot3;
        leadingRatioPlot3 = (TGraphAsymmErrors *) leadingRivetPlot3->Clone ("");

        TGraphAsymmErrors *leadingRivetPlot3UP=returnTGraphFromFile(rivetPathPlot3UP, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);
        TGraphAsymmErrors *leadingRivetPlot3DOWN=returnTGraphFromFile(rivetPathPlot3DOWN, rivet_data, rivet_data_minus, etaFolded, isPDFComparison, use_case,true);

        std::vector<double> data;
        std::vector<double> MC;
        std::vector<double> MCstat;
        std::vector<double> MCstFR_up;
        std::vector<double> MCstFRQ_up;
        std::vector<double> MCstFRQQcut_up;
        std::vector<double> MCstFR_down;
        std::vector<double> MCstFRQ_down;
        std::vector<double> MCstFRQQcut_down;


        // ------------------------------------------------------------
        // ------------------------------------------------------------
        // Get Systematics and data: --------------------------------------------
        // ------------------------------------------------------------
        // ------------------------------------------------------------
        // ------------------------------------------------------------

	
        leadingSystematics->SetName ("leadingSystematics");
        if (systTmpM.size () != leadingSystematics->GetNbinsX ())
          cout << "WRONG NUMBER OF BINS (# syst from file->" <<systTmpM.size()<<" - # bins leadingsystematics->"<<leadingSystematics->GetNbinsX()<<")"<<endl;

        if (!incMultiplicity){
          for (int i = 0; i < leadingSystematics->GetNbinsX (); i++)
            {
              double err, wmeanstat;
              if (etaFolded && use_case==3) { // MEGA CIUSKI per Eta FOLDED
                for (int mdm=(leading->GetNbinsX()/2)+1; mdm<=leading->GetNbinsX(); mdm++) {
                  wmeanstat =   (systTmpM[mdm-1]*leading->GetBinContent(mdm) 
                                 + systTmpM[leading->GetNbinsX()-mdm]*leading->GetBinContent(leading->GetNbinsX()-mdm+1)) 
                    / (leading->GetBinContent(mdm) + leading->GetBinContent(leading->GetNbinsX()-mdm+1));
                  err = sqrt (pow (leading->GetBinError(mdm), 2) + pow (wmeanstat*leadingSystematics->GetBinContent(mdm), 2));
                  leadingSystematics->SetBinError(mdm,err);
                }
              } else {
                err = sqrt (pow (leading->GetBinError (i + 1), 2) + pow (systTmpM[i] * leadingSystematics->GetBinContent (i + 1), 2));
                leadingSystematics->SetBinError (i + 1, err);
              }
            }
        } else {
          for (int i = 0; i < leadingSystematics->GetNbinsX (); i++)
            {
              double temperr = 0.0;
              for (int cc = i; cc < leadingSystematics->GetNbinsX (); cc++) {
                temperr = sqrt(pow(temperr,2) + pow(systTmpM[cc]*leadingSystematics->GetBinContent(cc + 1),2));
              }
              double err = sqrt (pow (leading->GetBinError (i + 1), 2) + pow (temperr, 2));
              leadingSystematics->SetBinError (i + 1, err);
            }

        }

        if ( (!absoluteNormalization) && (leadingSystematics->Integral()>1.001 | leadingSystematics->Integral()<0.999)) {
          cout << "Warning: DATA is NOT NORMALIZED CORRECTLY! I will fix it...";
          leadingSystematics->Scale(1./leadingSystematics->Integral());
          leading->Scale(1./leading->Integral());
        }

        TH1D *leadingSystematicsEta;
        leadingSystematicsEta = (TH1D *) leadingEta->Clone ("leadingEta");
        if (etaFolded && use_case==3) {
          for (int mdn=1; mdn<=leadingSystematicsEta->GetNbinsX(); mdn++) {
            leadingSystematicsEta->SetBinContent(mdn,leadingSystematics->GetBinContent((leading->GetNbinsX()/2)+mdn));
            leadingSystematicsEta->SetBinError(mdn,leadingSystematics->GetBinError((leading->GetNbinsX()/2)+mdn));
          }
        }


        /////////////////
        //
        //  Draw First Canvas (UP)
        /////////////////

 
        plots->cd ();
        TPad *pad1 = new TPad("pad1","pad1",0.01,0.55,0.99,0.99);

        pad1->Draw();
        pad1->cd();
        pad1->SetTopMargin(0.1);
        pad1->SetBottomMargin(0.0);
        pad1->SetRightMargin(0.1);
        pad1->SetFillStyle(0);
        if (use_case !=3) pad1->SetLogy(1); 
        else pad1->SetLogy(0);

        if (use_case ==2){
          if ( whichjet == 1 ) leadingSystematics->SetMinimum(0.1*leadingSystematics->GetMinimum());
        }
        if (use_case ==3){
          leadingSystematics->SetMinimum((0.5-0.05*(whichjet-1))*leadingSystematics->GetMinimum());
          leadingSystematics->SetMaximum((1.25+0.35*(whichjet-1))*leadingSystematics->GetMaximum());
          if ( whichjet == 3 || whichjet == 4 ) leadingSystematics->SetMaximum(0.65*leadingSystematics->GetMaximum());
        }

        leadingSystematics->SetLineColor (kBlack);
        leadingSystematics->SetLineWidth (0.);
        leadingSystematics->SetMarkerStyle (20);
        leadingSystematics->SetFillColor (12);
        leadingSystematics->SetFillStyle (3004);
        leadingSystematics->SetMarkerColor (kBlack);

        leadingSystematics->GetXaxis()->SetTitleOffset (2.);
        leadingSystematics->GetXaxis()->SetTitleFont (43);
        leadingSystematics->GetXaxis()->SetTitleSize (25);
        leadingSystematics->GetXaxis()->SetLabelFont (43);
        leadingSystematics->GetXaxis()->SetLabelSize (22);

        leadingSystematics->GetYaxis()->SetTitleOffset (2.5);
        leadingSystematics->GetYaxis()->SetTitleFont (43);
        leadingSystematics->GetYaxis()->SetTitleSize (25);
        leadingSystematics->GetYaxis()->SetLabelFont (43);
        leadingSystematics->GetYaxis()->SetLabelSize (22);

        leadingSystematics->SetTitle();
        leadingSystematics->GetXaxis()->SetTitle ();

        if (use_case ==1) {
          if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("#sigma(Z/#gamma*#rightarrow ll + N_{jet}) [pb]");
        }

        if (use_case ==2) {
          if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dp_{T} [pb/GeV]");
        }

        if (use_case ==3) {
          if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/d#eta [pb]");
        }
	  
        if (use_case ==4) {
          if (absoluteNormalization && whichjet==1) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dH_{T} [pb/GeV]");
          if (absoluteNormalization && whichjet==2) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dH_{T} [pb/GeV]");
          if (absoluteNormalization && whichjet==3) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dH_{T} [pb/GeV]");
          if (absoluteNormalization && whichjet==4) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dH_{T} [pb/GeV]");
        }

        if (etaFolded && use_case==3) leadingSystematics->GetXaxis()->SetRange((leadingSystematics->GetNbinsX()/2)+1,leadingSystematics->GetNbinsX());  
        leadingSystematics->Draw ("E2");
        if (use_case ==1) leadingSystematics->GetXaxis()->SetNdivisions(110);
        leading->SetFillColor (kBlack);
        leading->SetFillStyle (3001);
        leading->SetMarkerColor (kBlack);
        leading->SetLineColor (kBlack);
        leading->SetLineWidth (0.);
        leading->SetMarkerStyle (20);
        leading->Draw ("E1SAME");
	
        TH1D *leadingRatio;
        TH1D *leadingRatio2;
        TH1D *leadingRatio3;
        leadingRatio = (TH1D *) leading->Clone ("leading");
        leadingRatio2 = (TH1D *) leading->Clone ("leading");
        leadingRatio3 = (TH1D *) leading->Clone ("leading");
        TH1D *leadingRatioSystematics;
        TH1D *leadingRatio2Systematics;
        TH1D *leadingRatio3Systematics;
        leadingRatioSystematics = (TH1D *) leadingSystematics->Clone ("leading");
        leadingRatio2Systematics = (TH1D *) leadingSystematics->Clone ("leading");
        leadingRatio3Systematics = (TH1D *) leadingSystematics->Clone ("leading");

        // Superimpose RIVET: -----------------------
        Double_t dummyXvar=0.;
        Double_t dummyYvar=0.;
        Int_t nRivetPoints = 0;
        Double_t dummyNorm = 0.;
	

        /////////////////////////////////////////
        ////////
        ////////
        //////// Get Ratio Plots and make the Envelops
        ////////
        ////////
        /////////////////////////////////////////

        ///////////
        // SHERPA:
        ////////////
	
        nRivetPoints = leadingRivetPlot1->GetN();
	
        std::vector<double> DeltaAsUp_CT10_Ratio;
        std::vector<double> DeltaAsDown_CT10_Ratio;

        Double_t dummyNorm = 0.;
        Double_t y1temp = 0.;
        Double_t y2temp = 0.;
        Double_t x1temp = 0.;
        Double_t x2temp = 0.;

        std::vector<double> DeltaAsUp_CT10_Ratio;
        std::vector<double> DeltaAsDown_CT10_Ratio;

        if (addPlot1EnvelopSherpa){
	  
          for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
            leadingRivetPlot1->GetPoint(ovo,dummyXvar,dummyYvar); 
            leadingRivetPlot1DOWN->GetPoint(ovo,x1temp,y1temp); 
            leadingRivetPlot1UP->GetPoint(ovo,x2temp,y2temp); 

            if (absoluteNormalization) {
              dummyNorm= (1.0);
              if (lepton ==3) {
                //dummyNorm= dummyNorm*2.0;
                //y1temp=y1temp/2.0;	    
                //y2temp=y2temp/2.0;
              }
            }

            // This will adapt the folded Rivet to the unfolded data distributions for eta.
            Int_t ovoCorrected=ovo;
            if (whichobservable==3) ovoCorrected=ovo+leadingSystematics->GetNbinsX()/2;

            //Set Ratio plots
            leadingRatioPlot1->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovoCorrected+1));
            leadingRatioPlot1Stat->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovoCorrected+1));
            leadingRatioPlot1Stat->SetPointEYhigh(ovo,(leadingRatioPlot1->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
            leadingRatioPlot1Stat->SetPointEYlow(ovo,(leadingRatioPlot1->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));

            leadingRivetPlot1->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
            leadingRivetPlot1Stat->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);

            leadingRivetPlot1->SetPointEYhigh(ovo,sqrt(pow(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm,2) + pow(leadingRivetPlot1Stat->GetErrorYhigh(ovo),2)));
            leadingRivetPlot1->SetPointEYlow(ovo,sqrt(pow(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm,2) + pow(leadingRivetPlot1Stat->GetErrorYlow(ovo),2)));
	    
            leadingRatioPlot1->SetPointEYhigh(ovo,sqrt(pow((max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm),2) + pow(leadingRatioPlot1Stat->GetErrorYhigh(ovo),2)));
            leadingRatioPlot1->SetPointEYlow(ovo, sqrt(pow((-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm),2) + pow(leadingRatioPlot1Stat->GetErrorYlow(ovo),2)));

            leadingRatio->SetBinContent(ovoCorrected+1,1.0);
            leadingRatio->SetBinError(ovoCorrected+1,leading->GetBinError(ovoCorrected+1)/leading->GetBinContent(ovoCorrected+1));

            //Filling DeltaAsForTheOtherPDF

            DeltaAsUp_CT10_Ratio.push_back( (max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm) );
            DeltaAsDown_CT10_Ratio.push_back( (-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	    
            leadingRatioSystematics->SetBinContent(ovoCorrected+1,1.0);
            leadingRatioSystematics->SetBinError(ovoCorrected+1,leadingSystematics->GetBinError(ovoCorrected+1)/leadingSystematics->GetBinContent(ovoCorrected+1));

            //Some debugging...
            if (verboseSherpa){
              cout<<"Bin "<<ovo<<endl;
              cout<<"statistics envelop, high "<<leadingRatioPlot1Stat->GetErrorYhigh(ovo)<<endl;
              cout<<"statistics envelop, low "<<leadingRatioPlot1Stat->GetErrorYlow(ovo)<<endl;
              cout<<"statistics envelop + FR envelop, high "<<leadingRatioPlot1->GetErrorYhigh(ovo)<<endl;
              cout<<"statistics envelop + FR envelop, low "<<leadingRatioPlot1->GetErrorYlow(ovo)<<endl;
              Double_t dumX,dumY;
              data.push_back(leadingSystematics->GetBinContent(ovoCorrected+1));
              //          std::cout << "data " << data[ovo] << std::endl;
              leadingRivetPlot1->GetPoint(ovo,dumX,dumY);
              MC.push_back(dumY);
              //          std::cout << "MC   " << MC[ovo] << std::endl;
              MCstat.push_back(0.5*(leadingRatioPlot1Stat->GetErrorYhigh(ovo)+leadingRatioPlot1Stat->GetErrorYlow(ovo))*data[ovo]);
              MCstFR_up.push_back(leadingRatioPlot1->GetErrorYhigh(ovo)*data[ovo]);
              MCstFR_down.push_back(leadingRatioPlot1->GetErrorYlow(ovo)*data[ovo]);
            }
          }
        }

        // Q envelop for Plot1:
        TGraphAsymmErrors *leadingRivetPlot1Q;
        leadingRivetPlot1Q = (TGraphAsymmErrors *) leadingRivetPlot1->Clone ();
        TGraphAsymmErrors *leadingRatioPlot1Q;
        leadingRatioPlot1Q = (TGraphAsymmErrors *) leadingRatioPlot1->Clone ();
	
        Double_t y1temp = 0.;
        Double_t y2temp = 0.;
        Double_t x1temp = 0.;
        Double_t x2temp = 0.;
        Double_t r1temp = 0.;
        Double_t r2temp = 0.;
	
        //Adding first envelop
	
        if (addPlot2EnvelopSherpa){
	  
          for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
            leadingRivetPlot1Q->GetPoint(ovo,dummyXvar,dummyYvar); 
            leadingRivetPlot1QUP->GetPoint(ovo,x1temp,y1temp); 
            leadingRivetPlot1QDOWN->GetPoint(ovo,x2temp,y2temp); 
	    
            if (absoluteNormalization) {
              dummyNorm= (1.0);
              if (lepton ==3) {
                //dummyNorm= dummyNorm*2.0;
                //y1temp=y1temp/2.0;	    
                //y2temp=y2temp/2.0;
              }
            }

            leadingRivetPlot1Q->SetPointEYhigh(ovo,sqrt(pow(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm,2) + pow(leadingRivetPlot1->GetErrorYhigh(ovo),2)));
            leadingRivetPlot1Q->SetPointEYlow(ovo,sqrt(pow(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm,2) + pow(leadingRivetPlot1->GetErrorYlow(ovo),2)));
            leadingRatioPlot1->GetPoint(ovo,r1temp,r2temp);
            leadingRatioPlot1Q->SetPoint(ovo,r1temp,r2temp);
            leadingRatioPlot1Q->SetPointEYhigh(ovo,sqrt(pow((max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/dummyYvar/dummyNorm,2) + pow(leadingRatioPlot1->GetErrorYhigh(ovo),2)));
            leadingRatioPlot1Q->SetPointEYlow(ovo, sqrt(pow((-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/dummyYvar/dummyNorm,2) + pow(leadingRatioPlot1->GetErrorYlow(ovo),2)));

            //Some debugging...
            if (verboseSherpa){
              cout<<"Bin "<<ovo<<endl;
              cout<<"statistics envelop + FR envelop, high "<<leadingRatioPlot1->GetErrorYhigh(ovo)<<endl;
              cout<<"statistics envelop + FR envelop, low "<<leadingRatioPlot1->GetErrorYlow(ovo)<<endl;
              cout<<"statistics envelop + FR envelop + QUP, high "<<leadingRatioPlot1Q->GetErrorYhigh(ovo)<<endl;
              cout<<"statistics envelop + FR envelop + QDOWN, low "<<leadingRatioPlot1Q->GetErrorYlow(ovo)<<endl;
              MCstFRQ_up.push_back(leadingRatioPlot1Q->GetErrorYhigh(ovo)*data[ovo]);
              MCstFRQ_down.push_back(leadingRatioPlot1Q->GetErrorYlow(ovo)*data[ovo]);
            }
          }
        }
        TGraphAsymmErrors *leadingRivetPlot1Qcut;
        leadingRivetPlot1Qcut = (TGraphAsymmErrors *) leadingRivetPlot1->Clone ();
        TGraphAsymmErrors *leadingRatioPlot1Qcut;
        leadingRatioPlot1Qcut = (TGraphAsymmErrors *) leadingRatioPlot1->Clone ();

	    Double_t y1temp = 0.;
	    Double_t y2temp = 0.;
	    Double_t x1temp = 0.;
	    Double_t x2temp = 0.;
	    Double_t r1temp = 0.;
	    Double_t r2temp = 0.;

        if (addPlot3EnvelopSherpa){
          // Qcut envelop for Plot1:

          if (!isPDFComparison){
            for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
              leadingRivetPlot1Q->GetPoint(ovo,dummyXvar,dummyYvar); 
              leadingRivetPlot1QUP->GetPoint(ovo,x1temp,y1temp); 
              leadingRivetPlot1QDOWN->GetPoint(ovo,x2temp,y2temp); 
	      
              for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
                leadingRivetPlot1Qcut->GetPoint(ovo,dummyXvar,dummyYvar); 
                leadingRivetPlot1QcutUP->GetPoint(ovo,x1temp,y1temp); 
                leadingRivetPlot1QcutDOWN->GetPoint(ovo,x2temp,y2temp); 
		
                if (absoluteNormalization) {
                  dummyNorm= (1.0);
                  if (lepton ==3) {
                    //dummyNorm= dummyNorm*2.0;
                    //y1temp=y1temp/2.0;	    
                    //y2temp=y2temp/2.0;
                  }
                }
		
                leadingRivetPlot1Qcut->SetPointEYhigh(ovo,sqrt(pow(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm,2) + pow(leadingRivetPlot1Q->GetErrorYhigh(ovo),2)));
                leadingRivetPlot1Qcut->SetPointEYlow(ovo,sqrt(pow(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm,2) + pow(leadingRivetPlot1Q->GetErrorYlow(ovo),2)));
                leadingRatioPlot1Q->GetPoint(ovo,r1temp,r2temp);
                leadingRatioPlot1Qcut->SetPoint(ovo,r1temp,r2temp);
                leadingRatioPlot1Qcut->SetPointEYhigh(ovo,sqrt(pow((max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/dummyYvar/dummyNorm,2) + pow(leadingRatioPlot1Q->GetErrorYhigh(ovo),2)));
                leadingRatioPlot1Qcut->SetPointEYlow(ovo, sqrt(pow((-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/dummyYvar/dummyNorm,2) + pow(leadingRatioPlot1Q->GetErrorYlow(ovo),2)));

                //Some debugging...
                if (verboseSherpa){
                  cout<<"Bin "<<ovo<<endl;
                  cout<<"statistics envelop + FR envelop + QUP, high "<<leadingRatioPlot1Q->GetErrorYhigh(ovo)<<endl;
                  cout<<"statistics envelop + FR envelop + QDOWN, low "<<leadingRatioPlot1Q->GetErrorYlow(ovo)<<endl;
                  cout<<"statistics envelop + FR envelop + QUP + QcutUP, high "<<leadingRatioPlot1Qcut->GetErrorYhigh(ovo)<<endl;
                  cout<<"statistics envelop + FR envelop + QDOWN + QcutUP, low "<<leadingRatioPlot1Qcut->GetErrorYlow(ovo)<<endl;
                  MCstFRQQcut_up.push_back(leadingRatioPlot1Qcut->GetErrorYhigh(ovo)*data[ovo]);
                  MCstFRQQcut_down.push_back(leadingRatioPlot1Qcut->GetErrorYlow(ovo)*data[ovo]);
                }
              }
            }
          }
        }

        std::vector<double> tsyst_up;
        std::vector<double> tsyst_down;
        if ( isPDFComparison ) {
          tsyst_up = MCstFRQ_up;
          tsyst_down = MCstFRQ_down;
        }
        else {
          tsyst_up = MCstFRQQcut_up;
          tsyst_down = MCstFRQQcut_down;
        }

        //               123456789012345678901234567890123456789012345678901234567890
        std::cout << "Bin    Sherpa      stat   syst-up syst-down    tot-up  tot-down" << std::endl;
        for ( Int_t i = 0; i < MC.size(); i++ ) {
          std::cout << std::setfill(' ') << std::setw(3) << std::fixed << std::setprecision(0) << i+1
                    << std::setfill(' ') << std::setw(10) << std::fixed << std::setprecision(5) << MC[i]
                    << std::setfill(' ') << std::setw(10) << std::fixed << std::setprecision(5) << MCstat[i]
                    << std::setfill(' ') << std::setw(10) << std::fixed << std::setprecision(5) << std::sqrt(tsyst_up[i]*tsyst_up[i]-MCstat[i]*MCstat[i])
                    << std::setfill(' ') << std::setw(10) << std::fixed << std::setprecision(5) << std::sqrt(tsyst_down[i]*tsyst_down[i]-MCstat[i]*MCstat[i])
                    << std::setfill(' ') << std::setw(10) << std::fixed << std::setprecision(5) << tsyst_up[i]
                    << std::setfill(' ') << std::setw(10) << std::fixed << std::setprecision(5) << tsyst_down[i]
                    << std::endl;
        }


        ///////////////	
        // POWHEG:
        ///////////////
	
        nRivetPoints = leadingRivetPlot2->GetN();

        // Plot2 FR-Up

        Double_t dummyNorm = 0.;
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          leadingRivetPlot2UP->GetPoint(ovo,dummyXvar,dummyYvar); 
          dummyNorm = dummyNorm + dummyYvar;
        }
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          if (absoluteNormalization) {
            dummyNorm= 1.0;
            //if (lepton ==3) dummyNorm= dummyNorm*2.0;
          }
          leadingRivetPlot2UP->GetPoint(ovo,dummyXvar,dummyYvar);
          leadingRivetPlot2UP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
          leadingRivetPlot2UP->SetPointEYhigh(ovo,leadingRivetPlot2UP->GetErrorYhigh(ovo)/dummyNorm);
          leadingRivetPlot2UP->SetPointEYlow(ovo,leadingRivetPlot2UP->GetErrorYlow(ovo)/dummyNorm);
        }

        // Plot2 Down
        Double_t dummyNorm = 0.;
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          leadingRivetPlot2DOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
          dummyNorm = dummyNorm + dummyYvar;
        }
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          if (absoluteNormalization) {
            dummyNorm= (1.0);
            //if (lepton ==3) dummyNorm= dummyNorm*2.0;
            //dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1));
          }
          leadingRivetPlot2DOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
          leadingRivetPlot2DOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
          leadingRivetPlot2DOWN->SetPointEYhigh(ovo,leadingRivetPlot2DOWN->GetErrorYhigh(ovo)/dummyNorm);
          leadingRivetPlot2DOWN->SetPointEYlow(ovo,leadingRivetPlot2DOWN->GetErrorYlow(ovo)/dummyNorm);
        }

        // Plot2 centrale
        Double_t dummyNorm = 0.;
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          leadingRivetPlot2Stat->GetPoint(ovo,dummyXvar,dummyYvar); 
          dummyNorm = dummyNorm + dummyYvar;
        }
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          if (absoluteNormalization) {
            if (lepton ==1) dummyNorm= (1.0);
            if (lepton ==2) dummyNorm= (1.0);
            if (lepton ==3) dummyNorm= (1.0);
          }

          Int_t ovoCorrected=ovo;
          if (whichobservable==3) ovoCorrected=ovo+leadingSystematics->GetNbinsX()/2;

          leadingRivetPlot2Stat->GetPoint(ovo,dummyXvar,dummyYvar); 
          leadingRivetPlot2Stat->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
          leadingRivetPlot2Stat->SetPointEYhigh(ovo,leadingRivetPlot2Stat->GetErrorYhigh(ovo)/dummyNorm);
          leadingRivetPlot2Stat->SetPointEYlow(ovo,leadingRivetPlot2Stat->GetErrorYlow(ovo)/dummyNorm);
          leadingRatioPlot2Stat->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovoCorrected+1));
          leadingRatioPlot2Stat->SetPointEYhigh(ovo,(leadingRivetPlot2Stat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
          leadingRatioPlot2Stat->SetPointEYlow(ovo,(leadingRivetPlot2Stat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));
        }

        //Double_t dummyNorm = 0.;
        //Double_t y1temp = 0.;
        //Double_t y2temp = 0.;
        //Double_t x1temp = 0.;
        //Double_t x2temp = 0.;
        //for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
        //leadingRivetPlot2->GetPoint(ovo,dummyXvar,dummyYvar); 
        //dummyNorm = dummyNorm + dummyYvar;
        //}
	
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          leadingRivetPlot2->GetPoint(ovo,dummyXvar,dummyYvar); 

          if (absoluteNormalization) {
            if (lepton ==1) dummyNorm= (1.0);
            if (lepton ==2) dummyNorm= (1.0);
            //if (lepton ==3) dummyNorm= (2.0);
            //dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
          }

          Int_t ovoCorrected=ovo;
          if (whichobservable==3) ovoCorrected=ovo+leadingSystematics->GetNbinsX()/2;

          //leadingRivetPlot2->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
          //leadingRivetPlot2->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetPlot2Stat->GetErrorYhigh(ovo));
          //leadingRivetPlot2->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetPlot2Stat->GetErrorYlow(ovo));

          //Here I am adding zeros...
          //leadingRatioPlot2->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovoCorrected+1));
          //leadingRatioPlot2->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetPlot2Stat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
          //leadingRatioPlot2->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetPlot2Stat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));
	  
          leadingRatio3->SetBinContent(ovoCorrected+1,1.0);
          leadingRatio3->SetBinError(ovoCorrected+1,leading->GetBinError(ovoCorrected+1)/leading->GetBinContent(ovoCorrected+1));

          leadingRatio3Systematics->SetBinContent(ovoCorrected+1,1.0);
          leadingRatio3Systematics->SetBinError(ovoCorrected+1,leadingSystematics->GetBinError(ovoCorrected+1)/leadingSystematics->GetBinContent(ovoCorrected+1));

        }

        // 2nd envelop for Plot2:
        TGraphAsymmErrors *leadingRivetPlot22ENV;
        leadingRivetPlot22ENV = (TGraphAsymmErrors *) leadingRivetPlot2Stat->Clone ();
        TGraphAsymmErrors *leadingRatioPlot22ENV;
        leadingRatioPlot22ENV = (TGraphAsymmErrors *) leadingRatioPlot2Stat->Clone ();

        Double_t y1temp = 0.;
        Double_t y2temp = 0.;
        Double_t x1temp = 0.;
        Double_t x2temp = 0.;
        Double_t r1temp = 0.;
        Double_t r2temp = 0.;
	
        if (lepton ==3) dummyNorm= (1.0); //Ratio plots do not need correction for combination!

        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          leadingRivetPlot22ENV->GetPoint(ovo,dummyXvar,dummyYvar);
          leadingRivetPlot2DOWN->GetPoint(ovo,x1temp,y1temp); 
          leadingRivetPlot2UP->GetPoint(ovo,x2temp,y2temp); 
	    
          Int_t ovoCorrected=ovo;
          if (whichobservable==3) ovoCorrected=ovo+leadingSystematics->GetNbinsX()/2;
	   
          //Set upper plot
          leadingRivetPlot22ENV->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
          //Set Ratio Plot
          leadingRatioPlot22ENV->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovoCorrected+1));
	    
          //Set Bands for upper plots (not used...)
          leadingRivetPlot22ENV->SetPointEYhigh(ovo,sqrt(pow((max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm),2) + pow(leadingRivetPlot2Stat->GetErrorYhigh(ovo),2)));
          leadingRivetPlot22ENV->SetPointEYlow(ovo, sqrt(pow((-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm),2) + pow(leadingRivetPlot2Stat->GetErrorYlow(ovo),2)));
	    
          //Set Bands for lower plots
	    
          double extraQuantityFromAlphaStrong_up=0.0;
          double extraQuantityFromAlphaStrong_down=0.0;
	    
          if (isPDFComparison){
            extraQuantityFromAlphaStrong_up=DeltaAsUp_CT10_Ratio[ovo];
            extraQuantityFromAlphaStrong_down=DeltaAsDown_CT10_Ratio[ovo];
          }
          leadingRatioPlot22ENV->SetPointEYhigh(ovo,sqrt(pow((max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar,2) + pow(leadingRatioPlot2Stat->GetErrorYhigh(ovo),2)+ pow(extraQuantityFromAlphaStrong_up,2) ));
          leadingRatioPlot22ENV->SetPointEYlow(ovo,sqrt(pow((-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar,2) + pow(leadingRatioPlot2Stat->GetErrorYlow(ovo),2)+ pow(extraQuantityFromAlphaStrong_down,2) ));

          if (verbosePowheg){
            cout<<"Powheg Bin "<<ovo<<endl;
            cout<<"statistics envelop, high "<<leadingRatioPlot2Stat->GetErrorYhigh(ovo)<<endl;
            cout<<"statistics envelop, low "<<leadingRatioPlot2Stat->GetErrorYlow(ovo)<<endl;
            cout<<"statistics envelop + Scale UP envelop, high "<<leadingRatioPlot22ENV->GetErrorYhigh(ovo)<<endl;
            cout<<"statistics envelop + Scale DOWN envelop, low "<<leadingRatioPlot22ENV->GetErrorYlow(ovo)<<endl;
          }
        }
	
        // Madgraph:

        Double_t dummyNorm = 0.;
   
        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
          leadingRivetPlot3->GetPoint(ovo,dummyXvar,dummyYvar); 
          dummyNorm = dummyNorm + dummyYvar;
        }


        for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {

          if (absoluteNormalization) {
            if (!isPDFComparison) dummyNorm= 2475.0/3048.0; else dummyNorm=1.0;
            //if (lepton==3) dummyNorm=dummyNorm*2.0;
          }
          leadingRivetPlot3->GetPoint(ovo,dummyXvar,dummyYvar); 
          leadingRivetPlot3->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);

          leadingRivetPlot3->SetPointEYhigh(ovo,leadingRivetPlot3->GetErrorYhigh(ovo)/dummyNorm);
          leadingRivetPlot3->SetPointEYlow(ovo,leadingRivetPlot3->GetErrorYlow(ovo)/dummyNorm);

          Int_t ovoCorrected=ovo;
          if (whichobservable==3) ovoCorrected=ovo+leadingSystematics->GetNbinsX()/2;

          leadingRatioPlot3->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovoCorrected+1));

          leadingRatioPlot3->SetPointEYhigh(ovo,leadingRivetPlot3->GetErrorYhigh(ovo)*dummyNorm/dummyYvar);
          leadingRatioPlot3->SetPointEYlow(ovo,leadingRivetPlot3->GetErrorYlow(ovo)*dummyNorm/dummyYvar);

          leadingRatio2->SetBinContent(ovoCorrected+1,1.0);
          leadingRatio2->SetBinError(ovoCorrected+1,leading->GetBinError(ovo+1)/leading->GetBinContent(ovo+1));

          leadingRatio2Systematics->SetBinContent(ovoCorrected+1,1.0);
          leadingRatio2Systematics->SetBinError(ovoCorrected+1,leadingSystematics->GetBinError(ovoCorrected+1)/leadingSystematics->GetBinContent(ovoCorrected+1));
        }

        // 2nd envelop for Madgraph:
        TGraphAsymmErrors *leadingRivetPlot32ENV;
        leadingRivetPlot32ENV = (TGraphAsymmErrors *) leadingRivetPlot3->Clone ();
        TGraphAsymmErrors *leadingRatioPlot32ENV;
        leadingRatioPlot32ENV = (TGraphAsymmErrors *) leadingRatioPlot3->Clone ();

        Double_t y1temp = 0.;
        Double_t y2temp = 0.;
        Double_t x1temp = 0.;
        Double_t x2temp = 0.;
        Double_t r1temp = 0.;
        Double_t r2temp = 0.;
	
        if (isPDFComparison){
	  
          for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
            leadingRivetPlot32ENV->GetPoint(ovo,dummyXvar,dummyYvar);
            leadingRivetPlot3DOWN->GetPoint(ovo,x1temp,y1temp); 
            leadingRivetPlot3UP->GetPoint(ovo,x2temp,y2temp); 

            if (absoluteNormalization) {
              if (lepton ==3) {
                dummyNorm= 1.0;
                //y1temp=y1temp/2.0;	    
                //y2temp=y2temp/2.0;
              }
            }
	  
            Int_t ovoCorrected=ovo;
            if (whichobservable==3) ovoCorrected=ovo+leadingSystematics->GetNbinsX()/2;
            //Set upper plot
            leadingRivetPlot32ENV->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
            //Set Ratio Plot
            leadingRatioPlot32ENV->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovoCorrected+1));

            double extraQuantityFromAlphaStrong_up=0.0;
            double extraQuantityFromAlphaStrong_down=0.0;
	  
            if (isPDFComparison){
              extraQuantityFromAlphaStrong_up=DeltaAsUp_CT10_Ratio[ovo];
              extraQuantityFromAlphaStrong_down=DeltaAsDown_CT10_Ratio[ovo];
            }

            //Set Bands for upper plots (not used...)
            leadingRivetPlot32ENV->SetPointEYhigh(ovo,sqrt(pow((max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm),2) + pow(leadingRivetPlot3->GetErrorYhigh(ovo),2)));
            leadingRivetPlot32ENV->SetPointEYlow(ovo, sqrt(pow((-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm),2) + pow(leadingRivetPlot3->GetErrorYlow(ovo),2)));
	  
	  
            //Set Bands for lower plots
            leadingRatioPlot32ENV->SetPointEYhigh(ovo,sqrt(pow((max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar,2) + pow(leadingRatioPlot3->GetErrorYhigh(ovo),2) + pow(extraQuantityFromAlphaStrong_up,2) ));
            leadingRatioPlot32ENV->SetPointEYlow(ovo,sqrt(pow((-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar,2) + pow(leadingRatioPlot3->GetErrorYlow(ovo),2)+ pow (extraQuantityFromAlphaStrong_down,2) ));
	  
            if (verboseMadGraph){
              cout<<"MadGraph Bin "<<ovo<<endl;
              cout<<"statistics envelop, high "<<leadingRatioPlot2Stat->GetErrorYhigh(ovo)<<endl;
              cout<<"statistics envelop, low "<<leadingRatioPlot2Stat->GetErrorYlow(ovo)<<endl;
              cout<<"statistics envelop + Scale UP envelop, high "<<leadingRatioPlot22ENV->GetErrorYhigh(ovo)<<endl;
              cout<<"statistics envelop + Scale DOWN envelop, low "<<leadingRatioPlot22ENV->GetErrorYlow(ovo)<<endl;
            }
	  
          }
        }

        ///////////////
        /////// DRAWING THE RESULTS
        ///////////////////////


        leadingRivetPlot1Stat->SetFillColor(kBlue-10);
        leadingRivetPlot1Stat->SetFillStyle(1001);
        leadingRivetPlot1Stat->SetLineColor(kBlue);
        leadingRivetPlot1Stat->SetMarkerColor(kBlue);
        leadingRivetPlot1Stat->SetMarkerStyle(24);
        leadingRivetPlot1Stat->Draw("pz");

        leadingRivetPlot2Stat->SetFillColor(kMagenta-8);
        leadingRivetPlot2Stat->SetFillStyle(1001);
        leadingRivetPlot2Stat->SetLineColor(kMagenta+4);
        leadingRivetPlot2Stat->SetMarkerColor(kMagenta+4);
        leadingRivetPlot2Stat->SetMarkerStyle(26);
        leadingRivetPlot2Stat->Draw("pz");

        leadingRivetPlot3->SetFillColor(kOrange-2);
        leadingRivetPlot3->SetFillStyle(1001);
        leadingRivetPlot3->SetLineColor(kOrange+10);
        leadingRivetPlot3->SetMarkerColor(kOrange+10);
        leadingRivetPlot3->SetMarkerStyle(25);
        leadingRivetPlot3->Draw("pz");

        leading->Draw ("ESAME");


        // Draw the label and save plot: (in the proper position)

        TLatex *latexLabel;

        // CMSPrel : for preliminary version

        /* if (lepton ==1) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow ee selection", 0.20, 0.16); */
        /* if (lepton ==2) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow #mu#mu selection", 0.20, 0.16); */
        /* if (lepton ==3) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow ll selection", 0.20, 0.16); */

        // CMSFinal: for journal draft

        std::cout << "***********************************************" << std::endl;
        std::cout << "Final journal draft version, no \"Preliminary\"" << std::endl;
        std::cout << "***********************************************" << std::endl;

        if (lepton ==1) latexLabel = CMSFinal (4.890, "Z/#gamma*#rightarrow ee selection", 0.20, 0.19);
        if (lepton ==2) latexLabel = CMSFinal (4.890, "Z/#gamma*#rightarrow #mu#mu selection", 0.20, 0.19);
        if (lepton ==3) latexLabel = CMSFinal (4.890, "Z/#gamma*#rightarrow ll selection", 0.20, 0.19);

        leadingSystematics->SetMarkerColor(kBlack);
        leadingSystematics->SetMarkerSize(0.8);
        leading->SetMarkerSize(0.8);
        latexLabel->Draw ("same");

        //        Double_t tsize = mmTsize(0.05);

        TLegend *legenddx_d;
        if (!isPDFComparison) {
          legenddx_d = new TLegend (0.46, 0.75, 1.0, 1.0);	   
        } else {
          legenddx_d = new TLegend (0.5, 0.75, 1.0, 1.0);	   
        }
        legenddx_d->SetFillColor (0);
        legenddx_d->SetFillStyle (1001);
        legenddx_d->SetBorderSize (1);
        legenddx_d->SetTextFont(43);
        legenddx_d->SetTextSize(19);
        legenddx_d->AddEntry (leadingSystematics, "Data", "PLEF");
        if (!isPDFComparison){
          legenddx_d->AddEntry (leadingRivetPlot1Stat, "Sherpa2#beta2 (0,1j NLO #leq4j LO)", "PLEF");
          legenddx_d->AddEntry (leadingRivetPlot2Stat, "Powheg+Pythia6 (1j NLO)", "PLEF");
          legenddx_d->AddEntry (leadingRivetPlot3, "MadGraph+Pythia6 (#leq4j LO)", "PLEF");
        }
        else{
          legenddx_d->AddEntry (leadingRivetPlot1Stat, "Sherpa2#beta2 CT10", "PLEF");
          legenddx_d->AddEntry (leadingRivetPlot2Stat, "Sherpa2#beta2 NNPDF21", "PLEF");
          legenddx_d->AddEntry (leadingRivetPlot3, "Sherpa2#beta2 MSTW2008nlo", "PLEF");
        }
        legenddx_d->Draw ("same");


        plots->cd ();
        TPad *pad2 = new TPad("pad2","pad2",0.01,0.39,0.99,0.55);
        pad2->Draw();
        pad2->cd();
        pad2->SetTopMargin(0.0);
        pad2->SetBottomMargin(0.0);
        pad2->SetRightMargin(0.1);
        pad2->SetFillStyle(0);

        leadingRatioSystematics->GetXaxis()->SetLabelFont (43);
        leadingRatioSystematics->GetXaxis()->SetTitleFont (43);
        leadingRatioSystematics->GetXaxis()->SetTitleSize(22);
        leadingRatioSystematics->GetXaxis()->SetLabelSize(22);
        leadingRatioSystematics->GetYaxis()->SetTitleSize(22);
        leadingRatioSystematics->GetYaxis()->SetLabelSize(22);
        leadingRatioSystematics->GetYaxis()->SetTitleOffset(2.5);

        leadingRatioSystematics->GetYaxis()->SetTitle("Theory/Data   "); 

        leadingRatioSystematics->GetYaxis()->SetNdivisions(505);
        leadingRatioSystematics->GetYaxis()->SetRangeUser(0.2,1.8);
        leadingRatioSystematics->SetTitle("");    
        leadingRatioSystematics->SetMarkerStyle(1);
        leadingRatio->SetMarkerStyle(1);
        leadingRatioSystematics->Draw ("E2");
        leadingRatio->Draw ("E1SAME");

        if (!isPDFComparison){
          leadingRatioPlot1Qcut->SetFillColor(kBlue-10);
          leadingRatioPlot1Qcut->SetFillStyle(1001);
          leadingRatioPlot1Qcut->SetLineColor(kBlue-10);
          leadingRatioPlot1Qcut->SetMarkerStyle(24);
          leadingRatioPlot1Qcut->SetMarkerColor(kBlue-10);
          leadingRatioPlot1Qcut->SetLineWidth(1);
          leadingRatioPlot1Qcut->Draw("2");
          leadingRatioPlot1Qcut->Draw("pz");
        }
        else{
          leadingRatioPlot1Q->SetFillColor(kBlue-10);
          leadingRatioPlot1Q->SetFillStyle(1001);
          leadingRatioPlot1Q->SetLineColor(kBlue-10);
          leadingRatioPlot1Q->SetMarkerStyle(24);
          leadingRatioPlot1Q->SetMarkerColor(kBlue-10);
          leadingRatioPlot1Q->SetLineWidth(1);
          leadingRatioPlot1Q->Draw("2");
          leadingRatioPlot1Q->Draw("pz");
        }

        leadingRatioPlot1Stat->SetFillColor(kBlue-9);
        leadingRatioPlot1Stat->SetFillStyle(1001);
        leadingRatioPlot1Stat->SetLineColor(kBlue);
        leadingRatioPlot1Stat->SetMarkerColor(kBlue);
        leadingRatioPlot1Stat->SetMarkerStyle(24);
        leadingRatioPlot1Stat->SetLineWidth(1);
        leadingRatioPlot1Stat->Draw("2");
        leadingRatioPlot1Stat->Draw("pz");

        leadingRatioSystematics->Draw ("E2SAME");
        leadingRatio->Draw ("E1SAME");
        leadingRatio->Draw ("E1SAME AXIS");


        TLatex *latexLabelPlot1 = new TLatex();
        latexLabelPlot1->SetTextFont(43);
        latexLabelPlot1->SetTextSize(18);
        latexLabelPlot1->SetLineWidth(2);
        latexLabelPlot1->SetNDC();
        if (!isPDFComparison) {
          latexLabelPlot1->DrawLatex(0.21,0.83,"Sherpa2#beta2");
        } else {
          latexLabelPlot1->DrawLatex(0.21,0.83,"Sherpa2#beta2 CT10");
        }
        TLegend *legendPlot1;
        legendPlot1 = new TLegend (0.21, 0.04, 0.46, 0.2);       
        legendPlot1->SetFillColor (0);
        legendPlot1->SetFillStyle (0);
        legendPlot1->SetBorderSize (0);
        legendPlot1->SetTextFont(43);
        legendPlot1->SetTextSize(18);
        if (!isPDFComparison) legendPlot1->AddEntry (leadingRatioPlot1Qcut, "Theory syst.", "F");
        else legendPlot1->AddEntry (leadingRatioPlot1Q, "Theory syst.", "F");
        legendPlot1->Draw ("same");

        TLegend *legendPlot12;
        legendPlot12 = new TLegend (0.46, 0.04, 0.75, 0.2);       
        legendPlot12->SetFillColor (0);
        legendPlot12->SetFillStyle (0);
        legendPlot12->SetBorderSize (0);
        legendPlot12->SetTextFont(43);
        legendPlot12->SetTextSize(18);
        legendPlot12->AddEntry (leadingRatioPlot1Stat, "Theory stat.", "F");
        legendPlot12->Draw ("same");


        // Plot2 ratio plot: ----------------------------------
        plots->cd ();
        TPad *pad4 = new TPad("pad4","pad4",0.01,0.23,0.99,0.39);
        pad4->Draw();
        pad4->cd();
        pad4->SetTopMargin(0.0);
        pad4->SetBottomMargin(0.0);
        pad4->SetRightMargin(0.1);
        pad4->SetFillStyle(0);

        leadingRatio3Systematics->GetXaxis()->SetLabelFont (43);
        leadingRatio3Systematics->GetXaxis()->SetTitleFont (43);
        leadingRatio3Systematics->GetXaxis()->SetLabelSize(22);
        leadingRatio3Systematics->GetYaxis()->SetTitleSize(22);
        leadingRatio3Systematics->GetYaxis()->SetLabelSize(22);
        leadingRatio3Systematics->GetYaxis()->SetTitleSize(22);
        leadingRatio3Systematics->GetYaxis()->SetTitleOffset(2.5);

        //	if (!isPDFComparison) {
        leadingRatio3Systematics->GetYaxis()->SetTitle("Theory/Data   "); 
        //	} else {
        //	  leadingRatio3Systematics->GetYaxis()->SetTitle("MSTW2008/Data");
        //	}

        leadingRatio3Systematics->GetYaxis()->SetNdivisions(505);
        leadingRatio3Systematics->GetYaxis()->SetRangeUser(0.2,1.8);
        leadingRatio3Systematics->SetMarkerStyle(1);
        leadingRatio3->SetMarkerStyle(1);
        leadingRatio3Systematics->SetTitle("");	  
        leadingRatio3Systematics->Draw ("E2");
        leadingRatio3->Draw ("E1SAME");

        leadingRatioPlot22ENV->SetFillColor(kMagenta-9);
        leadingRatioPlot22ENV->SetFillStyle(1001);
        leadingRatioPlot22ENV->SetLineColor(kMagenta-9);
        leadingRatioPlot22ENV->SetMarkerColor(kMagenta-9);
        leadingRatioPlot22ENV->SetLineWidth(0.6);
        leadingRatioPlot22ENV->Draw("5");
	
        leadingRatioPlot2Stat->SetFillColor(kMagenta-6);
        leadingRatioPlot2Stat->SetFillStyle(1001);
        leadingRatioPlot2Stat->SetLineColor(kMagenta+4);
        leadingRatioPlot2Stat->SetMarkerColor(kMagenta+4);
        leadingRatioPlot2Stat->SetMarkerStyle(26);
        leadingRatioPlot2Stat->SetLineWidth(1);
        leadingRatioPlot2Stat->Draw("2");
        leadingRatioPlot2Stat->Draw("pz");

        leadingRatio3Systematics->Draw ("E2SAME");
        leadingRatio3->Draw ("E1SAME");
        leadingRatio3->Draw ("E1SAME AXIS");

        TLatex *latexLabelPlot2 = new TLatex();
        latexLabelPlot2->SetTextFont(43); 
        latexLabelPlot2->SetTextSize(18);
        latexLabelPlot2->SetLineWidth(2);
        latexLabelPlot2->SetNDC();
        if (!isPDFComparison) {
          latexLabelPlot2->DrawLatex(0.21,0.83,"Powheg+Pythia6");
        } else {
          latexLabelPlot2->DrawLatex(0.21,0.83,"Sherpa2#beta2 NNPDF21");
        }

        TLegend *legendPlot2;
        legendPlot2 = new TLegend (0.21, 0.04, 0.46, 0.2);       
        legendPlot2->SetFillColor (0);
        legendPlot2->SetFillStyle (0);
        legendPlot2->SetBorderSize (0);
        legendPlot2->SetTextFont(43);
        legendPlot2->SetTextSize(18);
        legendPlot2->AddEntry (leadingRatioPlot22ENV, "Theory syst.", "F");
        legendPlot2->Draw ("same");

        TLegend *legendPlot22;
        legendPlot22 = new TLegend (0.46, 0.04, 0.75, 0.2);       
        legendPlot22->SetFillColor (0);
        legendPlot22->SetFillStyle (0);
        legendPlot22->SetBorderSize (0);
        legendPlot22->SetTextFont(43);
        legendPlot22->SetTextSize(18);
        legendPlot22->AddEntry (leadingRatioPlot2Stat, "Theory stat.", "F");
        legendPlot22->Draw ("same");


        // Madgraph ratio plot: ---------------------
        plots->cd();
        TPad *pad3 = new TPad("pad3","pad3",0.01,0.01,0.99,0.23);
        pad3->Draw();
        pad3->cd();
        pad3->SetTopMargin(0.0);
        pad3->SetBottomMargin(0.3);
        pad3->SetRightMargin(0.1);
        pad3->SetFillStyle(0);

        leadingRatio2Systematics->GetXaxis()->SetTitleFont (43);
        leadingRatio2Systematics->GetXaxis()->SetLabelFont (43);
        leadingRatio2Systematics->GetXaxis()->SetTitleSize(24);
        leadingRatio2Systematics->GetXaxis()->SetLabelSize(22);
        leadingRatio2Systematics->GetXaxis()->SetTitleOffset(5.);
        leadingRatio2Systematics->GetYaxis()->SetTitleFont (43);
        leadingRatio2Systematics->GetYaxis()->SetLabelFont (43);
        leadingRatio2Systematics->GetYaxis()->SetTitleSize(22);
        leadingRatio2Systematics->GetYaxis()->SetLabelSize(22);
        leadingRatio2Systematics->GetYaxis()->SetTitleOffset(2.5);

        leadingRatio2Systematics->GetYaxis()->SetTitle("Theory/Data   "); 

        leadingRatio2Systematics->GetYaxis()->SetNdivisions(505);
        leadingRatio2Systematics->GetYaxis()->SetRangeUser(0.2,1.8);

        leadingRatioPlot3->SetTitle("");	  

        if (use_case ==1) {
          leadingRatio2Systematics->GetXaxis()->SetTitle ("N_{jet}");
          if (incMultiplicity) {
            leadingRatio2Systematics->GetXaxis()->SetBinLabel(1,"#geq 1");
            leadingRatio2Systematics->GetXaxis()->SetBinLabel(2,"#geq 2");
            leadingRatio2Systematics->GetXaxis()->SetBinLabel(3,"#geq 3");
            leadingRatio2Systematics->GetXaxis()->SetBinLabel(4,"#geq 4");
            leadingRatio2Systematics->GetXaxis()->SetBinLabel(5,"#geq 5");
            leadingRatio2Systematics->GetXaxis()->SetBinLabel(6,"#geq 6");
            leadingRatio2Systematics->GetXaxis()->SetTitle ("N_{jet}");
          }
          leadingRatio2Systematics->GetXaxis()->SetNdivisions(110);
          leadingRatio3Systematics->GetXaxis()->SetNdivisions(110);
          leadingRatioSystematics->GetXaxis()->SetNdivisions(110);
        }
        if (use_case ==2) {
          if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Leading jet p_{T} [GeV]");
          if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Second jet p_{T} [GeV]");
          if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Third jet p_{T} [GeV]");
          if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Fourth jet p_{T} [GeV]");
        }
        if (use_case ==3) {
          if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Leading jet #eta");
          if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Second jet #eta");
          if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Third jet #eta");
          if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Fourth jet #eta");
        }
        if (use_case ==4) {
          if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 1 [GeV]");
          if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 2 [GeV]");
          if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 3 [GeV]");
          if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 4 [GeV]");
        }

        leadingRatio2Systematics->SetMarkerStyle(1);
        leadingRatio2->SetMarkerStyle(1);
        leadingRatio2Systematics->Draw ("E2");
        leadingRatio2->Draw ("E1SAME");

        if (isPDFComparison){
          leadingRatioPlot32ENV->SetFillColor(kOrange-4);
          leadingRatioPlot32ENV->SetFillStyle(1001);
          leadingRatioPlot32ENV->SetLineColor(kOrange-4);
          leadingRatioPlot32ENV->SetMarkerColor(kOrange-4);
          leadingRatioPlot32ENV->SetLineWidth(0.6);
          leadingRatioPlot32ENV->Draw("5");
        }	
      
        leadingRatioPlot3->SetFillColor(kOrange-1);
        leadingRatioPlot3->SetFillStyle(1001);
        leadingRatioPlot3->SetLineColor(kOrange+10);
        leadingRatioPlot3->SetMarkerColor(kOrange+10);
        leadingRatioPlot3->SetMarkerStyle(25);
        leadingRatioPlot3->SetLineWidth(1);
        leadingRatioPlot3->Draw("2");
        leadingRatioPlot3->Draw("pz");


        leadingRatio2Systematics->Draw ("E2SAME");
        leadingRatio2->Draw ("E1SAME");
        leadingRatio2->Draw ("E1SAME AXIS");

        TLatex *latexLabelPlot3 = new TLatex();
        //        latexLabelPlot3->SetTextSize(0.08);
        //        latexLabelPlot3->SetTextFont(42);
        latexLabelPlot3->SetTextFont(43);
        latexLabelPlot3->SetTextSize(18);
        latexLabelPlot3->SetLineWidth(2);
        latexLabelPlot3->SetNDC();
        if (!isPDFComparison) {
          latexLabelPlot3->DrawLatex(0.21,0.88,"MadGraph+Pythia6");
        } else {
          latexLabelPlot3->DrawLatex(0.21,0.88,"Sherpa2#beta2 MSTW2008nlo");
        }

        TLegend *legendPlot3;
        //        legendPlot3 = new TLegend (0.19, 0.33, 0.40, 0.44);       
        legendPlot3 = new TLegend (0.21, 0.33, 0.49, 0.46);       
        legendPlot3->SetFillColor (0);
        legendPlot3->SetFillStyle (0);
        legendPlot3->SetBorderSize (0);
        legendPlot3->SetTextFont(43);
        legendPlot3->SetTextSize(18);
        legendPlot3->AddEntry (leadingRatioPlot32ENV, "Theory syst.", "F");
        if (isPDFComparison) legendPlot3->Draw ("same");

        TLegend *legendPlot32;
        if (isPDFComparison) {
          legendPlot32 = new TLegend (0.46, 0.33, 0.77, 0.46);       
        } else {
          legendPlot32 = new TLegend (0.21, 0.33, 0.49, 0.46);
        }
        legendPlot32->SetFillColor (0);
        legendPlot32->SetFillStyle (0);
        legendPlot32->SetBorderSize (0);
        legendPlot32->SetTextFont(43);
        legendPlot32->SetTextSize(18);
        legendPlot32->AddEntry (leadingRatioPlot3, "Theory stat.", "F");
        legendPlot32->Draw ("same");

        TString title1;
        title1 = s + "DifferentialX" + stringmatch + ".pdf";
        if (incMultiplicity) title1 = s + "DifferentialXInc" + stringmatch + ".pdf";
        if (etaFolded && use_case == 3 ) title1 = s + "DifferentialX" + stringmatch + "Abs.pdf";
        
        TString pdf = ".pdf";
        TString PDFpdf = "_PDF.pdf";
        if ( isPDFComparison ) title1.ReplaceAll(pdf,PDFpdf);
        
        cout << title1 << endl;
        
        plots->Print (title1);
        
        TString title2(title1);
        TString png = ".png";
        title2.ReplaceAll(pdf,png);
        
        cout << title2 << endl;
        
        plots->Print (title2);
        
        if (lepton==1) {
          name = name + "_ele";
          if (incMultiplicity) name = name + "_inclusive_ele";
        }
        if (lepton==2) {
          name = name + "_muo";
          if (incMultiplicity) name = name + "_inclusive_muo";
        }
        if (lepton==3) {
          name = name + "_combined";
          if (incMultiplicity) name = name + "_inclusive_combined";
        }
        if (use_case ==1) {
          if (absoluteNormalization && !incMultiplicity) leadingSystematics->SetTitle ("Exclusive Jet Multiplicity");
          if (absoluteNormalization && incMultiplicity) leadingSystematics->SetTitle ("Inclusive Jet Multiplicity");
        }
        if (use_case ==2) {
          if (absoluteNormalization && whichjet==1) leadingSystematics->SetTitle ("1st Jet Transverse Momentum");
          if (absoluteNormalization && whichjet==2) leadingSystematics->SetTitle ("2nd Jet Transverse Momentum");
          if (absoluteNormalization && whichjet==3) leadingSystematics->SetTitle ("3rd Jet Transverse Momentum");
          if (absoluteNormalization && whichjet==4) leadingSystematics->SetTitle ("4th Jet Transverse Momentum");
        }
        if (use_case ==3) {
          if (absoluteNormalization && whichjet==1) leadingSystematics->SetTitle ("1st Jet Pseudorapidity");
          if (absoluteNormalization && whichjet==2) leadingSystematics->SetTitle ("2nd Jet Pseudorapidity");
          if (absoluteNormalization && whichjet==3) leadingSystematics->SetTitle ("3rd Jet Pseudorapidity");
          if (absoluteNormalization && whichjet==4) leadingSystematics->SetTitle ("4th Jet Pseudorapidity");
          if (absoluteNormalization && whichjet==1) leadingSystematicsEta->SetTitle ("1st Jet Pseudorapidity");
          if (absoluteNormalization && whichjet==2) leadingSystematicsEta->SetTitle ("2nd Jet Pseudorapidity");
          if (absoluteNormalization && whichjet==3) leadingSystematicsEta->SetTitle ("3rd Jet Pseudorapidity");
          if (absoluteNormalization && whichjet==4) leadingSystematicsEta->SetTitle ("4th Jet Pseudorapidity");
        }	  
        if (use_case ==4) {
          if (absoluteNormalization && whichjet==1) leadingSystematics->SetTitle ("Ht, # Jets > 1");
          if (absoluteNormalization && whichjet==2) leadingSystematics->SetTitle ("Ht, # Jets > 2");
          if (absoluteNormalization && whichjet==3) leadingSystematics->SetTitle ("Ht, # Jets > 3");
          if (absoluteNormalization && whichjet==4) leadingSystematics->SetTitle ("Ht, # Jets > 4");
        }
        leadingSystematics->SetName(name.c_str());
        leadingSystematicsEta->SetName(name.c_str());
        dumphistos_file.cd();
        if (etaFolded && use_case==3) {
          leadingSystematicsEta->Write();
        } else {
          leadingSystematics->Write();
        }	  
        return;
      }
    }
}

TGraphAsymmErrors* returnTGraphFromFile(string rivetPath, string rivet_data, string rivet_data_minus, bool etaFolded, bool isPDFComparison, int use_case, bool readTH1F){
  cout<<rivetPath<<endl;
  TGraphAsymmErrors *leadingRivet;
  TFile *histoRivet = TFile::Open (rivetPath.c_str ());
  histoRivet->cd ("");
  TDirectory *dirRivet = gDirectory;
  TList *mylistRivet= (TList *) dirRivet->GetListOfKeys ();
  TIter iterRivet(mylistRivet);
  TObject *tobjRivet= 0;
  while ((tobjRivet= iterRivet.Next ()))
    {
      string nameRivet= tobjRivet->GetName ();
      if (nameRivet == rivet_data_minus) 
        {
          cout<<nameRivet<<endl;
          if (!readTH1F) {
            gDirectory->GetObject (nameRivet.c_str (), leadingRivet);
          }
          else{
            TH1F *histo;
            gDirectory->GetObject (nameRivet.c_str (), histo);
            leadingRivet=new TGraphAsymmErrors(histo);
          }
        }
    }

  return leadingRivet;
}
