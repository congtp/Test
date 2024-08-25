#include "Linked.hpp"

/*
  This function only support the insert if it < the size of current linked list
  - Example if the size of the current linked list is 1, so we can only insert
  at the index 0;
*/
void Intlist::Insert(int data, size_t index){
  // check if head is nullptr
  if (this->head == nullptr){

      std::cout << "the list is empty" << std::endl;

  }else{
    
    if (index < this->size){
      // travers to the index
      Node *p = this->head;
      for (int i = 0; i < index - 1;i++)
      {
        // go to next node
        p = p->next;
      }
      // create the new node
      Node *temp = (Node *)malloc(sizeof(Node));
      temp->data = data;
      temp->next = nullptr;

      if (index == 0)
      {
        // assign the next of the new node to the head
        temp->next = this->head;
        // assign the head to the new node
        this->head = temp;
        
      }else{
        // we have the node at position index - 1 = q
        // assign the next of new node by the next of q
        temp->next = p->next;
        // assign the next of the next q to new node
        p->next = temp;
      }
      this->size++;
    }else{
      std::cout << "the index is beyond the size of linked list" << std::endl;
    }
  }
}




void Intlist::Show(){
  if(this->head == nullptr){
    std::cout << "the linked is empty" << std::endl;
  }else{
    Node *p = this->head;
    while(p){
      std::cout << p->data << " ";
      p = p->next;
    }
  }
}

void Intlist::Push_Front(int data){
  // Create the new node
  Node *temp = new Node;
  temp->data = data;
  temp->next = nullptr;
  // check if the head is nullptr
  if (head == nullptr){
    this->head = temp;
    this->tail = this->head;
  }else{
    // assign the new->next = head
    temp->next = this->head;
    // assign the head to new
    this->head = temp;
  }
  this->size++;
}

void Intlist::Push_Back(int data){
  // Create a new node
  Node *temp = new Node;
  temp->data = data;
  temp->next = nullptr;
  if (head == nullptr)
  {
    this->head = temp;
    this->tail = temp;
  }else{
    // assign the tail->next to the new
    this->tail->next = temp;
    // assign the tail to the new
    this->tail = temp;
  }
  this->size++;
}

void Intlist::Pop_Front(){
  if (this->head == nullptr){
    std::cout << "the linked is empty" << std::endl;
  }else{
    if(this->head == this->tail){
      delete head;
      this->head = nullptr;
      this->tail = nullptr;
    }
    else
    {
      // create a temp Node to hold the front node
      Node *temp = this->head;
      // assign head to the next node
      this->head = this->head->next;
      // free the front node
      delete temp;
      
    }
    this->size--;
  }
}
void Intlist::Pop_Back(){
  if (this->head == nullptr){
    std::cout << "the linked is empty" << std::endl;
  }else{
    if(this->head == this->tail){
      delete head;
      this->head = nullptr;
      this->tail = nullptr;
    }
    else
    {
      // traverse to the prev last node
      Node *p = this->head;
      for (int i = 0; i < this->size - 2; i++){
        p = p->next;
      }
      // make the prev last node to null
      p->next = nullptr;
      // delete the last node
      delete tail;
      // assign tail to the new value
      tail = p;
    }
    this->size--;
  }
}

void Intlist::Erase(size_t index){
  if(this->head == nullptr){
    std::cout << "the linked list is empty" << std::endl;
  }else{
    if(index == 0){
      this->Pop_Front();
    }else if(index == this->size - 1){
      this->Pop_Back();
    }else if(index < size - 1){
      Node *p = head;
      Node *q = nullptr;

      for (int i = 0; i < index; i++){
        q = p;
        p = p->next;
      }

      // assign the q-next to p->next
      q->next = p->next;
      // assign the p->next to nullptr
      p->next = nullptr;
      // free the p
      delete p;
      this->size--;
    }
    else
    { // index > size -1
      std::cout << "the index beyond the size" << std::endl;
    }
  }

}

void Intlist::Clear(){
  int len = this->size;
  for (int i = 0; i < len; i++)
  {
    this->Pop_Back();
  }
}