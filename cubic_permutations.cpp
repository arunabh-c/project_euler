#include <iostream>
#include <math.h>
#include <vector>
#include<set>
#include <algorithm>
#include <chrono>
using lli = long long int;

class cubic_permutations
{
    int max = 20;//80000;
    int ans = 1;
	int root = 5;
	std::vector<lli> cube_array;
	std::set<lli> answer_set;
	//int cube_permutation_counter;
	
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
			if (cube_array.size() > 1 && std::find(cube_array.begin(), cube_array.end(), new_sum) != cube_array.end())
			{
				lli ans_cube = pow(root,3);
				std::cout<<"Match found: "<<new_sum<<", root: "<<root<<", cube: "<<ans_cube<<std::endl;
				answer_set.insert(new_sum);
				answer_set.insert(ans_cube);
			}
			//std::cout<<new_sum<<", ";						
		}
		return;
	}

	int power_of_X(lli x)
	{
		int pow_of_X= 0;
		while (x/pow(10,pow_of_X) > 10)
		{
			pow_of_X++;
		}
		return pow_of_X;
	}

	public:    
    void do_cubic_permutations()
    {
		long long int cube = 0;
		int power, prev_power;
		
		 while (answer_set.size() < 4)
		{
			//cube_permutation_counter = 1;
			answer_set.clear();
			cube = pow(root,3);
			power = power_of_X(cube);
			if (prev_power != power)
			{
				cube_array.clear();
				//std::cout<<"cube array reset"<<std::endl;
			}
			prev_power = power;
			permutate_number(cube,0,power);
			cube_array.push_back(cube);
			//std::cout<<"root: "<<root<<", cube: "<<cube<<", answer_set.size(): "<<answer_set.size()<<std::endl;
			root++;
		}
		std::cout<<"Ans: "<<root<<std::endl;
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
