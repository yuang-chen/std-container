#include <iostream>
/*
1. A node is either red or black.
2. The root and leaves (nil, nullptr node) are always black.
3. If a node is red, then its children are black.
4. All paths from a node to its leaves contain the same number of black nodes.
5. The longest path from the root to a leaf is no more than twice as long as the shortest path from the root to a leaf.
  -- The shortest path: all black nodes.
  -- The longest path: alternate red and black nodes.

Three basic operations:
1. Insert O(logN), requires rotation
2. Remove O(logN), requires rotation
3. Search O(logN)

Rotation:
1. alters the structure of the tree by rearranging subtrees
2. goal is to decrease the height of the tree
  -- maximum height: log(N)
  -- larger subtrees up, smaller subtrees down
3. left rotation: clockwise rotation
4. right rotation: counterclockwise rotation
*/
enum Color
{
  RED,
  BLACK
};

template <typename T>
struct Node
{
  //K   key; for map
  T     value;
  Color color;
  Node* left;
  Node* right;
  Node* parent;

  Node(Color c, Node* p = nullptr, T val)
      : color(c), left(nullptr), right(nullptr), parent(p), value(val)
  {
  }
};

template <typename T>
class RedBlackTree
{
  private:
  Node* root;

  void deleteTree(Node* node)
  {
    if(node)
    {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }
  //! very annoying to write
  // GOAL: node x become the [left child] of its [right child] y
  // totally six pointers need to be updated
  void rotateLeft(Node* x)
  {
    Node* y  = x->right;
    x->right = y->left;    //the left child of y will become the new right child of x.
    if(y->left != nullptr)
    {
      y->left->parent = x;    // if y had a left child, update its parent pointer to x.
    }
    y->parent = x->parent;    // update y's parent to x's parent.
    if(x->parent == nullptr)
    {
      root = y;    // if x was the root, then y becomes the new root.
    }
    else if(x == x->parent->left)
    {    //if x was the left child of its parent, then update the left child of x's parent to y
      x->parent->left = y;
    }
    else
    {    //if x was the right child of its parent, update the right child of x's parent to y
      x->parent->right = y;
    }
    y->left   = x;    // make x the left child of y
    x->parent = y;    // update the parent of x to y.
  }
  // symmetric operations of rotateLeft
  // GOAL: node y become the [right child] of its [left child] x
  void rotateRight(Node* y)
  {
    Node* x = y->left;
    y->left = x->right;
    if(x->right != nullptr)
    {
      x->right->parent = y;
    }
    x->parent = y->parent;

    if(y->parent == nullptr)
    {
      root = x;
    }
    else if(y == y->parent->left)
    {
      y->parent->left = x;
    }
    else
    {
      y->parent->right = x;
    }

    x->right  = y;
    y->parent = x;
  }

  void fixViolations(Node* x)
  {
    Node* parent      = nullptr;
    Node* grandparent = nullptr;

    while((x != root) && (x->color != BLACK) && (x->parent->color == RED))
    {
      parent      = x->parent;
      grandparent = parent->parent;

      // Case A: Parent is left child of grandparent
      if(parent == grandparent->left)
      {
        Node* uncle = grandparent->right;
        if(uncle && uncle->color == RED)    // uncle is RED
        {
          grandparent->color = RED;
          parent->color      = BLACK;
          uncle->color       = BLACK;
          x                  = grandparent;
        }
        else
        {
          if(x == parent->right)    // uncle is BLACK and x is right child
          {
            rotateLeft(parent);
            x      = parent;
            parent = x->parent;
          }
          rotateRight(grandparent);
          std::swap(parent->color, grandparent->color);
          x = parent;
        }
      }
      else
      {    // Case B: Parent is right child of grandparent
        Node* uncle = grandparent->left;
        if(uncle && uncle->color == RED)    // uncle is RED
        {
          grandparent->color = RED;
          parent->color      = BLACK;
          uncle->color       = BLACK;
          x                  = grandparent;
        }
        else
        {
          if(x == parent->left)    // uncle is BLACK and x is left child
          {
            rotateRight(parent);
            x      = parent;
            parent = x->parent;
          }
          rotateLeft(grandparent);
          std::swap(parent->color, grandparent->color);
          x = parent;
        }
      }
    }
    root->color = BLACK;
  }

  void insert(Node*& node, Node* parent, const T& value)
  {
    if(node == nullptr)
    {
      node = new Node(RED, parent, value);    // insert the node and color it RED
      fixViolations(node);
      return;
    }

    if(value == node->value)
    {
      return;    // no need to insert
    }

    if(value < node->value)
    {
      insert(node->left, node, value);
    }
    else
    {
      insert(node->right, node, value);
    }
  }

  public:
  RedBlackTree() : root(nullptr) {}

  ~RedBlackTree()
  {
    deleteTree(root);
  }
};

template <typename T>
class Set
{
  private:
  RedBlackTree<T> tree;

  public:
  void insert(const T& value)
  {
    tree.insert(value);
  }

  bool find(const T& value)
  {
    return tree.find(value);
  }
};

template <typename K, typename V>
struct Pair
{
  K key;
  V value;

  Pair(const K& k, const V& v) : key(k), value(v) {}

  bool operator<(const Pair& rhs) const
  {
    return key < rhs.key;
  }
};

template <typename K, typename V>
class Map
{
  private:
  RedBlackTree<Pair<K, V>> tree;

  public:
  void insert(const K& key, const V& value)
  {
    tree.insert(Pair<K, V>(key, value));
  }

  void find(const K& key)
  {
    return tree.find(Pair<K, V>(key, V()));
  }
};

int main()
{
  Set<int> my_set;
  my_set.insert(5);
  my_set.insert(3);
  my_set.insert(7);

  return 0;
}
