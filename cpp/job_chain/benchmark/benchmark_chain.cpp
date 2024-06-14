#include <string>
#include <benchmark/benchmark.h>
#include <job_chain.h>
using namespace std;

const string file1 = "input_few.txt";

static void map_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map(file1);
    }
}
BENCHMARK(map_few);


static void unordered_map_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map(file1);
    }
}
BENCHMARK(unordered_map_few);


static void unordered_map_extract_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map_extract(file1);
    }
}
BENCHMARK(unordered_map_extract_few);


static void vector_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_vector(file1);
    }
}
BENCHMARK(vector_few);


const string file2 = "input_many.txt";

static void map_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map(file2);
    }
}
BENCHMARK(map_many);


static void unordered_map_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map(file2);
    }
}
BENCHMARK(unordered_map_many);


static void unordered_map_extract_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map_extract(file2);
    }
}
BENCHMARK(unordered_map_extract_many);


static void vector_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_vector(file2);
    }
}
BENCHMARK(vector_many);

BENCHMARK_MAIN();
