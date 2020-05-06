#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdbool>

using namespace std;

__uint32_t str2bin(const char *str) {
    __uint32_t result = 0;
    int len = strlen(str);
    for(int i=0;i<len;i++) {
        if(str[i] == '1')
            result = (result << 1) + 1;
        else
            result = result << 1;
    }
    return result;
}

bool getDn(__uint32_t list, __uint32_t cn, int seek) {
    bool dn = ((cn >> seek) & (list >> seek)) & 1;
    while((--seek) > -1) {
        dn ^= ((cn >> seek) & (list >> seek)) & 1;
    }
    return dn;
}



int main(int argc, char const *argv[]) {
    int size = strlen(argv[1]);
    __uint32_t bit = str2bin(argv[1]);
    int n = 0 ,ln = 0, m;
    __uint32_t fm = 0;
    __uint32_t f = 1;
    bool isZero, dn;
    __uint32_t fn_1;

    do {
        dn = getDn(bit >> (size - n - 1), f, ln);
        if(dn) {
            if(isZero) {
                m = n;
                fm = f;
                f = (1 << (n+1)) | 1;
                ln = n + 1;
            }
            else {
                fn_1 = f;
                f ^= fm << (n - m);
                if(ln < n + 1 - ln) {
                    m = n;
                    fm = fn_1;
                    ln = n + 1 - ln;
                }
            }
            if(ln != 0) {
                isZero = false;
            }
        }
        n++;
    } while(n < size);

    cout << "f(x) = 1";

    for(int i=1;i<size;i++)
        if((f >> i) & 1)
            cout << " + x^" << i;
    
    cout << endl;

    return 0;
}

