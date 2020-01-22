for d in `cat samples/CMSSW_10_6_0_patch2-PU25ns_106X_upgrade2023.txt`; do 
D=`echo $d | sed 's/\//-/g'`
dasgoclient --query="file dataset=$d" > samples/${D}.txt 
done
