#include <iostream>
#include <string>
#include "pcfg.hpp"

int main(int argc, char* argv[]){
	if(argc < 3){
		std::cout << "Usage: " << argv[0] << " learnfile targetfile [threshold [max attempts]]" << std::endl;
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
	std::string targetfile = argv[2];
	if(! std::ifstream(targetfile)){
		std::cerr << targetfile << " does not exist!" << std::endl;
		return EXIT_FAILURE;
	}
	Pcfg pcfg = Pcfg();
	bool learn = false;
	learn = true;
	if(learn){
		pcfg.learn(learnfile);
		// pcfg.dump("rockyou.bin");
	}
	else{
		pcfg.load("rockyou.bin");
	}
	pcfg.enumerate(targetfile, pthresh, max_att);
}