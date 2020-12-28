/**
 * Program do sum of numbers
**/

#include <iostream>
#include <chrono>

constexpr auto maxValue = 10000000;

int64_t doSum(int64_t start, int64_t end) {
  int64_t sum = 0;
  for(auto i=start; i<=end; i++) {
    sum += i;
  }
  return sum;
}

using namespace std;

int main(int argc, char **argv)
{
  int64_t linearSum = 0;
  auto begin_time = chrono::steady_clock::now();
  linearSum = doSum(1, maxValue);
  auto end_time =chrono::steady_clock::now();
  
  double elapsed_ms = 
  chrono::duration_cast<chrono::milliseconds>(end_time - begin_time).count();

  cout << "len, sum, time(milli seconds)\n";
  cout << maxValue << ", " << linearSum
       << ", " << elapsed_ms << endl;

  return 0;
}

