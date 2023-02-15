#include <bit>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

typedef unsigned char byte_t;

class Md5
{
protected:
	unsigned int m_hash[4];
	unsigned int m_len_low;
	unsigned int m_len_high;
	union
	{
		unsigned char b8[64];
		unsigned int b32[16];
	} m_in;

public:
	Md5();

	void Reset();
	void ComputeHash(const std::string& str);
	void ComputeHash(const byte_t* data, size_t size);

	std::vector<byte_t> Finalize();

protected:
	void Transform();
};

#pragma intrinsic(std::rotl)
#pragma intrinsic(std::rotr)

#define rotlFixed(x, n) std::rotl((x), (n))
#define rotrFixed(x, n) std::rotr((x), (n))

#define byteReverse(buf, length)    // No-op

Md5::Md5()
{
	Reset();
}

void Md5::Reset()
{
	memset(m_in.b8, 0, sizeof(m_in.b8));

	m_hash[0] = 0x67452301; // a
	m_hash[1] = 0xefcdab89; // b
	m_hash[2] = 0x98badcfe; // c
	m_hash[3] = 0x10325476; // d

	m_len_low = 0;
	m_len_high = 0;
}

void Md5::ComputeHash(const std::string& str)
{
	ComputeHash(reinterpret_cast<const byte_t*>(str.c_str()), str.size());
}

void Md5::ComputeHash(const byte_t* buf, size_t size)
{
	if (size > INT32_MAX)
		return;

	unsigned int len = static_cast<unsigned int>(size);

	// Update bit count
	unsigned int tempLow = m_len_low;
	m_len_low = tempLow + (len << 3);
	if (m_len_low < tempLow)
		++ m_len_high;     // Carry from low to high.

	m_len_high += len >> 29;

	tempLow = (tempLow >> 3) & 0x3f;	// Bytes already in shsInfo->data.

	// Handle any leading odd-sized chunks.
	if (tempLow)
	{
		unsigned char* p = m_in.b8 + tempLow;
		const unsigned int cb = sizeof(m_in.b8) - tempLow;

		tempLow = 64 - tempLow;
		if (len < tempLow)
		{
			memcpy(p, buf, len);
			return;
		}

		memcpy(p, buf, tempLow);

		byteReverse(m_in.b32, 16);
		Transform();
		buf += tempLow;
		len -= tempLow;
	}

	// Process data in 64-byte chunks
	while (len >= 64)
	{
		memcpy(m_in.b8, buf, 64);
		byteReverse(m_in.b32, 16);
		Transform();
		buf += 64;
		len -= 64;
	}

	// Handle any remaining bytes of data.
	memcpy(m_in.b8, buf, len);
}

std::vector<byte_t> Md5::Finalize()
{
	// Compute number of bytes mod 64.
	unsigned int count = (m_len_low >> 3) & 0x3F;

	// Set the first char of padding to 0x80.  This is safe since there is
	// always at least one byte free.
	unsigned char* p = m_in.b8 + count;
	*p++ = 0x80;

	// Bytes of padding needed to make 64 bytes.
	count = 64 - 1 - count;

	// Pad out to 56 mod 64.

	if (count < 8)
	{
		// Two lots of padding:  Pad the first block to 64 bytes.
		memset(p, 0, count);
		byteReverse(m_in.b32, 16);
		Transform();

		// Now fill the next block with 56 bytes.
		memset(m_in.b8, 0, 56);
	}
	else
	{
		// Pad block to 56 bytes.
		memset(p, 0, count - 8);
	}

	byteReverse (m_in.b32, 14);

	// Append length in bits and transform.
	m_in.b32[14] = m_len_low;
	m_in.b32[15] = m_len_high;

	Transform();

	byteReverse(m_hash, 4);

	constexpr size_t c_digest_size = sizeof(m_hash);
	std::vector<byte_t> digest(c_digest_size);
	memcpy(digest.data(), m_hash, c_digest_size);

	Reset();

	return digest;
}

inline unsigned int f1(unsigned int x, unsigned int y, unsigned int z) { return z ^ (x & (y ^ z)); }
inline unsigned int f2(unsigned int x, unsigned int y, unsigned int z) { return f1(z, x, y); }
inline unsigned int f3(unsigned int x, unsigned int y, unsigned int z) { return x ^ y ^ z; }
inline unsigned int f4(unsigned int x, unsigned int y, unsigned int z) { return y ^ (x | ~z); }

