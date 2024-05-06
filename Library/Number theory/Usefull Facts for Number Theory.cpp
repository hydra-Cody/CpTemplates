

// --------------------------------------------------
// Usefull Facts for Cp:

    
=>  9592 prime below 1e5
=>  gcd(p,q)=gcd(p,p-q)
=>  Two integers a,b (b != 0) there exist two unique integers
    q and r such that
                a = bq + r, 0 <= r < b
=>  bezout's identity states that if d = gcd(a,b) 
    then there always exist integers x and y such that ax+by = d.
=>  number of prime smaller than n are n/log2(n)
=>  number of Divisors of a number n at max (n)^(1/3)
=>  number of prime Divisors of n at max log(n)
=>  harmonic series N + N/2 + N/3 + ... + 1 = O(N log N)
=>  (1+1/4 + 1/9 + 1/16 + 1/25 + ...) = (π^2 / 6)
=>  nCr = (n-1)C(r-1) + (n-1)Cr
=>  The total number of pairs (x,y) with 1≤x,y≤n,gcd(x,y)=1 
    is φ(1)+φ(2)+⋯+φ(n)
    , where φ is Euler's totient function. 
    We also want to substract a single pair (1,1). 
    And this sum grows so fast that after about 600
    iteratons φ(1)+φ(2)+⋯+φ(600) will be greater than 100000
    for any n.
=>  Number of divisors of a number n is (1+p1)*(1+p2)...
    where p1 ,p2..are power of prime factor of n that is
    n=a1^p1*a2^p2...
=> N + N / 2 + N / 4 + N / 8 + N / 16 + ... is 2*N so it's O(N)
=> distinct values of floor of (N / i) is 2 * sqrt(N)

