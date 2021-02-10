import numpy as np
import pandas as pd
import root_numpy as rnp
import uproot as upr
from ROOT import *

path = '/afs/cern.ch/work/m/mobelfki/MLPhotonID/Val_Stg_4/MixtureNN/Stg4/Loose/NEW/'

tight = pd.read_csv(path+'/output.csv')
#loose = pd.read_csv(path+'Loose/output.csv')

tight = tight.to_records()
#loose = loose.to_records()

tight.dtype.names = ('Index', 'Event', 'Truth', 'ETA', 'PT', 'E', 'Cov', 'MU', 'EdepWP', 'EindWP', 'CNN', 'isCNN', 'isCNNTight', 'isCNNLoose', 'LooseID', 'Reta', 'Rphi', 'Weta2', 'F1', 'Fside', 'Rhad1', 'Rhad')
#loose.dtype.names = ('Index', 'Event', 'Truth', 'ETA', 'PT', 'E', 'Cov', 'MU', 'EdepWP', 'EindWP', 'CNN', 'AthCNN', 'Reta', 'Rphi', 'Weta2', 'F1', 'Fside', 'Rhad1', 'Rhad')

tight_tree =  rnp.array2tree(tight, name='Tree_Loose')
#loose_tree =  rnp.array2tree(loose, name='Tree_Loose')

f = TFile(path+'output.root', 'RECREATE')

tight_tree.SetDirectory(f)
#loose_tree.SetDirectory(f)
f.Write()
f.Close()
