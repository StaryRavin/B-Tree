#ifndef _BTREE_H_
#define _BTREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <new>
#include <assert.h>
#include "BTree.h"
#include <iostream>
using namespace std;

using namespace std;

template<class T, class U>
class Elem
{
    T key_;
    U val_;
public:
    Elem():key_(NULL),val_(NULL){};
    Elem(const Elem<T, U> &c){T key_(c.key_); U val_(c.val_);};
    ~Elem(){delete key; delete val_;};
    bool operator>(const U &c){return key_ > c.key_;};
    bool operator<(const U &c){return key_ < c.key_;};
    bool operator<=(const U &c){return key_ <= c.key_;};
    bool operator>=(const U &c){return key_ >= c.key_;};
    bool operator==(const U &c){return key_ == c.key_;};
    bool operator!=(const U &c){return key_ != c.key_;};
    friend std::ostream& operator<< (ostream &, Elem<T, U> &);
};

template <class T, class U, size_t t>
class Node
{
    bool leaf_;
    size_t n;
    Elem<T,U> *elem_;
    Node<T,U,t> *child_[2*t];
public:
    Node(){n=0; leaf_=false; child_[0]=NULL; Elem<T,U> *elem_=new Elem<T,U>[2*t-1];}
    Node(const Node<T,U,t> &c);
    void just_insert(Elem<T, U> &key);
    void split_child(int i, Node<T, U, t> *y);
    void traverse();
    void remove(Elem<T, U> &key>);
    void borrow_from_next(size_t index);
    void borrow_from_prev(size_t index);
    void remove_from_leaf(size_t index);
    void remove_from_non_leaf(size_t index);
    void get_prev(size_t index);
    void get_succ(size_t index);
    void sort();
    void clear();
};

template <class T, class U, size_t t>
class BTree
{
    Node<T,U,t> *root;
public:
    Tree():root(NULL){};
    Elem<T, U>* Find(const T &c);
    Node<T, U, t> Parent(Node<T, U, t> &child);
    size_t * i(Node<T, U, t> &child);
    bool empty();
    void clear();
    ~BTree();
    void insert(Elem<T, U, t> &key);
    void remove(Elem<T, U, t> &key);
    void traverse();
    void sort();
};

template <class T, class U, size_t t>
class Iterator
{
  Node<T, U, t> *cur;
  U *val_;
  T *key_;
public:
  Iterator() {cur = NULL; val_ = 0; key_ = 0;};
  Iterator(Iterator &it) {cur = it.cur; val_ = it.val_; key_ = it.key;};
  Iterator & operator++(int);
  Iterator & operator--(int);
  Iterator &BTree<T, U, t> go_to_min();
  Iterator &BTree<, U, t> go_to_max();
};

//ПОИСК

template <class T, class U, size_t t>
Elem<T, U> &BTree<T, U, t>::Find_key(U &key)
{
    Node<T, U, t>  *curnode_ = root_;
    size_t i = 0;
    while (!curnode_.leaf_)
    {
        while (curnode_->elem_[i].key_ <= key)
        {
            if (curnode_->elem_[i].key_ == key)
                return curnode_->elem_[i];
            i++;
        }
        curnode_ = curnode_->child[i];
    }
    for (size_t i = 0; i < curnode_.n; i++)
    {
        if (key == curnode_->elem_[i].val_)
            return curnode_->elem[i];
    }
    throw 0;
}

template <class T, class U, size_t t>
Node<T, U, t> &Bree<T, U, t>::Parent(Node<T, U, t> &child)
{
    Node<T, U, t> *parent?, curnode_ = root_;
    U count = child->elem_[0];
    if (root_->elem_[0] ==  child->elem[0])
        return NULL;
    size_t i = 0;
    while (!curnode_.leaf_)
    {
        while (curnode_->elem_[i].key_ <= key)
        {
            if (curnode_->elem_[i].key_ == key)
                return parent?
            i++;
        }
        parent? = curnode_
        curnode_ = curnode_->child[i];
    }
    return parent?;
}

