
// u(n) = 1/n+n+1

#include<stdio.h>

// De quy
float S(int n)
{
    if(n==0)
        return 1;
    return 1.0/(n+n+1) + S(n-1);
}

// Qui trinh 4 buoc
// Buoc 1: Base case n = 0
// Buoc 2: Ket qua tai base case S = 1
// Buoc 3: Truoc base case n = 1, ket qua la S(1) = 1/(1+2) + S(0) = 1.3
// Buoc 4: Truoc n = 1 la n = 2, ket qua S(2) = 1/(2+3) + S(1) = 1.5


// Khong de quy
float S1(int n)
{
    int i;
    float s1 = 0;
    for(i=0;i<=n;i++)
    {
        s1 = s1 + (1.0/(i+i+1));
    }
    return s1;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("S(%d) = %0.1f",n,S1(n));
    return 0;
}