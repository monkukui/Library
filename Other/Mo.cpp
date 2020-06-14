struct Mo {
  using ADD = function<void(int)>;
  using DEL = function<void(int)>;
  using REM = function<void(int)>;

  int width;
  vector<int> left, right, order;
  vector<bool> v;

  Mo(int n, int q) : width((int) sqrt(n)), order(q), v(n) {
    iota(begin(order), end(order), 0);
  }

  // [l, r)
  void add_query(int l, int r) {
    left.push_back(l);
    right.push_back(r);
  }

  int run(const ADD &add, const DEL &del, const REM &rem) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if(ablock != bblock) return ablock < bblock;
      if(ablock & 1) return right[a] < right[b];
      return right[a] > right[b];
    });
    int nl = 0, nr = 0;
    auto push = [&](int idx) {
      v[idx].flip();
      if(v[idx]) add(idx);
      else del(idx);
    };
    for(auto idx : order) {
      while(nl > left[idx]) push(--nl);
      while(nr < right[idx]) push(nr++);
      while(nl < left[idx]) push(nl++);
      while(nr > right[idx]) push(--nr);
      rem(idx);
    }
  }
};

/* テンプレ
  Mo mo(n, q);
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    l--;
    mo.add_query(l, r);
  }

  int sum = 0; // 区間内の種類数
  vector<int> ans(n);
  auto add = [&](int idx) {
    if (cnt[a[idx]] == 0) sum++;
    cnt[a[idx]]++;
  };
  auto del = [&](int idx) {
    if (cnt[a[idx]] == 1) sum--;
    cnt[a[idx]]--;
    assert(cnt[a[idx]] >= 0);
  };
  auto rem = [&](int idx) {
    ans[idx] = sum;
  };
  mo.run(add, del, rem);
  for (int i = 0; i < q; i++) {
    cout << ans[i] << endl;
  }
*/
