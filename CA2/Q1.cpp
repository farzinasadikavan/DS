#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Maxheap implementation
struct PriorityQueue
{
private:
    // vector to store heap elements
    vector<ll> data;
 
    // return parent of `data[i]`
    // don't call this function if `i` is already a root node
    int get_parent(int i) {
        return (i-1) / 2;
    }
 
    // return left child of `data[i]`
    int left_child(int i) {
        return (2*i + 1);
    }
 
    // return right child of `data[i]`
    int right_child(int i) {
        return (2*i + 2);
    }
 
    // Recursive heapify-down algorithm.
    // The node at index `i` and its two direct children
    // violates the heap property
    void heapify_down(int i)
    {
        // get left and right child of node at index `i`
        int left = left_child(i);
        int right = right_child(i);
 
        int largest = i;
 
        // compare `data[i]` with its left and right child
        // and find the largest value
        if (left < size() && data[left] > data[largest]) {
            largest = left;
        }
 
        if (right < size() && data[right] > data[largest]) {
            largest = right;
        }
 
        // swap with a child having greater value and
        // call heapify-down on the child
        if (largest != i)
        {
            swap(data[i], data[largest]);
            heapify_down(largest);
        }
    }
 
    // Recursive heapify-up algorithm
    void heapify_up(int i)
    {
        // check if the node at index `i` and its parent violate the heap property
        if (i && data[get_parent(i)] < data[i])
        {
            // swap the two if heap property is violated
            swap(data[i], data[get_parent(i)]);
 
            // call heapify-up on the parent
            heapify_up(get_parent(i));
        }
    }
 
public:
    // return size of the heap, O(1)
    int size() {
        return data.size();
    }
 
    // Function to check if the heap is empty or not, O(1)
    bool empty() {
        return size() == 0;
    }
 
    // insert key into the heap, O(log(N))
    void push(ll key)
    {
        // insert a new element at the end of the vector
        data.push_back(key);
 
        // get element index and call heapify-up procedure
        int index = size() - 1;
        heapify_up(index);
    }
 
    // Function to remove an element with the highest priority (present at the root), O(log(N))
    void pop()
    {
		// if the heap has no elements, throw an exception
		if (size() == 0)
			throw out_of_range("Heap Underflow");

		// replace the root of the heap with the last element
		// of the vector
		data[0] = data.back();
		data.pop_back();

		// call heapify-down on the root node
		heapify_down(0);
    }
 
    // Function to return an element with the highest priority (present at the root), O(1)
    ll top()
    {
		// if the heap has no elements, throw an exception
		if (size() == 0)
			throw out_of_range("Heap Underflow");

		// otherwise, return the top (first) element
		return data.at(0);        // or return data[0];   
    }
};

int main()
{
    ll n, giant_power, max_actions;
    cin >> n >> giant_power >> max_actions;
	
	PriorityQueue soldier_powers;

    for (int i=0; i<n; i++)
    {
        ll power;
        cin >> power;
        soldier_powers.push(power);
    }

    ll steps = 0;
    for (int i = 0; i<max_actions; i++)
    {
		// Each action, we choose soldier with the highest power to fight giant
        ll x = soldier_powers.top();
        if (x==0)
        {
            cout << -1 << endl;
            return 0;
        }
        
		soldier_powers.pop();
        soldier_powers.push(x/2);
		giant_power -= x;
		steps++;

		if (giant_power <= 0)
        {
            cout << steps << endl;
            return 0;
        }
    }

    cout << -1 << endl;
}