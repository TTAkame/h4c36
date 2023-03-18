#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
#include<memory>
#include "json.hpp"
#include "AVL.h"


int main(int argc, char** argv){

	AVL b1;
	std::ifstream source(argv[1]);
	nlohmann::json sdata = nlohmann::json::parse(source);

	for(auto v = sdata.begin(); v != std::prev(sdata.end());++v){
		if(v.value()["operation"]=="Insert"){
			b1.Insert(v.value()["key"]);
		//	std::cout<<b1.JSON();
//std::cout<< v.value()["key"];
		}
	}

	
//	std::cout<<b1.size();
	std::cout<<b1.JSON();



	

	return 0;
}
