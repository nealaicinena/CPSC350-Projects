#ifndef LazyBST_H
#define LazyBST_H

#include "TreeNode.h"

template <typename T>
class LazyBST {
    public:
        LazyBST(); //default constructor
        virtual ~LazyBST(); //default destructor

        bool iterContains(T d);
        bool contains(T d); //similar to search   
        void printInOrder();      
        void printTreePostOrder(); 
        void insert(T d);
        int size();
        T max();    
        T min();   
        T median(); //finds the value in the middle (mostly used for resizing)
        void remove(T d);

        int getHeight(TreeNode<T> *n); //returns height of the node in the tree
        T* get(T key);    
        void test();
        void printInOrder(ostream &file);
        void printIOHelper(TreeNode<T> *n, ostream &file);
    private:
        TreeNode<T> *m_root; //pointer is changed to different node when resized
        int m_size; //total nodes

        //helpers for organizing  (not fully intended to be used outside of this class so they are private)
        bool recContainsHelper(TreeNode<T> *n, T d);
        void printIOHelper(TreeNode<T> *n);
        void printTreePostOrderHelper(TreeNode<T> *subTreeRoot);
        void insertHelper(TreeNode<T> *&subTreeRoot, T &d);
        T getMaxHelper(TreeNode<T> *n);
        T getMinHelper(TreeNode<T> *n);
        void findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent);
        TreeNode<T> *getSuccessor(TreeNode<T> *rightChild);

        void updateHeights(TreeNode<T> *n);
        bool needsRebalance(TreeNode<T> *n);
        void rebalance(TreeNode<T> *n);
        void getArray(TreeNode<T> *n, T *arr, int &index);
        void insertMedians(T *arr, int size, LazyBST<T> &newTree);
        void noBalanceInsert(T d);

        T* getHelper(T target, TreeNode<T> *root);
};

template <typename T>
LazyBST<T>::LazyBST() {
    m_root = NULL; // starts root as null
    m_size = 0;
}

template <typename T>
LazyBST<T>::~LazyBST() {
    
}

template <typename T>
bool LazyBST<T>::iterContains(T d) {
    if (m_root == NULL) {
        return false;
    }
    if (m_root->data == d) {  //if the root is the data then no deep search needed
        return true;
    }

    bool found = false;
    TreeNode<T> *current = m_root;
    while (!found) { //go left and right until we find it or we reach a leaf node
        if (d > current->m_data) {
            current = current->m_right;
        } else { 
            current = current->m_left;
        }
        
        if (current == NULL) {
            found = false;
            break;
        }

       if (current->m_data == d) {
            found = true;
        }
    }
    return found;
}

template <typename T>
bool LazyBST<T>::contains(T d) { //public function that uses helper function
    return recContainsHelper(m_root, d);
}

template <typename T>
bool LazyBST<T>::recContainsHelper(TreeNode<T> *n, T d) { //recursive search method version
    if (n == NULL) { 
        return false;
    }
    if (n->m_data == d) { 
        return true;
    }
    if (d > n->m_data) { 
        return recContainsHelper(n->m_right, d);
    } else {
        return recContainsHelper(n->m_left, d);
    }
}

template <typename T>
void LazyBST<T>::printInOrder() { //uses helper to print tree in order
    printIOHelper(m_root);
}

template <typename T>
void LazyBST<T>::printIOHelper(TreeNode<T> *n) {
    if (n != NULL) { //as long as theres another node, print the children and recursively move down                                
        printIOHelper(n->m_left);   
        std::cout << n->m_data << std::endl; 
        printIOHelper(n->m_right);           
    }
}

template <typename T>
void LazyBST<T>::printInOrder(ostream &file) { //
    printIOHelper(m_root, file);
}

template <typename T>
void LazyBST<T>::printIOHelper(TreeNode<T> *n, ostream &file) {
    if (n != NULL)
    {                                        
        printIOHelper(n->m_left, file);            
        file << n->m_data << std::endl; 
        printIOHelper(n->m_right, file);        
    }
}


