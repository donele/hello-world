#ifndef __job_chain_h__
#define __job_chain_h__
#include<string>

bool process_jobs_map(const std::string& filename, bool verbose=false);
bool process_jobs_unordered_map(const std::string& filename, bool verbose=false);
bool process_jobs_vector(const std::string& filename, bool verbose=false);

#endif
