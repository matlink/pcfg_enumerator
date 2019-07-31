#include <iostream>
#include <string>
#include "pcfg.hpp"

int main(int argc, char* argv[]){
	if(argc < 2){
		std::cout << "Usage: " << argv[0] << " learnfile" << std::endl;
		return EXIT_SUCCESS;
	}
	std::string learnfile = argv[1];
	Pcfg pcfg = Pcfg();
	pcfg.learn(learnfile);
	pcfg.dump("rockyou.bin");
	// pcfg.load("rockyou.bin");
}