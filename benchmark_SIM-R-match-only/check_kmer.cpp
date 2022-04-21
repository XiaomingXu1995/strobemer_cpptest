#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <set>
#include <unordered_set>
#include <math.h>
int main(int argc , char **argv){
    srand(time(NULL));
    char nucs[4] = { 'A','T','G','C'};
    if( argc != 3 ) {
        std::cerr<<"Usage : "<<argv[0]<<" k target.kmer<input.seq" <<std::endl;
        return -1;
    }
    int k = std::atoi(argv[1]);
    std::string kmer_marker = std::string(argv[2]);
    std::unordered_set<std::string> markers;
    //std::set<std::string> markers;
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
    int found=0;
		std::unordered_set<std::string> inputSet;
    for( int i = 0 ; i<input.size()-k+1;i++){
        std::string kmer = input.substr(i,k);
        //if( markers.find(kmer) != markers.end()){
        if( markers.find(kmer) != markers.end() && inputSet.find(kmer) == inputSet.end()){
            found++;
        }
				inputSet.insert(kmer);
    }
		if(found > markers.size())
			found = markers.size();
    //int denom = markers.size() + input.size()-k+1 - found;
    int denom = markers.size() + inputSet.size() - found;
		double matchRate = (double)found / (double)(markers.size());
    double jaccard = (double)found / (double)denom;
    double mashD; 
		if(found == 0)
			mashD = 1.0;
		else
			mashD = -1.0 / (double)k * log(2.0 * jaccard / (1.0 + jaccard));
		
    std::cout << found << '\t' << matchRate << '\t' << jaccard << '\t'<< mashD <<std::endl;
    //std::cout << "the matchRate is: " << matchRate << std::endl;
    //std::cout << "the jaccard is: " << jaccard << std::endl;
    //std::cout << "the mashD is: " << mashD << std::endl;

    return 0;
}
