#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>

int count = 1;
std::mutex m;
std::condition_variable cv;

void printOdd(){
  std::unique_lock<std::mutex> lk(m);
  while(count < 100){
    cv.wait(lk, []{ return (count % 2 != 0) ? true : false; });
    std::cout << "Odd = " << count << std::endl;
    count++;
    cv.notify_one();
  }
}

void printEven(){
  std::unique_lock<std::mutex> lk(m);
  while(count < 100){
    cv.wait(lk, []{ return (count % 2 != 0) ? false : true; });
    std::cout << "Even = " << count << std::endl;
    count++;
    cv.notify_one();
  }
}


int main(){
  std::thread t1(printEven);
  std::thread t2(printOdd);

  t1.join();
  t2.join();
  return 0;
}