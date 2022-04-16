#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 2e5 + 22;

int a[N];
int gt_index_left[N]; 
// gt_index_left[i] : highest index less than i which a[x] > a[i]

int gte_index_right[N]; 
// gte_index_right[i] : minimum index greater than i which a[x] >= a[i]

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

int32_t main()
{
	// To speed up I/O actions 
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;

	for(int i=0; i<n; i++)
        cin >> a[i];

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
    
	map<int, ll> answer;
	// for each element, calculate number of subarrays which it is maximum
	// then add result to overall answer of value
    for (int i=0; i<n; i++)
		answer[a[i]] +=  (1LL * (gte_index_right[i]-i) * (i-gt_index_left[i]));
        
    while(q--) 
	{
        int x;
        cin >> x;
        cout << answer[x] << endl;
    }

    return 0;
}