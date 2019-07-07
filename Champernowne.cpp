#include <iostream>
#include <math.h>
#include <chrono>

int number_of_digits(int x)
{
    int power_of_ten = 0;
    while (x >= 10)
    {
        power_of_ten++;
        x /= 10;
    }
    return power_of_ten + 1;
}

int get_power_of_tenth_digit (int num, int offset)
{
    return (int)(num/pow(10,offset))%10;
}

int main() {
    
    auto start = std::chrono::high_resolution_clock::now();
    
    int digit_counter = 1;
    int max = 1000000;
    int number = 1;
    int next_power_of_ten = 10;
    int ans = 1;
    
    while(digit_counter < max)
    {
            ++number;
            digit_counter += number_of_digits(number);
            if (digit_counter >= next_power_of_ten)
            {
                ans *= get_power_of_tenth_digit(number,digit_counter - next_power_of_ten);
                next_power_of_ten *= 10;
            }
    }
    std::cout<<ans<<std::endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
