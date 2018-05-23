#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>
#include <chrono>
const int N = 50;
const unsigned int c = 0xffffffff;
const int b = 3;
const double PI = 3.1415926535;

int main(){
	std::cout<<"c = "<<c<<std::endl;
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_real_distribution<double> dist(0,1);

	auto start = std::chrono::system_clock::now();

	int z[N] = {0};
#pragma omp parallel
	{
		int private_z[N] = {0};

#pragma omp for
		for(unsigned int i = 0;i < c;i++){
			double z1 = std::sqrt(-2 * std::log( dist(mt) )) * std::cos(2 * PI * dist(mt));
			if( std::abs( z1 * b ) < N/2 ){
				private_z[static_cast<int>(z1 * b) + N/2]++;
			}
		}
#pragma omp critical
		for(int i = 0;i < N;i++){
			z[i] += private_z[i];
		}
	}

	auto end = std::chrono::system_clock::now();

	std::cout<<"elapsed time = "<<std::chrono::duration_cast<std::chrono::seconds>(end-start).count()<<" [s]"<<std::endl;

	for(int i = 0;i < N;i++){
		std::cout<<"["<<std::setw(static_cast<int>(std::log10(c)+1))<<std::setfill(' ')<<z[i]<<"] ";
		for(int j = 0;j < z[i]/(c/100);j++){
			std::cout<<"*";
		}
		std::cout<<std::endl;
	}
}
