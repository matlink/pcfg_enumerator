#include <iostream>
#include <string>
#include "pcfg.hpp"

int main(int argc, char* argv[]){
	if(argc < 2){
		std::cout << "Usage: " << argv[0] << " learnfile [threshold [max attempts]]" << std::endl;
		return EXIT_SUCCESS;
	}
	double pthresh = 0;
	if (argc >= 4){
		pthresh = std::stod(argv[3]);
	}
	int max_att = 0;
	if (argc >= 5){
		max_att = std::stod(argv[4]);
	}
	std::string learnfile = argv[1];
	if(! std::ifstream(learnfile)){
		std::cerr << learnfile << " does not exist!" << std::endl;
		return EXIT_FAILURE;
	}
	Pcfg pcfg = Pcfg();
	pcfg.learn(learnfile);
	pcfg.enumerate(pthresh, max_att);
}