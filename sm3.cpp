#include <bits/stdc++.h>

using namespace std;

uint32_t H[8], G[8];
uint32_t w[68], w_buf[64];

uint32_t T(int i) {
    if (i >= 0 && i <= 15)
		return 0x79CC4519;
	else if (i >= 16 && i <= 63)
		return 0x7A879D8A;
	else
		return -1;
}

uint32_t* reverse(uint32_t *s) {
    uint8_t* byte;
    uint8_t buf;
    byte = (uint8_t*) s;

    buf = byte[0];
    byte[0] = byte[3];
    byte[3] = buf;

    buf  = byte[1];
    byte[1] = byte[2];
    byte[2] = buf;

    return s;
}

uint32_t FF(uint32_t x, uint32_t y, uint32_t z, int i) {
    if (i >= 0 && i <= 15)
		return x ^ y ^ z;
	else if (i >= 16 && i <= 63)
		return (x & y) | (x & z) | (y & z);
	else
        return 0;
}

uint32_t GG(uint32_t x, uint32_t y, uint32_t z, int i) {
    if (i >= 0 && i <= 15)
		return x ^ y ^ z;
	else if (i >= 16 && i <= 63)
		return (x & y) | (~x & z);
	else
		return 0;
}

uint32_t lRotate(uint32_t x, uint32_t f) {
    return (x) << (f) | (x) >> (32 - (f));
}

uint32_t P0(uint32_t x) {
    return x ^ lRotate(x, 9) ^ lRotate(x, 17);
}

uint32_t P1(uint32_t x) {
    return x ^ lRotate(x, 15) ^ lRotate(x, 23);
}

void initH() {
    H[0] = 0x7380166F, H[1] = 0x4914B2B9, H[2] = 0x172442D7, H[3] = 0xDA8A0600;
	H[4] = 0xA96F30BC, H[5] = 0x163138AA, H[6] = 0xE38DEE4D, H[7] = 0xB0FB0E4E;
}

void processString(const char *s) {
    for(int i=0;i<16;i++) {
        w[i] = *(uint32_t*) (s + i * 4);
        reverse(w+i);
    }

    for(int i=16;i<68;i++) {
        uint32_t t = w[i-16] ^ w[i-9] ^ lRotate(w[i-3], 15);
        w[i] = P1(t) ^ lRotate(w[i-13], 7) ^ w[i-6];
    }
    for(int i=0;i<64;i++) {
        w_buf[i] = w[i] ^ w[i+4];
    }

    G[0] = H[0]; G[1] = H[1]; G[2] = H[2]; G[3] = H[3];
    G[4] = H[4]; G[5] = H[5]; G[6] = H[6]; G[7] = H[7];

    uint32_t s1, s2, t1, t2;

    for(int i=0;i<64;i++) {
        s1 = lRotate((lRotate(G[0], 12) + G[4] + lRotate(T(i), i)), 7);
		s2 = s1 ^ lRotate(G[0], 12);
		t1 = FF(G[0], G[1], G[2], i) + G[3] + s2 + w_buf[i];
		t2 = GG(G[4], G[5], G[6], i) + G[7] + s1 + w[i];
		G[3] = G[2];
		G[2] = lRotate(G[1], 9);
		G[1] = G[0];
		G[0] = t1;
		G[7] = G[6];
		G[6] = lRotate(G[5], 19);
		G[5] = G[4];
		G[4] = P0(t2);
    }

    H[0] ^= G[0]; H[1] ^= G[1]; H[2] ^= G[2]; H[3] ^= G[3];
    H[4] ^= G[4]; H[5] ^= G[5]; H[6] ^= G[6]; H[7] ^= G[7];

}

char* sm3(const char* s) {
    initH();
    int length = strlen(s);
    char* buf = new char[length];
    uint32_t i;
    for(i=0;i<length/64;i++) {
        memcpy(buf, s+i*64, 64);
        processString(buf);
    }

    unsigned int remain = length % 64;
    unsigned int bitlen = length * 8;
    reverse(&bitlen);
    memcpy(buf, s + i * 64, remain);
    buf[remain] = 0x80;

    if(remain <= 55) {
        memset(buf+remain+1, 0, 59-remain);
        memcpy(buf+60, &bitlen, 4);
        processString(buf);
    }
    else {
        memset(buf+remain+1, 0, 63-remain);
        processString(buf);
        memset(buf, 0, 60);
        memcpy(buf+60, &bitlen, 4);
        processString(buf);
    }

    for(int i=0;i<8;i++) {
        reverse(H+i);
    }

    return (char*)H;
}

const char* lut = "0123456789abcdef";
char ans[64];

char* sm3_run(const char* s) {
    char* r = sm3(s);
    for(int i=0;i<32;i++) {
        ans[i*2] = lut[(r[i] >> 4) & 0xf];
        ans[i*2 + 1] = lut[r[i] & 0xf];
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
    
    int size = atoi(argv[1]);
    if(size == 0) {
        cout << "input string is: " << argv[2] << endl;
        cout << "output hash is: " << sm3_run(argv[2]) << endl;
        return 0;
    }
    else {
        char* s = generateRandomString(size);

		double start = clock();
		sm3(s);
        double end = clock();

		cout << ((end - start) / CLOCKS_PER_SEC) << endl;
        
        return 0;
    }
}

