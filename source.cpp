#include <random>
#include <iostream>

int main(){
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::normal_distribution<float> dist(0.0f,0.1f);
	for(int i=0;i<100;i++)
		std::cout<<dist(mt)<<std::endl;
}
