#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

struct RSA{
	mpz_t N, e, d, p, q, dp, dq;
};

struct RSA* RSA_init(){
	struct RSA* k;
	k=malloc(sizeof(struct RSA));
	mpz_inits(k->N,
            k->e,
            k->d,
            k->p,
            k->q,
            k->dp,
            k->dq,
            NULL);
	return k;
}

void RSA_free(struct RSA* k){
    mpz_inits(k->N,
            k->e,
            k->d,
            k->p,
            k->q,
            k->dp,
            k->dq,
            NULL);
    free(k);
}

unsigned RSA_genparams(struct RSA* k){ //requires either p,q,e or N,p,e
    mpz_t t;
    mpz_init(t);
    if(!mpz_cmp_ui(k->p,0)){
        if(!mpz_cmp_ui(k->q,0)){
            printf("[Error] In RSA_genparams: p,q=0\n");
            return -1;
        }
        if(!mpz_divisible_p(k->N,k->q)){
            printf("[Error] In RSA_genparams: N%%q!=0\n");
            return -1;
        }
        mpz_divexact(k->p,k->N,k->q);
    }else if(!mpz_cmp_ui(k->q,0)){
        if(!mpz_divisible_p(k->N,k->p)){
            printf("[Error] In RSA_genparams: N%%p!=0\n");
            return -1;
        }
        mpz_divexact(k->q,k->N,k->p);
    }else if(!mpz_cmp_ui(k->N,0)){
        mpz_mul(k->N,k->p,k->q);
    }else{
        if(!mpz_divisible_p(k->N,k->p)){
            printf("[Error] In RSA_genparams: N%%p!=0\n");
            return -1;
        }
        if(!mpz_divisible_p(k->N,k->q)){
            printf("[Error] In RSA_genparams: N%%q!=0\n");
            return -1;
        }
    }
    //N,p,q should be defined
    if(!mpz_cmp_ui(k->e,0)){
        printf("[Error] In RSA_genparams: e=0");
        return -1;
    }
    mpz_sub_ui(k->p,k->p,1);
    mpz_sub_ui(k->q,k->q,1);
    mpz_lcm(t,k->p,k->q);
    if(!mpz_invert(k->d,k->e,t)){
        printf("[Error] In RSA_genparams: lambda(n)%%e=0");
        return -1;
    }
    mpz_fdiv_r(k->dp,k->d,k->p); //should use mod instead? idk
    mpz_fdiv_r(k->dq,k->d,k->q);
    mpz_add_ui(k->p,k->p,1);
    mpz_add_ui(k->q,k->q,1);
    return 0;
}

int main(){
	struct RSA* k=RSA_init();
    mpz_set_str(k->p, "sKqqTYntco0pCc8tcorHWdh7wCRZ4p0AhO9cRcJDzqSV8aA8TNB9sKysj1ZTBEiIIdE7ycI7nfhRagOUiSU1Qo3UYJ5MbEDu8D1wwdiqInF1D12QpLBPuW4kYzWGULTTuBt9ueprxhVmIDn0cRaGPZ7GSk3TSm2LMuQa8VhJka43", 62);
    mpz_set_str(k->q, "1nEm7i4ZAaVrqON0dthhUhM5gz0vyB0MFLcULpxC8tQiKtIhEQMEY9IoHrExFqCrVZ94XtT0itCE3CqYTrmH1KK3HK2AxfaOu1JjwO47p75LbHAaF35dwajl8yEEPUA5soZIfw6Yeq2DRz9DbYcBZsUPwncyOnhemx0CrvEXOa40R", 62);
    mpz_set_str(k->e, "H33", 62);
    //mpz_set_str(k->N, "1ZUHUmfNfq9nChljC758NRBgZaA7U3fIvSWvmZi15bNVtQcEllgRyMU7aPafAerDfNpWlfEdPGeT5AWvVNE0tkARBO6QyCS1LjVWNScgNvG34xv9JmEeg1v88Grk4lDOuZRalxnMEjw1fcrBDCzZTmk1YqUiIQWMUfRBxkjOvLNQOjssPv3JVD5gNDyUH0UfCeHaIscVg3WMabnRgpiiK0mBrwaSQdBHN7JdK96DLkImk2UBR3aFtNTeyE2NP90NFFJz8gOAObI23f2lGbeG9k0N2rjic3hXN3WQ7JWix8DO8AwOl3DYRaOgvSvF2LBVAri4P6b2Pw05xR4WnruyRHtlJ", 62);
    if(RSA_genparams(k)){
        printf("An error occured\n");
        return 1;
    };
    gmp_printf("N = %Zx\n",k->N);
    gmp_printf("p = %Zx\n",k->p);
    gmp_printf("q = %Zx\n",k->q);
    gmp_printf("e = %Zx\n",k->e);
    gmp_printf("d = %Zx\n",k->d);
    gmp_printf("dp = %Zx\n",k->dp);
    gmp_printf("dq = %Zx\n",k->dq);

    //encrypting a message 
	return 0;
}
