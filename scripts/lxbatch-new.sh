#!/bin/bash

## Step 1: create a submission directory
## Step 2: Submission directory contain sample text files 2023D42PU0p5.txt, 2023D42PU1.txt, 2023D42PU100.txt, 2023D42PU140.txt, 2023D42PU10.txt, 2023D42PU1p5.txt, 2023D42PU2.txt, 2023D42PU200.txt, etc. and where log files will be put 
## Step 3: The sample text files contain .root files /store/relval/CMSSW_10_6_0_patch2/RelValNuGun/GEN-SIM-RECO/PU25ns_106X_upgrade2023_realistic_v3_2023D42PU200-v1/10000/B843994D-03DC-9F43-9E2C-E8D04B11F320.root
##         /store/relval/CMSSW_10_6_0_patch2/RelValNuGun/GEN-SIM-RECO/PU25ns_106X_upgrade2023_realistic_v3_2023D42PU200-v1/10000/9B6F5078-6F58-FE47-AB32-D6A24D6613D3.root
##         /store/relval/CMSSW_10_6_0_patch2/RelValNuGun/GEN-SIM-RECO/PU25ns_106X_upgrade2023_realistic_v3_2023D42PU200-v1/10000/9E425928-AEA2-664F-A904-A4EF670B3740.root
##         /store/relval/CMSSW_10_6_0_patch2/RelValNuGun/GEN-SIM-RECO/PU25ns_106X_upgrade2023_realistic_v3_2023D42PU200-v1/10000/209E5015-A5A9-EA4A-A86E-995CCFE22689.root
##         /store/relval/CMSSW_10_6_0_patch2/RelValNuGun/GEN-SIM-RECO/PU25ns_106X_upgrade2023_realistic_v3_2023D42PU200-v1/10000/95A7E5A6-3D38-D148-8385-ECE34384D67F.root corresponding to each pileup value.
## Step 4: Copy the sample text files in submission directory where each sample text file will be one job 
## Step 5: Create the job execution files (.sh, .sub) using > source BRIL-upgrade/scripts/lxbatch.sh samples_17Feb2020 0

## Step 6: submit the jobs using > source BRIL-upgrade/scripts/lxbatch-new.sh samples_17Feb2020 1

## Step 7: Modify the output directory (outputdir) path before running the code

submitdir=$1
if [ "$submitdir" == "" ]; then
    echo "invalid submitdir"
    return
fi

## what to do : 0=create scripts, 1=submit, 2=check
action=$2

## where the results will be stored, this directory will be created below
outputdir=/eos/user/a/asehrawa/TEPX/$submitdir

#outputdir=/eos/user/a/asehrawa/TEPX_TkOnly/$submitdir
echo "output: $outputdir"

## set number of jobs to process
NROOTFILESPERJOB=10
NJOBSPERPOINT=20

#outputdir=/eos/user/b/benitezj/BRIL/UpgradeStudies/$submitdir
#echo "output: $outputdir"

## set number of jobs to process
#NROOTFILESPERJOB=2
#NJOBSPERPOINT=2

## get the absolute path
INSTALLATION=${CMSSW_BASE}/src

cfg=$INSTALLATION/BRIL-upgrade/Ashish2xCoincidences_cfg.py

