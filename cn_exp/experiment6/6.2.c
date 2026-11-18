/*
PR6_2_RSAEncryption.c:
Program that uses RSA algorithm to encrypt a text message and decrypt the same.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 256
#define SYMBOL_BASE 33 // '!' character
#define SYMBOL_RANGE 94 // printable ASCII: 33 to 126

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

long long modexp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long modinv(long long e, long long phi)
{
    long long t = 0, newt = 1;
    long long r = phi, newr = e;
    while (newr != 0)
    {
        long long q = r / newr;
        long long temp = newt;
        newt = t - q * newt;
        t = temp;
        temp = newr;
        newr = r - q * newr;
        r = temp;
    }
    if (r > 1) return -1;
    if (t < 0) t += phi;
    return t;
}

int main()
{
    // Fixed small primes (for demo)
    long long p = 61, q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 17;
    long long d = modinv(e, phi);

    if (d == -1)
    {
        printf("Modular inverse error.\n");
        return 1;
    }

    printf("\n");
    printf("Public key (e, n) = (%lld, %lld)\n", e, n);
    printf("Private key (d, n) = (%lld, %lld)\n\n", d, n);

    char message[MAX_LEN];
    printf("Enter message to encrypt: ");
    fgets(message, MAX_LEN, stdin);
    size_t len = strlen(message);
    if (message[len - 1] == '\n') message[len - 1] = '\0';

    long long encrypted[MAX_LEN];
    printf("\nEncrypted (as symbols): ");
    for (size_t i = 0; i < strlen(message); i++)
    {
        encrypted[i] = modexp((long long)message[i], e, n);
        char symbol = SYMBOL_BASE + (encrypted[i] % SYMBOL_RANGE);
        printf("%c", symbol);
    }

    printf("\n\nDecrypted message: ");
    for (size_t i = 0; i < strlen(message); i++)
    {
        char ch = (char)modexp(encrypted[i], d, n);
        printf("%c", ch);
    }
    printf("\n\n");

    return 0;
}
