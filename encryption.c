// Encrypting a message
#include<stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
	char *number_str= BN_bn2hex(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}

int main()
{
	BN_CTX *ctx = BN_CTX_new();

	BIGNUM *n = BN_new();
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");

	BIGNUM *e = BN_new();
	BN_hex2bn(&e, "010001");

	BIGNUM *m = BN_new();
	BN_hex2bn(&m, "4120746f702073656372657421");

	//encryption
	BIGNUM *c = BN_new(); //c=m^e(mod n)
	BN_mod_exp(c,m,e,n,ctx);
	printBN("Encryption Result : ",c);
	printf("\n");


	//verification
	BIGNUM *d =BN_new();
	BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

	BIGNUM *result=BN_new(); //result=c^d(mod n)
	BN_mod_exp(result,c,d,n,ctx);


	printBN("Decryption Result : ",result);
	printf("\n");
	printBN("Original Message : ",m);

	BN_clear_free(n);
    BN_clear_free(e);
    BN_clear_free(m);
    BN_clear_free(c);
    BN_clear_free(d);
    BN_clear_free(result);

}