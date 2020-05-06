#include <iostream>
using namespace std;

__uint8_t key[256];
__uint8_t T[256];
__uint8_t S[256];
int DATALENGTH = 1024;          // 明文的字节数

__uint8_t *plaindata;
__uint8_t *secret;

const char *lut = "0123456789abcdef";

void displayAsHex(__uint8_t* u, int length) {
    for(int i=0;i<length;i++) {
        cout << lut[u[i] >> 4] << lut[u[i] & 0xf];
    }
    cout << endl;
}

void init(int keysize, int isRandom) {
    
    if(isRandom) {
        for(int i=0;i<keysize;i++) {
            key[i] = rand() & 0xff;
        }
    }
    else {
        for(int i=0;i<keysize;i++) {
            key[i] = i & 0xff;
        }
    }

    cout << "key is: ";
    displayAsHex(key, keysize);

    for(int i=0;i<256;i++) {
        S[i] = i;
        T[i] = key[i % keysize];
    }
}

void Permutation() {
    int buf = 0;
    int tmp = 0;
    for(int i=0;i<256;i++) {
        buf = (buf + S[i] + T[i]) % 256;
        tmp = S[i];
        S[i] = S[buf];
        S[buf] = tmp;
    }
}

void generateKeyStream() {

    int x, y, tmp, t, k;

    for(int i=0;i<DATALENGTH;i++) {
        x = (x + 1) % 256;
        y = (y + S[x]) % 256;

        tmp = S[x];
        S[x] = S[y];
        S[y] = tmp;

        t = (S[x] + S[y]) % 256;
        k = S[t];
        secret[i] = k;
        plaindata[i] ^= S[t];
    }
}

int main(int argc, char const *argv[]) {

    DATALENGTH = atoi(argv[1]);
    plaindata = new __uint8_t[DATALENGTH];
    secret = new __uint8_t[DATALENGTH];

    init(128, true);
    Permutation();

    double start = clock();
    generateKeyStream();
    double end = clock();

    displayAsHex(secret, DATALENGTH);

    cout << ((end-start)/CLOCKS_PER_SEC) << endl;
    return 0;
}
