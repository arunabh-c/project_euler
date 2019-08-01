#include <iostream>
#include <math.h>
#include <chrono>

class Champernowne
{
    int digit_counter = 1;
    int max = 1000000;
    int next_power_of_ten = 10;
    int number = 1;
    int ans = 1;

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

    int get_power_of_tenth_digit()
    {
        return (int)(number/pow(10,(digit_counter - next_power_of_ten)))%10;
    }
    
    public:    
    void do_champernowne()
    {
        while(digit_counter < max)
        {
            ++number;
            digit_counter += number_of_digits(number);
            if (digit_counter >= next_power_of_ten)
            {
                ans *= get_power_of_tenth_digit();
                next_power_of_ten *= 10;
            }
        }
    }
    
    int get_champernowne()
    {
        return ans;
    }
};

int main() {
    
    auto start = std::chrono::high_resolution_clock::now();
    
    Champernowne ch;
    ch.do_champernowne();
    std::cout<<ch.get_champernowne()<<std::endl;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
