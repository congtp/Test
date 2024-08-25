#include <iostream>
#include <thread>
#include <sys/types.h>

using namespace std;
 
 
void display(char ch) {
    while (1) {
        if (ch == 'A')
        {
          cout << "A has been pressed" << endl;
        }
        else if (ch == 'Q') {
            cout << "Q has been pressed" << endl;
        }
    }
}
 
 
int main() {
  char ch;
  cout << "Enter some Data: ";
  cin >> ch;
  thread t1(display, ch);
  //string data;

  
  t1.join();
}