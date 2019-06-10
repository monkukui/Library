template<typename T,T MOD = 1000000007>
struct Mint{
    T v;
    vector<Mint> fact;
    vector<Mint> fact_inv;
    Mint():v(0){}
    Mint(signed v):v(v){}
    Mint(long long t){v=t%MOD;if(v<0) v+=MOD;}

    Mint pow(long long k){
        Mint res(1),tmp(v);
        while(k){
            if(k&1) res*=tmp;
            tmp*=tmp;
            k>>=1;
        }
        return res;
    }

    static Mint add_identity(){return Mint(0);}
    static Mint mul_identity(){return Mint(1);}

    Mint inv(){return pow(MOD-2);}

    Mint& operator+=(Mint a){v+=a.v;if(v>=MOD)v-=MOD;return *this;}
    Mint& operator-=(Mint a){v+=MOD-a.v;if(v>=MOD)v-=MOD;return *this;}
    Mint& operator*=(Mint a){v=1LL*v*a.v%MOD;return *this;}
    Mint& operator/=(Mint a){return (*this)*=a.inv();}

    Mint operator+(Mint a) const{return Mint(v)+=a;};
    Mint operator-(Mint a) const{return Mint(v)-=a;};
    Mint operator*(Mint a) const{return Mint(v)*=a;};
    Mint operator/(Mint a) const{return Mint(v)/=a;};

    Mint operator-() const{return v?Mint(MOD-v):Mint(v);}

    bool operator==(const Mint a)const{return v==a.v;}
    bool operator!=(const Mint a)const{return v!=a.v;}
    bool operator <(const Mint a)const{return v <a.v;}
    
    Mint comb(long long n,int k){
        Mint res(1);
        for(int i=0;i<k;i++){
            res*=Mint(n-i);
            res/=Mint(i+1);
        }
        return res;
    }
};

struct Math{
    
    using M = Mint<long long>;
    vector<M> fac;
    vector<M> finv;
    vector<M> inv;
    Math(long long MAX_N = 510000){
        fac = vector<M>(MAX_N);
        finv = vector<M>(MAX_N);
        inv = vector<M>(MAX_N);
        fac[0] = fac[1] = M(1);
        finv[0] = finv[1] = M(1);
        inv[1] = M(1);
        cout << "ok" << endl;
        for(long long i = 2; i < MAX_N; i++){
            fac[i] = fac[i - 1] * M(i);
            inv[i] = M(i).inv();
            finv[i] = finv[i - 1] * inv[i];
        }
        cout << "ok" << endl;
    }

    long long comb(long long n, long long r){
        if(n < r) return 0;
        if(n < 0 || r < 0) return 0;
        return (fac[n] * finv[r] * finv[n - r]).v;
    }
};
