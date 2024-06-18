#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode {
  public:
    TreeNode(T d); //overloaded constructor
    virtual ~TreeNode(); //default destructor
    T getData();
    int getLeftHeight();
    int getRightHeight();
    double getHeightDiffFactor();

    template <typename S>
    friend class LazyBST; //used entirely in the tree
    friend class Database; 

  private:
    T m_data;
    TreeNode<T>* m_left;
    TreeNode<T>* m_right;

    int m_left_height = 0;
    int m_right_height = 0;

};

template <typename T>
TreeNode<T>::TreeNode(T d) {
  m_data = d;
  //default no child node references
  m_left = NULL;
  m_right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode() {
  //makes sure to delete children pointers before deleting
  if(m_left != NULL) {
    delete m_left;
  }
  if(m_right != NULL) {
    delete m_right;
  }
}

template <typename T>
T TreeNode<T>::getData() {
  return m_data;
}

template <typename T>
int TreeNode<T>::getLeftHeight() {
  return m_left_height;
}

template <typename T>
int TreeNode<T>::getRightHeight() { //gets height of only the right
  return m_right_height;
}

template <typename T>
double TreeNode<T>::getHeightDiffFactor() {
  double factor = 0.0;
  if(m_left_height > m_right_height) {
    if(m_right_height == 0) {
      return m_left_height;
    }
    factor = (double)m_left_height / (double)m_right_height; 
  } else {
    if (m_left_height == 0) {
      return m_right_height;
    }
    factor = (double)m_right_height / (double)m_left_height;
  }
  return factor; //finds overall difference between the 2 on average
}


#endif