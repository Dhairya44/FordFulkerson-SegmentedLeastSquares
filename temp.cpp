 #include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long int
#define endl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
const ll inf = 1e18;
const ll mod = 1e9 + 7;
 
double cost(vector<pair<double, double>>& points, int i, int j, double c) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;
    for (int k = i; k <= j; k++) {
        sum_x += points[k].first;
        sum_y += points[k].second;
        sum_xy += points[k].first * points[k].second;
        sum_xx += points[k].first * points[k].first;
    }
    double n = j - i + 1;
    double denominator = n * sum_xx - sum_x * sum_x;
    if (denominator == 0) {
        return INT_MAX;
    }
    double slope = (n * sum_xy - sum_x * sum_y) / denominator;
    double intercept = (sum_y - slope * sum_x) / n;
    double res = 0;
    for (int k = i; k <= j; k++) {
        double error = points[k].second - (slope * points[k].first + intercept);
        res += error * error;
    }
    return res + c;
}
 
pair<vector<pair<int, int>>, double> segmented_least_squares(vector<pair<double, double>>& points, double c) {
    int n = points.size();
    bool same_line = true;
    for (int i = 1; i < n; i++) {
        if ((points[i].second - points[0].second) * (points[i - 1].first - points[0].first) != (points[i - 1].second - points[0].second) * (points[i].first - points[0].first)) {
            same_line = false;
            break;
        }
    }
    if (same_line) {
        return {{}, 0};
    }
    // dp[j] = min(ei,j + c + dp[i - 1]) for all i <= j
    vector<double> dp(n);
    vector<int> prev(n);
    for (int i = 0; i < n; i++) {
        dp[i] = cost(points, 0, i, c);
        prev[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            double curr_cost = cost(points, i, j, c) + dp[i - 1];
            if (curr_cost < dp[j]) {
                dp[j] = curr_cost;
                prev[j] = i - 1;
            }
        }
    }
    vector<pair<int, int>> segments;
    int curr = n - 1;
    while (curr != -1) {
        cout << curr << " " << prev[curr] << endl;
        segments.pb({prev[curr] + 1, curr});
        curr = prev[curr];
    }
    reverse(segments.begin(), segments.end());
    return {segments, dp[n - 1]};
}
 
int count_partitions(vector<pair<int, int>>& segments, int n) {
    int cnt = 0;
    int last = -1;
    for (auto& p : segments) {
        if (p.first > last) {
            cnt++;
        }
        last = max(last, p.second);
    }
    if (last < n - 1) {
        cnt++;
    }
    return cnt;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // take input from points.txt
    freopen("points.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    double c;
    cin >> n >> c;
    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    pair<vector<pair<int, int>>, double> res = segmented_least_squares(points, c);
    cout << fixed << setprecision(2) << "The final cost of segments is: " << res.ss << endl;
    for (auto x : res.ff) {
        cout << "The starting index is: " << x.ff << " and " << "The ending index is: " << x.ss << endl;
    }
    cout << "The number of segments are : " << count_partitions(res.ff, n) << endl; 
    for (auto x : res.ff) {
        for (int i = x.ff; i <= x.ss; i++) {
            cout << "(" << points[i].first << ", " << points[i].second << ") ";
        }
        cout << endl;
    }
 
    for (auto x : res.ff) {
        double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;
        for (int i = x.ff; i <= x.ss; i++) {
            sum_x += points[i].first;
            sum_y += points[i].second;
            sum_xy += points[i].first * points[i].second;
            sum_xx += points[i].first * points[i].first;
        }
        double n = x.ss - x.ff + 1;
        double denominator = n * sum_xx - sum_x * sum_x;
        if (denominator == 0) {
            cout << "The equation of the line is: " << "x = " << points[x.ff].first << endl;
        } else {
            double slope = (n * sum_xy - sum_x * sum_y) / denominator;
            double intercept = (sum_y - slope * sum_x) / n;
            ofstream out;
            out.open("equations.txt", ios::app);
            out << slope << "*x+" << intercept << endl;
            out.close();
            cout << "The equation of the line is: " << "y = " << slope << "x + " << intercept << endl;
        }
    }
    
    return 0;
}