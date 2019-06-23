#include <iostream>
#include <deque>

void array_sum(std::deque<int> &smaller, const std::deque<int> &larger, std::deque<int> &sum)
{
        int carry = 0;
        int total = 0;
        sum = {};
        
        for (int i=0;i<(larger.size()-smaller.size());i++)
        {
            smaller.push_front(0);
        }
        for (int i =larger.size()-1;i>=0;i--)
        {
            total = larger[i] + smaller[i] + carry;
            carry = total/10;
            sum.push_front(total - 10*carry);
        }
        if (carry > 0)
        {
            sum.push_front(carry);
        }
}

int main()
{
    std::deque<int> a = {1};
    std::deque<int> b = {1};
    std::deque<int> ans;
    int counter = 2;
    while (ans.size() < 1000)
    {
        counter++;
        array_sum(a,b,ans);
        a = b;
        b = ans;
    }
    std::cout<<counter<<std::endl;
    return 0;
}
