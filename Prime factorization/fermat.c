#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

//https://www.ams.org/journals/mcom/1974-28-126/S0025-5718-1974-0340163-2/S0025-5718-1974-0340163-2.pdf eventually?

void fermat(mpz_t p, mpz_t q, mpz_t N){
    mpz_t a,b;
    mpz_inits(a,b,NULL);
    mpz_sqrt(a,N);
    mpz_mul(b,a,a);
    if(!mpz_cmp(b,N)){
        mpz_set(p,a);
        mpz_set(q,a);
        mpz_clears(a,b,NULL);
        return;
    }
    mpz_add(b,b,a);
    mpz_add_ui(a,a,1);
    mpz_add(b,b,a);
    mpz_sub(b,b,N);
    while(!mpz_perfect_square_p(b)){
        mpz_add(b,b,a);
        mpz_add_ui(a,a,1);
        mpz_add(b,b,a);
    }
    mpz_sqrt(b,b);
    mpz_sub(p,a,b);
    mpz_add(q,a,b);
    mpz_clears(a,b,NULL);
}

int main(){
    mpz_t N,p,q;
    mpz_inits(N,p,q,NULL);
    mpz_set_str(N,
            "KMpcYlls7oodihezdPVsVLbymnmfMDuKMK9YTH81Tjav06TSOshI6I8CLZFdgwGUSMTTdlsQ8GranINcWW9MKlOhpMjQ9KN6onSw9GZ0evBwyNhn9bSOExYSWMdSWXN20B9c6ysuCfOyagXcRjdqurkDj6XGco9bCJwkzlYWbweMQCOXSL6HuIuIqxB6XO3ejw7mmYIk9nBzfvBWzGjswCqQKZjd3NV6eZxyPlU23IRpyKDHtj9VGpN8GYYffEnYyuFrOzagKP2PMnnG1X4jdpJV88N9FWjKT0QVgR3X7cJDPGt0Oq3zNfClg0JWlJIaPHhszJ6yZPOuNuzlNIQjwKpp"
            ,62);
    fermat(p,q,N);
    gmp_printf("%Zd = %Zd * %Zd\n",N,p,q);
    mpz_clears(N,p,q,NULL);
    return 0;
}
