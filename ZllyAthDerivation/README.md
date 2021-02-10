
# ZllyAthDerivation
is a framework built with ATLAS AthDerivation > 21.2.51.0.
The goal of this framework is : 
- Applied the Z->lly and single photon events selection to Monte Carlo and Data.  
- Decorate the radiated photon (Egamma object need to be generalize) with the calorimeter cells used to reconstruct the corresponding object.
- Produce ROOT Ntuple needed for CNN training
                                
# Setup 

To setup the framework :

    # source setup.sh

# Test Run 

To run the framework (localy) :

    # cd run 
    # source run.sh
    
This framework is not totally automatic, there is some variable that you should change when you change your samples :

In the MyxAODAnalysis.cxx :

    # DSID : The dataset ID (eg. 301899, when running on MC)
    # Year : Data year (eg. 2015 , when running on data)
Don't forget to add the PRW files (mc16a, mc16c and mc16d) if there are not in the data/PRW directory 
In the jobOption file :

    #TestFile : path to the dataset file
    
To run on Grid : 

    #pathena MyAnalysis/ATestRun_jobOptions.py --inDS=%InputDataSet  --outDS=user.%USERNAME.output --mergeOutput --nGBPerJob=MAX
