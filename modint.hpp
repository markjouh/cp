constexpr int MOD = 1e9 + 7; // 998244353

struct Mint {
    int v;

    Mint() : v(0) {}
    Mint(int64_t _v) {
        v = (-MOD < _v && _v < MOD ? _v : _v % MOD);
        if (v < 0) {
            v += MOD;
        }
    };

    Mint operator+(Mint b) { return Mint(v + b.v); }
    Mint operator-(Mint b) { return Mint(v - b.v); }
    Mint operator*(Mint b) { return Mint(1ll * v * b.v); }
    Mint operator/(Mint b) { return Mint(1ll * v * b.inv().v); }

    Mint pow(int e) {
        Mint b = *this;
        Mint ret = 1;
        while (e != 0) {
            if (e & 1) {
                ret = ret * b;
            }
            b = b * b;
            e >>= 1;
        }
        return ret;
    }

    Mint inv() {
        return pow(MOD - 2);
    }
};
