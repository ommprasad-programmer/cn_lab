/*
PR6_2_RSA_Cryptography.c:
Program to implement public-key cryptography using the RSA algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Simple function to calculate the greatest common divisor
long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to perform efficient modular exponentiation: (base^exp) % mod
long long powerMod(long long base, long long exp, long long mod)
{
    long long res = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return res;
}

int main()
{
    // Select small primes for programmatic validation simplicity (p * q must fit integer limits)
    long long p = 61;
    long long q = 53;

    long long n = p * q;               // Calculate modulus product bounds
    long long phi = (p - 1) * (q - 1); // Calculate Euler's totient function value
    long long e = 17;                  // Public exponent choice (must be coprime to phi)

    // Ensure choices align with cryptographic math constraint rules
    while (e < phi)
    {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }

    // Compute private key exponent 'd' (Modular multiplicative inverse of 'e' mod 'phi')
    long long d = 1;
    while (1)
    {
        if ((d * e) % phi == 1)
            break;
        d++;
    }

    printf("\n=== Message Confidentiality Engine (RSA Cryptography) ===\n");
    printf("Generated Key Parameters:\n");
    printf("-> Public Encryption Coordinates (e, n): (%lld, %lld)\n", e, n);
    printf("-> Private Decryption Coordinates (d, n): (%lld, %lld)\n\n", d, n);

    long long msg;
    printf("Enter an integer message payload value to securely transmit (Must be < %lld): ", n);
    scanf("%lld", &msg);

    if (msg >= n || msg < 0)
    {
        printf("Error: Payload input size breaks cryptographic boundary rules.\n\n");
        return 1;
    }

    // Step 1: Execute Encryption Operation -> Ciphertext = (Message ^ e) % n
    long long encrypted_ciphertext = powerMod(msg, e, n);
    printf("\n--- Encryption Sequence ---\n");
    printf("Transforming plain text numerical data using Public Key configurations...\n");
    printf("Resulting Ciphertext Package generated: %lld\n", encrypted_ciphertext);

    // Step 2: Execute Decryption Operation -> Decrypted Plaintext = (Ciphertext ^ d) % n
    long long decrypted_plaintext = powerMod(encrypted_ciphertext, d, n);
    printf("\n--- Decryption Sequence ---\n");
    printf("Reconstructing payload string at target endpoint using Private Key keys...\n");
    printf("Resulting Plaintext Package extracted:  %lld\n\n", decrypted_plaintext);

    // Verification check logic
    if (msg == decrypted_plaintext)
    {
        printf("Validation Integrity Status: Success. Message contents match perfectly without leakage.\n\n");
    }
    else
    {
        printf("Validation Integrity Status: Failure. Mismatched bit boundaries detected.\n\n");
    }

    return 0;
}
