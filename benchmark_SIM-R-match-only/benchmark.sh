#!/bin/bash
#make clean
#make

function run_1_round() {
		kmerSize=$1
    err_rate=$2
    ./rmutation100k $err_rate  <ref100k.fa >"ref100k_mu"$err_rate".fa"

    ### test k 30
    ./gen_kmer $kmerSize <ref100k.fa >k$kmerSize.all
    KM=`./check_kmer $kmerSize  k$kmerSize.all <"ref100k_mu"$err_rate".fa"`
    echo "$err_rate $KM"
#    ### test minstrobe (2,15,50)
#    ./gen_minstrobe <ref100k.fa >min.all
#    MM=`./check_minstrobe min.all <"ref100k_mu"$err_rate".fa"`
#    echo "gen_minstrobe_2_15_50 $err_rate $MM"
#		echo
#    ### test randstrobe (2,15,50)
#    ./gen_randstrobe <ref100k.fa >rand.all
#    RM=`./check_randstrobe rand.all <"ref100k_mu"$err_rate".fa"`
#    echo "gen_ranstrobe_2_15_50 $err_rate $RM"
#		echo
}

function run100(){
		kmerSize=$1
    err_rate=$2
    for i in {1..10}
    do
        ./random100k >ref100k.fa
        for j in {1..10}
        do
            run_1_round $kmerSize $err_rate
        done
				echo "finish kmer: $kmerSize, err_rate: $err_rate" >&2 
    done
}

# echo result header
echo "type error match"
path=result
mkdir -p $path
for k in {7..30}
do
	# test error rate 1/100
	run100 $k 10 >$path/"res_k"$k"_m.01"
	# test error rate 5/100
	run100 $k 50 >$path/"res_k"$k"_m.05"
	# test error rate 10/100
	run100 $k 100 >$path/"res_k"$k"_m.10"
	run100 $k 250 >$path/"res_k"$k"_m.25"
	run100 $k 300 >$path/"res_k"$k"_m.30"
	run100 $k 500 >$path/"res_k"$k"_m.50"
done

#run100 500
#run100 700
