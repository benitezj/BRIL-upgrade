#!/bin/bash

## directory which contains info about the samples and where log files will be put
submitdir=$1
if [ "$submitdir" == "" ]; then
    echo "invalid submitdir"
    return
fi


## what to do : 0=create scripts, 1=submit, 2=check
action=$2

##where the results will be stored, this directory will be created below
outputdir=/eos/user/b/benitezj/BRIL/UpgradeStudies/$submitdir
echo "output: $outputdir"

#get the absolute path
INSTALLATION=${CMSSW_BASE}/src
cfg=$INSTALLATION/BRIL-upgrade/ITclusterAnalyzer_cfg.py
fullsubmitdir=`readlink -f $submitdir`

echo "Config: $cfg"

########################
### lxbatch submit
submit(){
    local job=$1
    rm -f $fullsubmitdir/${job}.log
    rm -f ${outputdir}/${job}.root
    condor_submit $fullsubmitdir/${job}.sub 
}

## copy the cfg
if [ "$action" == "0" ]; then 
    /bin/cp $cfg $fullsubmitdir/cfg.py

    echo "mkdir -p $outputdir"
    mkdir -p $outputdir
    #/bin/ls $outputdir
fi


##### loop over the jobs
counter=0
for f in `/bin/ls $fullsubmitdir | grep .txt | grep -v "~" `; do

    job=`echo $f | awk -F".txt" '{print $1}'`
    echo $job

    ###create the scripts
    if [ "$action" == "0" ]; then
	rm -f $fullsubmitdir/${job}.sh
	rm -f $fullsubmitdir/${job}.sub

	##create the CMSSW job
	echo "export X509_USER_PROXY=${HOME}/x509up_u55361 " >> $fullsubmitdir/${job}.sh
	echo "cd ${INSTALLATION} " >> $fullsubmitdir/${job}.sh
	echo "eval \`scramv1 jobtime -sh\` " >> $fullsubmitdir/${job}.sh
	echo "cd \$TMPDIR  "   >> $fullsubmitdir/${job}.sh
	echo "pwd  "   >> $fullsubmitdir/${job}.sh

	echo "export INPUTFILE=${fullsubmitdir}/${job}.txt" >> $fullsubmitdir/${job}.sh

	echo "env" >> $fullsubmitdir/${job}.sh

	echo "Hello Ashish. This is job ${job}" >> $fullsubmitdir/${job}.sh

	#echo "cmsJob  ${fullsubmitdir}/cfg.py" >> $fullsubmitdir/${job}.sh
	#echo "cp CorrectionHisto.root $outputdir/${job}.root " >> $fullsubmitdir/${job}.sh


	##create condor jdl
	echo "Universe   = vanilla" >>  $fullsubmitdir/${job}.sub
	echo "+JobFlavour = \"workday\" " >> $fullsubmitdir/${job}.sub
#	echo "+JobFlavour = \"testmatch\" " >> $fullsubmitdir/${job}.sub
	echo "Executable = /bin/bash" >> $fullsubmitdir/${job}.sub 
	echo "Arguments  = ${fullsubmitdir}/${job}.sh" >> $fullsubmitdir/${job}.sub 
	echo "Log        = ${fullsubmitdir}/${job}.log" >> $fullsubmitdir/${job}.sub 
	echo "Output     = ${fullsubmitdir}/${job}.log" >> $fullsubmitdir/${job}.sub 
	echo "Error      = ${fullsubmitdir}/${job}.log" >> $fullsubmitdir/${job}.sub 
	echo "Queue  " >> $fullsubmitdir/${job}.sub 

    fi
    

    ##submit to lxbatch
    if [ "$action" == "1" ]; then
	submit $job
    fi


    counter=`echo $counter | awk '{print $1+1}'`
done

echo "Total jobs: $counter"
