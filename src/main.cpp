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
		max_att = std::stoi(argv[4]);
	}
	std::string learnfile = argv[1];
	std::string targetfile = argv[2];
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