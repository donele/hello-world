#include <benchmark/benchmark.h>
#include <job_chain.h>

static void bm_job_chain_map(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map();
    }
}
BENCHMARK(bm_job_chain_map);

static void bm_job_chain_vector(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_vector();
    }
}
BENCHMARK(bm_job_chain_vector);

BENCHMARK_MAIN();
