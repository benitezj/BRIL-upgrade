#!/bin/bash 

#INPUTPATH=root://cms-xrd-global.cern.ch/    
                                                                                                                                  
SONORA=""
COUNT=0
file="/afs/cern.ch/user/a/asehrawa/CMSSW_10_6_0_patch2/src/BRIL-upgrade/samples/2023D42noPU.txt"
while  IFS= read -r line && [ $COUNT -lt 25 ]; do
#echo "$COUNT"
cft=root://cms-xrd-global.cern.ch/     
COUNT=$(($COUNT +1))
line=$cft$line
SONORA=$SONORA$line,
done < "$file"
echo "Value of count is: $COUNT"
echo "${SONORA::-1}" 
export INPUT=${SONORA::-1}
OUTPUTPATH=/eos/user/a/asehrawa/TEPX
#export OUTPUT=$OUTPUTPATH/summary_PU0.root

cmsRun  /afs/cern.ch/user/a/asehrawa/CMSSW_10_6_0_patch2/src/BRIL-upgrade/ITclusterAnalyzer_cfg.py
