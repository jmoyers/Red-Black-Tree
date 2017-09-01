#pragma once
#include <vector>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

template <class K, class V>
class RBTree
{
private:
  enum class Color { RED, BLACK };

  struct Node {
    K key;
    V value;
    Color color = Color::RED;
    size_t count = 0;
    
    Node *left = nullptr;
    Node *right = nullptr;

    Node(K key, V value, Color color = Color::RED) : 
      key(key), 
      value(value), 
      color(color) {}
  };

  Node *root = nullptr;

  Node * rotate_left(Node *node)
  {
    Node *new_parent = node->right;
    
    Node *snip = new_parent->left;
    node->right = snip;
    
    new_parent->left = node;
    new_parent->left->color = Color::RED;
    new_parent->color = Color::BLACK;
    
    return new_parent;
  }

  Node * rotate_right(Node *node)
  {
    Node *new_parent = node->left;
    Node *snip = node->left->right;    
    node->left->right = node;
    node->left = snip;
    return new_parent;
  }

  void color_flip(Node *node)
  {
    node->color = Color::RED;
    node->left->color = Color::BLACK;
    node->right->color = Color::BLACK;
  }

  bool is_red(Node* node)
  {
    return node != nullptr && node->color == Color::RED;
  }

  Node * put(Node *node, K& key, V& value)
  {
    if (node == nullptr)
    {
      return new Node( key, value );
    }

    if (node->key < key)
    {
      cout << "Put right" << endl;
      node->right = put(node->right, key, value);
    }
    else if (node->key > key)
    {
      cout << "Put left" << endl;
      node->left = put(node->left, key, value);
    }
    else if (node->key == key)
    {
      cout << "Set value" << endl;
      node->value = key;
    }

    // Resolve RB tree invariants
    
    // right leaning red
    if (is_red(node->right) && !is_red(node->left))
    {
      node = rotate_left(node);
    }

    // two red links in a row, balance 4 node
    if (is_red(node->left) && is_red(node->left->left))
    {
      node = rotate_right(node);
    }

    // both children, split 4 node
    if (is_red(node->left) && is_red(node->right))
    {
      color_flip(node);
    }

    return node;
  }
public:
  void insert(K key, V value)
  { 
    root = put(root, key, value);
  }

  void remove(const K &key)
  {
    throw std::logic_error("too lazy");
  }

  V& get(const K &key)
  {
    Node *x = root;

    while (x)
    {
      if (key > x->key)
      {
        x = x->right;
      }
      else if (key < x->key)
      {
        x = x->left;
      }
      else if (key == x->key)
      {
        return x->value;
      }
    }

    throw std::out_of_range("key not found");
  }

  void debug()
  {
    if (root == nullptr)
    {
      cout << "Tree empty" << endl;
      return;
    }

    print_node(root);
  }

  void print_node(Node* node_ref, int indent = 0)
  {
    if (node_ref == nullptr) {
      return;
    }

    cout << std::setw(indent) << ' ';
    cout << "Key: " << node_ref->key << endl;
    cout << std::setw(indent) << ' ';
    cout << "Value: " << node_ref->value << endl;
    cout << std::setw(indent) << ' ';
    cout << "Color: " << (node_ref->color == Color::BLACK ? "Black" : "Red") << endl;
    cout << std::setw(indent) << ' ';
    cout << "Count: " << node_ref->count << endl;
    cout << std::setw(indent) << ' ';
    cout << "Left --> " << endl;
    print_node(node_ref->left, indent+4);
    cout << std::setw(indent) << ' ';
    cout << "Right --> " << endl;
    print_node(node_ref->right, indent+4);
  }
};