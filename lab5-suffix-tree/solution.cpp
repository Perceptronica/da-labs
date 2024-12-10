#include <bits/stdc++.h>

struct Node;
struct STree;

struct Node {
  std::map<char, Node *> to;
  std::string::iterator begin;
  std::string::iterator end;
  Node *suffixLink;

  Node(std::string::iterator begin, std::string::iterator end)
      : begin(begin), end(end), suffixLink(nullptr) {}

  ~Node() {};
};

struct STree {
  std::string text;
  Node *root;
  Node *activeNode;
  Node *lastAdded;
  std::string::iterator activeEdge;
  int32_t activeLength;
  int32_t remainder;

  STree() = default;
  STree(std::string &str)
      : text(str), activeLength(0), activeEdge(text.begin()), remainder(0) {
    root = new Node(text.end(), text.end());
    lastAdded = root;
    activeNode = root;
    root->suffixLink = root;

    for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
      addLetter(it);
    }
  }

  ~STree() { destroy(root); }

  void addLetter(std::string::iterator i) {
    lastAdded = root;
    ++remainder;
    while (remainder > 0) {
      activeEdge = (activeLength == 0) ? i : activeEdge;
      std::map<char, Node *>::iterator it =
          activeNode->to.find(*activeEdge);
      Node *next;
      if (it == activeNode->to.end()) {
        Node *leaf = new Node(i, text.end());
        activeNode->to[*activeEdge] = leaf;
        lastAdded->suffixLink =
            (lastAdded != root) ? activeNode : lastAdded->suffixLink;
        lastAdded = activeNode;
      } else {
        next = it->second;
        if (checkEdge(i, next)) {
          continue;
        }
        if (*(next->begin + activeLength) == *i) {
          ++activeLength;
          lastAdded->suffixLink =
              (lastAdded != root) ? activeNode : lastAdded->suffixLink;
          lastAdded = activeNode;
          break;
        }
        Node *split = new Node(next->begin, next->begin + activeLength);
        Node *leaf = new Node(i, text.end());
        activeNode->to[*activeEdge] = split;
        split->to[*i] = leaf;
        next->begin += activeLength;
        split->to[*next->begin] = next;
        lastAdded->suffixLink =
            (lastAdded != root) ? split : lastAdded->suffixLink;
        lastAdded = split;
      }
      --remainder;
      if (activeNode == root && activeLength > 0) {
        --activeLength;
        activeEdge = i - remainder + 1;
      } else {
        activeNode = activeNode->suffixLink;
      }
    }
  }

  void searchLeaves(Node *node, std::vector<int32_t> &answer, int32_t loc) {
    if (node->end == text.end()) {
      answer.push_back(text.size() - loc + 1);
    } else {
      Node *child;
      for (auto it = node->to.begin(); it != node->to.end(); ++it) {
        child = it->second;
        searchLeaves(child, answer, loc + child->end - child->begin);
      }
    }
  }

  std::vector<int32_t> search(std::string &str) {
    std::vector<int32_t> answer;
    int32_t loc = 0;
    Node *current = root;
    if (str.length() > text.length()) {
      return answer;
    }
    for (std::string::iterator pos = str.begin(); pos != str.end(); ++pos) {
      auto path = current->to.find(*pos);
      if (path == current->to.end()) {
        return answer;
      }
      current = path->second;
      loc += current->end - current->begin;
      for (std::string::iterator p = current->begin;
           p != current->end && pos != str.end(); ++p, pos++) {
        if (*p != *pos) {
          return answer;
        }
      }
      if (pos == str.end()) {
        break;
      }
      --pos;
    }
    searchLeaves(current, answer, loc);
    sort(answer.begin(), answer.end());
    return answer;
  }

  void destroy(Node *node) {
    for (auto it = node->to.begin(); it != node->to.end(); ++it) {
      destroy(it->second);
    }
    delete node;
  }

  bool checkEdge(std::string::iterator pos, Node *node) {
    int32_t edgeLength = (pos + 1 < node->end) ? (pos + 1 - node->begin)
                                               : (node->end - node->begin);
    if (activeLength >= edgeLength) {
      activeEdge += edgeLength;
      activeLength -= edgeLength;
      activeNode = node;
      return true;
    }
    return false;
  }
};

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string text;
  std::cin >> text;
  text += "$";

  STree tree(text);
  int32_t k{0};
  std::vector<int32_t> answer;
  std::string pattern;
  while (std::cin >> pattern) {
    if (pattern.empty()) {
      break;
    }
    ++k;
    answer = tree.search(pattern);
    if (!answer.empty()) {
      std::cout << k << ": ";
      for (std::size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << ((i == answer.size() - 1) ? "\n" : ", ");
      }
    }
  }
  return 0;
}
