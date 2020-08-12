// spoj FBRICK 
#include <iostream>
#include <stdio.h>
 
using namespace std;
 
#define LL long long
 
typedef LL mtxArray[4][4];
 
int T;
LL A2,N,M;
 
mtxArray emptyMtx = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
 
bool check = 0;
 
struct Matrix{
    mtxArray mtx;
    Matrix operator * (Matrix M2){
        Matrix newMtx;
        for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k){
                newMtx.mtx[i][j] += ((mtx[i][k]*M2.mtx[k][j]) % M);
                newMtx.mtx[i][j] += M;
                newMtx.mtx[i][j] %= M;
            }
        return newMtx;
    }
    Matrix(mtxArray arr = emptyMtx){
        for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j) mtx[i][j] = arr[i][j];
    }
    void modulo(){
        for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j) mtx[i][j] = ((mtx[i][j] % M) + M) % M;
    }
    void show(){
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j) cout << mtx[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
};
 
Matrix Base;
 
Matrix exponent(LL hat){
    if(hat <= 1) return Base;
    Matrix newMtx = exponent(hat/2);
    newMtx = newMtx * newMtx;
    if(hat % 2 > 0) newMtx = newMtx * Base;
    return newMtx;
}
 
//LL F[8234567],A[8234567];
 
/*void Cal(){
    
    A[1] = 1;
    A[2] = A2;
    cout << "N = " << N << endl;
    for(int i = 3; i <= N; ++i) {
        A[i] = ((2*A2*A[i - 1]) % M - A[i - 2]) % M;
        A[i] += M;
        A[i] %= M;
    }
    LL res = 0;
    for(int i = 1; i <= N; ++i) res = (res + A[i]*A[i]) % M;
    
    cout << "BruteForce : " << res << endl;
 
}*/
int main(){
 
//    freopen("FBRICK.INP","r",stdin);
//    freopen("FBRICK.OUT","w",stdout);
 
    cin >> T;
    for(int i = 1; i <= T; ++i){
        cin >> A2 >> N >> M;
 
        //cout << "____________________________________________________________________________________" << endl;
        //cout << "new Case " << N << " " << M << " " << A2 << endl;
 
        //Cal();
 
        mtxArray mm = {
            {1,0,0,0},
            {0,0,1,0},
            {1,1,((4*A2) % M)*A2,2*A2},
            {0,0,-4*A2,-1}
        };
        
        Base = Matrix(mm);
        Base.modulo();
 
        //cout << "Base matrix : " << endl;
        //Base.show();
 
        if(N == 2){
            cout << (1 + A2*A2) % M << endl;
            continue;
        }
 
        Matrix mat = exponent(N - 1);
        
        //cout << "Res Matrix : " << endl;
        //mat.show();
 
        LL res = (mat.mtx[0][0] + mat.mtx[1][0]) % M;
        LL r1 = (A2 * A2) % M;
        r1 *= mat.mtx[2][0];
        r1 %= M;
        LL r2 = (A2 * mat.mtx[3][0]) % M;
        res += (r1 + r2)%M;
        res %= M;
        
        cout << res << endl;
    
    }
 
    return 0;
} 
