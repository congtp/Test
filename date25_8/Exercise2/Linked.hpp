#ifndef __LINKED_HPP_
#define __LINKED_HPP_

#include <iostream>

struct Intlist{
  struct Node{
    int data;
    Node *next;
  };
  Node *head;
  Node *tail;
  int size;
  Intlist() : head{nullptr}, tail{nullptr}, size{0} {}
  void Insert(int data, size_t index);
  void Show();
  void Push_Front(int data);
  void Push_Back(int data);
  void Pop_Front();
  void Pop_Back();
  void Erase(size_t index);
  void Clear();
};

#endif