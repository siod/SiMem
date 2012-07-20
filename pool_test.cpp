#include <iostream>
#include "pool.h"
#include <time.h>
#include <vector>

#define SIZE 1000000
SiLib::SiMem::PoolAllocator pool(SIZE);
using std::vector;
using std::cout;

vector<int*> results;
void test_Ref(int size) {
	for(int i(0);i!= size;++i) {
		int* tmp;
		tmp = new int(i);
		results.push_back(tmp);
	}
}

void test_Alloc(int size) {
	for(int i(0);i!= size;++i) {
		int* tmp;
		tmp = (int*)pool.Allocate();
		new (tmp) int(i);
		results.push_back(tmp);
	}
}

int main(int argc,char** argv) {
	results.reserve(SIZE);
	int size;

	clock_t start = clock();
	test_Ref(SIZE);
	clock_t fin = clock();

	int time_ref = ((fin - start));
	for (int i(0);i!=SIZE;++i)
		if (*(results[i]) !=i) 
			cout << "results not valid : " << i << " != " << results[i] << "\n";
	results.clear();
	cout << "Ref time = " << time_ref << " cycles\n";

	start = clock();
	test_Alloc(SIZE);
	fin = clock();
	int time_custom = ((fin - start));
	for (int i(0);i!=SIZE;++i)
		if (*(results[i]) !=i) 
			cout << "results not valid : " << i << " != " << results[i] << "\n";
	results.clear();
	cout << "Alloc time = " << time_custom << " cycles\n";
	cout << "difference = " <<  time_ref - time_custom << " cycles\n";


	return 0;
}
