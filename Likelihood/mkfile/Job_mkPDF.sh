# #!/bin/sh
# cd $HOME/private/ML/Likelihood

# for((i=0; $i<5000; i++))
# {
# bsub -q s -o"/dev/null" root -q -b "mkrootfile_pdf.C($i)"
# }

######################################################
#    chmod +x Job_mkPDF.sh
#    ./Job_mkPDF.sh
#    スクリプトに実行権限を与えてから直接実行
#######################################################


#!/bin/sh
cd $HOME/work/ML/Likelihood/mkfile
# Function to run mkrootfile_test.C with specified parameters
run_mkrootfile_pdf() {
    local tof_option=$1
    local energy_option=$2

    echo "Running mkrootfile_test for TOF $tof_option, Energy $energy_option..."

    # for ((i=0; i<5000; i++)); do
    #     root -q -b -l "mkrootfile_test.C($tof_option, $energy_option, $i)"
    # done
    for((i=0; $i<50; i++))
    {
    bsub -q s -o"/dev/null" root -q -b "mkrootfile_pdf.C($tof_option, $energy_option, $i)"
    }

    #bjobs -w の出力から "PEND" または "RUN" という文字列を含む行を検索し,
    #その結果が0である間, 60秒待機して再度検索する
    bjobs -w | grep -q "PEND\|RUN"
    while [ $? -eq 0 ]
    do
        echo "Waiting for all jobs to finish..."
        sleep 30
        bjobs -w | grep -q "PEND\|RUN"
    done

    cd /home/had/kohki/work/ML/Likelihood/buf
    # ファイルに書き込み権限を与える
    hadd -j 6 pdf_tof${tof_option}ene${energy_option}.root pdf_tof${tof_option}ene${energy_option}_run*.root
    #6つのスレッドで処理が並列実行される

    if [ $? -eq 0 ]; then
        echo "Merging successful for TOF $tof_option, Energy $energy_option. Deleting individual files..."
        rm -rf pdf_tof${tof_option}ene${energy_option}_run*.root
    else
        echo "Error occurred during merging for TOF $tof_option, Energy $energy_option. Individual files were not deleted. Exiting..."
        exit 1
    fi

    echo "Finished processing TOF $tof_option, Energy $energy_option!"
    cd $HOME/work/ML/Likelihood/mkfile
}

# Run for different combinations
#run_mkrootfile_pdf 0 0
#run_mkrootfile_pdf 0 1
#run_mkrootfile_pdf 0 10
#run_mkrootfile_pdf 0 30
#run_mkrootfile_pdf 10 0
#run_mkrootfile_pdf 10 1
run_mkrootfile_pdf 10 10
run_mkrootfile_pdf 10 30
#run_mkrootfile_pdf 100 0
#run_mkrootfile_pdf 100 1
run_mkrootfile_pdf 100 10
run_mkrootfile_pdf 100 30
#run_mkrootfile_pdf 500 0
#run_mkrootfile_pdf 500 1
run_mkrootfile_pdf 500 10
run_mkrootfile_pdf 500 30
