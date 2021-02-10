g++  subplot.cxx AtlasLabels.C AtlasStyle.C -o subplot `root-config --cflags --glibs` -L$ROOTSYS/lib

#./subplot HealthyNN/Stg4/ Histo_Tree_Tight.root HealthyNN All Tight
#./subplot HealthyNN/Stg4/ Histo_Tree_Loose.root HealthyNN All Loose

#./subplot HealthyNN/Stg2/ Histo_Tree_Tight.root HealthyNN UnHealthy Tight
#./subplot HealthyNN/Stg2/ Histo_Tree_Loose.root HealthyNN UnHealthy Loose

#./subplot HealthyNN/Stg1/ Histo_Tree_Tight.root HealthyNN Healthy Tight
#./subplot HealthyNN/Stg1/ Histo_Tree_Loose.root HealthyNN Healthy Loose

#./subplot MixtureNN/Stg4/ Histo_Tree_Tight.root MixtureNN All Tight
#./subplot MixtureNN/Stg4/ Histo_Tree_Loose.root MixtureNN All Loose

#./subplot MixtureNN/Stg2/ Histo_Tree_Tight.root MixtureNN UnHealthy Tight
#./subplot MixtureNN/Stg2/ Histo_Tree_Loose.root MixtureNN UnHealthy Loose

#./subplot MixtureNN/Stg1/ Histo_Tree_Tight.root MixtureNN Healthy Tight
#./subplot MixtureNN/Stg1/ Histo_Tree_Loose.root MixtureNN Healthy Loose

#root -l -q 'subplot.cxx("MixtureNN/Stg4/","Histo_Tree_Loose.root", "MixtureNN", "All", "Loose")'
#root -l -q 'subplot.cxx("MixtureNN/Stg4/","Histo_Tree_Loose.root", "MixtureNN", "All", "Tight")'

#root -l -q 'subplot.cxx("MixtureNN/Stg1/","Histo_Tree_Loose.root", "MixtureNN", "Healthy", "Loose")'
#root -l -q 'subplot.cxx("MixtureNN/Stg1/","Histo_Tree_Tight.root", "MixtureNN", "Healthy", "Tight")'

#root -l -q 'subplot.cxx("MixtureNN/Stg2/","Histo_Tree_Loose.root", "MixtureNN", "UnHealthy", "Loose")'
#root -l -q 'subplot.cxx("MixtureNN/Stg2/","Histo_Tree_Tight.root", "MixtureNN", "UnHealthy", "Tight")'

./subplot MixtureNN/Stg4/Loose/NEW/ Histo_Tree_Loose.root MixtureNN All Loose

<<COMMENT1
root -l -q 'subplot.cxx("HealthyNN/Stg4/","Histo_Tree_Loose.root", "HealthyNN", "All", "Loose")'
root -l -q 'subplot.cxx("HealthyNN/Stg4/","Histo_Tree_Loose.root", "HealthyNN", "All", "Tight")'

root -l -q 'subplot.cxx("HealthyNN/Stg1/","Histo_Tree_Loose.root", "HealthyNN", "Healthy", "Loose")'
root -l -q 'subplot.cxx("HealthyNN/Stg1/","Histo_Tree_Tight.root", "HealthyNN", "Healthy", "Tight")'

root -l -q 'subplot.cxx("HealthyNN/Stg2/","Histo_Tree_Loose.root", "HealthyNN", "UnHealthy", "Loose")'
root -l -q 'subplot.cxx("HealthyNN/Stg2/","Histo_Tree_Tight.root", "HealthyNN", "UnHealthy", "Tight")'

COMMENT1
