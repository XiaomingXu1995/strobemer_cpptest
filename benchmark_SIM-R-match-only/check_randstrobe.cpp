#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <set>
#include "../strobemer.h"
#include <math.h>
int main(int argc , char **argv){
    srand(time(NULL));
    char nucs[4] = { 'A','T','G','C'};
    if( argc != 2 ) {
        std::cerr<<"Usage : "<<argv[0]<<" target.kmer<input.seq" <<std::endl;
        return -1;
    }
    std::string kmer_marker = std::string(argv[1]);
    std::set<std::string> markers;
    std::ifstream infs(kmer_marker);
    if(!infs.is_open()){
        std::cerr<<"open file "<<kmer_marker<<" failed"<<'\n';
        return -1;
    }
    std::string kmer;;
    while ( ! infs.eof() ){
        infs>>kmer;
        markers.insert(kmer);
    }
    infs.close();
    std::string input;
    std::getline(std::cin,input);
    strobemer::init(2,15,15,50,strobemer_type::randstrobe);  
    int number = input.size()-strobemer::strobmer_span()+1;
    strobemer * buff = new strobemer[number];
    strobemer::chop_strobemer(input.c_str(),input.size(),buff);
    int found=0;
    for( int i = 0 ; i<number;i++){
        if(buff[i].valid)
            if(markers.find(buff[i].to_string()) != markers.end())
                found++;
    }
    std::cout<<found<<std::endl;
    int denom = markers.size() + number - found;
		double matchRate = (double)found / (double)(markers.size());
    double jaccard = (double)found / (double)denom;
    double mashD = -1.0 / (double)30 * log(2.0 * jaccard / (1.0 + jaccard));
    std::cout << "the matchRate is: " << matchRate << std::endl;
    std::cout << "the jaccard is: " << jaccard << std::endl;
    std::cout << "the mashD is: " << mashD << std::endl;
    delete []buff;
    return 0;
}
