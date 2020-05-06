#include <bits/stdc++.h>

#define block_len 512

using namespace std;

__uint32_t H[8], G[8], w[64];

const __uint32_t K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

char* padMessage(const char* s, __uint32_t &l) {
    __uint32_t orig = l = strlen(s);
	char* t = new char[l + block_len];
	memcpy(t, s, l);

	t[l++] = 0x80;                                          // pad 1 and several zeros
    
	while ((l << 3) % block_len != block_len - 64) {        // padding zeros
        l++;
    }

	l += 4;                                                 // first 32 bits are zeros
	for (int i = 24; i >= 0; i -= 8)
		t[l++] = (char)((orig << 3) >> i);                  // pad length to the end

	return t;
}

__uint32_t rRotate(const __uint32_t& t, const __uint32_t &f) {          // right rotate
    return (t >> f) | (t << (32 - f));
}

void initH() {
    H[0] = 0x6a09e667, H[1] = 0xbb67ae85, H[2] = 0x3c6ef372, H[3] = 0xa54ff53a;
	H[4] = 0x510e527f, H[5] = 0x9b05688c, H[6] = 0x1f83d9ab, H[7] = 0x5be0cd19;
}

char* sha(char *s, int len) {
    initH();
    char* ptr_w = (char*)(&w);
    for(int chunk=0;chunk<len;chunk+=64) {
        for(int i=0;i<64;i++) {
            ptr_w[i] = s[chunk | (i ^ 3)];
        }
        for(int i=16;i<64;i++) {
            __uint32_t s0 = rRotate(w[i-15], 7) ^ rRotate(w[i-15], 18) ^ (w[i-15] >> 3);
            __uint32_t s1 = rRotate(w[i-2], 17) ^ rRotate(w[i-2], 19) ^ (w[i-2] >> 10);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }
        memcpy(G, H, sizeof(H));
        for(int i=0;i<64;i++) {
            __uint32_t s0 = rRotate(G[0], 2) ^ rRotate(G[0], 13) ^ rRotate(G[0], 22);
            __uint32_t maj = (G[0] & G[1]) ^ (G[0] & G[2]) ^ (G[1] & G[2]);
            __uint32_t t2 = s0 + maj;
            __uint32_t s1 = rRotate(G[4], 6) ^ rRotate(G[4], 11) ^ rRotate(G[4], 25);
            __uint32_t ch = (G[4] & G[5]) ^ ((~G[4]) & G[6]);
            __uint32_t t1 = G[7] + s1 + ch + K[i] + w[i];
            G[7] = G[6], G[6] = G[5], G[5] = G[4], G[4] = G[3] + t1;
			G[3] = G[2], G[2] = G[1], G[1] = G[0], G[0] = t1 + t2;
        }
        H[0] += G[0], H[1] += G[1], H[2] += G[2], H[3] += G[3];
		H[4] += G[4], H[5] += G[5], H[6] += G[6], H[7] += G[7];
    }

    return (char*) H;
}

const char* lut = "0123456789abcdef";

char* sha_256(const char* s) {
	__uint32_t len = 0;
	char* padString = padMessage(s, len);
	char* r = sha(padString, len);
	char* ans = new char[64];
	for (int i = 0; i < 32; ++i) {
		unsigned char tmp = r[i ^ 3] & 0xff;
		ans[i << 1] = lut[tmp >> 4];
		ans[i << 1 | 1] = lut[tmp & 0xf];
	}
	return ans;
}

char* generateRandomString(int length) {
    char* ret = new char[length];
    for(int i=0;i<length;i++) {
        ret[i] = rand() % 26 + 'a';
    }
    return ret;
}

int main(int argc, char const *argv[]) {
	if (atoi(argv[1]) == 0) {
        cout << "input string is: " << argv[2] << endl;
        cout << "output hash is: " << sha_256(argv[2]) << endl;
        return 0;
    }
	else {
		int len = atoi(argv[1]);
		char* s = generateRandomString(len);

		double start = clock();
		sha_256(s);
        double end = clock();

		cout << ((end - start) / CLOCKS_PER_SEC) << endl;
        
        return 0;
	}
}