// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include <algorithm>
#include  "tree.h"

using namespace std;
TreeNode::TreeNode(char val) : value(val) {}
TreeNode::~TreeNode() {
  for (auto child : children)
    delete child;
}

PMTree::PMTree(const std::vector<char>& in) {
  root = new TreeNode(0);
  build(root, in);
}

PMTree::~PMTree() {
  delete root;
}

void PMTree::build(TreeNode* node, std::vector<char> remaining) {
  std::sort(remaining.begin(), remaining.end());
  for (size_t i = 0; i < remaining.size(); ++i) {
    char val = remaining[i];
    TreeNode* child = new TreeNode(val);
    node->children.push_back(child);
    std::vector<char> next = remaining;
    next.erase(next.begin() + i);
    build(child, next);
  }
}

void PMTree::collect(TreeNode* node, vector<char>& path, vector<vector<char>>& result) {
  if (node->value != 0)
    path.push_back(node->value);
  if (node->children.empty()){
        result.push_back(path);
  } else {
    for (auto child : node->children)
      collect(child, path, result);
  }
  if (!path.empty() && node->value != 0)
    path.pop_back();
}

vector<vector<char>> getAllPerms(PMTree& tree) {
  vector<vector<char>> result;
  vector<char> path;
  tree.collect(tree.root, path, result);
  return result;
}

vector<char> getPerm1(PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  return (num > 0 && num <= perms.size()) ? perms[num - 1] : vector<char>{};
}

vector<char> PMTree::getPermByIndex(TreeNode* node, int& index, int target) {
  if (node->children.empty()) {
    ++index;
    return (index == target) ? std::vector<char>{node->value} : vector<char>{};
  }

  for (auto child : node->children) {
    auto result = getPermByIndex(child, index, target);
    if (!result.empty()) {
      if (node->value != 0)
        result.insert(result.begin(), node->value);
      return result;
    }
  }
  return {};
}

vector<char> getPerm2(PMTree& tree, int num) {
  int index = 0;
  return tree.getPermByIndex(tree.root, index, num);
}

