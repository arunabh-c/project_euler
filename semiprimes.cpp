#include <iostream>
#include <math.h>
#include <deque>


int max_limit = 100000000;

std::deque<bool> list_of_primes(max_limit + 1, false);
std::deque<bool> double_prime_list(max_limit + 1, false);

void find_primes_sieve_of_atkins(const int& range_to_check)
{

    list_of_primes[2] = true;
    list_of_primes[3] = true;
    for (int x = 1;x<=sqrt(range_to_check);x++)
    {
        for (int y = 1;y<=sqrt(range_to_check);y++)
        {

            int n = 4*pow(x,2.0) + pow(y, 2.0);
            if (n <= range_to_check && (n%12 == 1 || n%12 == 5))
            {
                list_of_primes[n] ^= true;
            }

            n = 3*pow(x,2.0) + pow(y, 2.0);
            if (n <= range_to_check && n%12 == 7)
            {
                list_of_primes[n] ^= true;
            }

            n = 3*pow(x,2.0) - pow(y, 2.0);
            if (x > y && n <= range_to_check && n%12 == 11)
            {
                list_of_primes[n] ^= true;
            }

        }
   }


   for (int x = 5; x <= sqrt(range_to_check); x++) {

       if (list_of_primes[x])
       {
       int y = pow(x, 2.0);
       while (y <= range_to_check)
       {
           list_of_primes[y] = false;
           y += pow(x, 2.0);
       }}
   }
}

int main() {

    int counter = 0;
    find_primes_sieve_of_atkins(max_limit);

    for (int idx = 2; idx <= list_of_primes.size(); idx++)
    {
        for (int idy = idx; idy <= list_of_primes.size()/idx; idy++)
        {
            if (list_of_primes[idx] && list_of_primes[idy] && idx*idy <= max_limit)
           {
               if (!double_prime_list[idx*idy]) {
                   counter++;
               }}
        }
    }

    std::cout<<"Total semi-prime numbers are: "<<counter;
    return 0;
}
