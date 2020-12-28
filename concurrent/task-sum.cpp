/**
 * sum of numbers using tasks
**/

#include <iostream>
#include <chrono>
#include <future>
#include <vector>
#include <atomic>

using namespace std;

constexpr auto maxValue = 10000000;
constexpr int THREADS_COUNT = 10;
  
atomic<int64_t> concurrentSum{0};

void doSum(int64_t start, int64_t end) {
  int64_t sum = 0;
  for(auto i=start; i<=end; i++) {
    sum += i;
  }

  concurrentSum += sum;
}


int main(int argc, char **argv)
{
  cout << "len, sum, time(milli seconds)\n";
  vector<future<void>> taskPool(THREADS_COUNT);
  auto begin_time = chrono::steady_clock::now();
  for(int i=0; i<THREADS_COUNT; i++) {
    taskPool[i] = async(&doSum, (i*maxValue/THREADS_COUNT)+1, ((i+1)*maxValue/THREADS_COUNT));
  }

  for(auto &th: taskPool) {
    th.get();
  }

  auto end_time =chrono::steady_clock::now();
  
  double elapsed_ms = 
  chrono::duration_cast<chrono::milliseconds>(end_time - begin_time).count();

  cout << maxValue << ", " << concurrentSum
       << ", " << elapsed_ms << endl;

  return 0;
}

