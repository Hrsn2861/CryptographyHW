#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

int InitialPermutationTable[] =	   {58, 50, 42, 34, 26, 18, 10, 2,
                                        60, 52, 44, 36, 28, 20, 12, 4,
                                        62, 54, 46, 38, 30, 22, 14, 6,
                                        64, 56, 48, 40, 32, 24, 16, 8,
                                        57, 49, 41, 33, 25, 17,  9, 1,
                                        59, 51, 43, 35, 27, 19, 11, 3,
                                        61, 53, 45, 37, 29, 21, 13, 5,
                                        63, 55, 47, 39, 31, 23, 15, 7};

int InitialKeyPermutation[] = {57, 49,  41, 33,  25,  17,  9,
								 1, 58,  50, 42,  34,  26, 18,
								10,  2,  59, 51,  43,  35, 27,
								19, 11,   3, 60,  52,  44, 36,
								63, 55,  47, 39,  31,  23, 15,
								 7, 62,  54, 46,  38,  30, 22,
								14,  6,  61, 53,  45,  37, 29,
								21, 13,   5, 28,  20,  12,  4};

int shiftTable[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int SubKeyPermutationTable[] =    {14, 17, 11, 24,  1,  5,
								 3, 28, 15,  6, 21, 10,
								23, 19, 12,  4, 26,  8,
								16,  7, 27, 20, 13,  2,
								41, 52, 31, 37, 47, 55,
								30, 40, 51, 45, 33, 48,
								44, 49, 39, 56, 34, 53,
								46, 42, 50, 36, 29, 32};

int MessageExpansionTable[] =  {32,  1,  2,  3,  4,  5,
							 4,  5,  6,  7,  8,  9,
							 8,  9, 10, 11, 12, 13,
							12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21,
							20, 21, 22, 23, 24, 25,
							24, 25, 26, 27, 28, 29,
							28, 29, 30, 31, 32,  1};

int sBoxPermutationTable[8][4][16] = {
	{
		14, 4, 13, 1, 1, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
	},
	{
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
	},
	{
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
	},
	{
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
	},
	{
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
	},
	{
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
	},
	{
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
	},
	{
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 13, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
	}
};

int RightSubMessagePermutation[] =  {16,  7, 20, 21, 29, 12, 28, 17,
                                        1,  15, 23, 26, 5,  18, 31, 10,
                                        2,  8,  24, 14, 32, 27,  3,  9,
                                        19, 13, 30,  6, 22, 11,  4, 25};

int InversePermutationTable[] =  {40,  8, 48, 16, 56, 24, 64, 32,
									39,  7, 47, 15, 55, 23, 63, 31,
									38,  6, 46, 14, 54, 22, 62, 30,
									37,  5, 45, 13, 53, 21, 61, 29,
									36,  4, 44, 12, 52, 20, 60, 28,
									35,  3, 43, 11, 51, 19, 59, 27,
									34,  2, 42, 10, 50, 18, 58, 26,
									33,  1, 41,  9, 49, 17, 57, 25};

void display(bool subkeys[16][48]) {
    for(int i=0;i<16;i++) {
        for(int j=0;j<48;j++)
            cout << subkeys[i][j] << " ";
        cout << endl;
    }
}

void display(char *seq, int length) {
    for(int i=0;i<length;i++) {
        cout << (char)seq[i];
    }
    cout << endl;
}

void display(bool* byte, int length) {
    for(int i=0;i<length;i++) {
        cout << byte[i] << " ";
        if(i % 8 == 7) cout << endl;
    }
    cout << endl;
}

void createSubKey(char keyWord[8]);
void shiftLeft(bool *key, int length, int size);
void Transform(bool *subKey, bool *mainKey,const int *changeTable, int size);
void run(char *plainChar, char *cipherChar, bool isEncrypt);
void char2byte(bool *out, const char *in, int size);
void byte2char(char *out, const bool *in, int size);
void F_function(bool in[32], bool ki[48]);
void S_function(bool out[32], bool in[48]);
void Xor(bool *out, bool *in, int size);
void generateRandKey(bool isRandom);
string plaintext = "";
string ciphertext = "";
char keyword[8];
bool SubKey[16][48];

string Encrypt(string plain) {
    plaintext = plain;
    ciphertext = "";
    char plainChar[12];
    char cipherChar[12];
    for(int i=0;i<plain.size();i+=8) {
        strcpy(plainChar, plain.substr(i, 8).c_str());
        memset(cipherChar, 0, sizeof(plainChar));
        run(plainChar, cipherChar, true);
        ciphertext += cipherChar;
    }
    return ciphertext;
}

string Decrypt(string cipher) {
    plaintext = "";
    char plainChar[12];
    char cipherChar[12];
    for(int i=0;i<cipher.size();i+=8) {
        strcpy(cipherChar, cipher.substr(i, 8).c_str());
        memset(plainChar, 0, sizeof(cipherChar));
        run(cipherChar, plainChar, false);
        plaintext += plainChar;
    }
    return plaintext;
}

void run(char in[8], char out[8], bool isEncrypt) {
    static bool M[64], buffer[32];
    static bool *Li = &M[0];
    static bool *Ri = &M[32];
    char2byte(M, in, 64);
    Transform(M, M, InitialPermutationTable, 64);
    if(isEncrypt) {
        for(int i=0;i<16;i++) {
            memcpy(buffer, Ri, 32);
            F_function(Ri, SubKey[i]);
            Xor(Ri, Li, 32);
            memcpy(Li, buffer, 32);
        }
        for (int i=0;i<32;i++) {
            bool temp=M[i];
            M[i]=M[i+32];
            M[i+32]=temp;
        }
    }
    else {
        for (int i=0;i<32;i++) {
            bool temp=M[i];
            M[i]=M[i+32];
            M[i+32]=temp;
        }
        for(int i=15;i>=0;i--) {
            memcpy(buffer, Li, 32);
            F_function(Li, SubKey[i]);
            Xor(Li, Ri, 32);
            memcpy(Ri, buffer, 32);
        }
    }
    Transform(M, M, InversePermutationTable, 64);
    byte2char(out, M, 64);
}

void byte2char(char *out, const bool *in, int size) {
    memset(out, 0, (size+7)/8);
    for(int i=0;i<size;i++) {
        out[i/8] |= in[i] << (i % 8);
    }
}

void F_function(bool in[32], bool ki[32]) {
    static bool T[48];
    Transform(T, in, MessageExpansionTable, 48);
    Xor(T, ki, 48);
    S_function(in, T);
    Transform(in, in, RightSubMessagePermutation, 32);
}

void S_function(bool out[32], bool in[48]) {
    int j;
    char m, n, num;
    for(j=0;j<8;j++,in+=6,out+=4) {
        m = (in[0] << 1) + in[5];
        n = (in[1] << 3) + (in[2] << 2) + (in[3] << 1) + in[4];
        num = sBoxPermutationTable[j][(int)m][(int)n];
        char2byte(out, &num, 4);
    }
}

void Xor(bool *out, bool *in, int size) {
    for(int i=0;i<size;i++) {
        out[i] ^= in[i];
    }
}

void char2byte(bool *out, const char *in, int size) {
    for(int i=0;i<size;i++) {
        out[i] = (in[i/8]>>(i%8))&1;
    }
}

void Transform(bool *subKey, bool *mainKey, const int *changeTable, int size) {
    static bool buffer[256];
    for(int i=0;i<size;i++) {
        buffer[i] = mainKey[changeTable[i]-1];
    }
    memcpy(subKey, buffer, size);
}

void shiftLeft(bool *key, int length, int size) {
    static bool buffer[256];
    memcpy(buffer, key, size);
    memcpy(key, key+size, length-size);
    memcpy(key+length-size, buffer, size);
}

void createSubKey(char keyWord[8]) {
    char keys[8];
    for(int i=0;i<8;i++) {
        keys[i] = keyWord[i];
    }
    static bool K[64];
    static bool *KL = &K[0];
    static bool *KR = &K[28];
    char2byte(K, keys, 64);
    Transform(K, K, InitialKeyPermutation, 56);
    for(int i=0;i<16;i++) {
        shiftLeft(KL, 28, shiftTable[i]);
        shiftLeft(KR, 28, shiftTable[i]);
        Transform(SubKey[i], K, SubKeyPermutationTable, 48);
    }
}

void generateRandKey(bool isRandom) {
    srand((unsigned)time(NULL));
    if(isRandom) {
        for(int i=0;i<8;i++) {
            keyword[i] = rand() % 26 + 'a';
        }
    }
    else {
        for(int i=0;i<8;i++) {
            keyword[i] = 'a';
        }
    }
}

void init(bool isRandom) {
    generateRandKey(isRandom);
    createSubKey(keyword);
}

const char* lut = "0123456789abcdefg";

void displayAsHex(string s) {
    for(int i=0;i<s.size();i++) {
        uint8_t buf = s[i];
        cout << lut[((buf >> 4) & 0xf)] << lut[(buf & 0xf)];
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    init(false);
    int size = atoi(argv[1]);
    if(size == 0) {
        const char* input = argv[2];
        cout << "key is: "; display(keyword, 8);
        cout << "input string is: " << input << endl;
        string s = Encrypt(input);
        cout << "Encrypt hex string is: ";
        displayAsHex(s);
        cout << "Decrypt string is: " << Decrypt(s) << endl;
        return 0;
    }
    else {
        char* input = new char[size];
        for(int i=0;i<size;i++) {
            input[i] = rand() % 26 + 'a';
        }

        double start = clock();
        string s = Encrypt(input);
        double end = clock();

        cout << ((end - start) / CLOCKS_PER_SEC) << endl;
        return 0;
    }
}
