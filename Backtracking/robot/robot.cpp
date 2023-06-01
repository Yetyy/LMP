#include <iostream>
#include <vector>
#include <fstream>
int n,m;
int fi, fj; // место финиша
std::vector<std::vector<int> > arr;
std::vector < std::vector<bool> > holes;
int sum = 0;
int sum_max = 0;
int path_len;
void dfs(int cur_i , int cur_j) {
    if ((cur_i != fi) || (cur_j != fj))
    {
        sum += arr[cur_i][cur_j];
            if ((cur_i + 1 < n) && (!holes[cur_i + 1][cur_j]))
            {
                dfs(cur_i + 1, cur_j);
            }
            if ((cur_j + 1 < m) && (!holes[cur_i][cur_j + 1]))
            {
                dfs(cur_i, cur_j + 1);
            }
                    sum -= arr[cur_i][cur_j];
    }
        sum += arr[n - 1][m - 1];// последний элемент удалили из за строки 23 хз как исправить
    if ((cur_i == fi) && (cur_j == fj) && (sum != 0) && (sum < sum_max) || sum_max == 0)
    {
        sum_max = sum;
    }
        sum -= arr[n - 1][m - 1];
}
int main(){
    std::fstream file("data.txt");
    file >> n >> m;
    arr.resize(m);
    for (int i = 0; i < n; ++i)
        arr[i].resize(n);
    holes.resize(m);
    for (int i = 0; i < n; ++i)
        holes[i].resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            holes[i][j] = 0;
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j= 0; j < m; j++)
        {
            file >> arr[i][j];
        }
    }
    //std::cout << "N Holes:\n"; //нереализовал в data.txt вместо них просто 111 поля
    //int i, j, k;
    //std::cin >> k;
    //for (size_t c = 0; c < k; c++)
    //{
    //    std::cin >> i >> j;
    //    holes[i][j] = 1;
    //}
    fi = n-1;
    fj = m-1;
    dfs(0, 0);
    std::cout <<"\nSum: " << sum_max;
    std::cin.get();
}