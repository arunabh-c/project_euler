#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
#include <iomanip>      // std::setprecision

using lli = long long int;

class cubic_permutations
{
    int max = 20;//80000;
    int ans = 1;
	int root = 5;
	std::set<lli> cube_array;
	std::set<lli> answer_set;
	int cube_permutation_counter;
	
    void permutate_number(lli x, lli sum, int power_of_10)
	{
		lli new_sum = 0;
		//int id = rand();
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
		if (power_of_10 == 0 )
		{
			if (is_cube(new_sum))
			{
				answer_set.insert(new_sum);
				if (answer_set.size() > 2)
				{
					std::cout<<"Match found: answer_set.size(): "<<answer_set.size()<<", root: "<<root<<", number found: "<<pow(new_sum, (1.0/3.0))<<std::endl;					
					std::set<lli>::iterator setIt;
					for(setIt  = answer_set.begin(); setIt != answer_set.end(); ++setIt)
					{
						std::cout<<*setIt<<", ";
					}
					std::cout<<std::endl;
				}
			}			
		}
		return;
	}

	int power_of_X(lli x)
	{
		int pow_of_X= 0;
		while (x/pow(10,pow_of_X) >= 10)
		{
			pow_of_X++;
		}
		return pow_of_X;
	}
	
	bool is_digital_root_cube(lli cube)
	{
		int sum = 0;
		while (cube > 0)
		{
			sum += cube%10;
			cube = cube/10;
			if (cube == 0 && sum >= 10)
			{
				cube = sum;
				sum = 0;
			}
		}
		//std::cout<<"sum: "<<sum<<std::endl;
		if (sum == 0 || sum == 1 || sum == 8 || sum == 9)
		{return true;}
		return false;
	}
	
	bool is_cube(lli cube)//https://math.stackexchange.com/questions/1400263/how-to-make-this-cubic-root-c-algorithm-faster
	{
		if (true)//is_digital_root_cube(cube))
		{
			lli cube_root = round(pow(cube, (1.0/3.0))) ;
			lli derived_cube = pow(cube_root,3) ;
			//std::cout<<"cube: "<<cube<<", long double cube root: "<<cube_root<<", derived_cube: "<<derived_cube<<", equality: "<<(derived_cube - cube)<<std::endl;
			if (derived_cube - cube  == 0)
			{return true;}
		}
	return false;
	}
	
	
	bool is_cube_recursive(lli cube)
	{
		long double cube_root = cube* 0.01;
		long double  cube_root_prev = 0.0;
		float eps = 0.000000000000000000000000000001;
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
		std::cout<<"cube: "<<cube<<", long double cube root: "<<cube_root<<", long double cube_root_prev: "<<cube_root_prev<<", diff: "<<diff<<std::endl;//", equality: "<<(lli(cube_root*1000000) == cube_root*1000000)<<std::endl;
		if (diff < eps)//(lli(cube_root*1000000) == cube_root*1000000)
		{return true;}
	return false;
	}
	

	public:    
    void do_cubic_permutations()
    {
		long long int cube = 0;
		int power, prev_power;
		
		while (answer_set.size() < 5)
		{
			answer_set.clear();
			cube = pow(root,3);
			answer_set.insert(cube);
			power = power_of_X(cube);
			permutate_number(cube,0,power);
			root++;
		}	
		std::cout<<std::fixed<<"Ans: "<<root-1<<", answer_Set.size(): "<<answer_set.size()<<std::endl;
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