template <class T, class U, size_t t>
size_t &Bree<T, U, t>::i(Node<T, U, t> &child)
{
    Node<T, U, t> curnode_ = root_;
    size_t need;
    U count = child->elem_[0];
    size_t i = 0;
    while (!curnode_.leaf_)
    {
        while (curnode_->elem_[i].key_ <= key)
        {
            if (curnode_->elem_[i].key_ == key)
                return need;
            i++;
        }
        curnode_ = curnode_->child[i];
        need = i;
    }
    return need;
}

//ВСТАВКА

/*template <class U, class T, size_t t>
void &BTree<U, T, t>::split_into_parent(Elem<U, T> &tosplit)
{
    Node<T, U, t>  *curnode_, *parent;
    curnode_ = root_;
    while (!curnode_.leaf_)
    {
        while (curnode_->elem_[i].key_ < key)
            i++;
        parent = curnode;
        curnode_ = curnode_->child[i];
    }
    Elem<T, U> *key = curnode_->elem_[t];
    if (parent.n_ < 2 * t - 1)
        return split_if_necessary(curnode);
    else
    {
	split_into_parent(
    }
}*/


template <class T, class U, size_t t>
void &BTree<T, U, t>::insert(T key; U val;)
{
    Elem<T, U> = *elem;
    elem.key_ = key;
    elem.val_ = val;
    if (root == NULL)
    {
        root_ = new Node<T, U, t>;
        root_->elem_[0] = elem;
        root_->n = 1;
    }
    else
    {
        if (root->n == 2*t-1)
        {
            Node<T, U, t> *s = new Node<T, U, t>;
            s->child_[0] = root_;
            s->splitChild(0, root_);
            int i = 0;
            if (s->elem_[0] < elem)
                i++;
            s->child_[i]->just_insert(elem);
            root_ = s;
        }
        else
            root_->just_insert(elem);
    }
}

template <class T, class U, size_t t>
void &Node<T, U, t>::just_insert(Elem<T, U> &key)
{
    int i = n - 1;
    if (leaf_ == true)
    {
        while (i >= 0 && elem_[i] > key)
        {
            elem_[i + 1] = elem_[i];
            i--;
        }
        elem_[i + 1] = key;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && elem_[i] > key)
            i--;
        if (child_[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, child_[i + 1]);
            if (elem_[i + 1] < key)
                i++;
        }
        child_[i + 1]->just_insert(key);
    }
}

template <class T, class U, size_t t>
void &Node<T, U, t>::split_child(size_t i, Node<T, U, t> *child)
{
    Node<T, U, t> *z = new Node<T, U, t>;
    new_child->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        new_child->elem_[j] = child->elem_[j+t];
    if (child->leaf_ == false)
    {
        for (size_t j = 0; j < t; j++)
            new_child->child_[j] = child->child_[j + t];
    }
    child->n = t - 1;
    for (size_t j = n; j >= i + 1; j--)
        child_[j + 1] = child_[j];
    child_[i + 1] = new_child;
    for (size_t j = n - 1; j >= i; j--)
        elem_[j + 1] = elem_[j];
    elem_[i] = child->elem_[t - 1];
    n += 1;
}

//ОБХОД

template <class T, class U, size_t t>
std::ostream& operator<<(std::ostream &os, Elem<T, U> &elem)
{
  os << "<";
  for (size_t i = 0; i < n; i++)
    os << "(" << elem_[i].key_ << ", " << elem_[i].val_ << ")" << " ";
  }
  os << ">";
  return os;
}

template <class T, class U, size_t t>
void &Node<T, U, t>::traverse()
{
    size_t i;
    for (i = 0; i < n; i++)
    {
        if (leaf_ == false)
            child_[i]->traverse();
        std::cout << " " << elem_[i];
    }
}

void &BTree<T, U, t>::traverse()
{
  root_->traverse();
}

//УДАЛЕНИЕ

size_t &Node<T, U>::key_number(Elem<T, U> &key)
{
    size_t num = 0;
    while (num < n && elem_[num] < key)
        num++;
    return num;
}

