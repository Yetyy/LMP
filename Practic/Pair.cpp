#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> points(n);

    for (int i = 0; i < n; ++i)
        cin >> points[i].first >> points[i].second;


    pair<pair<int, int>, pair<int, int>> answer;
    double min_dist = sqrt(pow(abs(points[1].first - points[0].first), 2) + pow(abs(points[1].second - points[0].second), 2));
    double dist;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
        {
            dist = sqrt(pow(abs(points[i].first - points[j].first), 2) + pow(abs(points[i].second - points[j].second), 2));
            if (dist < min_dist) {
                min_dist = dist;
                answer.first = points[i];
                answer.second = points[j];
            }
        }
    }

    cout << "Min distance:" << min_dist << " between (" << answer.first.first << ", " << answer.first.second << ") and (" << answer.second.first << ", " << answer.second.second << " )" << endl;;

}