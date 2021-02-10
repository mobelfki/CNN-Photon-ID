#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <MyAnalysis/MCLumi.h>

//Tools include(s) :
#include "ElectronPhotonSelectorTools/AsgElectronLikelihoodTool.h"
#include "IsolationSelection/IsolationSelectionTool.h"
#include <AsgTools/AnaToolHandle.h>
#include "GaudiKernel/ToolHandle.h"
#include "MuonSelectorTools/MuonSelectionTool.h"
#include "MuonMomentumCorrections/MuonCalibrationAndSmearingTool.h"
#include "ElectronPhotonFourMomentumCorrection/EgammaCalibrationAndSmearingTool.h"
#include "AsgAnalysisInterfaces/IPileupReweightingTool.h"
#include "AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h"
#include "TrigConfxAOD/xAODConfigTool.h"
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "TriggerMatchingTool/IMatchingTool.h"
#include "TriggerMatchingTool/MatchingTool.h"
#include "ElectronEfficiencyCorrection/AsgElectronEfficiencyCorrectionTool.h"
#include "MuonEfficiencyCorrections/MuonEfficiencyScaleFactors.h"
#include "PathResolver/PathResolver.h"
#include "ElectronPhotonSelectorTools/EGammaAmbiguityTool.h"
#include "EgammaAnalysisInterfaces/IAsgDeadHVCellRemovalTool.h"
#include "EgammaAnalysisInterfaces/IAsgElectronLikelihoodTool.h"
#include "PhotonEfficiencyCorrection/AsgPhotonEfficiencyCorrectionTool.h"
#include "ElectronPhotonSelectorTools/AsgPhotonIsEMSelector.h"
#include "ElectronPhotonSelectorTools/egammaPIDdefs.h"

//ROOTCORE include(s) :
#include "xAODCore/ShallowCopy.h"
#include "xAODEgamma/Photon.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODEgamma/Electron.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/Muon.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/EgammaxAODHelpers.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterAuxContainer.h"
#include "xAODCaloEvent/CaloCluster.h"
#include "xAODTracking/Vertex.h"
#include "xAODTracking/VertexContainer.h"

#include "xAODEgamma/EgammaAuxContainer.h"
#include "xAODEgamma/Egamma.h"

#include "xAODTruth/TruthParticleAuxContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/xAODTruthHelpers.h"

#include "TruthUtils/PIDHelpers.h"
#include "xAODBase/IParticleHelpers.h"
#include "xAODBase/IParticle.h"


//Athena include(s) :

#include "CaloEvent/CaloClusterCellLink.h"
#include "CaloEvent/CaloCellContainer.h"
#include "CaloUtils/CaloClusterStoreHelper.h"
#include "CaloUtils/CaloCellDetPos.h"
#include "CaloClusterCorrection/CaloFillRectangularCluster.h"
#include "GaudiKernel/ToolHandle.h"

class EGammaAmbiguityTool;
class MyxAODAnalysis : public EL::AnaAlgorithm
{
public:
  // this is a standard algorithm constructor
  MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;
  void   decorateElectronObject(const xAOD::Electron*& egamma, int m_eta_size, int m_phi_size);
  void   decoratePhotonObject(const xAOD::Photon*& egamma, int m_eta_size, int m_phi_size);
  void   SelectZmumuyEvents(std::vector< const xAOD::Photon* > photons, std::vector< const xAOD::Muon* > muons);
  void   SelectZeeyEvents(std::vector< const xAOD::Photon* > photons, std::vector< const xAOD::Electron* > electrons);
  void   StoreEvent (int iph, int il1, int il2, TString Type);
  double getSF(int il,TString Type);
  void   getPhotonsShowerShapeValues(const xAOD::Photon* object, float& rhad1, float& rhad, float& e277, float& reta, float& rphi, float& weta1, float& weta2, float& f1, float& f3, float& f3core, float& wtots1, float& deltae, float& eratio, float& fracs1, float& e011, float& e132, float& e237, float& e2tsts1, float& emins1, float& emaxs1, float& ethad, float& ethad1);
  void   ClearVariables();
  void   SetupTree();
  bool matchTrigger(int l1, int l2, TString Type);
  int ApplySinglePhotonSelection();
  void decorateWithTruthInfo(const xAOD::Photon*& egamma);
  bool notFromHadron(const xAOD::TruthParticle *ptcl);
  void StoreSinglePhoton();
  bool  passAuthorCut(const xAOD::Photon *gam);
  //int    getDSID();
  CP::IsolationSelectionTool*  Electron_iso_tool;
  AsgElectronLikelihoodTool* Electron_id_tool;

