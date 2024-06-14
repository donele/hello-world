#include <job_chain.h>
#include <iostream>
using namespace std;

int main() {
    cout << "Using map..." << endl;
	process_jobs_map(true);
    cout << "Using vector..." << endl;
	process_jobs_vector(true);
	return 0;
}
