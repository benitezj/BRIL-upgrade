#!/bin/bash 

#INPUTPATH=root://cms-xrd-global.cern.ch/    
                                                                                                                                  
TINKU=""
COUNT=0
file="/afs/cern.ch/user/a/asehrawa/CMSSW_10_6_0_patch2/src/BRIL-upgrade/samples/2023D42PU200.txt"
while  IFS= read -r line && [ $COUNT -lt 50 ]; do
#echo "$COUNT"
cft=root://cms-xrd-global.cern.ch/     
COUNT=$(($COUNT +1))
line=$cft$line
TINKU=$TINKU$line,
done < "$file"
echo "Value of count is: $COUNT"
echo "${TINKU::-1}" 
export INPUT=${TINKU::-1}
OUTPUTPATH=/eos/user/a/asehrawa/TEPX
#export OUTPUT=$OUTPUTPATH/summary_PU200.root

cmsRun  /afs/cern.ch/user/a/asehrawa/CMSSW_10_6_0_patch2/src/BRIL-upgrade/ITclusterAnalyzer_cfg.py
