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
    
	lli X_num = 1023;
	std::vector<int> X = {0,1,2,3};
	
    void permutate_array(std::vector<int> x, lli sum)
	{
		lli new_sum;
		for (int i =0;i<x.size(); i++)
		{
			if (!(sum == 0 && x[i] == 0))
			{
				std::vector<int> next_x = x;
				new_sum = sum + x[i]*pow(10,x.size()-1);
				next_x.erase(next_x.begin() + i);
				if (next_x.size() > 0)
				{
					permutate_array(next_x, new_sum);			
				}
			}
		}
		if (x.size() < 2)
		{
			std::cout<<new_sum<<", ";						
		}
		return;
	}
    void permutate_number(lli x, lli sum, lli power_of_10)
	{
		
		lli new_sum = 0;
		for (int i =power_of_10; i >= 0; i--)
		{
			int digit = (int(x/pow(10,i)))%10;
			if (digit != 0)
			{
				new_sum = sum + digit*pow(10,i);
				int next_x = x - digit*pow(10,i);
				//std::cout<<"x: "<<x<<", digit: "<<digit<<", next_x: "<<next_x<<", new_sum: "<<new_sum<<std::endl;
				permutate_number(next_x,new_sum,i-1);
			}
		}
		if (power_of_10 < 1)
		{
			std::cout<<new_sum<<", ";						
		}
		return;
	}
	public:    
    void do_cubic_permutations()
    {
		//permutate_array(X,0);
		permutate_number(X_num,0,3);
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
