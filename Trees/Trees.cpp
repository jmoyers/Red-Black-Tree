#include "stdafx.h"
#include "RBTree.h"
#include <iostream>
#include <exception>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
  RBTree<int, string> tree;

  for (int i = 0; i < 20; i++)
  {
    tree.insert(i, std::to_string(i));
    cout << "insert done" << endl << endl;
  }
  
  tree.debug();

  for (int i = 0; i < 20; i++)
  {
    cout << tree.get(i) << " ";
  }

  cin.get();
  return 0;
}