template <typename T>
void LazyBST<T>::printTreePostOrder() {
    printTreePostOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreePostOrderHelper(TreeNode<T> *subTreeRoot) { //works its way up through tree
    if (subTreeRoot != NULL)
    {
        printTreePostOrderHelper(subTreeRoot->m_left); //goes as far left first...
        printTreePostOrderHelper(subTreeRoot->m_right); //then prints the right data
        std::cout << subTreeRoot->m_data << std::endl;
    }
}

template <typename T>
void LazyBST<T>::insert(T d) {
    insertHelper(m_root, d);
    ++m_size;

    if (needsRebalance(m_root)) {
        rebalance(m_root);
    }
}

template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T> *&subTreeRoot, T &d) {
    if (subTreeRoot == NULL) {
        subTreeRoot = new TreeNode<T>(d); // insert here  & stop recursive call
    } else if (d > subTreeRoot->m_data) {
        insertHelper(subTreeRoot->m_right, d); //keep going right until we find the right spot
        ++subTreeRoot->m_right_height;
    } else { 
        insertHelper(subTreeRoot->m_left, d); //keep going left until we find the right spot
        ++subTreeRoot->m_left_height;
    }
}

template <typename T>
int LazyBST<T>::size() {
    return m_size;
}

template <typename T>
T LazyBST<T>::max() {
    return getMaxHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMaxHelper(TreeNode<T> *n) {
    if (n->m_right == NULL) {
        return n->m_data;
    } else {
        return getMaxHelper(n->m_right); //only need to go right because values increase to the right
    }
}

template <typename T>
T LazyBST<T>::min() {
    return getMinHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMinHelper(TreeNode<T> *n) {
    if (n->m_left == NULL) {
        return n->m_data;
    } else {
        return getMinHelper(n->m_left); //only need to go left because values decrease to the left
    }
}

template <typename T>
T LazyBST<T>::median() {
    return m_root->m_data; //middle is always the root (if tree is balanced)
}

template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent) {
    while (target != NULL && target->m_data != key) { //iterates till null or we find it
        parent = target;
        if (key < target->m_data) {
            target = target->m_left; //move to the left if target is less than where were at
        } else {
            target = target->m_right; //move to the right if target is more than where were at
        }
    }
}

template <typename T>
TreeNode<T> *LazyBST<T>::getSuccessor(TreeNode<T> *rightChild) {
    while (rightChild->m_left != NULL) {
        rightChild = rightChild->m_left; //finds the left-most right child to be next successor
    }
    return rightChild;
}

template <typename T>
void LazyBST<T>::remove(T d) {
    if (m_root == NULL) {
        return;
    }
    
    TreeNode<T> *target = NULL;
    TreeNode<T> *parent = NULL;
    target = m_root;

    findTarget(d, target, parent); 

    if (target == NULL) { //if there is nothing to delete
        return;
    }
    if (target->m_left == NULL && target->m_right == NULL) { //if there are no children...
        if (target == m_root) {
            m_root = NULL; //just get rid of the root if its the target
        } else { 
            if (target == parent->m_left) {
                parent->m_left = NULL;
            } else {
                parent->m_right = NULL;
            }
        }
        delete target;
        --m_size;
    } else if (target->m_left != NULL && target->m_right != NULL) { //if there are 2 children...
        //finds which node will be the successor to replace
        TreeNode<T> *suc = getSuccessor(target->m_right);
        T value = suc->m_data;
        remove(value);
        target->m_data = value;
    } else {
        TreeNode<T> *child;
        if (target->m_left != NULL) {
            child = target->m_left;
        } else {
            child = target->m_right;
        }

        if (target == m_root) {
            m_root = child;
        } else {
            if (target == parent->m_left) {                           
                parent->m_left = child; 
            } else {                            
                parent->m_right = child;
            }
        }
        target->m_left = NULL;
        target->m_right = NULL;

        delete target;
        --m_size;
    }
    updateHeights(m_root); 

    if (needsRebalance(m_root)) { //rebalance if needed after all removal
        rebalance(m_root);
    }
}

template <typename T>
void LazyBST<T>::updateHeights(TreeNode<T> *n)
{
    int leftHeight = 0;
    int rightHeight = 0;

    if (n->m_left != NULL) {
        leftHeight = getHeight(n->m_left); //finds the deepest height of the left recursively
    }
    if (n->m_right != NULL) {
        rightHeight = getHeight(n->m_right); //finds the deepest height of the right recursively
    }

    n->m_left_height = leftHeight;
    n->m_right_height = rightHeight;

    if (n->m_left != NULL) {
        updateHeights(n->m_left);
    }
    if (n->m_right != NULL) {
        updateHeights(n->m_right);
    }
}

template <typename T>
int LazyBST<T>::getHeight(TreeNode<T> *n) {
    if (n == NULL) {
        return 0;
    } else {
        return 1 + std::max(getHeight(n->m_left), getHeight(n->m_right)); //finds max and returns +1 of max
    }
}

template <typename T>
bool LazyBST<T>::needsRebalance(TreeNode<T> *n) {
    if (n->getHeightDiffFactor() > 1.5) { //checks if rebalance is needed due to differerence of more than 1.5
        return true;
    } else {
        return false;
    }
}

template <typename T>
void LazyBST<T>::rebalance(TreeNode<T> *n) { //lazily creates a new tree and inserts data in
    int size = m_size;
    T *arr = new T[size];
    int index = 0;
    getArray(n, arr, index); //stores data into array

    LazyBST<T> newTree;

    insertMedians(arr, size, newTree); //new middle to rebalance tree 

    delete m_root;

    m_root = newTree.m_root;

    updateHeights(m_root); //update height of tree

}

template <typename T>
void LazyBST<T>::insertMedians(T *arr, int size, LazyBST<T> &newTree) {
    if (size == 0) {
        return;
    }

    int medianIndex = size / 2; //grabs middle data
    newTree.noBalanceInsert(arr[medianIndex]);

    int leftSize = medianIndex;
    insertMedians(arr, leftSize, newTree);

    int rightSize = size - medianIndex - 1;
    insertMedians(arr + medianIndex + 1, rightSize, newTree);
}

template <typename T>
void LazyBST<T>::getArray(TreeNode<T> *n, T *arr, int &index) {
    if (n != NULL) { //goes thru tree and adds data to the array
        getArray(n->m_left, arr, index);
        arr[index] = n->m_data; //moves down the array adding more data
        ++index;
        getArray(n->m_right, arr, index);
    }
}

template <typename T>
void LazyBST<T>::noBalanceInsert(T d) {
    insertHelper(m_root, d);
    ++m_size;
}

template <typename T>
T* LazyBST<T>::get(T targetData) {
    if (m_root == NULL) {
        return NULL;
    }

    return getHelper(targetData, m_root);
}

template <typename T>
T* LazyBST<T>::getHelper(T target, TreeNode<T> *root) { //recursively finds the target
    if (root == NULL) {
        return NULL;
    }
    if (target == root->m_data) { 
        return &(root->m_data);
    }
    if (target > root->m_data) { 
        return getHelper(target, root->m_right);
    } else {
        return getHelper(target, root->m_left);
    }
}


template <typename T>
void LazyBST<T>::test() {
    std::cout << "Testing" << std::endl;
    double factor = m_root->getHeightDiffFactor();
    rebalance(m_root);
    double factor2 = m_root->getHeightDiffFactor();

    std::cout << "Factor before: " << factor << endl;
    std::cout << "Factor after: " << factor2 << endl;
    std::cout <<"\n";
}

#endif