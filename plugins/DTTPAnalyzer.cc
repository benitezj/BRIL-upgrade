// -*- C++ -*-

// system include files
#include <algorithm>
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
//#include "DataFormats/Phase2TrackerDigi/interface/Phase2TrackerDigi.h"
#include "DataFormats/SiPixelDigi/interface/PixelDigi.h"
#include "SimDataFormats/TrackerDigiSimLink/interface/PixelDigiSimLink.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include <TH2F.h>

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


class DTTPAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
    explicit DTTPAnalyzer(const edm::ParameterSet&);
    ~DTTPAnalyzer();

private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;


};


DTTPAnalyzer::DTTPAnalyzer(const edm::ParameterSet& iConfig)
  : 
{
}

DTTPAnalyzer::~DTTPAnalyzer() {

}

void DTTPAnalyzer::beginJob() {

    edm::Service<TFileService> fs;

    fs->file().cd("/");
    TFileDirectory td = fs->mkdir("TEPX");

    td = fs->mkdir("TEPX/Residuals");
    //m_residualX = td.make<TH1F>("ResidualsX", "ResidualsX;deltaX;counts", 1000, 0, 1);


}

void DTTPAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

}

void DTTPAnalyzer::endJob() {
}



DEFINE_FWK_MODULE(DTTPAnalyzer);
