long double pi = acos(-1);
class FFT{
    public:
    static void reorder(vector<complex<long double>> &A){
        ll n = A.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1){
                j ^= bit;
            }
            j ^= bit;
            if (i < j){
                swap(A[i], A[j]);
            }
        }
    }
    static void fft(vector<complex<long double>> &A, bool invert = false){
        ll n = A.size();
        if(n==1) return;
        reorder(A);
        for(ll sz=2; sz<=n; sz*=2){
            long double angle = ((2*pi)/sz) * (1-2*invert);
            complex<long double> sz_root(cos(angle), sin(angle));
            for(ll i=0; i<n; i+=sz){
                complex<long double> cur_w(1);
                rep(j, 0, sz/2){
                    complex<long double> ff = A[i+j], ss = A[i+j+sz/2]*cur_w;
                    A[i+j] = ff + ss;
                    A[i+j+sz/2] = ff - ss;
                    cur_w *= sz_root;
                }
            }
        }
        if(invert)
            for(auto &x: A)
                x/=n;
    }
    static vector <ll> multiply(vector <ll> &A, vector <ll> &B){
        vector<complex<long double>> dA(all(A)), dB(all(B));
        ll n = 1;
        while(n < A.size() + B.size())
        n *= 2;
        dA.resize(n);
        dB.resize(n);
        fft(dA);
        fft(dB);
        rep(i, 0, n)
            dA[i] *= dB[i];
        fft(dA, true);
        vector <ll> ans(n);
        rep(i, 0, n)
        ans[i] = round(dA[i].real());
        reverse(all(ans));
        while(ans.back() == 0) ans.pop_back();
        reverse(all(ans));
        return ans;
    }
};