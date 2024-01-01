#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <codecvt>
#include <cstddef>
#include <fstream> // std::ifstream
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <vector>

enum NodeType {
  Addition,
  Subtraction,
  Multiplication,
  Division,
  OpenBracket,
  CloseBracket,
  ConstantNumber
};

struct Node {
  Node(NodeType type) : node_type_(type) {}
  virtual int Eval() { return 0; };
  virtual ~Node() = default;
  NodeType node_type_;
};

using ConstIter = std::vector<Node *>::const_iterator;
using NodeRange = std::pair<ConstIter, ConstIter>;

struct Constant : public Node {
  Constant(int val) : Node(NodeType::ConstantNumber), val_(val) {}
  virtual int Eval() override { return val_; }
  int val_;
};

struct OpeningBracket : public Node {
  OpeningBracket() : Node(NodeType::OpenBracket) {}
};
struct ClosingBracket : public Node {
  ClosingBracket() : Node(NodeType::CloseBracket) {}
};

struct Operation : public Node {
  Operation(NodeType type, Node *left = nullptr, Node *right = nullptr)
      : Node(type), left_(left), right_(right) {}
  virtual int Eval() override {
    int left_val = left_->Eval();
    int right_val = right_->Eval();
    switch (node_type_) {
    case Addition:
      return left_val + right_val;
    case Subtraction:
      return left_val - right_val;
    case Multiplication:
      return left_val * right_val;
    case Division:
      return left_val / right_val;
    default:
      throw std::runtime_error("Unknown operation type");
    }
  }
  Node *left_;
  Node *right_;
};

std::vector<Node *> Parse(const std::string &expr) {
  std::vector<Node *> result;
  std::istringstream iss(expr);
  while (!iss.eof()) {
    if (iss.peek() == ' ' || iss.peek() == EOF) {
      iss.ignore(1);
      continue;
    }
    if (iss.peek() == '(') {
      result.push_back(new OpeningBracket());
      iss.ignore(1);
      continue;
    }
    if (iss.peek() == ')') {
      result.push_back(new ClosingBracket());
      iss.ignore(1);
      continue;
    }
    if (iss.peek() == '+') {
      result.push_back(new Operation(NodeType::Addition));
      iss.ignore(1);
      continue;
    }
    if (iss.peek() == '*') {
      result.push_back(new Operation(NodeType::Multiplication));
      iss.ignore(1);
      continue;
    }
    if (iss.peek() == '/') {
      result.push_back(new Operation(NodeType::Division));
      iss.ignore(1);
      continue;
    }
    int sign = 1;
    if (iss.peek() == '-') {
      iss.ignore(1);
      if (iss.peek() == ' ') {
        result.push_back(new Operation(NodeType::Subtraction));
        continue;
      }
      sign = -1;
    }
    int constant;
    iss >> constant;
    result.push_back(new Constant(sign * constant));
  }
  return result;
}

auto MatchBrackets(const std::vector<Node *> &nodes) {
  std::unordered_map<size_t, size_t> result;
  std::vector<size_t> stack;
  for (size_t i = 0; i < nodes.size(); ++i) {
    auto node_type = nodes[i]->node_type_;
    if (node_type == NodeType::OpenBracket) {
      stack.push_back(i);
    }
    if (node_type == NodeType::CloseBracket) {
      if (stack.empty()) {
        throw std::runtime_error("Incorrect bracket sequence.");
      }
      result[stack.back()] = i;
      stack.pop_back();
    }
  }
  return result;
}

void CheckIfOperator(ConstIter it) {
  auto node_type = (*it)->node_type_;
  if (node_type == NodeType::Addition ||
      node_type == NodeType::Multiplication ||
      node_type == NodeType::Subtraction || node_type == NodeType::Division) {
    return;
  }
  throw std::runtime_error("Failed to ReadOperator: no operator found.");
}

class NodesReader {
public:
  NodesReader(const std::vector<Node *> &nodes)
      : nodes_(nodes), matching_brackets_(MatchBrackets(nodes)) {}
  NodeRange ReadSubExpr(ConstIter it) const {
    auto node_type = (*it)->node_type_;
    if (node_type == NodeType::ConstantNumber) {
      return {it, it + 1};
    }
    if (node_type == NodeType::OpenBracket) {
      auto close_bracket = GetMatchingBracketIter(it);
      return {it + 1, close_bracket};
    }
    throw std::runtime_error("Failed to ReadSubExpr.");
  }

  const ConstIter GetMatchingBracketIter(ConstIter opening_bracket) const {
    size_t offset = opening_bracket - nodes_.begin();
    if (auto match_offset = matching_brackets_.find(offset);
        match_offset != matching_brackets_.end()) {
      return nodes_.begin() + match_offset->second;
    }
    throw std::runtime_error("Matching bracket not found!");
  }

private:
  const std::vector<Node *> &nodes_;
  std::unordered_map<size_t, size_t> matching_brackets_;
};

Node *BuildTree(ConstIter begin, ConstIter end, const NodesReader &reader) {
  if (end - begin == 1) {
    return *begin;
  }
  Node *left_operand;
  Node *op;
  Node *right_operand;
  // Reading left operand.
  auto [left, right] = reader.ReadSubExpr(begin);
  left_operand = BuildTree(left, right, reader);
  if ((*right)->node_type_ == NodeType::CloseBracket) {
    ++right;
  }
  if (right == end) {
    return left_operand;
  }
  begin = right;
  // Reading operator.
  CheckIfOperator(begin);
  op = *begin;
  ++begin;
  if (begin == end)
    throw std::runtime_error("Operator without an operand.");
  // Reading right operand.
  std::tie(left, right) = reader.ReadSubExpr(begin);
  right_operand = BuildTree(left, right, reader);
  // Constructing the opert
  auto operation = reinterpret_cast<Operation *>(op);
  operation->left_ = left_operand;
  operation->right_ = right_operand;
  return operation;
}

int eval(const std::string &expr) {
  auto nodes = Parse(expr);
  NodesReader reader(nodes);
  Node *ast = BuildTree(nodes.begin(), nodes.end(), reader);
  int result = ast->Eval();
  for (Node *node : nodes) {
    delete node;
  }
  return result;
}
