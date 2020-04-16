/*myvector.h*/

// 
// Syed Hassan
// 
// myVector class that mimics std::vector, but with my own
// implemenation outlined as follows:
//
//

#pragma once
#include <iostream>  // print debugging
#include <cstdlib>   // malloc, free

using namespace std;
template<typename T>

// class myvector:
// This is an implementation of a data structure that is a two way linked-list. 
// It utilizes a NODE struct that holds Data of type T and NODE pointers that point
// to the Next and Prev NODE. It also holds a Head pointer, a Tail pointer, and an int Size.
// The addition to this data structure to improve runtime in accessing elements is the lastNode and lastIndex.
// These two variables will use memoization to remember the last accessed values to make the process of accessing the next element faster.
class myvector
{
private:
  struct NODE
  {
    T            Data;
    struct NODE* Next;
    struct NODE* Prev;
  };

  struct NODE* Head;  // first node in list (or nullptr)
  struct NODE* Tail;  // last node in list (or nullptr)
  int    Size;        // # of elements (i.e. nodes) in list
  
  struct NODE* lastNode;
  int          lastIndex;

public:
  // default constructor:
  // This function sets the default values and pointers to nullptr when 
  // there is an instance created without passing any parameters.
  myvector()
  {
     Head = nullptr;
     Tail = nullptr;
     Size = 0;
     
     lastNode = nullptr;
     lastIndex = -1;
  }

  // constructor with initial size:
  // This function sets the size that is passed in via a single int parameter
  // and initializes Head and Tail pointers to nullptr. The additional feature to this function
  // in order to improve runtime in other fucntions, it uses memoization by initializing the lastNode and lastIndex. 
  myvector(int initial_size)
  {
     Head = nullptr;
     Tail = nullptr;
     
     lastNode = nullptr;
     lastIndex = -1;;
     Size = 0;
     
     for (int i = 0; i < initial_size; ++i){
       push_back(0);
     }
  }

  // copy constructor for parameter passing:
  // This function allows for the elements of the "other" vector passed in via parameters
  // to be copied over into the new vector that it is being set to by traversing the list
  // and storing it into the current vector. 
  myvector(const myvector& other)
  {   
     Head = nullptr;
     Tail = nullptr;
     NODE* tmp = other.Head;
     
     lastNode = nullptr;
     lastIndex = -1;;
     Size = 0;
     
     while(tmp != nullptr){
       push_back(tmp->Data);
       tmp = tmp->Next;
     }
  }
  
  // size() function allows access to the private member Size 
  // and returns an int value associated with the vector.
  int size()
  {
    return Size;
  }

  // T& at(int i) allows access to the vector at position i
  // by returning the address of the element. We are able to access/modify the vector.
  // This function sets and uses the lastNode acessed and lastIndex to improve runtime 
  // for elements accessed in the future by checking if they are next in the vector.
  // There are 3 conditions that it checks for: if the position is the first one, 
  // if the position is the next one from the last one accessed, and if the position is in the middle.
  T& at(int i)
  {
    if (i == 0){
        lastNode = Head;
        lastIndex = 0;
        return Head->Data;
    }
    else if (i == lastIndex + 1){
        lastNode = lastNode->Next;
        lastIndex = lastIndex + 1;
        return lastNode->Data;
    }
    else{
        int index = -1;
        struct NODE* tmp = Head;
        while(tmp != nullptr){
            index++;
            if (i == index){
                return tmp->Data;
            }
            tmp = tmp->Next;
        }
    }
  }

  // push_back(T value) allows the vector to be filled by a T value passed through the parameter.
  // It goes through the end of the list, and adds value to the tail allowing constant runtime. 
  void push_back(T value)
  {
    struct NODE* newNode = new struct NODE();
    newNode->Data = value;
    newNode->Next = nullptr;
    newNode->Prev = nullptr;
    
    if (Head == nullptr){
       Head = newNode;
       Tail = newNode;
    }
    else{
       Tail->Next = newNode;
       newNode->Prev = Tail;
       Tail = newNode;
    }
    Size++;
  }

// This is an additional function that will go through the vector and output all of its Data values.
void output()
  {
    cout << "Size: " << Size << endl;
    cout << "Elements: ";
    
    NODE* curr = Head;
    while( curr != nullptr){
      cout << curr->Data << " ";  
      curr = curr->Next;
    }
    cout << endl;
  }

  // T erase(int i) takes an int parameter that represents the position of the element in the vector to be removed.
  // It then decrements the size assuming that the value passed in is i >= 0 and i <= Size.
  // The function checks for 4 conditions: If the element to be removed is the only one,
  // if the lement is the first one in the list of more than one, if the element is the last one in a list of more than one,
  // and if the element is in the middle of the list. It then deletes and returns the data accordingly.
  T erase(int i)
  {
    T data;
    Size--;
    if (Head->Next == nullptr && i == 0){
     data = Head->Data;
     Head = nullptr;
     Tail = nullptr;
     return data;
    }
    else if (i == 0){
      lastNode = Head;
      lastIndex = 0;
      data = Head->Data;
      Head = Head->Next;
      Head->Prev = nullptr;
      return data;
    }
    else if (i == Size){
      data = Tail->Data;
      Tail = Tail->Prev;
      Tail->Next = nullptr;
      return data;
    }
    else{
          int index = -1;
          NODE* tmp = Head;
          while (tmp != nullptr){
           index++;
           if (i == index){
              NODE* curr = tmp->Prev;
              NODE* curr2 = tmp->Next;
              data = tmp->Data;
              
              curr->Next = tmp->Next;
              curr2->Prev = curr;
              tmp = nullptr;
              
              return data;
           }
           tmp = tmp->Next;
          }
       }
  }
  
  // T& operator[](int i) allows usage of [] for the vector if the position passed in is greater than 0 and less than Size.
  // It allows the ability to access and modify the element at the given position and uses a reference to the address of the element to be returned.
  T& operator[](int i)
  {
     if ( i < 0 || Size <= i)
          throw out_of_range{"Vector::operator[]"};
     return at(i);
     
  }

  // T* rangeof(int i, int j) allocates a dynamic array by first determining its size.
  // Then it inclusively fills the array with all elements between i and j.
  // This array is then returned.
  T* rangeof(int i, int j)
  {
     int size = j-i;
     T* p = new T[(j-i)+1];
     
     for (int x = 0; x <= size; x++){
        p[x] = this->at(i);
        i++;
     }
     return p;
  }
};
