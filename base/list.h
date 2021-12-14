#ifndef _LIST_H
#define _LIST_H

#include "eq_exception.h"

#include <vector>


template <class T>
struct TNode
{
  T key = T();
  TNode* pNext = nullptr;
};

template <class T>
class TList;

template <class T>
class TListItertor;

template <class T>
class TListIterator
{
private:
  friend class TList<T>;
  TNode<T>* pptr;
  TNode<T>* ptr;

  TListIterator(TNode<T>* _ptr) : ptr(_ptr), pptr(_ptr)
  {}
public:
  TListIterator(const TListIterator& it) : ptr(it.ptr), pptr(it.pptr)
  {}

  bool operator==(const TListIterator& it) const
  {
    return (ptr == it.ptr);
  }

  bool operator!=(const TListIterator& it) const
  {
    return (ptr != it.ptr);
  }

  T& operator*() const
  {
    return ptr->key;
  }

  TListIterator& operator++()
  {
    pptr = ptr;
    ptr = ptr->pNext;
    return *this;
  }
};

template <class T> 
class TList
{
private:
  int size;
  TNode<T> *pFirst;
  TNode<T> *pLast;

public:
  TList() : size(0), pFirst(nullptr), pLast(nullptr) {}

  using iterator = TListIterator<T>;
  iterator begin() const
  {
    return iterator{pFirst};
  }

  iterator end() const
  {
    return iterator{nullptr};
  }

  TListIterator<T> Insert(iterator iter, const T& val)
  {
    if(iter.ptr == pFirst) {
      AddNode(val);
      return iterator{nullptr};
    }

    TNode<T>* tmp = new TNode<T>();
    tmp->key = val;
    tmp->pNext = iter.ptr;
    iter.pptr->pNext = tmp;
    iter.ptr = tmp;
    return iter;
  }

  void Erase(iterator iter)
  {
    TNode<T>* tmp = pFirst;
    TNode<T>* prev;
    int pos = 0;
    while (tmp != iter.ptr) {
      prev = tmp;
      tmp = tmp -> pNext;
      pos++;
     }
    if (pos == 0) {
      pFirst = pFirst->pNext;
      delete tmp;
      size--;
    }
    else {
      prev->pNext = tmp->pNext;
      delete tmp;
      size--;
    }
  }

  TList(T* arr) : size(0), pFirst(nullptr), pLast(nullptr)
  {
    if(arr == nullptr)
      throw(EqException(EqException::bad_array,"Wrong length of mass"));
    for(int i = 0; i < sizeoff(arr) / sizeoff(arr[0]); i++) {
      AddNode(arr[i]);
    }
  }

  TList(std::vector<T>& v) : size(0), pFirst(nullptr), pLast(nullptr)
  {
    if(v.size() == 0)
      throw(EqException(EqException::bad_array,"Wrong length of vector"));
    for(T tmp: v) {
      AddNode(tmp);
    }
  }

  T& operator[](int index)
  {
    if ((index > size - 1) || (index < 0)) {
      throw(EqException(EqException::out_of_range, "Incorrect index"));
    }
    int n = 0;

    TNode<T>* pCurrent = pFirst;
    while(pCurrent != nullptr) {
      if (index == n) {
        return pCurrent->key;
      }
      pCurrent = pCurrent->pNext;
      n++;
    }
    throw(EqException(EqException::out_of_range, "Incorrect index"));
  }

  inline bool operator==(const TList& other)
  {
    if(size != other.size) {
      return false;
    }

    if(this == &other) {
      return true;
    }

    iterator it1 = this->begin();
    iterator it2 = other.begin();

    for(;it1 != this->end(); ++it1, ++it2) {
      if(it1.ptr->key != it2.ptr->key) {
        return false;
      }
    }
    return true;
  }

  inline bool operator!=(const TList& other)
  {
    return !(*this == other);
  }

  TList(TList && list) noexcept
  {
    size = list.size;
    pFirst = list.pFirst;
    pLast = list.pLast;

    list.pFirst = nullptr;
    list.pLast = nullptr;
    list.size = 0;
  }

  TList& operator=(TList && list) noexcept
  {
    if (this != &list) {
      while (pFirst != nullptr) {
        TNode<T>* tmp = pFirst;
        pFirst = pFirst->pNext;
        delete tmp;
      }

      size = list.size;
      pFirst = list.pFirst;
      pLast = list.pLast;

      list.size = 0;
      list.pFirst = nullptr;
      list.pLast = nullptr;

      //std::swap(pFirst, list.pFirst)
      //std::swap(pLast, list.pLast)
      //std::swap(size, list.size)
    }
    return *this;
  }
  
  TList(const TList& other)
  {
    pFirst = nullptr;
    pLast = nullptr;
    size = 0;

    if(other.pFirst == nullptr) {
      return;
    }

    pFirst = new TNode<T>();
    pFirst->key = other.pFirst->key;
    TNode<T>* pCurrent = pFirst;
    size = 1;

    for(TNode<T>* pTmp = other.pFirst->pNext;
        pTmp != nullptr; pTmp = pTmp->pNext) {
      pCurrent->pNext = new TNode<T>();
      pCurrent = pCurrent->pNext;
      pCurrent->key = pTmp->key;
      size++;
    }
    pCurrent->pNext = nullptr;
    pLast = pCurrent;
  }

  void EraseList()
  {
    TNode<T>* pCurrent = pFirst;
    while(pCurrent != nullptr) {
      pCurrent = pCurrent->pNext;
      delete  pFirst;
      pFirst = pCurrent;
    }
    size = 0;
  }

  ~TList()
  {
    EraseList();
  }

  TList& operator=(const TList& other)
  {
    if(this == &other)
      return *this;

    TList tmp(other);
    std::swap(tmp, *this);
    return *this;
  }

  TNode<T>* AddNode(T item)
  {
    if(pLast == nullptr) {
      TNode<T>* tmp = new TNode<T>();
      pLast = tmp;
      pLast->key = item;
      pFirst = pLast;
    }
    else{
      TNode<T>* tmp = new TNode<T>();
      pLast->pNext = tmp;
      pLast = tmp;
      pLast->key = item;
    }
    pLast->pNext = nullptr;
    size++;
    return pLast;
  }
  
  TNode<T>* GetNode(int index) const
  {
    if((index > size - 1) || (index < 0) )
      throw(EqException(EqException::out_of_range, "Index incorrect"));
    if(index == size - 1) {
      return pLast;
    }
    else if(index == 0) {
      return pFirst;
    }
    else {
      TNode<T>* ptr = pFirst;
      while(index) {
        ptr = ptr->pNext;
        index--;
      }
      return ptr;
    }
  }

  inline int GetSize() const
  {
    return size;
  }

  inline bool IsEmpty() const
  {
    return (size == 0);
  }
};

#endif
