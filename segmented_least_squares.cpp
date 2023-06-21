/**
 * @file segmented_least_squares.cpp
*   @authors Manasa SK - 2020A7PS0223H
*   @authors Ayush Agrawal - 2020A7PS0160H
*   @authors Vedant Mathur - 2020A7PS2047H
*   @authors Dhairya Agrawal - 2020A7PS0130H
 */
#include <bits/stdc++.h>
using namespace std;
struct Points {
    /**
     * @brief A structure to store the points
     */
    double x, y;
};
 
pair<double,double> calculate_cost(vector<Points>& points, int i, int j, double c,int z) {
    /**
     * @brief Calculates the cost of a line segment
     * @param points The vector of points
     * @param i The starting index of the line segment
     * @param j The ending index of the line segment
     * @param c The constant c
     * @param z The number of points
     */
    int k = i;
    pair<double,double> sum, sum_sq;

    while(k<=j){
        sum.first += points[k].x;
        sum.second += points[k].y;
        sum_sq.first += points[k].x * points[k].y;
        sum_sq.second += points[k].x * points[k].x;
        k++;
    }
    vector<double> pref(j - i + 1);
    pref[0] = points[i].y;
    for (int k = i + 1; k <= j; k++) {
        pref[k - i] = pref[k - i - 1] + points[k].y;
    }
 
    double n = j - i + 1;
    vector<int>suff(1000-j-1);
    suff[0] = points[j].y;
    for (int k = j - 1; k >= i; k--) {
        suff[j - k - 1] = suff[j - k - 2] + points[k].y;
    }

    double denominator = n * sum_sq.second - sum.first * sum.first;
    if (denominator == 0) {
        return {INT_MAX, 0};
    }
    double slope = (n * sum_sq.first - sum.first * sum.second) / denominator;
    double intercept = (sum.second - slope * sum.first) / n;
    double res = 0;
    k = i;
    while(k<=j){
        double error = points[k].y - (slope * points[k].x + intercept);
        res += error * error;
        k++;
    }
    return {res + c,0};
}
 
pair<vector<pair<int, int>>, double> segmented_least_squares(vector<Points>& points, double c) {
    /**
     * @brief Calculates the optimal line segments
     * @param points The vector of points
     * @param c The constant c
     */
    int n = points.size();
    bool same_line = true;
    int i = 1;
    while(i<n) {
        if ((points[i].y - points[0].y) * (points[i - 1].x - points[0].x) != (points[i - 1].y - points[0].y) * (points[i].x - points[0].x)) {
            same_line = false;
            break;
        }
        i++;
    }
    if (same_line) {
        return {{}, 0};
    }
    // vector<double> dp(n);
    // vector<int> prev(n);
    vector<pair<double,int>> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i].first = calculate_cost(points, 0, i, c, n).first;
        // prev[i] = -1;
        dp[i].second = -1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            double curr_cost = calculate_cost(points, i, j, c, n).first + dp[i - 1].first;
            if (curr_cost < dp[j].first) {
                dp[j].first = curr_cost;
                // prev[j] = i - 1;
                dp[j].second = i - 1;
            }
        }
    }
    vector<pair<int, int>> segments;
    int curr = n - 1;
    while (curr != -1) {
        segments.push_back({dp[curr].second + 1, curr});
        curr = dp[curr].second;
    }
    reverse(segments.begin(), segments.end());
    return {segments, dp[n - 1].first};
}
 
pair<int, int> partitions_calculate_count(vector<pair<int, int>>& segments, int n) {
    /**
     * @brief Calculates the number of partitions
     * @param segments The vector of segments
     * @param n The number of points
     * 
     */
    // int cnt = 0;
    // int last = -1;
    pair<int,int> val = {0,-1};
    for (auto& p : segments) {
        if (p.first > val.second) {
            val.first++;
        }
        val.second = max(val.second, p.second);
    }
    if (val.second < n - 1) {
        val.first++;
    }
    return val;
}

void printResults(pair<vector<pair<int, int>>, double> res, vector<Points>& points, int n){
    /**
     * @brief Prints the results
     * @param res The vector of segments
     * @param points The vector of points
     * @param n The number of points
     */
    cout << "Number of Segments : " << partitions_calculate_count(res.first, n).first << endl; 
    for (auto x : res.first) {
        for (int i = x.first; i <= x.second; i++) {
            cout << "(" << points[i].x << ", " << points[i].y << ") ";
        }
        cout << endl;
    }
}

void writeToFile(pair<vector<pair<int, int>>, double> res, vector<Points>& points, int n){
    /**
     * @brief Writes the results to a file
     * @param res The vector of segments
     * @param points The vector of points
     * @param n The number of points
     */
    freopen("output.txt", "w+", stdout);
    cout << partitions_calculate_count(res.first, n).first << endl; 
    for (auto x : res.first) {
        for (int i = x.first; i <= x.second; i++) {
            cout << points[i].x << " " << points[i].y << ", ";
        }
        cout << endl;
    }
}
 
int main() {
    /**
     * @brief Main function
     * Takes input from input2.txt
     * Calls the segmented_least_squares function
     * Calls the printResults function
     * Calls the writeToFile function
     */
    freopen("input2.txt", "r", stdin);
    int n;
    double c;
    cin >> n >> c;
    vector<Points> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    int t = 100;
    while(t--){
        
    }
    pair<vector<pair<int, int>>, double> res = segmented_least_squares(points, c);
    cout << "Final Cost: " << (double)res.second << endl;

    printResults(res, points, n);
    writeToFile(res, points, n);

    return 0;
}