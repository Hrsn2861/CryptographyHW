#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const uint8_t InitialKeyPermutation[56] = {
    57,49,41,33,25,17,9,1,
    58,50,42,34,26,18,10,2,
    59,51,43,35,27,19,11,3,
    60,52,44,36,63,55,47,39,
    31,23,15,7,62,54,46,38,
    30,22,14,6,61,53,45,37,
    29,21,13,5,28,20,12,4,
};

const uint8_t C0[28] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
};

const uint8_t D0[28] = {
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4,
};

const uint8_t Shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

const uint8_t PC_2[48] = {
    14,17,11,24, 1, 5,
     3,28,15, 6,21,10,
    23,19,12, 4,26, 8,
    16, 7,27,20,13, 2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32,
};

const uint8_t IP[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17, 9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7,
};

const uint8_t IP_[64] = {
    40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,33,1,41, 9,49,17,57,25,
};

const uint8_t E[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1,
};

const uint8_t S[8][4][16] = {
    14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,

    15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,

    10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,

    7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,

    2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,

    12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,

    4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,

    13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11,
};

const uint8_t P[32] = {
    16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25,
};

uint8_t key[16][48];
uint8_t tmp[256];
uint8_t cd[56];

void displayAsHex(uint8_t *a, uint8_t len) {
    for (int i = 0; i < (len >> 2); i++)
        printf("%01x", (a[i << 2 | 0] << 3) | (a[i << 2 | 1] << 2) | (a[i << 2 | 2] << 1) | (a[i << 2 | 3]));
    printf("\n");
}

void lRotate(uint8_t *a, uint8_t len, uint8_t shift) {
    memcpy(tmp, a, len);
    memcpy(a, tmp + shift, (len - shift));
    memcpy(a + (len - shift), tmp, shift);
}

void createSubKey(const uint8_t* K) {
    uint8_t i, j;
    for (i = 0; i < 56; i++) {
        cd[i] = K[InitialKeyPermutation[i] - 1];
    }
    for (i = 0; i < 16; i++) {
        lRotate(cd, 28, Shift[i]);
        lRotate(cd + 28, 28, Shift[i]);
        uint8_t *currKey = key[i];
        for (j = 0; j < 48; j++) {
            currKey[j] = cd[PC_2[j] - 1];
        }
    }
}

uint8_t ext[48], ext_s[32];

void F_function(uint8_t *R, uint8_t *subkey) {
    uint8_t i, j;
    for (i = 0; i < 48; i++) {
        ext[i] = R[E[i] - 1] ^ subkey[i];
    }
    for (i = 0; i < 8; i++) {
        uint8_t *e = ext + (i * 6);
        uint8_t *es = ext_s + (i * 4);
        uint8_t row = (e[0] << 1) | (e[5]);
        uint8_t col = (e[1] << 3) | (e[2] << 2) | (e[3] << 1) | (e[4]);
        uint8_t ans = S[i][row][col];
        for (int j = 0; j < 4; j++)
            es[j] = (ans >> 3-j & 1);
    }
    for (i = 0; i < 32; i++)
        R[i] = ext_s[P[i] - 1];
}

uint8_t L[32], R[32];


void DES(uint8_t *plaintext, uint8_t *ciphertext, bool encrypto) {
    uint8_t i, j;
    for (i = 0; i < 32; i++) {
        L[i] = plaintext[IP[i] - 1];
        R[i] = plaintext[IP[i + 32] - 1];
    }
    for (i = 0; i < 16; i++) {
        memcpy(tmp, R, 32);
        if (encrypto) F_function(R, key[i]);
        else F_function(R, key[15 - i]);
        for (j = 0; j < 32; j++) {
            R[j] ^= L[j];
        }
        memcpy(L, tmp, 32);
    }
    for (i = 0; i < 64; i++) {
        if (IP_[i] <= 32) {
            ciphertext[i] = R[IP_[i] - 1];
        } else {
            ciphertext[i] = L[IP_[i] - 32 - 1];
        }
    }
}

