#root -l -q 'readtree.cxx("Tree_Tight","MixtureNN/Stg4/")'
#root -l -q 'readtree.cxx("Tree_Loose","MixtureNN/Stg4/")'

#root -l -q 'readtree.cxx("Tree_Tight","MixtureNN/Stg2/")'
#root -l -q 'readtree.cxx("Tree_Loose","MixtureNN/Stg2/")'

#root -l -q 'readtree.cxx("Tree_Tight","MixtureNN/Stg1/")'
#root -l -q 'readtree.cxx("Tree_Loose","MixtureNN/Stg1/")'

#root -l -q 'readtree.cxx("Tree_Tight","HealthyNN/Stg4/")'
#root -l -q 'readtree.cxx("Tree_Loose","HealthyNN/Stg4/")'

#root -l -q 'readtree.cxx("Tree_Tight","HealthyNN/Stg2/")'
#root -l -q 'readtree.cxx("Tree_Loose","HealthyNN/Stg2/")'

#root -l -q 'readtree.cxx("Tree_Tight","HealthyNN/Stg1/")'
#root -l -q 'readtree.cxx("Tree_Loose","HealthyNN/Stg1/")'

root -l -q 'readtree_RadZ.cxx("Tree","/afs/cern.ch/work/m/mobelfki/MLPhotonID/Zllg/run","output_Strategy_IsoLoose_4_Zllj")'
