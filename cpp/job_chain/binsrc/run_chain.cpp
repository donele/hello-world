#include <job_chain.h>
#include <iostream>
using namespace std;

int main() {
    cout << "Few chains" << endl;
    cout << "Using unordered map..." << endl;
	process_jobs_unordered_map("input_few.txt", true);
    cout << "Using map..." << endl;
	process_jobs_map("input_few.txt", true);
    cout << "Using vector..." << endl;
	process_jobs_vector("input_few.txt", true);
	return 0;
}
