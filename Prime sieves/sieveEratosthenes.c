#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    const unsigned int res[8] = {1,7,11,13,17,19,23,29};
    const unsigned int N = 1000000000;
    unsigned int nextelem[8][8][2]={0}; //res[i]+nextelem[i][j][0]*res[j]=nextelem[i][j][1]
    unsigned int startk[8]={0}; //res[i]*2=res[startk[j]]
    unsigned int i,j,k,ii,jj;
    u_int8_t *primes = calloc(N/30+1,sizeof(char));
    //jth bit of primes[i]: 30*i+res[j]
    primes[0] = '\x01';
    unsigned int ub = sqrt(N)/30+1;
    unsigned int t = N/30+1;
    for(i=0;i<8;++i){// genning nextelem
        for(j=0;j<8;++j){
            for(k=2;k<30;k+=2){
                for(ii=0;ii<8;++ii){
                    if(res[ii]==(res[i]+k*res[j])%30){
                        break;
                    }
                }
                if(ii!=8){
                    nextelem[i][j][0]=k;
                    nextelem[i][j][1]=ii;
                    break;
                }
            }
        }
    }
    for(i=0;i<8;++i){// genning startk
        for(j=0,k=(res[i]*res[i])%30;j<8;++j){
            if(res[j]==k){
                startk[i]=j;
                break;
            }
        }
    }
    for(i=0;i<ub;++i){
        for(j=0;j<8;++j){
            //current number is i*30+res[j]
            if(primes[i]>>j&1){// jth bit is set to 1
                continue;
            }
            // we start from the square and go up, have a lookup table to figure how much to increment
            ii=i*30+res[j];
            jj=ii*ii;
            k=startk[j];
            while(jj<N){
                primes[jj/30]|=1<<k; // jj not a prime
                jj+=nextelem[k][j][0]*ii;
                k=nextelem[k][j][1];
            }
        }
    }
    // counting primes
    k=3; // 2,3,5
    for(i=0;i<t-1;++i){
        for(j=0;j<8;++j){
            if(primes[i]>>j&1){
                continue;
            }
            ++k;
        }
    }
    for(j=0;j<8;++j){
        if(primes[i]>>j&1){
            continue;
        }
        if(i*30+res[j]>N){
            break;
        }
        ++k;
    }
    printf("Number of primes equal or less than %d: %d\n",N,k);
    free(primes);
    return 0;
}
