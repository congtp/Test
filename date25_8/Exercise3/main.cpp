#include <iostream>
#include <vector>
#include <fstream>

enum State
{
  IDLE,
  MENU,
  SIGN_UP,
  SIGN_IN,
  IGNORE,
};

void state_dispatch(State *currState);
void IDLE_State_Handler(State *currState);
void MENU_State_Handler(State *currState);
void SIGN_UP_State_Handler(State *currState);
void SIGH_IN_State_Handler(State *currState);
int main(){
  std::ifstream fp("menu.txt");

  if(!fp.is_open()){
    exit(1);
  }

  std::vector<std::string> vec;
  std::string str;
  State currState = IDLE;
  while (getline(fp, str))
  {
    vec.push_back(str);
  }
  fp.close();
  while (1)
  {
    state_dispatch(&currState);
  }

  return 0;
}

void state_dispatch(State *currState){
  switch(*currState){
    case IDLE:
      IDLE_State_Handler(currState);
      break;
    case MENU:
      MENU_State_Handler(currState);
      break;
    case SIGN_UP:
      SIGN_UP_State_Handler(currState);
      break;
    case SIGN_IN:
      SIGH_IN_State_Handler(currState);
      break;
    case IGNORE:
      
      break;
    }
}


void IDLE_State_Handler(State *currState){
  std::ifstream fp1("login.txt");
  if(!fp1.is_open()){
    std::cout << "Failed to open file login" << std::endl;
  }
  std::string temp;
  while(getline(fp1, temp)){
    std::cout << temp << std::endl;
  }
  
  fp1.close();
  char ch;
  do{
    std::cin >> ch;
    if(ch != '1' && ch != '2'){
      std::cout << "Invalid input, Please input again" << std::endl;
    }
  } while (ch != '1' && ch != '2');

  if(ch == '1'){
    *currState = SIGN_UP;
  }else if(ch == '2'){
    *currState = SIGN_IN;
  }else{
    *currState = IGNORE;
  }
}
void MENU_State_Handler(State *currState){

}
void SIGN_UP_State_Handler(State *currState){

}
void SIGH_IN_State_Handler(State *currState){

}