  CP::IsolationSelectionTool* Photon_loose_tool;
  CP::IsolationSelectionTool* Photon_tightCaloOnly_tool;
  CP::IsolationSelectionTool* Photon_tight_tool;
  CP::IsolationSelectionTool* Muon_iso_tool;
  CP::MuonSelectionTool* Muon_id_tool;
  CP::MuonCalibrationAndSmearingTool* Muon_calib_tool;
  CP::MuonCalibrationAndSmearingTool* Muon_calib17_tool;
  CP::EgammaCalibrationAndSmearingTool* Egamma_calib_tool;
 
  asg::AnaToolHandle<CP::IPileupReweightingTool> PileUp_tool;
  asg::AnaToolHandle<IGoodRunsListSelectionTool> GRL_tool;
  ToolHandle<Trig::TrigDecisionTool> Trigger_dic_tool;
  asg::AnaToolHandle<Trig::IMatchingTool> Trigger_match_tool;

  AsgElectronEfficiencyCorrectionTool* Electron_RecoSF_tool;
  AsgElectronEfficiencyCorrectionTool* Electron_IsoSF_tool;
  AsgPhotonEfficiencyCorrectionTool* Photon_IsoTighSF_tool;	
  AsgPhotonEfficiencyCorrectionTool* Photon_IsoLooseSF_tool;	
  AsgPhotonEfficiencyCorrectionTool* Photon_IsoTighCaloSF_tool;		
  CP::MuonEfficiencyScaleFactors* Muon_RecoSF_tool;

  AsgPhotonIsEMSelector* Photon_Off_isEMLoose_tool;
  AsgPhotonIsEMSelector* Photon_Off_isEMTightInc_tool;
  AsgPhotonIsEMSelector* Photon_Off_isEMTightDep_tool;

  AsgPhotonIsEMSelector* Photon_On_isEMLoose_tool;
  AsgPhotonIsEMSelector* Photon_On_isEMTight_tool;
  AsgPhotonIsEMSelector* Photon_On_isEMMedium_tool;


  ToolHandle<CaloClusterCollectionProcessor> caloFillRectangularTools;
  CaloFillRectangularCluster *Calotool;

  asg::AnaToolHandle<IAsgDeadHVCellRemovalTool> m_deadHVTool;

  IEGammaAmbiguityTool* m_fakeTool;

  MCLumi *mclumi = new MCLumi(PathResolverFindCalibFile("MyAnalysis/Files/samples.txt"));

  std::vector< const xAOD::Muon* > m_selMuons;
  std::vector< const xAOD::Electron* > m_selElectrons;
  std::vector< const xAOD::Photon* > m_selPhotons;
  std::vector< const xAOD::Photon* > m_singlePhotons;
  const xAOD::EventInfo *eventInfo = nullptr;

  bool doSinglePhoton;
  bool isAOD = true;
  bool retrieveCells = true;
  bool isMC = false;
  float mllMin = 40.;
  float mllMax = 83.;
  float mllyMin = 80.;
  float mllyMax = 100.;
  float mindREl = 0.4;
  float mindRMu = 0.2;
  unsigned int DSID;
  bool passTrigger;
  bool passSingleElTrigger = false;
  bool passDoubleElTrigger = false;
  bool passSingleMuTrigger = false;
  bool passDoubleMuTrigger = false;
  std::vector<TString> triggerList;
  std::string fullGRLFilePath;
  //variables; 
  double mc_wgt;
  double mc_xsec;
  double pu_wgt;
  double pu_mu;
  int    mc_event_number;
  bool isZeey;
  bool isZmumuy;

  //***** Photon *****//
  double ph_pt;
  double ph_eta;
  double ph_phi;
  double ph_E;
  double ph_topoetcone20;
  double ph_topoetcone30;
  double ph_topoetcone40;
  double ph_ptcone20;
  double ph_ptcone30;
  double ph_ptcone40;
  double ph_etcone20;
  double ph_etcone30;
  double ph_etcone40;
  double ph_ptvarcone20;
  double ph_ptvarcone30;
  double ph_ptvarcone40;
  bool ph_isIsoLoose;
  bool ph_isIsoTightCalo;
  bool ph_isIsoTight;

