#include <bits/stdc++.h>

using namespace std;

struct Node;
struct Trie;

using bit_t = int32_t;
using stype = string;
using vtype = uint64_t;
using key = pair<stype, vtype>;
using nptr = Node*;
using tptr = Trie*;

const bit_t MAX_LEN_KEY = 257;
const bit_t BIT_COUNT = 5;

struct Node {
  key k;
  bit_t bit;
  Node* l;
  Node* r;
  vtype num;

  Node() {
    k.first = nullptr;
    k.second = -1;
    bit = -1;
    l = this;
    r = this;
  }

  Node(stype word, vtype value, bit_t b) : l(this), r(this) {
    k.first = word;
    k.second = value;
    bit = b;
  }

  Node(stype word, vtype value, bit_t b, nptr left, nptr right) {
    k.first = word;
    k.second = value;
    bit = b;
    l = left;
    r = right;
  }

  ~Node() {
    l = nullptr;
    r = nullptr;
    k.first = "\0";
  };
};

bool get_bit(stype& key, bit_t bit_id) {
  bit_t byte_n = bit_id / 8;
  bit_t bit_n = bit_id % 8;
  bit_t symbol;
  if (bit_id < 0 || byte_n >= key.size()) {
    return false;
  } else {
    symbol = key[byte_n];
  }
  return (symbol & (128 >> bit_n)) != 0;
}

bit_t leftmost_bit(stype& key1, stype& key2) {
  bit_t i = 0;
  bit_t max_sz = max(key1.size(), key2.size());
  while (key1[i] == key2[i]) {
    i++;
    if (i == max_sz) {
      return i * 8;
    }
  }
  i = i * 8;
  while (get_bit(key1, i) == get_bit(key2, i)) {
    i++;
  }
  return i;
}

struct Trie {
  nptr header;

  Trie() { header = nullptr; }

  ~Trie() { destructR(header); }

  void destructR(nptr n) {
    if (n == nullptr) {
      return;
    } else if (n->l->bit > n->bit) {
      destructR(n->l);
    } else if (n->r != nullptr && n->r->bit > n->bit) {
      destructR(n->r);
    }
  }

  nptr search(stype& k) {
    if (header == nullptr) {
      cout << "NoSuchWord\n";
      return nullptr;
    }
    nptr p = this->header;
    nptr c = this->header->l;
    while (p->bit < c->bit) {
      p = c;
      c = get_bit(k, c->bit) ? c->r : c->l;
    }
    if (c->k.first.compare(k) == 0) {
      cout << "OK: " << c->k.second << '\n';
    } else {
      cout << "NoSuchWord\n";
      return nullptr;
    }
    return c;
  }

  nptr insert(stype k, vtype d) {
    if (this->header == nullptr) {
      auto newNode = new Node(k, d, 0, nullptr, nullptr);
      newNode->l = newNode;
      this->header = newNode;
      cout << "OK\n";
      return header;
    } else {
      nptr p;
      nptr t;
      nptr x;
      p = this->header;
      t = this->header->l;
      while ((p->bit < t->bit)) {
        p = t;
        t = (get_bit(k, t->bit) ? t->r : t->l);
      }
      if (t->k.first.compare(k) == 0) {
        cout << "Exist\n";
        return nullptr;
      }
      bit_t i = leftmost_bit(k, t->k.first);
      // cout << "!: " << i << "\n";
      p = this->header;
      x = this->header->l;
      auto newNode = new Node(k, d, i, nullptr, nullptr);
      while ((p->bit < x->bit) && (x->bit < newNode->bit)) {
        p = x;
        x = (get_bit(k, x->bit) ? x->r : x->l);
      }
      newNode->l = (get_bit(k, i) ? x : newNode);
      newNode->r = (get_bit(k, i) ? newNode : x);
      if (x == p->r) {
        p->r = newNode;
      } else {
        p->l = newNode;
      }
      cout << "OK\n";
      return t;
    }
  }

  bool remove(stype& k) {
    if (header == nullptr) {
      cout << "NoSuchWord\n";
      return false;
    }
    if (header->l == header) {  // header is an only node
      if (header->k.first.compare(k) == 0) {
        delete header;
        header = nullptr;
        cout << "OK\n";
        return true;
      } else {
        cout << "NoSuchWord\n";
        return false;
      }
    }
    nptr prePrev = nullptr, parOfPrev = nullptr, previous = header,
         current = header->l;
    while (previous->bit < current->bit) {
      prePrev = previous;
      previous = current;
      current = get_bit(k, current->bit) ? current->r : current->l;
    }
    if ((current->k.first).compare(k) != 0) {
      std::cout << "NoSuchWord\n";
      return false;
    }
    if (current == previous) {
      if (prePrev->l == current) {
        prePrev->l = (current->l == current ? current->r : current->l);
      } else {
        prePrev->r = (current->l == current ? current->r : current->l);
      }
      delete current;
      std::cout << "OK\n";
      return true;
    }
    nptr p = current, q = previous, qPar = prePrev, r = nullptr;
    current = header->l;
    r = header;
    while (r->bit < current->bit) {
      r = current;
      current = get_bit(q->k.first, current->bit) ? current->r : current->l;
    }
    bool flag = get_bit(r->k.first, q->bit);
    if (r->r == q) {
      r->r = p;
    } else {
      r->l = p;
    }
    if (qPar->r == q) {
      qPar->r = flag ? q->r : q->l;
    } else {
      qPar->l = flag ? q->r : q->l;
    }
    p->k.first = q->k.first;
    p->k.second = q->k.second;
    delete q;
    std::cout << "OK\n";
    return true;
  }

