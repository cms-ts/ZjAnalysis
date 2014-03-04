ZjAnalysis
==========

Repository for the Z + jets analysis @ 7 TeV - NEW

Sub-packages:

1) SevenTeVSelection : production of root-ple, runs with CMSSW_4_4_X, SLC5 only!

   -) Directory "/test" 

      It contains the configuration file to be used if you need to reprocess the rootuples

         jetValidationPfAK5ChsNewIsoOldIdWP90MCEandMu_UnfoldingSherpa_cfg.py     ---> create the sherpa MC dataset (systematics for unfolding)

         jetValidationPfAK5ChsNewIsoOldIdWP90MCEandMu_cfg.py                     ---> create the madgraph MC dataset (ONLY RECO). 

         jetValidationPfAK5ChsNewIsoOldIdWP90MCEandMu_Unfolding_cfg.py           ---> create the madgraph MC dataset (RECO And GEN LEVEL).

         jetValidationPfAK5ChsNewIsoOldIdWP90mu_cfg.py                           ---> run on data (muons)

         jetValidationPfAK5ChsNewIsoOldIdWP90_cfg.py                             ---> run on data (ele)

   -) "scripts". COntains cfgs to run the forementioned files over the analysis datasets

        crabProcessDataMuRunA44.cfg  crabProcessDataMunB44.cfg     --> run runA and B for muons

        crabProcessDataRunA44.cfg  crabProcessDataRunB44.cfg       --> run runA and B for electrons

        crabProcessMCNoXroot.cfg                                   --> run madgraph using XrootD

        crabProcessMCWZLocale.cfg                                  --> run WZ dataset (locally)

	crabTTBarScalingDOWNRemote.cfg crabTTBarScalingUPRemote.cfg--> run ttbar dataset scaled down (systematics)

	crabProcessMCDYLocale.cfg           			   --> run madgraph reco (locally)

	crabProcessMCTTBarLocale.cfg  				   --> run ttbar dataset (locally)

	crabProcessMCZZLocale.cfg      				   --> run zz dataset (locally)

	crabProcessMCDYLocaleUnfolding.cfg  			   --> run madgraph reco and gen level (locally)

	crabProcessMCWWLocale.cfg     				   --> run WW dataset (locally)

	crabSherpaUnfoldingRemote.cfg  				   --> run madgraph reco and gen level (grid)

	multicrabMC44X.cfg					   --> run QCD datasets (grid)

   -) "/interface" "/src" "/python". It contains plugins/code called inside these python files 

   -) "/data" contains the rootuples required for the MC Pile-up reweighting and JEC systematics (must be correctly shipped if you run on crab!)

+++Logic Workflow to reprocess the full analysis++

All you need to do is to run each of the configuration files listed below. Output is copied in the local directory

crab -cfg crabProcessDataMuRunA44.cfg -create -submit

crab -cfg crabProcessDataMuRunB44.cfg -create -submit

crab -cfg crabProcessDataRunA44.cfg -create -submit

crab -cfg crabProcessDataRunB44.cfg -create -submit

crab -cfg crabProcessMCDYLocale.cfg -create -submit

crab -cfg crabProcessTTBarLocale.cfg -create -submit

crab -cfg crabProcessMCZZLocale.cfg -create -submit

crab -cfg crabProcessMCWZLocale.cfg -create -submit

crab -cfg crabProcessMCWWLocale.cfg -create -submit

crab -cfg multicrabMC44X.cfg -create -submit

Output of previous reporcessing is stored in this area:
/gpfs/cms/data/2011/jet/

=========================================

2) SevenTeVTools : pre-unfolding , unfolding , systematics and theory comparison 
utilities, can run in CMSSW_5_3_X on SLC6            
 
    -) "macros", "/scripts", "include", "data". Macros to plot the pre-unfolded distributions, to perform unfolding and calculate the various systematics. In the following, a brief explanation of the macro themselve and their usages is provided. 

data/MuScleFit_2011_DATA_44X.txt    		    -> Coefficients for muscle fit correction on muons pt     

macros/RooUnfold-1.1.1/          		    -> Directory which contains the official RooUnfold Package. To trun the unfold, you need to copy the .h files on your working area, at to compile the "libRooUnfold.so" using the attached makefile.


data/TAPfitter_config.txt 			    -> TAP configuration file

data/TAPfitter_configMU.txt          		    -> TAP configuration file


macros/lumi_scale_factors.h			    -> cross sections for the MC dataset normalization

macros/lumi_scale_factorsARC.h                      -> cross sections for the MC dataset normalization 

macros/lumi_scale_factors_scaleDownARC.h	    -> cross sections for the MC dataset normalization, scaled down for bnackground systematics

