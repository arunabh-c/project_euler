#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>

void fill_cell_value_sets(std::vector<std::vector<int>> &A, std::vector<std::vector<std::set<int>>> &A_set)
{
    for (int row=0;row<A.size();row++)
    {
        for (int col=0;col<A.size();col++)
        {
            if (A[row][col] == 0)
            {
                std::set<int> pos_vals = {1,2,3,4,5,6,7,8,9};
                for (int i = 0;i<A.size();i++)
                {
                    if (A[row][i] != 0)
                    {
                        pos_vals.erase(A[row][i]);
                    }
                    if (A[i][col] != 0)
                    {
                        pos_vals.erase(A[i][col]);
                    }
                }
    
                int row_offset = 3*(row/3);
                int col_offset = 3*(col/3);
                for (int i = row_offset;i<=row_offset+2;i++)
                {
                    for (int j = col_offset;j<=col_offset+2;j++)
                    {
                        if (A[i][j] != 0)
                        {
                            pos_vals.erase(A[i][j]);
                        }
            
                    }
                }
                A_set[row][col] = pos_vals;
            }
        }
    }
}

void remove_common_elements(std::set<int> &remove_from, std::set<int> &remove_of)
{
    for(std::set<int>::iterator it = remove_of.begin(); it != remove_of.end(); it++) 
    {
        remove_from.erase(*it);
    }
}

void delete_value_fron_sets(const int &row,const int &col,int &value,std::vector<std::vector<std::set<int>>> &A_set)
{
                for (int i = 0;i<A_set.size();i++)
                {
                        A_set[row][i].erase(value);
                        A_set[i][col].erase(value);
                }
    
                int row_offset = 3*(row/3);
                int col_offset = 3*(col/3);
                for (int i = row_offset;i<=row_offset+2;i++)
                {
                    for (int j = col_offset;j<=col_offset+2;j++)
                    {
                        A_set[i][j].erase(value);
                    }
                }
}

void singleton_set_fill(int &row,int &col,std::vector<std::vector<int>> &A,std::vector<std::vector<std::set<int>>> &A_set, int &zeros, int &value)
{
    A[row][col] = value; 
    --zeros;

    A_set[row][col] = {};
    delete_value_fron_sets(row,col,value,A_set);
}

void deduce_from_cell_value_sets(std::vector<std::vector<int>> &A, std::vector<std::vector<std::set<int>>> &A_set, int &zeros)
{
    std::set<int> temp;
    for (int row=0;row<A.size();row++)
    {
        for (int col=0;col<A.size();col++)
        {
            if (A_set[row][col].size() > 1 && A[row][col] == 0)
            {
                temp = A_set[row][col];
                for (int i = 0;i<A.size();i++)
                {
                    if (A_set[row][i].size() > 0 && i != col)
                    {
                        remove_common_elements(temp,A_set[row][i]);
                    }
                    
                }
                if (temp.size() == 1)
                {
                    int x = *temp.begin();
                    singleton_set_fill(row,col,A,A_set,zeros,x);
                    continue;
                }

                temp = A_set[row][col];
                for (int i = 0;i<A.size();i++)
                {
                    if (A_set[i][col].size() > 0 && i != row)
                    {
                        remove_common_elements(temp,A_set[i][col]);
                    }
                }
                if (temp.size() == 1)
                {
                    int x = *temp.begin();
                    singleton_set_fill(row,col,A,A_set,zeros,x);
                    continue;
                }
    
                int row_offset = 3*(row/3);
                int col_offset = 3*(col/3);
                temp = A_set[row][col];
                for (int i = row_offset;i<=row_offset+2;i++)
                {
                    for (int j = col_offset;j<=col_offset+2;j++)
                    {
                        if (A_set[i][j].size() > 0 && (i != row || j!= col))
                        {
                            remove_common_elements(temp,A_set[i][j]);
                        }
            
                    }
                }
                if (temp.size() == 1)
                {
                    int x = *temp.begin();
                    singleton_set_fill(row,col,A,A_set,zeros,x);
                    continue;
                }
            }
            else if (A_set[row][col].size() == 1 && A[row][col] == 0)
            {
                    int x = *A_set[row][col].begin();
                    singleton_set_fill(row,col,A,A_set,zeros,x);
                    continue;
            }
        }
    }   
}