inline void md5step(unsigned int f, unsigned int& w, unsigned int x, unsigned int data, unsigned int s)
{
	w += f + data;
	w  = rotlFixed(w, s);
	w += x;
}

void Md5::Transform()
{
	unsigned int a = m_hash[0];
	unsigned int b = m_hash[1];
	unsigned int c = m_hash[2];
	unsigned int d = m_hash[3];

	md5step(f1(b,c,d), a, b, m_in.b32[ 0] + 0xd76aa478,  7);
	md5step(f1(a,b,c), d, a, m_in.b32[ 1] + 0xe8c7b756, 12);
	md5step(f1(d,a,b), c, d, m_in.b32[ 2] + 0x242070db, 17);
	md5step(f1(c,d,a), b, c, m_in.b32[ 3] + 0xc1bdceee, 22);
	md5step(f1(b,c,d), a, b, m_in.b32[ 4] + 0xf57c0faf,  7);
	md5step(f1(a,b,c), d, a, m_in.b32[ 5] + 0x4787c62a, 12);
	md5step(f1(d,a,b), c, d, m_in.b32[ 6] + 0xa8304613, 17);
	md5step(f1(c,d,a), b, c, m_in.b32[ 7] + 0xfd469501, 22);
	md5step(f1(b,c,d), a, b, m_in.b32[ 8] + 0x698098d8,  7);
	md5step(f1(a,b,c), d, a, m_in.b32[ 9] + 0x8b44f7af, 12);
	md5step(f1(d,a,b), c, d, m_in.b32[10] + 0xffff5bb1, 17);
	md5step(f1(c,d,a), b, c, m_in.b32[11] + 0x895cd7be, 22);
	md5step(f1(b,c,d), a, b, m_in.b32[12] + 0x6b901122,  7);
	md5step(f1(a,b,c), d, a, m_in.b32[13] + 0xfd987193, 12);
	md5step(f1(d,a,b), c, d, m_in.b32[14] + 0xa679438e, 17);
	md5step(f1(c,d,a), b, c, m_in.b32[15] + 0x49b40821, 22);

	md5step(f2(b,c,d), a, b, m_in.b32[ 1] + 0xf61e2562,  5);
	md5step(f2(a,b,c), d, a, m_in.b32[ 6] + 0xc040b340,  9);
	md5step(f2(d,a,b), c, d, m_in.b32[11] + 0x265e5a51, 14);
	md5step(f2(c,d,a), b, c, m_in.b32[ 0] + 0xe9b6c7aa, 20);
	md5step(f2(b,c,d), a, b, m_in.b32[ 5] + 0xd62f105d,  5);
	md5step(f2(a,b,c), d, a, m_in.b32[10] + 0x02441453,  9);
	md5step(f2(d,a,b), c, d, m_in.b32[15] + 0xd8a1e681, 14);
	md5step(f2(c,d,a), b, c, m_in.b32[ 4] + 0xe7d3fbc8, 20);
	md5step(f2(b,c,d), a, b, m_in.b32[ 9] + 0x21e1cde6,  5);
	md5step(f2(a,b,c), d, a, m_in.b32[14] + 0xc33707d6,  9);
	md5step(f2(d,a,b), c, d, m_in.b32[ 3] + 0xf4d50d87, 14);
	md5step(f2(c,d,a), b, c, m_in.b32[ 8] + 0x455a14ed, 20);
	md5step(f2(b,c,d), a, b, m_in.b32[13] + 0xa9e3e905,  5);
	md5step(f2(a,b,c), d, a, m_in.b32[ 2] + 0xfcefa3f8,  9);
	md5step(f2(d,a,b), c, d, m_in.b32[ 7] + 0x676f02d9, 14);
	md5step(f2(c,d,a), b, c, m_in.b32[12] + 0x8d2a4c8a, 20);

	md5step(f3(b,c,d), a, b, m_in.b32[ 5] + 0xfffa3942,  4);
	md5step(f3(a,b,c), d, a, m_in.b32[ 8] + 0x8771f681, 11);
	md5step(f3(d,a,b), c, d, m_in.b32[11] + 0x6d9d6122, 16);
	md5step(f3(c,d,a), b, c, m_in.b32[14] + 0xfde5380c, 23);
	md5step(f3(b,c,d), a, b, m_in.b32[ 1] + 0xa4beea44,  4);
	md5step(f3(a,b,c), d, a, m_in.b32[ 4] + 0x4bdecfa9, 11);
	md5step(f3(d,a,b), c, d, m_in.b32[ 7] + 0xf6bb4b60, 16);
	md5step(f3(c,d,a), b, c, m_in.b32[10] + 0xbebfbc70, 23);
	md5step(f3(b,c,d), a, b, m_in.b32[13] + 0x289b7ec6,  4);
	md5step(f3(a,b,c), d, a, m_in.b32[ 0] + 0xeaa127fa, 11);
	md5step(f3(d,a,b), c, d, m_in.b32[ 3] + 0xd4ef3085, 16);
	md5step(f3(c,d,a), b, c, m_in.b32[ 6] + 0x04881d05, 23);
	md5step(f3(b,c,d), a, b, m_in.b32[ 9] + 0xd9d4d039,  4);
	md5step(f3(a,b,c), d, a, m_in.b32[12] + 0xe6db99e5, 11);
	md5step(f3(d,a,b), c, d, m_in.b32[15] + 0x1fa27cf8, 16);
	md5step(f3(c,d,a), b, c, m_in.b32[ 2] + 0xc4ac5665, 23);

	md5step(f4(b,c,d), a, b, m_in.b32[ 0] + 0xf4292244,  6);
	md5step(f4(a,b,c), d, a, m_in.b32[ 7] + 0x432aff97, 10);
	md5step(f4(d,a,b), c, d, m_in.b32[14] + 0xab9423a7, 15);
	md5step(f4(c,d,a), b, c, m_in.b32[ 5] + 0xfc93a039, 21);
	md5step(f4(b,c,d), a, b, m_in.b32[12] + 0x655b59c3,  6);
	md5step(f4(a,b,c), d, a, m_in.b32[ 3] + 0x8f0ccc92, 10);
	md5step(f4(d,a,b), c, d, m_in.b32[10] + 0xffeff47d, 15);
	md5step(f4(c,d,a), b, c, m_in.b32[ 1] + 0x85845dd1, 21);
	md5step(f4(b,c,d), a, b, m_in.b32[ 8] + 0x6fa87e4f,  6);
	md5step(f4(a,b,c), d, a, m_in.b32[15] + 0xfe2ce6e0, 10);
	md5step(f4(d,a,b), c, d, m_in.b32[ 6] + 0xa3014314, 15);
	md5step(f4(c,d,a), b, c, m_in.b32[13] + 0x4e0811a1, 21);
	md5step(f4(b,c,d), a, b, m_in.b32[ 4] + 0xf7537e82,  6);
	md5step(f4(a,b,c), d, a, m_in.b32[11] + 0xbd3af235, 10);
	md5step(f4(d,a,b), c, d, m_in.b32[ 2] + 0x2ad7d2bb, 15);
	md5step(f4(c,d,a), b, c, m_in.b32[ 9] + 0xeb86d391, 21);

	m_hash[0] += a;
	m_hash[1] += b;
	m_hash[2] += c;
	m_hash[3] += d;
}

