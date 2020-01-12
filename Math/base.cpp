
const long long MAXN = 1001024;

// a, b の最大公約数を返す O( log max(a, b) )
long long gcd(long long a, long long b) {
  if(b == 0) return a;
  return gcd(b, a % b);
}

// ax + by = 1 となるような (x, y) と gcd(a, b) を返す. gcd(a, b) = 1 の時、解が存在する.
long long extgcd(long long a, long long b, long long &x, long long &y){
  long long d = a;
  if(b != 0){
    d = extgcd(b, a, y, x);
    y -= (a / b) * x;
  }else{
    x = 1;
    y = 0;
  }
  return d;
}


// 区間 [a, b) に存在する素数の個数を返す関数

long long prime[MAXN];        // [a,b) の素数のうち i 番目の素数
bool is_prime[MAXN];    // 整数 i が素数であるかどうか
bool is_prime_ab[MAXN]; // 整数 i+a が素数であるかどうか

long long sieve(long long n) {
  long long res = 0; fill(is_prime, is_prime + MAXN, true);
  is_prime[0] = is_prime[1] = false; // 0 と 1 は素数ではない。
  for(long long i = 2; i <= n; ++i) {
    if(!is_prime[i]) continue;
    prime[res++] = i;
    for(long long j = 2 * i; j <= n; j += i) is_prime[j] = false; // 素数 i の倍数は素数ではない (ふるい(篩)にかける)
  }
  return res;
}

/*
long long segment_sieve(long long a, long long b){
  fill(is_prime, is_prime + MAXN, true);
  fill(is_prime_ab, is_prime_ab + MAXN, true);
  for(long long i = 2; i * i <= b - 1; i++) {
    if(!is_prime[i]) continue;
    for(long long j = 2 * i; j * j <= b - 1; j += i) is_prime[j] = false; // 素数 i で篩にかける
    for(long long j = a - a % i; j < b; j += i) {
      if(j < a) continue;
      if(is_prime_ab[j-a]) is_prime_ab[j-a] = false; // 素数 i で篩にかける
    }
  }

  long long res = 0;
  for(long long i = a; i < b; i++) if(is_prime_ab[i - a]) prime[res++] = i;
  return res;
}
*/

// ある整数の約数列挙
vector<long long> divisors(long long n) {
  vector<long long> res;
  for(long long i = 1; i*i <= n; ++i) {
    if(n % i != 0) continue;
    res.push_back(i);
    if(n/i == i) continue; // 上の行で追加済み。
    res.push_back(n/i);
  }
  return res;
}


// 素因数分解
map<long long, long long> prime_factors(long long n) {
  map<long long, long long> res;
  if(n == 1) { // n=1 の素因数分解は n^1
    res[n] = 1;
    return res;
  }
  for(long long i = 2, _n = n; i*i <= _n; ++i) {
    while(n % i == 0) {
      ++res[i]; // 素数i^{res[i]}
      n /= i;
    }
  }
  if(n != 1) res[n] = 1;
  return res;
}


// 繰り返し 2 乗法
long long modpow(long long a, long long n) {
  long long res = 1;
  while (n > 0) {
    if (n & 1) res = res * a % MOD;
    a = a * a % MOD;
    n >>= 1;
  }
  return res;
}


// 逆元を求める. a と m は互いに素であることが要請される.
long long modinv(long long a, long long m) {
  long long b = m, u = 1, v = 0;
  while(b){
    long long t = a / b;
    a -= t * b; swap(a, b);
    u -= t * v; swap(u, v);
  }
  u %= m; 
  if (u < 0) u += m;
  return u;
}

long long fac[MAXN], finv[MAXN], inv[MAXN];

// 前処理 O(n)
void math_init(){
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for(long long i = 2; i < MAXN; i++){
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
    finv[i] = finv[i - 1] * inv[i] % MOD;
  }
}

// 二項係数計算 O(1)
long long COM(long long n, long long k){
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}


// before your coding, you have to write a line "math_init()"
