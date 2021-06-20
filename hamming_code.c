///Hamming code implementation
///Name: Syed Mahmud Ahmed
///ID: 2017-2-60-153

#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void init(int*, int);
int calc_r(int, int);
void str2int(char*, int*, int);
void int2str(char*, int*, int);
void hamming(int*, int*, int);
void store_data(int*, int*, int);
void store_parity(int*, int*, int);
int check_error(int*, int);
int bin2dec(int);
void printcode(int*, int);
void printtrue(int*, int);
void printmsg(int*, int);
int* revarr(int*, int);

int parity;

int main()
{
    int m, n, r=1, i, err=0;
    char dstr[100], rstr[100];
    //char ostr[100];

    printf("Enter data to be sent: ");
    gets(dstr); ///data string
    strrev(dstr); ///reverse data string
    m = strlen(dstr);
    printf("\ndata bits, m = %d\n", m);
    int data[m], drev[m], rec[m];
    str2int(dstr, data, m); ///converting reversed data string to int

    printf("\nFor %d bits of data,\n\n", m);
    r = calc_r(m, r);
    n = m+r;
    printf("\tredundant bits,\t r = %d\n", r);
    printf("\tframe length,\t n = m+r = %d\n\n", n);

    printf("\nchoose parity:\t[1] Odd\n\t\t[2] Even\n\nYour choice: ");
    while(1)
    {
        scanf("%d", &parity);
        printf("\n");
        if(parity == 1 | parity == 2)
            break;
        else
            printf("Wrong input, please try again...\n\n");
    }

    int codeword[n];
    memset(codeword, 0, n*sizeof(codeword[0]));
    hamming(data, codeword, n);

    printf("\n\nTransmitted codeword\t: ");
    printcode(codeword, n);
    printf("Received codeword\t: ");
    getchar();
    gets(rstr); ///received string
    strrev(rstr); ///reverse received string
    str2int(rstr, rec, n); ///reversed string to reversed int

    err = check_error(rec, n);

    if(err==0)
    {
        printf("No errors detected!");
    }
    else
    {
        err = bin2dec(err);
        //printf("\n76: dec err index = %d\n", err);
        printf("\nError detected in D%d\n", err);
        printf("\n-----------Correction-----------\n", err);
        //printf("\n83: ");
        //printtrue(rec, n);
        str2int(rstr, rec, n);
        //printf("\n86: ");
        //printtrue(rec, n);
        //printf("\n81: rec[%d] = %d", err-1, rec[err-1]);
        rec[err-1] = !rec[err-1];
        //printf("\n83: rec[%d] = %d\n", err-1, rec[err-1]);
    }

    printf("\nCorrected codeword\t: ");
    printcode(rec, n);

    printf("\nOriginal message\t: ");
    printmsg(rec, n);

    return 0;
}

void printcode(int* arr, int n)
{
    ///function to print codeword
    int i;
    for(i=n-1; i>=0; i--)
        printf("%d", arr[i]);
    printf("\n");
}

void printtrue(int* arr, int n)
{
    ///function to print reversed codeword
    int i;
    for(i=0; i<n; i++)
        printf("%d", arr[i]);
    printf("\n");
}

void printmsg(int* code, int clen)
{
    ///function to decode message from codeword
    int i;
    //for(i=clen-1; i>=0; i--)
    for(i=clen-1; i>=0; i--)
    {
        if(ceilf(log2(i+1))!=log2(i+1))
        {
            printf("%d", code[i]);
        }
    }
    printf("\n\n");
}

int calc_r(int m, int r)
{
    ///recursive function to determine the value of r
    if( m+r+1 <= pow(2,r) )
    {
        return r;
    }
    else
    {
        return calc_r(m, r+1);
    }
}

void str2int(char* dstr, int* data, int len)
{
    ///function to convert a string to integer array
    int i;
    for(i=0; i<len; i++)
    {
        data[i] = dstr[i]-48;
    }
}

int bin2dec(int bin)
{
    ///function for binary to decimal conversion
    int dec = 0, base = 1, last_digit;
    //printf("160: bin = %d", bin);
    while (bin)
    {
        last_digit = bin % 10;
        bin = bin / 10;
        dec += last_digit * base;
        base = base * 2;
    }
    return dec;
}

int* revarr(int* arr, int n)
{
    int i, j=n-1, temp[n];
    for(i=0; i<n; i++)
    {
        temp[i] = arr[j];
        j--;
    }
    printcode(temp, n);
    return temp;
}

void hamming(int* data, int* codeword, int clen)
{
    store_data(data, codeword, clen);
    store_parity(data, codeword, clen);
}

void store_data(int* data, int* codeword, int clen)
{
    int i, k=0;
    for(i=0; i<clen; i++)
    {
        if(ceilf(log2(i+1))!=log2(i+1))
        {
            codeword[i] = data[k];
            k++;
        }
    }
}

void store_parity(int* data, int* code, int clen)
{
    int i,j,l;
    printf("Parity bits: ");
    for(i=0; i<clen; i++)
    {
        if(ceilf(log2(i+1))==log2(i+1))
        {
            j=i;
            while(j<clen)
            {
                l=i+1;
                while(l>0 && j<clen)
                {
                    code[i] ^= code[j];
                    l--;
                    j++;
                }
                j=j+i+1;
            }
            if(parity==1)
            {
                code[i] = !(code[i]);
            }
            printf(" P%d = %d ", i+1, code[i]);
        }
    }
}

int check_error(int* code, int clen)
{
    //printf("\n210: checking code\t: ");
    //printtrue(code, clen);
    printf("\n");
    int i,j,l, ebin=0, r=1;
    for(i=0; i<clen; i++)
    {
        if(ceilf(log2(i+1))==log2(i+1))
        {
            //printf("\n240: P = %d\n", i);
            //temp = code[i];
            j=i;
            while(j<clen)
            {
                l=i+1;
                while(l>0 && j<clen)
                {
                    //printf("\n250: %d   code[%d] = %d\n",j,j, code[j]);
                    if(j!=i)
                        code[i] ^= code[j];
                    l--;
                    j++;
                }
                j=j+i+1;
            }
            //printf("\n257: XOR = %d\n", code[i]);
            if(parity==1)
            {
                code[i] = !code[i];
                //printf("\n229: temp = %d\n", temp);
            }
            ebin += code[i]*r;
            r = r*10;
            //printf("\n264: ebin = %d ", ebin);
        }
    }
    //printf("\n234: ebin = %d\n", ebin);
    return ebin;
}
