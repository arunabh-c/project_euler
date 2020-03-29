#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
using lli = long long int;

class cubic_permutations
{
    int max = 20;//80000;
    int ans = 1;
	//std::vector<lli> cube_array;
    
	lli X = 1203044;

    void permutate_number(lli x, lli sum, int power_of_10)
	{
		lli new_sum = 0;
		int id = rand();
		for (int i =power_of_10; i >= 0; i--)
		{
			int digit = (int(x/pow(10,i)))%10;
			//std::cout<<"id: "<<id<<", i: "<<i<<", x: "<<x<<", digit: "<<digit<<", sum: "<<sum<<std::endl;
			if (!(sum == 0 && digit == 0))
			{
				new_sum = sum + digit*pow(10,power_of_10);
				int next_x = (x/(int(pow(10,i+1))))*pow(10,i) + x%((int)pow(10,i));
				//std::cout<<"id: "<<id<<", i: "<<i<<", x: "<<x<<", increment: "<<digit*pow(10,power_of_10)<<", next_x: "<<next_x<<", new_sum: "<<new_sum<<std::endl;
				if (next_x > 0)
				{
					permutate_number(next_x,new_sum,std::max(0,power_of_10-1));					
				}
			}
		}
		if (power_of_10 == 0)
		{
			std::cout<<"final sum: "<<new_sum<<std::endl;						
		}
		return;
	}
	public:    
    void do_cubic_permutations()
    {
		int power_of_X= 0;
		while (X/pow(10,power_of_X) > 10)
		{
			power_of_X++;
		}
		
		permutate_number(X,0,power_of_X);
		
		long long int cube = 0;
		
		for (int i =5; i < max; i++)
		{
			cube = pow(i,3);
			//std::cout<<cube<<std::endl;
		}
	}
    
    int get_cubic_permutations()
    {
        return ans;
    }
};

int main() {
    
    auto start = std::chrono::high_resolution_clock::now();
    
    cubic_permutations cp;
    cp.do_cubic_permutations();
    std::cout<<cp.get_cubic_permutations()<<std::endl;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
