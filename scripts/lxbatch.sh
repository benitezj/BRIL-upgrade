#!/bin/bash

## directory which contains info about the samples and where log files will be put
submitdir=$1
if [ "$submitdir" == "" ]; then
echo "invalid submitdir"
return
fi


## what to do : 0=create scripts, 1=submit, 2=check
action=$2
if [ "$action" == "" ]; then
echo "invalid action"
return
fi


outputdir=/eos/user/b/benitezj/BRIL/
echo "output: $outputdir"


#get the absolute path
submitdir=`readlink -f $submitdir`

INSTALLATION=${CMSSW_BASE}/src




########################
### lxbatch submit
submit(){
    local job=$1
    rm -f $submitdir/${job}.log
    rm -f ${outputdir}/${job}.root
    condor_submit $submitdir/${job}.sub 
}

## copy the cfg
if [ "$action" == "0" ]; then 
    cfg=$3
    if [ "$cfg" == "" ]; then
	echo "No cfg provided\n"
	exit;
    fi

    /bin/cp $cfg $submitdir/cfg.py

    echo "mkdir -p $outputdir"
    mkdir -p $outputdir
    #/bin/ls $outputdir
fi


##### loop over the jobs
counter=0
for f in `/bin/ls $submitdir | grep .txt | grep -v "~" `; do

    job=`echo $f | awk -F".txt" '{print $1}'`

    ###create the scripts
    if [ "$action" == "0" ]; then
	rm -f $submitdir/${job}.sh
	rm -f $submitdir/${job}.sub

	##create the CMSSW job
	echo "export X509_USER_PROXY=${HOME}/x509up_u55361 " >> $submitdir/${job}.sh
	echo "cd ${INSTALLATION} " >> $submitdir/${job}.sh
	echo "eval \`scramv1 jobtime -sh\` " >> $submitdir/${job}.sh
	echo "cd \$TMPDIR  "   >> $submitdir/${job}.sh
	echo "pwd  "   >> $submitdir/${job}.sh

	echo "export INPUTFILE=${submitdir}/${job}.txt" >> $submitdir/${job}.sh

	echo "env" >> $submitdir/${job}.sh
	echo "cmsJob  ${submitdir}/cfg.py" >> $submitdir/${job}.sh
	echo "cp CorrectionHisto.root $outputdir/${job}.root " >> $submitdir/${job}.sh


	##create condor jdl
	echo "Universe   = vanilla" >>  $submitdir/${job}.sub
	echo "+JobFlavour = \"workday\" " >> $submitdir/${job}.sub
#	echo "+JobFlavour = \"testmatch\" " >> $submitdir/${job}.sub
	echo "Executable = /bin/bash" >> $submitdir/${job}.sub 
	echo "Arguments  = ${submitdir}/${job}.sh" >> $submitdir/${job}.sub 
	echo "Log        = ${submitdir}/${job}.log" >> $submitdir/${job}.sub 
	echo "Output     = ${submitdir}/${job}.log" >> $submitdir/${job}.sub 
	echo "Error      = ${submitdir}/${job}.log" >> $submitdir/${job}.sub 
	echo "Queue  " >> $submitdir/${job}.sub 

    fi
    

    ##submit to lxbatch
    if [ "$action" == "1" ]; then
	submit $job
    fi


    counter=`echo $counter | awk '{print $1+1}'`
done

echo "Total jobs: $counter"

