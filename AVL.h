#ifndef AVL_H
#define AVL_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include "json.hpp"

class AVL;

class AVLNode {
 public:
  AVLNode(int key);
  AVLNode(int key, std::weak_ptr<AVLNode> parent);
  bool IsLeaf() const;
  bool IsMissingChild() const;
  bool HasLeftChild() const;
  bool HasRightChild() const;

 private:
  int key_;
  int balancefactor;
  int height;
  std::weak_ptr<AVLNode> parent_;
  std::shared_ptr<AVLNode> left_;
  std::shared_ptr<AVLNode> right_;

  friend AVL;
}; // class AVLNode

class AVL {
 public:
  AVL();

  void Insert(int key);
  bool Find(int key) const;
  std::string JSON();
  size_t size() const;
  bool empty() const;

 private:
  int height(std::shared_ptr<AVLNode> N);
  int max(int a, int b);
  std::shared_ptr<AVLNode> newNode(int key);
  std::shared_ptr<AVLNode> rightRotate(std::shared_ptr<AVLNode> y);
  std::shared_ptr<AVLNode> leftRotate(std::shared_ptr<AVLNode> x);
  int getBalance(std::shared_ptr<AVLNode> N);
  std::shared_ptr<AVLNode> insert(std::shared_ptr<AVLNode> node, int key);

  std::shared_ptr<AVLNode> root_;
  size_t size_;
};

#endif // AVL_H

