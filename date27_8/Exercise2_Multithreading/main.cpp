#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <queue>
#include <fstream>
/*
  - main_thread() that throw the object
  - queue_manage() that will manage the queues
    - if have data in queue
      - create a thread queue_handler
      - if queue_handler >= 3, wait for it < 3
    

*/
#define MAX_CENCORS 10
#define MAX_CENCOR_VALUE  10


int cencorCount = 1;
struct Cencor{
  std::string cencorName;
  int cencorValue;
  
  Cencor(std::string name = "", int cencorValue = 0):cencorName{name}, cencorValue{cencorValue}{

  }
  ~Cencor() {  }
};



bool stop = false;
std::mutex m;
std::condition_variable cv;
std::queue<Cencor> que;


void InitCencor(std::vector<Cencor> &cencors);

void main_thread();
void queue_manage();
void queue_handler();

int main()
{
  std::thread main_th(main_thread);
  std::thread queue_man(queue_manage);

  main_th.join();
  {
      std::unique_lock<std::mutex> lk(m);
      stop = true;
  }
  cv.notify_all();  // Notify all waiting threads to exit
  queue_man.join();
  return 0;
}



void InitCencor(std::vector<Cencor> &cencors){
  for (int i = 0; i < MAX_CENCORS;i++){
    int temp = rand() % MAX_CENCOR_VALUE + 1;
    std::string cencorName = "cencor_monitor" + std::to_string(cencorCount);
    cencors.push_back(Cencor(cencorName, temp));
    cencorCount++;
  }
}

void main_thread(){
  std::vector<Cencor> cencors;
  InitCencor(cencors);
  int local_count = 0;
  while (local_count < 100){
    std::unique_lock<std::mutex> lk(m); // take the key
    // push the message to the queue
    int temp = rand() % 10;
    que.push(cencors[temp]);
    local_count++;
    lk.unlock();
    cv.notify_one();

    if(local_count % 10 == 0){
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
}

void queue_manage(){
  
  std::vector<std::thread> threadHandlers;
  int threadHandlerCount = 0;
  while (true)
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{ return !que.empty() || stop; });
    if(!que.empty() && threadHandlerCount < 3){
      // create new thread
      threadHandlers.emplace_back(std::thread(queue_handler));
      // increase thread count
      threadHandlerCount++;
    }
    lk.unlock(); 
    for (auto it = threadHandlers.begin(); it != threadHandlers.end();){
      if(it->joinable()){
        it->join();
        threadHandlerCount--;
        it = threadHandlers.erase(it);  // return the next it
      }else{
        it++; 
      }
    }
    if (stop && que.empty()) {
        break;
    }
  }
}

void queue_handler(){
  Cencor temp;
  {
      std::unique_lock<std::mutex> lk(m); // Lock the queue while accessing it
      if (!que.empty()) {
          temp = que.front();
          que.pop();
          std::ofstream file(temp.cencorName + ".log", std::ios::app);
          if (file.is_open()) {
              file << temp.cencorValue << " ";
              file.close();
          } else {
              std::cerr << "Unable to open file: " << temp.cencorName << ".log\n";
          }
      }

  }
}