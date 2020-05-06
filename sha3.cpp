#include <bits/stdc++.h>

using namespace std;

const uint64_t RC[24] = {   0x0000000000000001,
                            0x0000000000008082,
                            0x800000000000808A,
                            0x8000000080008000,
                            0x000000000000808B,
                            0x0000000080000001,
                            0x8000000080008081,
                            0x8000000000008009,
                            0x000000000000008A,
                            0x0000000000000088,
                            0x0000000080008009,
                            0x000000008000000A,
                            0x000000008000808B,
                            0x800000000000008B,
                            0x8000000000008089,
                            0x8000000000008003,
                            0x8000000000008002,
                            0x8000000000000080,
                            0x000000000000800A,
                            0x800000008000000A,
                            0x8000000080008081,
                            0x8000000000008080,
                            0x0000000080000001,
                            0x8000000080008008};

const uint64_t r[5][5] = {{0, 36, 3, 41, 18},
                        {1, 44, 10, 45, 2},
                        {62, 6, 43, 15, 61},
                        {28, 55, 25, 21, 56},
                        {27, 20, 39, 8, 14}};


// Circular shift "x" left by "n" bits                                    
uint64_t lRotate(const uint64_t &x,int n) {
    return ((x) << (n) | ((x) >> (64 - (n))));
}

// Converts a string of 0's and 1's to its equivalent character representation
uint8_t bin2char( const string& binary_string ) {
	int res = 0;
	for (uint32_t i=0;i<8;i++) {
		res <<= 1;
		res += binary_string[i] - '0';
	}
	return (uint8_t)res;
}

// Converts a character into its equivalent binary representation of exactly 8 bits and append it to "binary"
void char2bin( const uint8_t& c, vector<bool>& binary )
{
	string res;
	uint32_t c_bak = c;
    for(int i=0;i<8;i++) {
        res += (char)((c_bak & 1) + '0');
        c_bak >>= 1;
    }
	reverse( res.begin(), res.end() );
	for ( int i = 0; i < ( int )res.size(); i++ ) {
        if(res[i] == '1') binary.push_back(true);
        else binary.push_back(false);
	}
}

string uint2bin( const uint64_t& n ) {
	string res;
	uint64_t n_bak = n;
    for(int i=0;i<64;i++) {
        res += (char) ((n_bak & 1) + '0');
        n_bak >>= 1;
    }
	reverse( res.begin(), res.end() );
	return res;
}

uint64_t bin2uint( const vector<bool>& binary ) {
	uint64_t res = 0;
	for ( uint32_t i = 0; i < 64; i++ ) {
		res <<= 1;
		res += binary[i];
	}
	return res;
}

uint64_t str2uint( const string& s ) {
	vector<bool> s_binary;
	for ( int i = 0; i < 8; i++ ) {
		char2bin(s[i], s_binary);
	}
	return bin2uint(s_binary);
}

string bin2hex( const string& s ) {
    string res;
	static map<string, char> bin_to_hex_mapping;
	bin_to_hex_mapping["0000"] = '0'; bin_to_hex_mapping["0001"] = '1';
	bin_to_hex_mapping["0010"] = '2'; bin_to_hex_mapping["0011"] = '3';
	bin_to_hex_mapping["0100"] = '4'; bin_to_hex_mapping["0101"] = '5';
	bin_to_hex_mapping["0110"] = '6'; bin_to_hex_mapping["0111"] = '7';
	bin_to_hex_mapping["1000"] = '8'; bin_to_hex_mapping["1001"] = '9';
	bin_to_hex_mapping["1010"] = 'a'; bin_to_hex_mapping["1011"] = 'b';
	bin_to_hex_mapping["1100"] = 'c'; bin_to_hex_mapping["1101"] = 'd';
	bin_to_hex_mapping["1110"] = 'e'; bin_to_hex_mapping["1111"] = 'f';
	for ( uint32_t i = 0; i < s.size(); i += 4 ) {
		res += bin_to_hex_mapping[s.substr( i, 4 )];
	}
	return res;
}

