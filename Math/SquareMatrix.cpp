template<typename T,T MOD = 1000000007>
struct Mint{
    T v;
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

    static Mint comb(long long n,int k){
        Mint res(1);
        for(int i=0;i<k;i++){
            res*=Mint(n-i);
            res/=Mint(i+1);
        }
        return res;
    }
};

template<typename T>
struct SquareMatrix{
    
    vector<vector<T>> dat;
    size_t N;
    SquareMatrix() = default;
    SquareMatrix(size_t N, T val = T()):N(N){
        dat = vector<vector<T>> (N, vector<T> (N));
        for(size_t i=0;i<N;i++)
            for(size_t j=0;j<N;j++)
                dat[i][j]=val;
    }
    SquareMatrix& operator=(const SquareMatrix& a){
        dat=a.dat;
        return (*this);
    }
    bool operator==(const SquareMatrix& a) const{
        return dat==a.dat;
    }

    size_t size() const{return N;};
    vector<T>& operator[](size_t k){return dat[k];};
    const vector<T>& operator[](size_t k) const {return dat[k];};

    SquareMatrix operator*(const SquareMatrix &B) const{
        SquareMatrix res(N, 0);
        for(size_t i=0;i<N;i++)
            for(size_t j=0;j<N;j++)
                for(size_t k=0;k<N;k++)
                    res[i][j]=res[i][j]+(dat[i][k]*B[k][j]);
        return res;
    }

    SquareMatrix operator+(const SquareMatrix &B) const{
        SquareMatrix res(N, 0);
        for(size_t i=0;i<N;i++)
            for(size_t j=0;j<N;j++)
                res[i][j]=dat[i][j]+B[i][j];
        return res;
    }

    SquareMatrix pow(long long n) const{
        SquareMatrix a=*this;
        SquareMatrix res(N, 0);
        for(size_t i = 0; i < N; i++) res[i][i] = 1;    
        while(n){
            if(n&1) res=res*a;      
            a=a*a;      
            n>>=1;
        }
        return res;
    }
};
