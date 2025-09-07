#include <iostream>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

unordered_map<int64_t, vector<int64_t>> cd;//cube_dir

int64_t sort_num(int64_t num)
{
	vector<int> dig;
	int64_t ans = 0;
	while (num)
	{
		dig.emplace_back(num%10);
		num /= 10;
	}

	sort(dig.begin(), dig.end());

	for (int i = 0; i < dig.size(); ++i)
		ans += dig[i] * pow(10,i);
	return ans;
}

int main()
{
   uint8_t cnt = 0;
   int64_t ip = 5;
   while (cnt < 5)
   {
       int64_t cube = pow(ip,3);
       int64_t cube_sort = sort_num(cube);
       cd[cube_sort].emplace_back(cube);
       //   cout<<"ip: "<<ip<<", cube_sort: "<<cube_sort<<", cm[cube_sort]: "<<cm[cube_sort]<<endl;
       cnt = max(cnt, (uint8_t)cd[cube_sort].size());
       if (cnt == 5)
       {
          cout<<fixed<<"ans is "<<cd[cube_sort][0]<<endl;
          break;
       }
       ip++;
   }
   
   return 0;
}