int display_matrix(std::vector<std::vector<int>> &A)
{
    int zero_counter = 0;
    for (int row=0;row<A.size();row++)
    {
        for (int col=0;col<A.size();col++)
        {
            if (A[row][col] == 0)
            {
                zero_counter++;
            }
            std::cout<<A[row][col]<<" ";
            if (col == 8)
            {
                std::cout<<std::endl;
            }
            else if ((col+1)%3 == 0)
            {
                std::cout<<"|";
            }
        }
        if ((row+1)%3 == 0)
        {
            std::cout<<std::endl;
        }
    }
    return zero_counter;
}

void solve (int &loop, int &pre_loop, std::vector<std::vector<std::set<int>>> &A_set, std::vector<std::vector<int>> &A, bool &solved)
{
    while (loop > 0 && pre_loop != loop)
    {
        pre_loop = loop;
        A_set = {{{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}},
                 {{},{},{},{},{},{},{},{},{}}};
        fill_cell_value_sets(A,A_set);
        deduce_from_cell_value_sets(A, A_set, loop);
    }
    if (loop == 0)
    {
        solved = true;
    }
}

void solve_recursively(int &loop, int &pre_loop, std::vector<std::vector<std::set<int>>> &A_set, std::vector<std::vector<int>> &A, bool &solved)
{
    std::vector<std::vector<std::set<int>>> A_set_copy = A_set;
    std::vector<std::vector<int>> A_copy = A;
    int loop_copy = loop;
    int pre_loop_copy = pre_loop; 
    std::set<int> temp;
        int row_it = -1;
        int col_it;
        for (int row =0;row<A_set.size();row++)
        {
            for (int col = 0;col<A_set.size();col++)
            {
                if (A_set[row][col].size() > 0)
                {
                    temp = A_set_copy[row][col];
                    row_it = row;
                    col_it = col;
                    break;
                }
            }
        }       
        if (row_it < 0)
        {
            return;
        }
        
        for(std::set<int>::iterator it = temp.begin(); it != temp.end(); it++) {
            A_copy = A;
            loop_copy = loop;
            A_copy[row_it][col_it] = *it;
            --loop_copy;
            pre_loop_copy = 0;
            solve(loop_copy, pre_loop_copy, A_set_copy, A_copy, solved);
            if (loop_copy > 0)
            {
                solve_recursively(loop_copy, pre_loop_copy, A_set_copy, A_copy, solved);
            }
            else
            {
                A = A_copy;
                A_set = A_set_copy;
                loop = loop_copy;
                return;
            }
            if (solved)
            {
                A = A_copy;
                A_set = A_set_copy;
                loop = loop_copy;
                break;
            }
        }
}

int main()
{
    std::string line;
    std::vector<std::vector<int>> X = {{0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0}};    
    int row_counter =0;
    std::ifstream out("p096_sudoku.txt");
    int sum = 0;
    while(getline(out, line)) {
        if (!isdigit(line[0]))
        {
            row_counter = 0;
        }
        else{
            std::vector<int> xx = {line[0],line[1],line[2],line[3],line[4],line[5],line[6],line[7],line[8]};
            for ( int j = 0; j < xx.size(); j++ ) {
                X[row_counter][j] = ((int)xx[j] - 48);
            }
            row_counter++;
            if (row_counter == 9)
            {
                std::vector<std::vector<std::set<int>>> X_set;
                std::cout<<"unsolved array solution: "<<std::endl;
                int loop = display_matrix(X);
                int pre_loop = 0;
                bool solved = false;
                solve (loop, pre_loop, X_set, X, solved);

                if (loop > 0)
                {
                    solve_recursively(loop, pre_loop, X_set, X, solved);
                }
                std::cout<<"solved array solution: "<<std::endl;
                display_matrix(X);
                std::cout<<std::endl;
                sum = sum + X[0][0] * 100 + X[0][1] * 10 + X[0][2];
            }    
        }
    }
    std::cout<<sum;
    out.close();
    return 0;
}
