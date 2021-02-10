
#See: https://twiki.cern.ch/twiki/bin/viewauth/AtlasComputing/SoftwareTutorialxAODAnalysisInCMake for more details about anything here

testFile = '/eos/user/m/mobelfki/AOD/mc16_13TeV/mc16_13TeV/AOD.12863129._000001.pool.root.1'

#override next line on command line with: --filesInput=XXX
jps.AthenaCommonFlags.FilesInput = [testFile] 

#Specify AccessMode (read mode) ... ClassAccess is good default for xAOD
jps.AthenaCommonFlags.AccessMode = "POOLAccess" 


from RecExConfig import AutoConfiguration
AutoConfiguration.ConfigureSimulationOrRealData() #configures DataSource global flag
AutoConfiguration.ConfigureConditionsTag() #sets globalflags.ConditionsTag
from AthenaCommon.DetFlags import DetFlags
DetFlags.all_setOff() #skip this line out to leave everything on. But this will take longer
DetFlags.detdescr.Calo_setOn() #e.g. if I am accessing CaloCellContainer, I need the calo detector description
include("RecExCond/AllDet_detDescr.py")

# Create the algorithm's configuration.
from AnaAlgorithm.DualUseConfig import createAlgorithm
alg = createAlgorithm ( 'MyxAODAnalysis', 'AnalysisAlg' )

# later on we'll add some configuration options for our algorithm that go here

from egammaRec.Factories import ToolFactory
from CaloClusterCorrection.CaloClusterCorrectionConf import CaloFillRectangularCluster as CFRC
CaloFillRectangularCluster = ToolFactory( CFRC, 
                                          cells_name = "AODCellContainer", 
                                          fill_cluster = True ) 
cluster_sizes = (3,7), (5,5), (7,11)
ToolSvc = [CaloFillRectangularCluster.copy(name = "CaloFillRectangularCluster_%sx%s" % (neta, nphi), 
      eta_size = neta,
      phi_size = nphi)() for neta, nphi in cluster_sizes]

from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
ToolSvc += Trig__TrigDecisionTool( "TrigDecisionTool" )

ToolSvc += CfgMgr.Trig__MatchingTool("Trigger_match_tool",OutputLevel=DEBUG)

jps.AthenaCommonFlags.HistOutputs = ["ANALYSIS:MyxAODAnalysis.outputs.root"]
# Add our algorithm to the main alg sequence
athAlgSeq += alg


# optional include for reducing printout from athena
include("AthAnalysisBaseComps/SuppressLogging.py")

