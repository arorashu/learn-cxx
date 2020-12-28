/**
 * Program do sum of numbers
**/

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

constexpr auto maxValue = 10000000;

int64_t concurrentSum{0};
mutex sum_mutex;

void doSum(int64_t start, int64_t end) {
  int64_t sum = 0;
  for(auto i=start; i<=end; i++) {
    sum += i;
  }
  sum_mutex.lock();
  concurrentSum += sum;
  sum_mutex.unlock();
}


int main(int argc, char **argv)
{
  constexpr int THREADS_COUNT = 10;
  cout << "len, sum, time(milli seconds)\n";
  vector<thread> threadPool(10);
  auto begin_time = chrono::steady_clock::now();
  for(int i=0; i<THREADS_COUNT; i++) {
    threadPool[i] = thread(&doSum, (i*maxValue/THREADS_COUNT)+1, ((i+1)*maxValue/THREADS_COUNT));
  }

  for(auto &th: threadPool) {
    th.join();
  }

  auto end_time =chrono::steady_clock::now();
  
  double elapsed_ms = 
  chrono::duration_cast<chrono::milliseconds>(end_time - begin_time).count();

  cout << maxValue << ", " << concurrentSum
       << ", " << elapsed_ms << endl;

  return 0;
}