// Reverses the order of bytes in the input string of exactly 8 characters
string reverse( const string& s ) {
	string bak = s;
    char buf;

    buf = bak[0]; bak[0] = bak[7]; bak[7] = buf;
    buf = bak[1]; bak[1] = bak[6]; bak[6] = buf;
    buf = bak[2]; bak[2] = bak[5]; bak[5] = buf;
    buf = bak[3]; bak[3] = bak[4]; bak[4] = buf;

	return bak;
}

// Reverses the order of bytes in the input
uint64_t reverse( const uint64_t& uint64 ) {
	string bin = uint2bin( uint64 );
	string s;
	for ( int i = 0; i < 64; i += 8 ) {
		s += bin2char( bin.substr( i, 8 ) );
	}
	assert( s.size() == 8 );
	s = reverse(s);
	return str2uint(s);
}


void round( vector<vector<uint64_t> >& S, const int& RC_index )
{
	vector<uint64_t> C( 5 );

	for ( int i = 0; i < 5; i++ ) {
		C[i] = S[i][0] ^ S[i][1] ^ S[i][2] ^ S[i][3] ^ S[i][4];
	}

	vector<uint64_t> D( 5 );
	for ( int i = 0; i < 5; i++ ) {
		D[i] = C[( i - 1 + 5 ) % 5] ^ lRotate( C[( i + 1 ) % 5], 1 );
	}

	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			S[i][j] ^= D[i];
		}
	}

	vector<vector<uint64_t> > B( 5, vector<uint64_t> ( 5, 0 ) );
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			B[j][( 2 * i + 3 * j ) % 5] = lRotate( S[i][j], r[i][j] );
		}
	}

	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			S[i][j] = B[i][j] ^ ( ( ~B[( i + 1 ) % 5][j] ) & B[( i + 2 ) % 5][j] );
		}
	}

	S[0][0] ^= RC[RC_index];
}

void keccak_f( vector<vector<uint64_t> >& S )
{
	for ( int i = 0; i < 24; i++ ) {
		round( S, i );
	}
}

string getBlock( const string& message, const int& block_index ) {
	return message.substr( block_index * 136, 136 );
}

string padMessage( const string& message ) {
	string res = message;
	uint32_t remaining = 1088 - ( ( message.size() * 8 ) % 1088 );
	if (remaining) {
		if (remaining == 8) {
			res += bin2char("10000110");
		}
		else {
			res += bin2char("00000110");
			res.append((remaining - 16) / 8, '\0');
			res += bin2char("10000000");
		}
	}
	return res;
}

string sha3( string message )
{
	message = padMessage(message);
	uint64_t message_block_count = (message.size() * 8) / 1088;
	vector<vector<uint64_t> > S(5, vector<uint64_t> (5, 0));
	for (uint32_t i = 0; i < message_block_count; i++) {
		string block = getBlock(message, i);
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (x + 5 * y < 17) {
					S[x][y] ^= str2uint( reverse( block.substr( ( x + 5 * y ) * 8, 8 ) ) );
				}
			}
		}
		keccak_f( S );
	}

	string digest;
	for (int y = 0, k = 0; y < 5; y++) {
		for ( int x = 0; x < 5; x++ ) {
			if ( x + 5 * y < 17 && k < 4 ) {
				digest += uint2bin( reverse( S[x][y] ) );
				k++;
			}
		}
	}
	return digest;
}

string generateRandomString(int size) {
    string ret;
    for(int i=0;i<size;i++) {
        ret += rand() % 26 + 'a';
    }
    return ret;
}

int main(int argc, char const *argv[]) {
    int size = atoi(argv[1]);
    if(size == 0) {
        string s = argv[2];
        cout << "input string is: " << s << endl;
        string digest = sha3(s);
        cout << "hash string is: " << bin2hex(digest) << endl;
        return 0;
    }

    else {
        string s = generateRandomString(size);
        if(size < 100) cout << "generate string is: " << s << endl;
        double start = clock();
        string digest = sha3(s);
        double end = clock();
        cout << "hash string is: " << bin2hex(digest) << endl;
        cout << ((end - start) / CLOCKS_PER_SEC);
        return 0;
    }
}