#cfg=$INSTALLATION/BRIL-upgrade/ITclusterAnalyzer_cfg.py

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

    JOB=`echo $f | awk -F".txt" '{print $1}'`

    filecounter=0
    filelist=""
    counter2=0
    for r in `/bin/cat $fullsubmitdir/${JOB}.txt | grep .root`; do
	filelist=root://cms-xrd-global.cern.ch/$r,$filelist
	filecounter=$(($filecounter+1))

	if  [ "${filecounter}" == "${NROOTFILESPERJOB}" ] && [ $counter2 -lt $NJOBSPERPOINT ]  ; then

	        #echo $filelist
	        job=${JOB}_${counter2}
		    #echo $job
		    
		    ## create the scripts
		    if [ "$action" == "0" ]; then
			rm -f $fullsubmitdir/${job}.sh
			rm -f $fullsubmitdir/${job}.sub
			
			## create the CMSSW job
			echo "export X509_USER_PROXY=${HOME}/x509up_u55361 " >> $fullsubmitdir/${job}.sh
			echo "cd ${INSTALLATION} " >> $fullsubmitdir/${job}.sh
			echo "eval \`scramv1 runtime -sh\` " >> $fullsubmitdir/${job}.sh
			echo "pwd"   >> $fullsubmitdir/${job}.sh                                                                            
			echo "export INPUT=${filelist::-1}" >>  $fullsubmitdir/${job}.sh
			echo "export OUTPUT=$outputdir/${job}.root" >>  $fullsubmitdir/${job}.sh
			echo "env" >> $fullsubmitdir/${job}.sh
			echo "cmsRun  ${fullsubmitdir}/cfg.py" >>  $fullsubmitdir/${job}.sh
			
			## create condor jdl
			echo "Universe   = vanilla" >>  $fullsubmitdir/${job}.sub
			echo "+JobFlavour = \"workday\" " >> $fullsubmitdir/${job}.sub
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
			    
			    
			    ## check successful completion of job
			    if [ "$action" == "2" ]; then
				var=`$(cat ${fullsubmitdir}/${job}.log | grep "IT cluster Analyzer processed")`
				
				if [ -z "$var" ]
				    then
				        echo "${job} is not successfully completed"
					else
				        echo "${job} is successfully completed $var"
					fi
				    fi			        
			        
			        filecounter=0
				    filelist=""
				        counter2=$(($counter2+1))

					    counter=$(($counter+1))
					    fi

	    #echo $filelist
	    job=${JOB}_${counter2}
	    #echo $job
	    
	    ## create the scripts
	    if [ "$action" == "0" ]; then
		rm -f $fullsubmitdir/${job}.sh
		rm -f $fullsubmitdir/${job}.sub
		
		## create the CMSSW job
		echo "export X509_USER_PROXY=${HOME}/x509up_u55361 " >> $fullsubmitdir/${job}.sh
		echo "cd ${INSTALLATION} " >> $fullsubmitdir/${job}.sh
		echo "eval \`scramv1 runtime -sh\` " >> $fullsubmitdir/${job}.sh
		echo "pwd"   >> $fullsubmitdir/${job}.sh                                                                                     
		echo "export INPUT=${filelist::-1}" >>  $fullsubmitdir/${job}.sh
		echo "export OUTPUT=$outputdir/${job}.root" >>  $fullsubmitdir/${job}.sh
		echo "env" >> $fullsubmitdir/${job}.sh
		echo "cmsRun  ${fullsubmitdir}/cfg.py" >>  $fullsubmitdir/${job}.sh
		
		## create condor jdl
		echo "Universe   = vanilla" >>  $fullsubmitdir/${job}.sub
		echo "+JobFlavour = \"tomorrow\" " >> $fullsubmitdir/${job}.sub
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
	    
	    
	    ## check successful completion of job
	    if [ "$action" == "2" ]; then
		var=`$(cat ${fullsubmitdir}/${job}.log | grep "IT cluster Analyzer processed")`
		
		if [ -z "$var" ]
		then
		    echo "${job} is not successfully completed"
		else
		    echo "${job} is successfully completed $var"
		fi
	    fi
	    
	    
	    filecounter=0
	    filelist=""
	    counter2=$(($counter2+1))

	    counter=$(($counter+1))

	fi

	
    done


    ##merge the output
    if [ "$action" == "3" ]; then

##	`hadd $outputdir/${JOB}.root $outputdir/${JOB}_*.root`
##	haddcommand="hadd ${outputdir}/${JOB}.root ${outputdir}/${JOB}_*.root"
##	echo $haddcommand  
##	rm -f $outputdir/${JOB}.root

rm -f $outputdir/${JOB}.root
hadd ${outputdir}/${JOB}.root ${outputdir}/${JOB}_*.root


  fi

done
echo "Total jobs: $counter"

	`hadd $outputdir/${JOB}.root $outputdir/${JOB}_*.root`
    fi

done
echo "Total jobs: $counter"

    