void &Node<T, U, t>::remove(Elem<T, U> &key)
{
    int num = key_number(key);
    if (num < n && elem_[num] == k)
    {
        if (leaf)
            remove_from_leaf(num);
        else
            remove_from_non_leaf(num);
    }
    else
    {
        if (leaf)
        {
            throw 4;
        bool flag = (num == n)? true: false ;
        if (child_[num]->n < t)
            fill(num);
        if (flag && num > n)
            child_[num - 1]->remove(k);
        else
            child_[num]->remove(k);
    }
}

template <class T, class U, size_t t>
void &Node<T, U, t>::remove_from_leaf (size_t index)
{
    for (size_t j = index + 1; j < n; j++)
        elem_[j - 1] = elem_[j];
    n--;
}

template <class T, class U, size_t t>
void BTreeNode::remove_from_non_leaf(size_t index)
{

    int k = keys[idx];
    if (child_[index]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ);
    }
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

template <class T, class U, size_t t>
Elem<T, U> Node<T, U, t>::get_prev(size_t idx)
{
    Node<T, U, t> *cur=child_[index];
    while (!cur->leaf_)
        cur = cur->child_[cur->n];
    return cur->elem_[cur->n - 1];
}

Elem<T, U> Node<T, U, t>::get_succ(size_t index)
{
    Node<T, U, t> *cur = child_[index + 1];
    while (!cur->leaf)
        cur = cur->child_[0];
    return cur->elem_[0];
}

template <class T, class U, size_t t>
void Node<T, U, t>::fill(size_t index)
{
    if (index != 0 && child_[index - 1]->n >= t)
        borrow_from_prev(index);
    else if (index != n && child_[index + 1]->n >= t)
        borrow_from_next(index);
    else
    {
        if (index != n)
            merge(index);
        else
            merge(index - 1);
    }
    return;
}

template <class T, class U, size_t t>
void BTreeNode::borrow_from_prev(size_t index)
{

    Node<T, U, t> *child=child_[index];
    Node<T, U, t> *sibling=child_[index - 1];
    for (size_t i = child->n - 1; i >= 0; i--)
        child->elem_[i + 1] = child->elem_[i];
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }
    child->elem_[0] = elem_[index - 1];
    if (!leaf)
        child->child_[0] = sibling->child_[sibling->n];
    elem_[index - 1] = sibling->elem_[sibling->n - 1];
    child->n++;
    sibling->n--;
}

template <class T, class U, size_t t>
void Node<T, U, t>::borrow_from_next(size_t index)
{
    Node<T, U, t> *child=child_[index];
    Node<T, U, t> *sibling=child_[index + 1];
    child->elem_[child->n] = elem_[index];
    if (!(child->leaf))
        child->child_[child->n + 1] = sibling->child_[0];
    elem_[index] = sibling->elem_[0];
    for (size_t i = 1; i < sibling->n; i++)
        sibling->elem_[i - 1] = sibling->elem_[i];
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }
    child->n++;
    sibling->n--;
}

template <class T, class U, size_t t>
void Node<T, U, t>::merge(size_t index)
{
    Node<T, U, t> *child = C[index];
    Node<T, U, t> *sibling = C[index+1];
    child->elem_[t - 1] = elem_[index];
    for (size_t i = 0; i < sibling->n; i++)
        child->elem_[i + t] = sibling->elem_[i];
    if (!child->leaf)
    {
        for (size_t i = 0; i <= sibling->n; i++)
            child->child_[i + t] = sibling->child_[i];
    }
    for (size_t i = index + 1; i < n; i++)
        elem_[i - 1] = elem_[i];
    for (size_t i = index + 2; i <= n; i++)
        child_[i - 1] = child_[i];
    child->n += sibling->n + 1;
    n--;
    delete(sibling);
}

