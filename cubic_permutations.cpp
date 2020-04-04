#include <iostream>
#include <math.h>
#include <vector>
#include<set>
#include <algorithm>
#include <chrono>
#include <iomanip>      // std::setprecision

using lli = long long int;

class cubic_permutations
{
    int max = 20;//80000;
    int ans = 1;
	int root = 5;
	std::vector<lli> cube_array;
	std::set<int> answer_set;
	int cube_permutation_counter;
	
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
			if (is_cube_recursive(new_sum))//(cube_array.size() > 1 && std::find(cube_array.begin(), cube_array.end(), new_sum) != cube_array.end())
			{
				//lli ans_cube = pow(root,3);
				//std::cout<<"Match found: "<<new_sum<<", root: "<<pow(new_sum, (1.0/3.0))<<", cube: "<<ans_cube<<std::endl;
				//std::cout<<answer_set.size()<<std::endl;
				answer_set.insert(pow(new_sum, (1.0/3.0)));
				/*std::cout<<answer_set[0]<<", "<<answer_set[1]<<", "<<answer_set[2]<<std::endl;
				std::set<int>::iterator setIt = answer_set.begin();
				for(int i = 0; i < answer_set.size(); i++)
				{
					setIt++;
					std::cout<<*setIt<<", ";
				}
				std::cout<<std::endl;*/
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
	
	bool is_cube(lli cube)//https://math.stackexchange.com/questions/1400263/how-to-make-this-cubic-root-c-algorithm-faster
	{
		long double cube_root = pow((long double)cube, (1.0/3.0));
		std::cout<<"cube: "<<cube<<", long double cube root: "<<cube_root*1000000<<", lli(cube_root): "<<lli(cube_root)*1000000 <<", equality: "<<(lli(cube_root*1000000) == cube_root*1000000)<<std::endl;
		if (lli(cube_root*1000000) == cube_root*1000000)
		{return true;}
	return false;
	}
	
	
	bool is_cube_recursive(lli cube)
	{
		long double cube_root = cube* 0.01;
		long double  cube_root_prev = 0.0;
		float eps = 0.0000000001;
		float diff = 99.99;
		int ctr = 0;
		while (diff > eps && ctr < 500)
		{
			cube_root_prev = cube_root;;
			cube_root  = cube_root_prev  - ( pow(cube_root_prev,3.0) - (long double)(cube)) / (3.0 * cube_root_prev * cube_root_prev);
			//std::cout<<std::setprecision(9)<<cube_root<<", "<<abs(cube_root - cube_root_prev)<<std::endl;
			diff = abs(cube_root - cube_root_prev); 
			ctr++;
		}
		//std::cout<<"cube: "<<cube<<", long double cube root: "<<cube_root<<", long double cube_root_prev: "<<cube_root_prev<<std::endl;//", equality: "<<(lli(cube_root*1000000) == cube_root*1000000)<<std::endl;
		if (lli(cube_root*1000000) == cube_root*1000000)
		{return true;}
	return false;
	}
	

	public:    
    void do_cubic_permutations()
    {
		long long int cube = 0;
		int power, prev_power;
		//std::cout<<is_cube(54872002)<<std::endl;
		//std::cout<<is_cube(41063625)<<std::endl;
		//std::cout<<is_cube(56623104)<<std::endl;
		//std::cout<<is_cube(66430125)<<std::endl;
		 while (answer_set.size() < 4)
		{
			cube_permutation_counter = 1;
			answer_set.clear();
			answer_set.insert(root);
			std::cout<<root<<std::endl;
			std::set<int>::iterator setIt = answer_set.begin();
			//for(int i = 0; i < answer_set.size(); i++)
			//{
			//	setIt++;
			//	std::cout<<*setIt<<", ";
			//}
			//std::cout<<std::endl;
			cube = pow(root,3);
			power = power_of_X(cube);
			//if (prev_power != power)
			//{
			//	cube_array.clear();
			//  std::cout<<"cube array reset"<<std::endl;
			//}
			prev_power = power;
			permutate_number(cube,0,power);
			//cube_array.push_back(cube);
			//std::cout<<"root: "<<root<<", cube: "<<cube<<", answer_set.size(): "<<answer_set.size()<<std::endl;
			root++;
		}
		//std::cout<<answer_set.size()<<std::endl;
		std::set<int>::iterator setIt = answer_set.begin();
		for(int i = 0; i < answer_set.size(); i++)
		{
			setIt++;
			std::cout<<*setIt<<", ";
		}
		std::cout<<"Ans: "<<root-1<<std::endl;
		//std::cout<<is_cube(27)<<std::endl;
		//std::cout<<is_cube(8)<<std::endl;
		//std::cout<<is_cube(29)<<std::endl;

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
