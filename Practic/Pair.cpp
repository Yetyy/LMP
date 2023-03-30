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

    for (int i = 1; i < n; i++) {
        if (points[i].first - points[i - 1].first < min_dist) {
            min_dist = sqrt(pow(abs(points[1].first - points[0].first), 2) + pow(abs(points[1].second - points[0].second), 2));
            answer.first = points[i];
            answer.second = points[i - 1];
        }
    }

    cout << "Min distance:" << min_dist << " between (" << answer.first.first << ", " << answer.first.second << ") and (" << answer.second.first << ", " << answer.second.second << " )" << endl;;

}