  int save(stype& filename) {
    ofstream file;
    file.open(filename, std::ios_base::binary | std::ios_base::out);
    if (this->header == nullptr) {
      char tmp[] = {"empty 0 -1\n"};
      if (!file.write(tmp, strlen(tmp))) {
        std::cout << "ERROR: can`t write to file\n";
        return -1;
      }
      std::cout << "OK\n";
      return 0;
    }
    if (!(file << this->header->k.first) ||
        !(file << ' ' << this->header->k.second << ' ' << this->header->bit
               << ' ' << 31415 << '\n')) {
      std::cout << "ERROR: can`t write to file\n";
      return -1;
    }
    if (this->header->l == header) {
      std::cout << "OK\n";
      return 0;
    }
    if (saveR(this->header->l, file) == 0) {
      std::cout << "OK\n";
      return 0;
    } else {
      std::cout << "ERROR: can`t write to file\n";
      return -1;
    }
  }

  int saveR(nptr node, std::ofstream& file) {
    if (!(file << node->k.first)) {
      return -1;
    }
    if (!(file << ' ' << node->k.second << ' ' << node->bit << ' ' << 31415
               << '\n')) {
      return -1;
    }
    int error = 0;
    if ((node->bit <= node->l->bit) && (node->l != node)) {
      error += saveR(node->l, file);
    }
    if ((node->bit <= node->r->bit) && (node->r != node)) {
      error += saveR(node->r, file);
    }
    if (error != 0) {
      return -1;
    }
    return 0;
  }

  int load(string filename) {
    std::ifstream file;
    file.open(filename, std::ios_base::binary | std::ios_base::in);
    stype keyRead;
    bit_t bitRead;
    vtype valRead;
    if (!(file >> keyRead)) {
      std::cout << "ERROR: wrong format\n";
      return -1;
    }
    if (keyRead == "empty") {
      keyRead = "\0";
      std::cout << "OK\n";
      return 0;
    }
    bit_t check;
    if (!(file >> valRead >> bitRead >> check)) {
      std::cout << "ERROR: wrong format\n";
      return -1;
    }
    if (check != 31415) {
      std::cout << "ERROR: wrong format\n";
      return -1;
    }
    nptr newNode = new Node(keyRead, valRead, 0);
    newNode->l = newNode;
    header = newNode;
    file.get();

    nptr p = this->header;
    nptr c = this->header->l;

    while (true) {
      stype keyRead;
      bit_t bitRead;
      vtype valRead;
      file >> keyRead;
      if (file.eof()) {
        std::cout << "OK\n";
        keyRead = "\0";
        return 0;
      }
      if (!(file >> valRead >> bitRead >> check)) {
        std::cout << "ERROR: wrong format\n";
        return -1;
      }
      if (check != 31415) {
        std::cout << "ERROR: wrong format\n";
        return -1;
      }
      file.get();
      while ((p->bit < c->bit) && (c->bit < bitRead)) {
        p = c;
        c = get_bit(keyRead, c->bit) ? c->r : c->l;
      }
      nptr tmpNode = new Node(keyRead, valRead, bitRead);
      tmpNode->l = get_bit(keyRead, bitRead) ? c : tmpNode;
      tmpNode->r = tmpNode->l == c ? tmpNode : c;
      if (get_bit(keyRead, p->bit)) {
        p->r = tmpNode;
      } else {
        p->l = tmpNode;
      }
      p = this->header;
      c = this->header->l;
    }
  }
};

void to_lowercase(stype& s) {
  for (size_t i = 0; s[i] != '\0'; ++i) {
    if (s[i] >= 'A' && s[i] <= 'Z') {
      s[i] = s[i] - 'A' + 'a';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  tptr t = new Trie;
  string s;
  string in;
  vtype v;
  while (cin >> s) {
    to_lowercase(s);
    if (s[0] == '+') {
      cin >> s >> v;
      to_lowercase(s);
      t->insert(s, v);
    } else if (s[0] == '-') {
      cin >> s;
      to_lowercase(s);
      t->remove(s);
    } else if (s[0] == '!') {
      cin >> s;
      if (s[0] == 'S') {
        cin >> in;
        t->save(in);
      } else {
        cin >> in;
        tptr new_t = new Trie();
        new_t->load(in);
        delete t;
        t = new_t;
      }
    } else {
      t->search(s);
    }
  }

  delete t;
  return 0;
}