bool satisfies(const std::vector<byte_t>& bytes)
{
    if (bytes.size() != 16)
    {
        printf("Bytes has wrong size %ld", bytes.size());
        return false;
    }

    return (bytes[0] == 0 && bytes[1] == 0 && bytes[2] == 0);
}

bool satisfies(const std::string& a)
{
    Md5 hash;
    hash.ComputeHash(a);
    std::vector<byte_t> bytes = hash.Finalize();
    return satisfies(bytes);
}

size_t find(const std::string& input)
{
    if (satisfies(input))
        return 0;

    size_t n = 1;
    while(true)
    {
        std::string test = input + std::to_string(n);
        if (satisfies(test))
            return n;

        n++;
    }
}

void printHash(const std::string& a)
{
    Md5 hash;
    hash.ComputeHash(a);
    std::vector<byte_t> bytes = hash.Finalize();
    for (int i = 0; i < bytes.size() - 1; i++)
    {
        printf("%02X ", bytes[i]);
    }

    printf("%02X\n", bytes[bytes.size() - 1]);
}

int main()
{
    std::string a = "yzbqklnj";
    printHash(a);

    if (satisfies(a))
        printf("Yay!\n");
    else
        printf("Nay!\n");

    size_t result = find(a);
    printf("%ld\n", result);

    printHash(a + std::to_string(result));
}