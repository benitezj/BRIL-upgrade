# imports
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os, sys, glob

# create a new CMS process
process = cms.Process("ITclusterAnalyzerCoincidences1")
#process = cms.Process("Ashish2xCoincidence")

# set up the options
options = VarParsing.VarParsing('analysis')

options.inputFiles = '%s' % (os.getenv('INPUT'))
options.outputFile = '%s' % (os.getenv('OUTPUT'))

#set up the defaults
#options.inputFiles = 'file:/eos/user/g/gauzinge/PUdata/step3_pixel_PU_1.1.root'
# options.inputFiles = 'file:/afs/cern.ch/user/g/gauzinge/ITsim/CMSSW_10_4_0_pre2/src/BRIL_ITsim/step3_pixel_PU_10.0.root'
# options.inputFiles = 'file:/afs/cern.ch/work/c/cbarrera/private/BRIL/outputDir/step3_pixel_PU_20.0.0.root'
#options.inputFiles = 'file:/eos/user/b/benitezj/BRIL/3B9F4459-69D5-C44F-A2C0-9AE1235BCEE5.root'
#options.inputFiles = 'file:/eos/user/g/gauzinge/PUdata/step3_pixel_PU_100.0.0.root'
#options.inputFiles = 'root://cms-xrd-global.cern.ch//store/relval/CMSSW_10_6_0_patch2/RelValNuGun/GEN-SIM-RECO/PU25ns_106X_upgrade2023_realistic_v3_2023D42PU0p5-v1/10000/28749F73-4D48-374E-800E-D70FB8C37FC6.root'
#options.outputFile='summary.root'
#options.maxEvents = 1 #one event

print options.inputFiles, options.outputFile, options.maxEvents

#get and parse command line arguments
options.parseArguments()

# load the geomtry that i modified
process.load('Configuration.Geometry.GeometryExtended2023D21Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('ITclusterAnalyzerCoincidences1')
#process.MessageLogger.categories.append('Ashish2xCoincidence')

process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit=cms.untracked.int32(-1)
)
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(False)
                                    # ,SkipEvent = cms.untracked.vstring('ProductNotFound')
                                    )

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(options.maxEvents))

# the input file
process.source = cms.Source("PoolSource",
                            fileNames=cms.untracked.vstring(options.inputFiles)
                            )

process.content = cms.EDAnalyzer("EventContentAnalyzer")
# the config of my analyzer

#process.BRIL_IT_Analysis = cms.EDAnalyzer('Ashish2xCoincidence',
process.BRIL_IT_Analysis = cms.EDAnalyzer('ITclusterAnalyzerCoincidences1',
                                         clusters=cms.InputTag("siPixelClusters"),
                                         simlinks=cms.InputTag("simSiPixelDigis", "Pixel", "HLT"),
                                         digis=cms.InputTag("simSiPixelDigis", "Pixel", "HLT"),
                                          #simlinks=cms.InputTag("Pixel"),
                                          #simtracks=cms.InputTag("g4SimHits"),
                                          maxBin=cms.untracked.uint32(5000),
                                          docoincidence=cms.untracked.bool(True),
                                          dx_cut=cms.double(0.5),
                                          dy_cut=cms.double(0.5),
                                          dz_cut=cms.double(1.4),
                                          C1_cut=cms.double(2),
                                          C2_cut=cms.double(2),
                                          C3_cut=cms.double(3),
                                          C4_cut=cms.double(2)
                                          )

# the TFIleService that produces the output root files
process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string(options.outputFile)
                                   )


# process.p = cms.Path( ... process.content * ...  )
process.p = cms.Path(process.BRIL_IT_Analysis)
