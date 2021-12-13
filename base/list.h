#ifndef _LIST_H
#define _LIST_H

#include "eq_exception.h"

#include <vector>


template <class T>
struct TNode
{
  T key;
  TNode *pNext;
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

  ~TList()
  {
    TNode<T>* pCurrent = pFirst;
    while(pCurrent != nullptr) {
      pCurrent = pCurrent->pNext;
      delete [] pFirst;
      pFirst = pCurrent;
    }
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
};

#endif
