#ifndef _LIST_H
#define _LIST_H

template <class T> class TNode {
public:
  T key_;
  TNode *pNext_;

private:
  TNode() : key_(0), pNext_(nullptr) {}
  TNode(T _key_, TNode *_pNext_) : key_(_key_), pNext_(_pNext_) {}

  inline T GetKey() const { return key_; }

  inline void Setkey(int _key_) { key_ = _key_; }

  inline void SetNext(TNode *other) { pNext_ = other; }

  inline TNode* GetNext() const { return pNext_; }

};

template <class T> class TList {
private:
  TNode<T> *pfirst;
  TNode<T> *plast;
  TNode<T> *pcurrent;

public:
  TList() : pfirst(nullptr), plast(nullptr), pcurrent(nullptr) {}
};

#endif
