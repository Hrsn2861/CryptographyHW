#include <iostream>
using namespace std;

__uint8_t key[256];
__uint8_t T[256];
__uint8_t S[256];
int DATALENGTH = 1024;          // 明文的字节数

__uint8_t *plaindata;
__uint8_t *secret;

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

    for(int i=0;i<256;i++) {
        S[i] = i;
        T[i] = key[i % keysize];
    }
}

void Permutation() {
    int buf = 0;
    int tmp = 0;
    for(int i=0;i<256;i++) {
        buf = (buf + S[i] + T[i]) & 0xff;
        tmp = S[i];
        S[i] = S[buf];
        S[buf] = tmp;
    }
}

void generateKeyStream() {

    int x, y, tmp, t, k;

    for(int i=0;i<DATALENGTH;i++) {
        x = (x + 1) & 0xff;
        y = (y + S[x]) & 0xff;

        tmp = S[x];
        S[x] = S[y];
        S[y] = tmp;

        t = (S[x] + S[y]) & 0xff;
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

    cout << ((end-start)/CLOCKS_PER_SEC) << endl;
    return 0;
}
