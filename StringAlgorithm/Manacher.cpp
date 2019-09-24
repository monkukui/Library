struct Manacher {
  vector<int> a;
  Manacher(){}
  Manacher(const string &s) {
    a.resize(s.size());
    int i = 0, j = 0;
    while (i < s.size()) {
      while (i-j >= 0 && i+j < s.size() && s[i-j] == s[i+j]) ++j;
      a[i] = j;
      int k = 1;
      while (i-k >= 0 && i+k < s.size() && k+a[i-k] < j) a[i+k] = a[i-k], ++k;
      i += k; j -= k;
    }
  }
  int & operator [](int n) {return a[n];}
  int size() {return a.size();}
};
