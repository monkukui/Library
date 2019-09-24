// KM 法
struct KM {
  vector<int> a;
  KM(){}
  KM(const string &s) {
    a.resize(s.size() + 1,-1);
    for(int i=0,j=-1;i<s.size();a[++i]=++j)while(j>=0&&s[i]!=s[j])j=a[j];
  }
  int & operator [](int n) {return a[n];}
  int size() {return a.size();}
};