macros/lumi_scale_factors_scaleUpARC.h		    -> cross sections for the MC dataset normalization, scaled up for bnackground systematics


interface/TemplateForHistograms.h           	    -> Templates for histyogram binning 

interface/TemplateForHistogramsUnfolding.h  	    -> Templates for histyogram binning taken as input by the Unfolding


macros/UnfoldingVJets2011.C			    -> COntains flags for the various Unfolding cases        

macros/UnfoldingVJets2011.h        		    -> COntains flags for the various Unfolding cases        

macros/LoopVJetsNew5.h                      	    -> Core of the unfolding. Rootuple reading and implementation of the unfolding in it!

macros/runUnfold2011.C				    -> Run the unfolding 

macros/runUnfold2011Custom.C			    -> Run the unfolding over the full observables, ele and mu

macros/BackgroundRemoval.h			    -> include for unfolding: implement the background removal                  

macros/SaveUnfolding.h     			    -> include for unfolding: save plots and rootuples

macros/DrawUnfolding.h                      	    ->          "           : draw plots    

macros/MCLimitedStatTool.h                          ->          "           : evaluate MC limited stat effect

macros/MuScleFitCorrector.h                         ->          "           : perform MF correcton

macros/SetObs.h                    		    ->		"	    : set Unfolding parameters for each observable

macros/JERCorrection.h                      	    ->		"	    : Include effect of JER

macros/ResolFunct.h                         	    ->		"	    : Include effect of JER

macros/getEfficiencyCorrection.C		    ->		"	    : perfeorm efficiency correction (scale factors)

macros/getMuscleFitCorrection.C			    ->		"	    : retrieve the MF correction from the file


macros/makeEleMuComparisonPlots.C		    -> provide a comparison between lepton specied

scripts/runAllMakeEleMuComparisonPlots.sh	    -> run previous macro

macros/DrawComparisonJetMCData.C            	    -> Pre-unfolding "plotter". It works after Observables.C

macros/DrawComparisonJetMCDataXScale.C	 	    -> As the previous line, but used for background systematics (see usage)

macros/runDrawComparisonJetMCDataXScale.C	    -> run prevoius macro

macros/DrawComparisonJetMCDataScaleDown.C   	    -> As the previous line, but used for background systematics (see usage)

macros/runDrawComparisonJetMCDataXScaleDown.C	    -> run prevoius macro

macros/DrawComparisonJetMCDataScaleUp.C   	    -> As the previous line, but used for background systematics (see usage)

macros/runDrawComparisonJetMCDataXScaleUp.C	    -> run prevoius macro

macros/makeZjetsPlots.C				    -> Plot final list of observables. 

scripts/runMakeZPlots.sh			    -> Run previous run


macros/Observables.C                        	    -> Creates rootuples for each dataset, to evaluate thew background compoent and the pre-unfolding plots

macros/Observables.h                        	    -> Creates rootuples for each dataset, to evaluate thew background compoent and the pre-unfolding plots

macros/runObs.C					    -> run previous macro

scripts/makeJetsPlotsWebPages.sh		    -> Publish the results fo proevious action on the web

macros/diow.C                      		    -> Publish the results fo proevious action on the web

macros/TagProbeFitter.C            		    -> TAP for ele and muons


macros/scorporateStat.C				    -> Separate the MC limited statistics effect from Unfolding

scripts/runAllScorporateStat.sh			    -> run previous macro

macros/MakePlotLumiLabel.C                  	    -> To create the official CMS labels

macros/tdrstyle.C				    -> make up 

macros/combineLeptonStatistics.C   		    -> To combine rootuples from unfolding

macros/evaluateNewJEC.C            		    -> calculate JEC systematics

scripts/runAllNewJEC.sh				    -> run previous macro

macros/flattenJECsystematics.C     		    -> if JEC systematics is fluctuating, use this to flatten it

				   
Workflow:

1) run the macro Observable.C, in order to normalize the backgrounds, steore them for the unfolding, prepare the rootpules for pre-unfolding plots. Run it using the proper script:

runObs.C (run it twice, editing the falg "isMu" twice to create electron and muon rootuples)


2) draw the results running 

DrawComparisonJetMCData.C (twice again)

makeJetsPlotsWebPages.sh (to create the pre-unfolding plots)


3) Unfolding (and sdystematics)

Run runUnfoldCustom.C to perform the unfolding (paramters to run the unfolding and the systematics are in Unfolding2011VJets.C)


4) Other systematics (backgrouns)
Run

macros/runDrawComparisonJetMCDataXScale.C

macros/DrawComparisonJetMCDataScaleDown.C

macros/runDrawComparisonJetMCDataXScaleDown.C

macros/DrawComparisonJetMCDataScaleUp.C

macros/runDrawComparisonJetMCDataXScaleUp.C