  bool ph_isEMLooseOff;
  bool ph_isEMTightIncOff;
  bool ph_isEMTightDepOff;
  bool ph_isEMLooseOn;
  bool ph_isEMTightOn;
  bool ph_isEMMediumOn;

  double ph_conv;
  double ph_Ethad;
  double ph_Ethad1;
  double ph_Rhad1;
  double ph_Rhad;
  double ph_E011;
  double ph_E132;
  double ph_E237;
  double ph_E277;
  double ph_Reta;
  double ph_Rphi;
  double ph_Weta1;
  double ph_Weta2;
  double ph_f1;
  double ph_f3;
  double ph_f3core;
  double ph_fracs1;
  double ph_Wtots1;
  double ph_deltaE;
  double ph_Eratio;
  double ph_E2tsts1;
  double ph_Emins1;
  double ph_Emaxs1;
  double ph_IsoLooseSF;
  double ph_IsoTightCaloSF;
  double ph_IsoTightSF;

  bool   ph_isTruthMatch;
  bool   ph_TruthConv;
  int    ph_PDG;

  int ph_ClusterSize7x11Lr2;
  int ph_ClusterSize3x7Lr2;
  int ph_ClusterSize5x5Lr2;
  int ph_ClusterSize7x11Lr3;
  int ph_ClusterSize3x7Lr3;
  int ph_ClusterSize5x5Lr3;
  int ph_ClusterSize7x11Lr1;
  int ph_ClusterSize3x7Lr1;
  int ph_ClusterSize5x5Lr1;
  int ph_ClusterSize7x11PreS;
  int ph_ClusterSize3x7PreS;
  int ph_ClusterSize5x5PreS;

//Lr2

  std::vector<float> ph_clusterCellsLr2E711;
  std::vector<float> ph_clusterCellsLr2Eta711;
  std::vector<float> ph_clusterCellsLr2Phi711;

  std::vector<float> ph_clusterCellsLr2X711;
  std::vector<float> ph_clusterCellsLr2Y711;
  std::vector<float> ph_clusterCellsLr2Z711;
  std::vector<float> ph_clusterCellsLr2T711;
  std::vector<bool> ph_clusterCellsLr2isBAD711;

  std::vector<float> ph_clusterCellsLr2E37;
  std::vector<float> ph_clusterCellsLr2Eta37;
  std::vector<float> ph_clusterCellsLr2Phi37;

  std::vector<float> ph_clusterCellsLr2X37;
  std::vector<float> ph_clusterCellsLr2Y37;
  std::vector<float> ph_clusterCellsLr2Z37;
  std::vector<float> ph_clusterCellsLr2T37;
  std::vector<bool> ph_clusterCellsLr2isBAD37;

  std::vector<float> ph_clusterCellsLr2E55;
  std::vector<float> ph_clusterCellsLr2Eta55;
  std::vector<float> ph_clusterCellsLr2Phi55;

  std::vector<float> ph_clusterCellsLr2X55;
  std::vector<float> ph_clusterCellsLr2Y55;
  std::vector<float> ph_clusterCellsLr2Z55;
  std::vector<float> ph_clusterCellsLr2T55;
  std::vector<bool> ph_clusterCellsLr2isBAD55;

//Lr3

  std::vector<float> ph_clusterCellsLr3E711;
  std::vector<float> ph_clusterCellsLr3Eta711;
  std::vector<float> ph_clusterCellsLr3Phi711;

  std::vector<float> ph_clusterCellsLr3X711;
  std::vector<float> ph_clusterCellsLr3Y711;
  std::vector<float> ph_clusterCellsLr3Z711;
  std::vector<float> ph_clusterCellsLr3T711;
  std::vector<bool> ph_clusterCellsLr3isBAD711;

  std::vector<float> ph_clusterCellsLr3E37;
  std::vector<float> ph_clusterCellsLr3Eta37;
  std::vector<float> ph_clusterCellsLr3Phi37;

  std::vector<float> ph_clusterCellsLr3X37;
  std::vector<float> ph_clusterCellsLr3Y37;
  std::vector<float> ph_clusterCellsLr3Z37;
  std::vector<float> ph_clusterCellsLr3T37;
  std::vector<bool> ph_clusterCellsLr3isBAD37;

