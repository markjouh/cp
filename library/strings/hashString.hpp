// https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int64_t MOD = (1LL << 61) - 1;
const int64_t B = uniform_int_distribution<int64_t>(1E3, MOD - 1E3)(rng);

vector<int64_t> powB = {1};

struct hashPart {
    int64_t value;
    int len;

    hashPart(int64_t x, int y) : value(x), len(y) {}

    hashPart operator+(hashPart b) {
        return hashPart((__int128_t(value) * powB[b.len] + b.value) % MOD, len + b.len);
    }

    bool operator==(hashPart b) {
        return value == b.value && len == b.len;
    }
};

template<class T>
struct hashString {
    vector<int64_t> hash;

    hashString(T s) {
        hash.resize(int(s.size()) + 1);
        for (int i = 0; i < int(s.size()); i++) {
            hash[i + 1] = (__int128_t(hash[i]) * B + s[i]) % MOD;
        }
        while (int(powB.size()) < int(hash.size())) {
            powB.push_back(__int128_t(powB.back()) * B % MOD);
        }
    }

    hashPart getHash(int l, int r) {
        return hashPart(((hash[r] - __int128_t(hash[l]) * powB[r - l]) % MOD + MOD) % MOD, r - l);
    }

    hashPart getHash() {
        return getHash(0, hash.size() - 1);
    }
};
