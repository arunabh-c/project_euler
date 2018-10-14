#include <iostream>
#include <math.h>
#include <deque>

int get_number_of_digits_minus_one(const int& input)
{
    int num_digits = 0;
    while (input/pow(10.0,num_digits) >= 1.0)
    {
        ++num_digits;
    }
    return num_digits-1;
}

std::deque<int> get_array_digit_product(const std::deque<int>& array, const int& digit)
{
    std::deque<int> prodct(array.size(),0);
    for(int idx = array.size()-1; idx >= 0; idx--)
    {
        int temp_prod = array[idx]*digit + prodct[idx];
        if (temp_prod >= 10)
        {
            //quotient
            prodct[idx] = temp_prod - (temp_prod/10)*10;
            //carry over
            if (idx == 0)
            {
               prodct.push_front(temp_prod/10);
            }
            else
            {
                prodct[idx - 1] = temp_prod/10;
            }
        }
        else
        {
            prodct[idx] = temp_prod;
        }
    }
    return prodct;
}

std::deque<int> get_array_sum(std::deque<int>& x, std::deque<int>& y)
{
    if (x.size() < y.size())
    {
        while (x.size() != y.size())
        {x.push_front(0);}
    }
    else if (x.size() > y.size())
    {
        while (x.size() != y.size())
        {y.push_front(0);}
    }

    std::deque<int> ans(x.size(),0);
    for (int idx = x.size()-1;idx>= 0;idx--)
    {
        int temp_sum = x[idx] + y[idx] + ans[idx];
        if (temp_sum >= 10)
            {
                //sum
                ans[idx] = temp_sum - (temp_sum/10)*10;
                //carry over
                if (idx == 0)
                {
                    ans.push_front(temp_sum/10);
                }
                else
                {
                    ans[idx - 1] = temp_sum/10;
                }
           }
           else
            {
                ans[idx] = temp_sum;
            }
    }
    return ans;
}

void multiply_array_by_power_of_ten(std::deque<int>& array, int power_of_ten)
{
    while (power_of_ten > 0) {
        array.push_back(0);
        --power_of_ten;
    }
}

std::deque<int> get_product_array(std::deque<int>& array, int next_digit)
{
    int number_of_digits = get_number_of_digits_minus_one(next_digit);
    std::deque<int> product(array.size(),0);

    while (number_of_digits >= 0)
    {
        int power_of_10 = pow(10, number_of_digits);
        int multiplier = next_digit/power_of_10;
        std::deque<int> next_digit_product = get_array_digit_product(array, multiplier);

        multiply_array_by_power_of_ten(next_digit_product, number_of_digits);
        product = get_array_sum(product, next_digit_product);
        next_digit -= multiplier * power_of_10;
        --number_of_digits;
    }
    return product;
}

std::deque<int> get_factorial(int& input)
{

    std::deque<int> starter = {1};
    std::deque<int> final_ans;

    while (input > 1)
    {
        final_ans = get_product_array(starter, input);
        starter = final_ans;
        --input;
    }
    return final_ans;
}


int main() {
    int ip = 100;
    std::deque<int> factorial = get_factorial(ip);

    int sum = 0;
    for (int idx = 0;idx< factorial.size();idx++)
    {
    sum += factorial[idx];
    }
    std::cout<<"Final Answer: "<<sum<<std::endl;
    return 0;
}