  std::vector<float> ph_clusterCellsLr3E55;
  std::vector<float> ph_clusterCellsLr3Eta55;
  std::vector<float> ph_clusterCellsLr3Phi55;

  std::vector<float> ph_clusterCellsLr3X55;
  std::vector<float> ph_clusterCellsLr3Y55;
  std::vector<float> ph_clusterCellsLr3Z55;
  std::vector<float> ph_clusterCellsLr3T55;
  std::vector<bool> ph_clusterCellsLr3isBAD55;

//Lr1

  std::vector<float> ph_clusterCellsLr1E711;
  std::vector<float> ph_clusterCellsLr1Eta711;
  std::vector<float> ph_clusterCellsLr1Phi711;

  std::vector<float> ph_clusterCellsLr1X711;
  std::vector<float> ph_clusterCellsLr1Y711;
  std::vector<float> ph_clusterCellsLr1Z711;
  std::vector<float> ph_clusterCellsLr1T711;
  std::vector<bool> ph_clusterCellsLr1isBAD711;

  std::vector<float> ph_clusterCellsLr1E37;
  std::vector<float> ph_clusterCellsLr1Eta37;
  std::vector<float> ph_clusterCellsLr1Phi37;

  std::vector<float> ph_clusterCellsLr1X37;
  std::vector<float> ph_clusterCellsLr1Y37;
  std::vector<float> ph_clusterCellsLr1Z37;
  std::vector<float> ph_clusterCellsLr1T37;
  std::vector<bool> ph_clusterCellsLr1isBAD37;

  std::vector<float> ph_clusterCellsLr1E55;
  std::vector<float> ph_clusterCellsLr1Eta55;
  std::vector<float> ph_clusterCellsLr1Phi55;

  std::vector<float> ph_clusterCellsLr1X55;
  std::vector<float> ph_clusterCellsLr1Y55;
  std::vector<float> ph_clusterCellsLr1Z55;
  std::vector<float> ph_clusterCellsLr1T55;
  std::vector<bool> ph_clusterCellsLr1isBAD55;

//PreS

  std::vector<float> ph_clusterCellsPreSE711;
  std::vector<float> ph_clusterCellsPreSEta711;
  std::vector<float> ph_clusterCellsPreSPhi711;

  std::vector<float> ph_clusterCellsPreSX711;
  std::vector<float> ph_clusterCellsPreSY711;
  std::vector<float> ph_clusterCellsPreSZ711;
  std::vector<float> ph_clusterCellsPreST711;
  std::vector<bool> ph_clusterCellsPreSisBAD711;

  std::vector<float> ph_clusterCellsPreSE37;
  std::vector<float> ph_clusterCellsPreSEta37;
  std::vector<float> ph_clusterCellsPreSPhi37;

  std::vector<float> ph_clusterCellsPreSX37;
  std::vector<float> ph_clusterCellsPreSY37;
  std::vector<float> ph_clusterCellsPreSZ37;
  std::vector<float> ph_clusterCellsPreST37;
  std::vector<bool> ph_clusterCellsPreSisBAD37;

  std::vector<float> ph_clusterCellsPreSE55;
  std::vector<float> ph_clusterCellsPreSEta55;
  std::vector<float> ph_clusterCellsPreSPhi55;

  std::vector<float> ph_clusterCellsPreSX55;
  std::vector<float> ph_clusterCellsPreSY55;
  std::vector<float> ph_clusterCellsPreSZ55;
  std::vector<float> ph_clusterCellsPreST55;
  std::vector<bool> ph_clusterCellsPreSisBAD55;
 

  //Lepton
  double l1_pt;
  double l1_eta;
  double l1_phi;
  double l1_e;
  double l1_Charge;
  double l2_pt;
  double l2_eta;
  double l2_phi;
  double l2_e;
  double l2_Charge;
  double l1_SF;
  double l2_SF;
  std::vector<float> m_ee;
  std::vector<float> m_eey;
  std::vector<float> m_mumu;
  std::vector<float> m_mumuy;