template <class T, class U, size_t t>
void &Node<T, U, t>::sort()
{
  T temp;
  for (size_t i = 0; i < n - 2; i++)
  {
    if (elem_[i].val_ > elem_[i + 1].val_)
    {
      temp = elem_[i].val_;
      elem_[i].val_ = elem_[i + 1].val_;
      elem_[i + 1].val_ = temp;
    }
  }
  for (size_t i = 0; i < n; i++)
  {
      if(leaf_ == false)
      {
	child_[i]->sort();
      }
  }
}

template <class T, class U, size_t t>
void &BTree<T, U, t>::sort()
{
  root_->sort();
}

template <class T, class U, size_t t>
bool &BTree<T, U, t>::empty()
{
  if (root_ == NULL)
    return true;
  return false;
}

template <class T, class U, size_t t>
void &Node<T, U, t>::clear()
{
  free(elem_);
  for (size_t i = 0; i < n; i++)
    child_[i]->clear();
  free(child);
  delete *this;
}

template <class T, class U, size_t t>
void &BTree<T, U, t>::clear()
{
  root_->clear;
}

template <class T, class U, size_t>
&BTree<T, U, t>::~BTree()
{
  clear();
}

//ИТЕРАТОР

template <class T, class U, size_t t>
Iterator<T, U, t> & Iterator<T, U, t>::operator++(int)
{
    Iterator *it;
    for (size_t i = 0; cur->elem_[i].key_!= key_; i++)
    if (i == cur.n - 1)
    {
        if (!cur->leaf_)
        {
            cur = cur->child_[cu->n];
            val_ = cur->elem_[0].val_;
            key_ = cur->elem_[0].key_;
        }
        else
        {
            while (i == cur.n - 1)
            {
                cur = Parent(cur);
                i = i(cur);
            }
            if (cur->elem_[0] == root_->elem_[0])
                throw 11;
            i++;
            cur = cur->child_[i]
            while(!cur->leaf_)
            {
                cur = cur->child_[0];
            }
            val_ = cur->elem_[0].val_;
            key_ = cur->elem_[0].key_;
        }
    }
    else
    {
        val_ = cur->elem_[i + 1].val_;
        key_ = cur->elem_[i + 1].key_;
    }
    return *this;
}

template<class T, class U, size_t t>
Iterator<T, U, t> & Iterator<T, U, t>::operator--(int)
{
    for (size_t i = 0; cur->elem_[i].key_!= key_; i++)
    if (i == 0)
    {
        if (!cur->leaf_)
        {
            cur = cur->child_[0];
            val_ = cur->elem_[cur->n].val_;
            key_ = cur->elem_[cur->n].key_;
        }
        else
        {
            while (i == 0)
            {
                cur = Parent(cur);
                i = i(cur);
            }
            if (root_->elem_[0] == cur->elem_[0])
                return NULL;
            i--;
            cur = cur->child_[i]
            while(!cur->leaf_)
            {
                cur = cur->child_[cur->n];
            }
            val_ = cur->elem_[cur->n].val_;
            key_ = cur->elem_[cur->n].key_;
        }
    }
    else
    {
        val_ = cur->elem_[i - 1].val_;
        key_ = cur->elem_[i - 1].key_;
    }
    return *this;
}

template <class T, class U, size_t t>
Iterator<T, U, t> &BTree<T, U, t>::get_min();
{
    Iterator<T, U, t> = *it;
    it.cur_ = root_;
    while (!it.cur_->leaf_)
    {
        it.cur_->child_[0];
    }
    it.key_ = it.cur_->elem_[0].key_;
    it.val_ = it.cur_->elem_[0].val_;
    return it;
}

template <class T, class U, size_t>
Iterator<T, U, t> &BTree<T, U, t>::get_max()
{
    Iterator<T, U, t> = *it;
    it.cur_ = root_;
    while (!it.cur_->leaf_)
    {
        it.cur->child_[it.cur_->n];
    }
    it.key_ = it.cur_->elem_[it.cur->n - 1].key_;
    it.val_ = it.cur_->elem_[it.cur->n - 1].val_;
    return it;
}
#endif // BTREE_H_INCLUDED

