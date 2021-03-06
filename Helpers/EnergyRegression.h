#ifndef EnergyRegression_h
#define EnergyRegression_h

#include "Riostream.h"
#include <TMath.h>
#include <TMVA/Reader.h>

class EnergyRegression {

 private:
  float EleSCEta, EleSCPhi, EleSigmaIEtaIEta;
  float EleSigmaIPhiIPhi, EleSCEtaWidth, EleSCPhiWidth;
  float EleHoverE;

  TMVA::Reader* tmvaReader[2];// = {NULL, NULL};  

 public:
  EnergyRegression() {
    tmvaReader[0] = 0;
    tmvaReader[1] = 0;
  }
  //~EnergyRegression() {};

  //call this function once at the beginning of event loop
  void initreader() {

    Printf("Init the TMVA reader");
    for (int iBE = 0; iBE < 2; iBE++) {

      tmvaReader[iBE] = new TMVA::Reader("!Color:Silent");

      //add classification variables, variable name have to be the same in weight files
      tmvaReader[iBE]->AddVariable("EleSCPhi", &EleSCPhi);
      tmvaReader[iBE]->AddVariable("EleSCEta", &EleSCEta);
      tmvaReader[iBE]->AddVariable("EleSigmaIEtaIEta", &EleSigmaIEtaIEta);
      tmvaReader[iBE]->AddVariable("EleSigmaIPhiIPhi", &EleSigmaIPhiIPhi);
      tmvaReader[iBE]->AddVariable("EleSCEtaWidth", &EleSCEtaWidth);
      tmvaReader[iBE]->AddVariable("EleSCPhiWidth", &EleSCPhiWidth);
      tmvaReader[iBE]->AddVariable("EleHoverE", &EleHoverE);

      //book method, read weight files
      Printf("book methods");
      if (iBE == 0)
        tmvaReader[0]->BookMVA("BDTG", "Helpers/weights/BDTG_EB_PbPb.weights.xml");
      else
        tmvaReader[1]->BookMVA("BDTG", "Helpers/weights/BDTG_EE_PbPb.weights.xml");
    }
  }

  //call this function for every electron
  //multiply return value with electron energy or electron pt (eg. elePt*ElectronRegressionTMVA(i))
  /* float ElectronRegressionTMVA(int i) { */

  /*   int iBE = (fabs(eleSCEta[i]) < 1.4442) ? 0 : 1; */

  /*   //set variable */
  /*   EleSCPhi = eleSCPhi[i]; */
  /*   EleSCEta = eleSCEta[i]; */
  /*   EleSigmaIEtaIEta = eleSigmaIEtaIEta_2012[i]; */
  /*   EleSigmaIPhiIPhi = eleSigmaIPhiIPhi[i]; */
  /*   EleSCEtaWidth = eleSCEtaWidth[i]; */
  /*   EleSCPhiWidth = eleSCPhiWidth[i]; */
  /*   EleHoverE = eleHoverE[i]; */

  /*   //get regression */
  /*   return (tmvaReader[iBE]->EvaluateRegression("BDTG"))[0]; */

  /* } */

  float ElectronRegressionTMVA(float EleSCPhi, float EleSCEta, float EleSigmaIEtaIEta, float eleSigmaIPhiIPhi, float EleSCEtaWidth, float EleSCPhiWidth, float EleHoverE) {

    int iBE = (fabs(EleSCEta) < 1.4442) ? 0 : 1;

    //get regression
    return (tmvaReader[iBE]->EvaluateRegression("BDTG"))[0];

  }
};
#endif
