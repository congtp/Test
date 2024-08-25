#include "Linked.hpp"

int main(){
  Intlist list;
  list.Push_Front(3);
  list.Push_Back(5);
  list.Show();

  list.Clear();

  std::cout << std::endl;
  std::cout << list.head << std::endl;
  std::cout << list.tail << std::endl;


  list.Show();


  return 0;
}