uint8_t IV[64], keyword[64];
uint8_t plain[64], cipher[64];

char plaintext[40000], str[10];
uint8_t ciphertext[20000];

void readin() {
    freopen("../plaintext.txt", "r", stdin);
    scanf("%s", plaintext);
    fclose(stdin);
    freopen("IV.txt", "r", stdin);
    scanf("%s", str);
    for (int i = 0; i < 16; i++) {
        int buffer;
        if (str[i] <= '9' && str[i] >= '0') {
            buffer = str[i] - '0';
        } else {
            buffer = str[i] - 'a' + 10;
        }
        for (int j = 0; j < 4; j++)
            IV[i << 2 | j] = uint8_t(buffer >> 3-j & 1);
    }
    fclose(stdin);
    freopen("key.txt", "r", stdin);
    scanf("%s", str);
    for (int i = 0; i < 16; i++) {
        int buffer;
        if (str[i] <= '9' && str[i] >= '0') {
            buffer = str[i] - '0';
        } else {
            buffer = str[i] - 'a' + 10;
        }
        for (int j = 0; j < 4; j++)
            keyword[i << 2 | j] = uint8_t(buffer >> 3-j & 1);
    }
    fclose(stdin);
}

void Encrypt(uint8_t *plaintext, uint8_t *ciphertext) {
    for(int i=0;i<64;i++) {
        IV[i] ^= plaintext[i];
    }
    DES(IV, ciphertext, true);
    memcpy(IV, ciphertext, 64);
}

void run(uint8_t *plaintext, uint8_t *ciphertext, bool encrypto) {
    uint8_t i;
    if (encrypto) {
        for (i = 0; i < 64; i++) {
            IV[i] ^= plaintext[i];
        }
        DES(IV, ciphertext, 1);
        memcpy(IV, ciphertext, 64);
    } else {
        DES(ciphertext, plaintext, 0);
        for (i = 0; i < 64; i++) {
            plaintext[i] ^= IV[i];
        }
        memcpy(IV, ciphertext, 64);
    }
}

void generateRandomKey(bool isRandom) {
    srand((unsigned)time(NULL));
    if(isRandom) {
        for(int i=0;i<8;i++) {
            keyword[i] = rand() % 26 + 'a';
        }
    }
    else {
        keyword[0] = 0x5d;
        keyword[1] = 0x6d;
        keyword[2] = 0x3e;
        keyword[3] = 0xea;
        keyword[4] = 0x07;
        keyword[5] = 0x77;
        keyword[6] = 0xb5;
        keyword[7] = 0x34;
    }
}

void init() {
    generateRandomKey(false);
    createSubKey(keyword);
}

int main(int argc, const char* argv) {

    int size = argv[1];
    if(size == 0) {
        
    }

    readin();
    init();
    for (int i = 0; i < 16; i++)
        displayAsHex(key[i], 48);
    for (int i = 0; i < 16384; i += 8) {
        char *str = plaintext + (i << 1);
        uint8_t *c = ciphertext + i;
        for (int j = 0; j < 16; j++) {
            int buffer;
            if (str[j] <= '9' && str[j] >= '0') {
                buffer = str[j] - '0';
            } else {
                buffer = str[j] - 'a' + 10;
            }
            for (int k = 0; k < 4; k++)
                plain[j << 2 | k] = uint8_t(buffer >> 3-k & 1);
        }
        displayAsHex(plain, 64);
        run(plain, cipher, 1);
        displayAsHex(cipher, 64);
        for (int k = 0; k < 8; k++) {
            int buffer = 0;
            for (int j = 0; j < 8; j++)
                buffer = (buffer << 1 | cipher[k << 3 | j]);
            c[k] = char(buffer);
        }
    }
    freopen("des.txt", "w", stdout);
    fclose(stdout);

    return 0;
}