  int l1_ClusterSize7x11Lr2;
  int l1_ClusterSize3x7Lr2;
  int l1_ClusterSize5x5Lr2;
  int l1_ClusterSize7x11Lr3;
  int l1_ClusterSize3x7Lr3;
  int l1_ClusterSize5x5Lr3;
  int l1_ClusterSize7x11Lr1;
  int l1_ClusterSize3x7Lr1;
  int l1_ClusterSize5x5Lr1;
  std::vector<float> l1_clusterCellsLr2E711;
  std::vector<float> l1_clusterCellsLr2Eta711;
  std::vector<float> l1_clusterCellsLr2Phi711;
  std::vector<float> l1_clusterCellsLr2E37;
  std::vector<float> l1_clusterCellsLr2Eta37;
  std::vector<float> l1_clusterCellsLr2Phi37;
  std::vector<float> l1_clusterCellsLr2E55;
  std::vector<float> l1_clusterCellsLr2Eta55;
  std::vector<float> l1_clusterCellsLr2Phi55;
  std::vector<float> l1_clusterCellsLr3E711;
  std::vector<float> l1_clusterCellsLr3Eta711;
  std::vector<float> l1_clusterCellsLr3Phi711;
  std::vector<float> l1_clusterCellsLr3E37;
  std::vector<float> l1_clusterCellsLr3Eta37;
  std::vector<float> l1_clusterCellsLr3Phi37;
  std::vector<float> l1_clusterCellsLr3E55;
  std::vector<float> l1_clusterCellsLr3Eta55;
  std::vector<float> l1_clusterCellsLr3Phi55;
  std::vector<float> l1_clusterCellsLr1E711;
  std::vector<float> l1_clusterCellsLr1Eta711;
  std::vector<float> l1_clusterCellsLr1Phi711;
  std::vector<float> l1_clusterCellsLr1E37;
  std::vector<float> l1_clusterCellsLr1Eta37;
  std::vector<float> l1_clusterCellsLr1Phi37;
  std::vector<float> l1_clusterCellsLr1E55;
  std::vector<float> l1_clusterCellsLr1Eta55;
  std::vector<float> l1_clusterCellsLr1Phi55;


  int l2_ClusterSize7x11Lr2;
  int l2_ClusterSize3x7Lr2;
  int l2_ClusterSize5x5Lr2;
  int l2_ClusterSize7x11Lr3;
  int l2_ClusterSize3x7Lr3;
  int l2_ClusterSize5x5Lr3;
  int l2_ClusterSize7x11Lr1;
  int l2_ClusterSize3x7Lr1;
  int l2_ClusterSize5x5Lr1;
  std::vector<float> l2_clusterCellsLr2E711;
  std::vector<float> l2_clusterCellsLr2Eta711;
  std::vector<float> l2_clusterCellsLr2Phi711;
  std::vector<float> l2_clusterCellsLr2E37;
  std::vector<float> l2_clusterCellsLr2Eta37;
  std::vector<float> l2_clusterCellsLr2Phi37;
  std::vector<float> l2_clusterCellsLr2E55;
  std::vector<float> l2_clusterCellsLr2Eta55;
  std::vector<float> l2_clusterCellsLr2Phi55;
  std::vector<float> l2_clusterCellsLr3E711;
  std::vector<float> l2_clusterCellsLr3Eta711;
  std::vector<float> l2_clusterCellsLr3Phi711;
  std::vector<float> l2_clusterCellsLr3E37;
  std::vector<float> l2_clusterCellsLr3Eta37;
  std::vector<float> l2_clusterCellsLr3Phi37;
  std::vector<float> l2_clusterCellsLr3E55;
  std::vector<float> l2_clusterCellsLr3Eta55;
  std::vector<float> l2_clusterCellsLr3Phi55;
  std::vector<float> l2_clusterCellsLr1E711;
  std::vector<float> l2_clusterCellsLr1Eta711;
  std::vector<float> l2_clusterCellsLr1Phi711;
  std::vector<float> l2_clusterCellsLr1E37;
  std::vector<float> l2_clusterCellsLr1Eta37;
  std::vector<float> l2_clusterCellsLr1Phi37;
  std::vector<float> l2_clusterCellsLr1E55;
  std::vector<float> l2_clusterCellsLr1Eta55;
  std::vector<float> l2_clusterCellsLr1Phi55;

private:
  // Configuration, and any other types of variables go here.
  //float m_cutValue;
  //TTree *m_myTree;
  //TH1 *m_myHist;
};

#endif
