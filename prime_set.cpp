#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
#define ll long long
#define floop_int(x,start,stop,increment) for(int x = start; x < stop; x = x + increment)

ll max_limit = 9000;

/* 
 * calculates (a * b) % c taking into account that a * b might overflow 
 */
ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/* 
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = mulmod(x,y,mod);
        y = mulmod(y,y,mod);
        exponent = exponent / 2;
    }
    return x % mod;
}
 
/*
 * Miller-Rabin primality test, iteration signifies the accuracy, assumes number >= 3
 */
bool Miller(ll p,int iteration)
{
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    floop_int(i,0,iteration,1)
    {
        ll a = 13 % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

int concatenate(const int &x, const int &y)
{
    int power_of_ten = 0;
    int divided_by_ten = y;
    while (divided_by_ten >= 10)
    {
        power_of_ten++;
        divided_by_ten = divided_by_ten/10;
    }
    
    int z = (x * pow(10,power_of_ten+1) + y);
    return z;
}

void recursive_prime_sets(int next_prime, std::vector<int> set, bool &keep_searching, int &iteration)
{
    if (keep_searching)
    {
        floop_int(i,next_prime,max_limit,2)
        {
            std::vector<int> temp_set = set;
            if (Miller(i,iteration))
            {
                if (temp_set.size() > 0)
                {
                    int j = 0;
                    int counter = 0;
                    while (j < temp_set.size())
                    {
                        int l = concatenate(temp_set[j],i);
                        int m = concatenate(i,temp_set[j]);
                        if (Miller(l,iteration) && Miller(m,iteration))
                        {
                            counter++;
                        }
                        j++;
                    }
                    if (counter == temp_set.size())
                    {
                        temp_set.push_back(i);
                        if (temp_set.size() == 5)
                        {
                            std::cout<<(temp_set[0] + temp_set[1] + temp_set[2] + temp_set[3] + temp_set[4])<<std::endl;
                            keep_searching = false;
                            break;
                        }
                        else if (i < max_limit-1)
                        {
                            recursive_prime_sets(i+2,temp_set,keep_searching, iteration);
                        }
                    }
                }
                else
                {
                    temp_set.push_back(i);            
                    recursive_prime_sets(i+2,temp_set,keep_searching, iteration);
                }
            }
        }
    }
    return;
}

int main() {
    
    auto start = std::chrono::high_resolution_clock::now();
    static bool search = true;
    std::vector<int> prime_set;
    int iteration = 1;
    
    floop_int(start,3,max_limit,2)
    {
        if (Miller(start,iteration) && search)
        {
            prime_set = {};
            recursive_prime_sets(start,prime_set,search,iteration);
        }
        else if (!search)
        {
            break;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
