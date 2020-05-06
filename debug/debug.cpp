#include <bits/stdc++.h>
using namespace std;
static const int endianTest = 1;
#define IsLittleEndian() (*(char *)&endianTest == 1)

int main(int argc, char const *argv[])
{
    cout << IsLittleEndian() << endl;
    return 0;
}
