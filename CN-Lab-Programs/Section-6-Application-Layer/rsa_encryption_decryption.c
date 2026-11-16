#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_prime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

long long compute_gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long extended_euclidean_inverse(long long e, long long phi) {
    long long t = 0;
    long long new_t = 1;
    long long r = phi;
    long long new_r = e;

    while (new_r != 0) {
        long long quotient = r / new_r;

        long long temp_t = t - quotient * new_t;
        t = new_t;
        new_t = temp_t;

        long long temp_r = r - quotient * new_r;
        r = new_r;
        new_r = temp_r;
    }

    if (r > 1) {
        return -1;
    }
    if (t < 0) {
        t = t + phi;
    }
    return t;
}

long long modular_power(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            __int128 temp = (__int128)result * base;
            result = (long long)(temp % modulus);
        }
        exponent = exponent >> 1;
        __int128 temp_base = (__int128)base * base;
        base = (long long)(temp_base % modulus);
    }
    return result;
}

int main(void) {
    printf("============================================================\n");
    printf("   Message Confidentiality Using RSA Encryption/Decryption  \n");
    printf("============================================================\n");
    printf("NOTICE: This is an educational RSA demonstration implementation\n");
    printf("designed for laboratory learning, not production cryptography.\n\n");

    long long p = 0;
    long long q = 0;

    printf("Enter first prime number p (e.g. 61 or 17): ");
    if (scanf("%lld", &p) != 1 || !is_prime(p)) {
        printf("Error: Input must be a valid prime number.\n");
        return 1;
    }

    printf("Enter second prime number q (e.g. 53 or 19): ");
    if (scanf("%lld", &q) != 1 || !is_prime(q)) {
        printf("Error: Input must be a valid prime number.\n");
        return 1;
    }

    if (p == q) {
        printf("Error: p and q must be distinct primes.\n");
        return 1;
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    if (n < 128) {
        printf("Warning: Modulus n = %lld is smaller than ASCII 127. Characters may exceed n.\n", n);
    }

    long long e = 0;
    for (long long candidate = 3; candidate < phi; candidate += 2) {
        if (compute_gcd(candidate, phi) == 1) {
            e = candidate;
            break;
        }
    }

    if (e == 0) {
        printf("Error: Failed to find valid public exponent e.\n");
        return 1;
    }

    long long d = extended_euclidean_inverse(e, phi);
    if (d == -1) {
        printf("Error: Modular inverse does not exist.\n");
        return 1;
    }

    printf("\n--- RSA Key Generation Results ---\n");
    printf("Prime 1 (p):             %lld\n", p);
    printf("Prime 2 (q):             %lld\n", q);
    printf("Modulus (n = p * q):     %lld\n", n);
    printf("Euler's Totient phi(n):  %lld\n", phi);
    printf("Public Exponent (e):     %lld\n", e);
    printf("Private Exponent (d):    %lld\n", d);
    printf("Public Key:              (e = %lld, n = %lld)\n", e, n);
    printf("Private Key:             (d = %lld, n = %lld)\n\n", d, n);

    char message[256];
    printf("Enter message string to encrypt (alphanumeric/text): ");
    if (scanf("%255s", message) != 1) {
        printf("Error reading message.\n");
        return 1;
    }

    int message_len = strlen(message);
    long long ciphertext[256];
    char decrypted_message[256];

    printf("\n--- Encryption Process ---\n");
    printf("%-6s %-12s %-12s %-16s\n", "Char", "Plain (M)", "Formula", "Ciphertext (C)");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < message_len; i++) {
        long long m_val = (unsigned char)message[i];
        if (m_val >= n) {
            printf("Error: Character ASCII value (%lld) exceeds modulus n (%lld).\n", m_val, n);
            return 1;
        }
        ciphertext[i] = modular_power(m_val, e, n);
        printf("'%c'    %-12lld (%lld^%lld)%%%lld     %-16lld\n",
               message[i], m_val, m_val, e, n, ciphertext[i]);
    }

    printf("\n--- Decryption Process ---\n");
    printf("%-16s %-20s %-12s %-6s\n", "Ciphertext (C)", "Formula", "Decrypted (M)", "Char");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < message_len; i++) {
        long long decrypted_val = modular_power(ciphertext[i], d, n);
        decrypted_message[i] = (char)decrypted_val;
        printf("%-16lld (%lld^%lld)%%%lld        %-12lld '%c'\n",
               ciphertext[i], ciphertext[i], d, n, decrypted_val, (char)decrypted_val);
    }
    decrypted_message[message_len] = '\0';

    printf("\n--- Summary ---\n");
    printf("Original Message:  %s\n", message);
    printf("Encrypted Stream:  ");
    for (int i = 0; i < message_len; i++) {
        printf("%lld ", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted Message: %s\n", decrypted_message);

    if (strcmp(message, decrypted_message) == 0) {
        printf("Status:            SUCCESS (Decrypted message matches original perfectly)\n");
    } else {
        printf("Status:            FAILED (Mismatch detected)\n");
    }

    return 0;
}
