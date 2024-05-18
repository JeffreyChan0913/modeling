#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <future>
#include <iomanip>

using namespace std;

struct Point{
    Point(const long double &x, const long double &y) : x2_(x*x), y2_(y*y) { }
    long double x2_, y2_;
};

uint32_t calculation(const Point &p){
    return p.x2_ + p.y2_ <= 1;
}

long double MonteCarlo(const uint32_t & thread_number, promise<long double> &&prom){
    const uint64_t numberOfIterations = 1e10;
    const long double lower_bound = 0.0;
    const long double upper_bound = 1.0;

    std::default_random_engine g(thread_number);
    std::uniform_real_distribution<long double> distribution(lower_bound, upper_bound);

    long double count = 0.0;
    for(uint64_t currentIteration = 0; currentIteration < numberOfIterations; ++currentIteration)
        count += calculation(Point(distribution(g), distribution(g)));

    long double tempResult = 4.0*count/numberOfIterations;
    prom.set_value(tempResult);
    cout << "Thread [" << thread_number << "] solution: " << setprecision(20) << tempResult << "\n";
    return tempResult;

}

int main(int argc, char *argv[]){
    vector<thread> threads;
    vector<future<long double>> futures;
    const uint32_t numberOfThreads = atoi(argv[1]);

    for(uint32_t thread = 1; thread <= numberOfThreads; ++thread){
        promise<long double> prom;
        futures.push_back(prom.get_future());
        threads.emplace_back(MonteCarlo, thread, std::move(prom));
    }

    long double PI = 0.0;
    for(auto &f : futures) PI += f.get();
    cout << "Esimated PI: " << setprecision(20) << PI / (1.0*numberOfThreads) << "\n";
}
