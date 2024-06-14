#include <job_chain.h>
#include <iostream>
using namespace std;

int main() {
    const string filename = "input_few.txt";
    cout << "Few chains" << endl;

    cout << "Using vector..." << endl;
	process_jobs_vector(filename, true);

    cout << "Using map..." << endl;
	process_jobs_map(filename, true);

    cout << "Using unordered map..." << endl;
	process_jobs_unordered_map(filename, true);

    cout << "Using unordered map::extract..." << endl;
	process_jobs_unordered_map_extract(filename, true);

	return 0;
}
