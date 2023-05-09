#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <Windows.h>
using namespace std;

const int MAX_N = 100; 
int n; 
int m; 
std::vector<std::vector<int> > dist;
vector<bool> visited;
list<int> path; //list
int path_len; 
bool dfs(int cur_vertex, int start_vertex, int max_len) {
    visited[cur_vertex] = true;
    bool result = false;
    path.push_back(cur_vertex);

    if (path.size() == n) { 
        if (dist[cur_vertex][start_vertex] > 0 && path_len + dist[cur_vertex][start_vertex] <= max_len) {
            path.push_back(start_vertex);
            result = true;
        }
    
    }
   for (int i = 0; i <= n; i++) {
        if (i != cur_vertex && !visited[i] && dist[cur_vertex][i] > 0 && path_len + dist[cur_vertex][i] <= max_len) {
            path_len += dist[cur_vertex][i];
            if (dfs(i, start_vertex, max_len)) {
                result = true;
                path_len -= dist[cur_vertex][i];
            }
        }
    }
   if (!result)
   {
       path.pop_back();
       visited[cur_vertex] = false;
   }
    return result;
}


list<int> find_closed_path(int max_len) {
    path.clear();
    path_len = 0;
    bool found = false;
    int i = 0;
    while (!found && i < n) {
        for (int j = 0; j < n + 1; j++)
            visited[j] = false;
        path_len = 0;
        if (dfs(i, i, max_len)) {
            found = true;
        }
        i++;
    }
    if (found) {
        return path;
    }
    else {
        return list<int>();
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "������� ���������� ������: ";
    cin >> n;
    cout << "������� ���������� �����: ";
    cin >> m;
    visited.resize(n+1);
    dist.resize(n+1);
    for (int i = 0; i < n+1; ++i)
        dist[i].resize(n+1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = 0;
        }
    }
    cout << "������� ����� � ���� 3 ����� u v w, ��� u � v - ������� ������, � w - ��� �����:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
        dist[v][u] = w;
    }
    int max_len;
    cout << "������� ������������ ����� ����: ";
    cin >> max_len;
    list<int> path = find_closed_path(max_len);
    if (path.empty()) {
        cout << "��������� ���� �� ������" << endl;
    }
    else {
        cout << "��������� ����: ";
        for (int i : path)
            cout << i << " ";
        cout << endl;
    }
    return 0;
}