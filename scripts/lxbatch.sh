#!/bin/bash

## create a submission directory which contains text files containing .root files corresponding to each pileup value and where log files will be put 
## copy the sample text files in submission directory where each sample text file will be one job 
## create the job execution files (.sh, .sub) using > source BRIL-upgrade/scripts/lxbatch.sh samples_17Feb2020 0
## submit the jobs using > source BRIL-upgrade/scripts/lxbatch.sh samples_17Feb2020 1
submitdir=$1
if [ "$submitdir" == "" ]; then
    echo "invalid submitdir"
    return
fi

## what to do : 0=create scripts, 1=submit, 2=check
action=$2

## where the results will be stored, this directory will be created below
outputdir=/eos/user/a/asehrawa/TEPX/$submitdir
echo "output: $outputdir"

## get the absolute path
INSTALLATION=${CMSSW_BASE}/src
cfg=$INSTALLATION/BRIL-upgrade/ITclusterAnalyzer_cfg.py
fullsubmitdir=`readlink -f $submitdir`

echo "Config: $cfg"

########################
## lxbatch submit
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

## loop over the jobs
counter=0
for f in `/bin/ls $fullsubmitdir | grep .txt | grep -v "~" `; do

    job=`echo $f | awk -F".txt" '{print $1}'`
    echo $job

    ## create the scripts
    if [ "$action" == "0" ]; then
	rm -f $fullsubmitdir/${job}.sh
	rm -f $fullsubmitdir/${job}.sub

	## create the CMSSW job
	echo "export X509_USER_PROXY=${HOME}/x509up_u55361 " >> $fullsubmitdir/${job}.sh
	echo "cd ${INSTALLATION} " >> $fullsubmitdir/${job}.sh
	echo "eval \`scramv1 runtime -sh\` " >> $fullsubmitdir/${job}.sh
	echo "pwd"   >> $fullsubmitdir/${job}.sh                                                                                            
	echo "export SONORA=\"\" " >> $fullsubmitdir/${job}.sh
        echo "cft=root://cms-xrd-global.cern.ch/" >>  $fullsubmitdir/${job}.sh
	echo "COUNT=0" >>  $fullsubmitdir/${job}.sh
	echo "file=\"${fullsubmitdir}/${job}.txt\"" >>  $fullsubmitdir/${job}.sh
	echo "while IFS= read -r line && [ \$COUNT -lt 10 ]; do" >>  $fullsubmitdir/${job}.sh
	echo "echo "\$COUNT=\$line=" "  >>  $fullsubmitdir/${job}.sh
	echo "COUNT=\$((\$COUNT +1))" >>  $fullsubmitdir/${job}.sh
	echo "line=\$cft\$line" >>  $fullsubmitdir/${job}.sh
	echo "export SONORA=\$SONORA\$line," >>  $fullsubmitdir/${job}.sh
	echo "done < \$file" >>  $fullsubmitdir/${job}.sh
	echo "echo \"Value of count is: \$COUNT\" " >>  $fullsubmitdir/${job}.sh
	echo "echo \${SONORA}" >>  $fullsubmitdir/${job}.sh
	echo "echo "\${SONORA::-1}"" >>  $fullsubmitdir/${job}.sh
	echo "echo \$INPUT"   >>  $fullsubmitdir/${job}.sh
	echo "export INPUT=\${SONORA::-1}" >>  $fullsubmitdir/${job}.sh
	echo "export OUTPUT=$outputdir/${job}.root" >>  $fullsubmitdir/${job}.sh
	echo "env" >> $fullsubmitdir/${job}.sh
        echo "cmsRun  ${fullsubmitdir}/cfg.py" >>  $fullsubmitdir/${job}.sh
	
	## create condor jdl
	echo "Universe   = vanilla" >>  $fullsubmitdir/${job}.sub
	echo "+JobFlavour = \"microcentury\" " >> $fullsubmitdir/${job}.sub
	echo "Executable = /bin/bash" >> $fullsubmitdir/${job}.sub 
	echo "Arguments  = ${fullsubmitdir}/${job}.sh" >> $fullsubmitdir/${job}.sub 
	echo "Log        = ${fullsubmitdir}/${job}.log" >> $fullsubmitdir/${job}.sub 
	echo "Output     = ${fullsubmitdir}/${job}.log" >> $fullsubmitdir/${job}.sub 
	echo "Error      = ${fullsubmitdir}/${job}.log" >> $fullsubmitdir/${job}.sub 
	echo "Queue  " >> $fullsubmitdir/${job}.sub 

    fi
    

    ## submit to lxbatch
    if [ "$action" == "1" ]; then
	submit $job
    fi


    counter=`echo $counter | awk '{print $1+1}'`
done

echo "Total jobs: $counter"

   ## check successful completion of job
     if [ "$action" == "2" ]; then
        echo "Checking job status"
  
   var = $(cat ${fullsubmitdir}/${job}.log | grep "IT cluster Analyzer processed")
    if [ -z "$var" ]
then
      echo "Job is not successfully completed"
else
      echo "Job is successfully completed \$var"
fi
   fi
