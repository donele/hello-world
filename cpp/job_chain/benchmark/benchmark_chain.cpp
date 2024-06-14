#include <string>
#include <benchmark/benchmark.h>
#include <job_chain.h>
using namespace std;

const string file1 = "input_few.txt";

static void bm_job_chain_map_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map(file1);
    }
}
BENCHMARK(bm_job_chain_map_few);

static void bm_job_chain_unordered_map_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map(file1);
    }
}
BENCHMARK(bm_job_chain_unordered_map_few);

static void bm_job_chain_vector_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_vector(file1);
    }
}
BENCHMARK(bm_job_chain_vector_few);

const string file2 = "input_many.txt";

static void bm_job_chain_map_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map(file2);
    }
}
BENCHMARK(bm_job_chain_map_many);

static void bm_job_chain_unordered_map_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map(file2);
    }
}
BENCHMARK(bm_job_chain_unordered_map_many);

static void bm_job_chain_vector_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_vector(file2);
    }
}
BENCHMARK(bm_job_chain_vector_many);

BENCHMARK_MAIN();
