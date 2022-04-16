#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 2e5 + 22;

int a[N];
int gt_index_left[N]; 
// gt_index_left[i] : highest index less than i which a[x] > a[i]

int gte_index_right[N]; 
// gte_index_right[i] : minimum index greater than i which a[x] >= a[i]

ll answer[N];
// answer[i] : number of subarrays with maximum i

template<typename T>
class Stack {
private:
	T data[N];
	int size = 0;
public:
	void pop() {
		if (size == 0)
			throw out_of_range("Stack Underflow");
		size--;
	}
	
	bool empty() {
		return size == 0;
	}

	T top() {
		if (size == 0)
			throw out_of_range("Stack Underflow");
		return data[size-1];
	}

	void push(T x)
	{
		if (size == N)
			throw out_of_range("Stack Overflow!");
		data[size] = x;
		size++;
	}
};

// Calculate normalized value of 'x' with lower_bound
int f_with_lower_bound(vector<int> normalized_values, int x)
{
	auto it = lower_bound(normalized_values.begin(), normalized_values.end(), x);
	if (it == normalized_values.end())
		return -1;
	if (it == normalized_values.begin() && *it != x)
		return -1;
	return it - normalized_values.begin();
}

// A recursive binary search function. It returns
// location of x in given array arr[l..r) is present,
// otherwise -1
int BinarySearch(const vector<int>& vec, int low, int high, int x)
{
	if (low >= high)
		return -1;
	
	int mid = (low + high) / 2;

	if (vec[mid] == x)
		return mid;
	else if (vec[mid] > x)
		return BinarySearch(vec, low, mid, x);
	else if (vec[mid] < x)
		return BinarySearch(vec, mid+1, high, x);
}

// Calculate normalized value of 'x' with binary search
int f(const vector<int>& normalized_values, int x)
{
	int normalized_x = BinarySearch(normalized_values, 0, normalized_values.size(), x);
	return normalized_x;
}

int32_t main()
{
	// To speed up I/O actions 
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	vector<int> normalized_values;

    int n, q;
    cin >> n >> q;

	for(int i=0; i<n; i++)
	{
		cin >> a[i];
		normalized_values.push_back(a[i]);
	}

	// normaliz values, erase duplicates
	sort(normalized_values.begin(), normalized_values.end());
	normalized_values.erase(
		unique(normalized_values.begin(), normalized_values.end()), normalized_values.end());
    
	for(int i=0; i<n; i++)
		a[i] = f(normalized_values, a[i]);

    Stack<int> s; // decreasing subsequence start from 0 to n
    for(int i=0; i<n; i++) 
	{
		// Delete each index which is less or equal than current value
		while (!s.empty() && a[i] >= a[s.top()])
			s.pop();
		
		if (s.empty())
			gt_index_left[i] = -1;
		else
			gt_index_left[i] = s.top();

        s.push(i);
    }

	Stack<int> ss; // decreasing subsequence started from end of array to begin
	for(int i=n-1; i>=0; i--)
	{
		// Delete each index which is strictly less than currnet value
		while (!ss.empty() && a[i] > a[ss.top()])
			ss.pop();
		
		if (ss.empty())
			gte_index_right[i] = n;
		else
			gte_index_right[i] = ss.top();
		
		ss.push(i);
	}
    
	// for each element, calculate number of subarrays which it is maximum
	// then add result to overall answer of value
    for (int i=0; i<n; i++)
		answer[a[i]] +=  (1LL * (gte_index_right[i]-i) * (i-gt_index_left[i]));
        
    while(q--) 
	{
        int x;
        cin >> x;
		int normalized_x = f(normalized_values, x);
		if (normalized_x == -1)
			cout << 0 << endl;
		else
        	cout << answer[normalized_x] << endl;
    }

    return 0;
}