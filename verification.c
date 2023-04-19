// Verifying the signature
#include<stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
	char *number_str= BN_bn2hex(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}
void printVM(BIGNUM *m, BIGNUM *result)
{
        if(m==result) {
             print("verified")
        } else {
             print("not verifies=d")
        }
int main()
{
	BN_CTX *ctx = BN_CTX_new();

	BIGNUM *n = BN_new();
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");

	BIGNUM *d = BN_new();
	BN_hex2bn(&d, " 74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

	BIGNUM *m = BN_new();
	BN_hex2bn(&m, "4120746f702073656372657421");

	//encryption
	BIGNUM *S = BN_new(); //S=m^e(mod n)
	BN_mod_exp(S,m,d,n,ctx);
	printBN("The signature is : ",S);
	printf("\n");

	BN_clear_free(n);
        

        
	//verification
	BIGNUM *e =BN_new();
	BN_hex2bn(&e, "010001");

	BIGNUM *result=BN_new(); //result=S^e(mod n)
	BN_mod_exp(result,S,e,n,ctx);


	printBN("Decryption Result : ",result);
	printf("\n");
	printBN("Original Message : ",m);
        printVM(m, result);

	BN_clear_free(n);
    BN_clear_free(d);
    BN_clear_free(m);
    BN_clear_free(S);
    BN_clear_free(e);
    BN_clear_free(result);

}