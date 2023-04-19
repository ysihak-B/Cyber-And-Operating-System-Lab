// Deriving the private key
#include <stdio.h>
#include <openssl/bn.h>

#define NBITS 256

void printBN(char *msg, BIGNUM *a)
{
	char *number_str = BN_bn2hex(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}

int main()
{

	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *p = BN_new();
	BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
	BIGNUM *q = BN_new();
	BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
	BIGNUM *e = BN_new();
	BN_hex2bn(&e, "0D88C3");

	BIGNUM *n = BN_new();
	BN_mul(n,p,q,ctx); //n=p*q

	BIGNUM *one =BN_new(); // one=1
	BN_hex2bn(&one, "1");

	BIGNUM *p1 = BN_new(); //p1=p-1
	BN_sub(p1,p,one);

        BIGNUM *q1 = BN_new(); //q1=q-1
        BN_sub(q1,q,one);

	BIGNUM *phi = BN_new(); //phi(n)=(p-1)(q-1)
	BN_mul(phi,p1,q1,ctx);

	BIGNUM *d = BN_new();
	BN_mod_inverse(d,e,phi,ctx); //d=e^-1(mod phi(n))
	printBN("Private key d : ", d);

	BN_clear_free(p);
    BN_clear_free(q);
    BN_clear_free(e);
    BN_clear_free(n);
    BN_clear_free(p1);
    BN_clear_free(q1);
    BN_clear_free(phi);
    BN_clear_free(d);
}