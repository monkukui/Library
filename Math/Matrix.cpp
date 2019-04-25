#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cmath>
#include <limits>
#include <cfloat>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <fstream>
#include <functional>
#include <bitset>

using namespace std;

template<typename T>
class Matrix{
    using arr = vector<T>;
    using mat = vector<arr>;
public:
    mat M_dat;
    Matrix(size_t r, size_t c):M_dat(r, arr(c, T())){}
    Matrix(mat dat):M_dat(dat){}
    Matrix(){}
    arr& operator[](size_t k){return M_dat[k];};
    const arr& operator[](size_t k) const {return M_dat[k];};
    
    Matrix operator*(Matrix a){
        size_t r_1 = this->M_dat.size();
        size_t c_1 = this->M_dat[0].size();
        size_t r_2 = a.M_dat.size();
        size_t c_2 = a.M_dat[0].size();
        assert(c_1 == r_2);
        
        Matrix<T> ret(r_1, c_2);
        for(size_t i = 0; i < r_1; i++){
            for(size_t j = 0; j < c_2; j++){
                for(size_t k = 0; k < c_1; k++){
                    ret[i][j] += this->M_dat[i][k] * a.M_dat[k][j];
                }
            }
        }

        return ret;
    };

    Matrix operator+(Matrix a){
        size_t r_1 = this->M_dat.size();
        size_t c_1 = this->M_dat[0].size();
        size_t r_2 = a.M_dat.size();
        size_t c_2 = a.M_dat[0].size();
        assert(r_1 == r_2 && c_1 == c_2);
        Matrix<T> ret(r_1, c_1);
        for(size_t i = 0; i < r_1; i++){
            for(size_t j = 0; j < c_1; j++){
                ret[i][j] = this->M_dat[i][j] + a.M_dat[i][j];
            }
        }

        return ret;
    }

    void show(){
        size_t r = this->M_dat.size();
        size_t c = this->M_dat[0].size();
        for(size_t i = 0; i < r; i++){
            for(size_t j = 0; j < c; j++){
                cerr << M_dat[i][j] << " ";
            }
            cerr << endl;
        }
    }
};


signed main(){
    vector<vector<double> > u(2, vector<double>(3, 2));
    vector<vector<double> > v(3, vector<double>(5, 1));
    Matrix<double> A(v);
    Matrix<double> B(u);
    Matrix<double> C = B * A;
    C.show();
    C = C + C;
    C.show();
    C = C + C + C + C;  
    C.show();
    return 0;
}

