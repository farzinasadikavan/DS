#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll seed;

ll RNG()
{
    ll a = 1103515245;
    ll m = (1LL<<31);
    ll c = 12345;
    seed = (seed * a + c) % m;
    return seed;
}

ll create_random(ll l, ll r)
{
    return (RNG() % (r-l+1)) + l;
}

class Node
{
public:
    Node* next;
    int value;

    Node(int _value)
    {
        next = nullptr;
        value = _value;
    }
};

Node* head;
Node* tail;

Node* add_node(Node* curr, Node* nw)
{
    if (curr->next == nullptr)
    {
        curr->next = nw;
        return nw;
    } else {
        return add_node(curr->next, nw);
    }
}

void print_deck(Node* head)
{
    head = head->next; // skip dummy
    while(head != nullptr)
    {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

Node* find_pos(Node* curr, int x)
{
    if(x<0)
        return nullptr;
    while(x--)
        curr = curr->next;
    return curr;
}

int main()
{
    int n, t;
    
    cin >> n >> t >> seed;

    head = new Node(-1);
    tail = head;
    for(int i=0; i<n; i++)
        tail = add_node(tail, new Node(i+1));

    while(t--)
    {
        ll x = create_random(0, n);
        ll y = create_random(0, n-x);
        if(x==0)
            continue;

        Node* n1 = find_pos(head, n-x);
        Node* n2 = n1->next;
        n1->next = nullptr;
        Node* n3 = find_pos(head, y);
        Node* n4 = n3->next;
        n3->next = n2;
        tail->next = n4;

        if (n1 == n3)
            tail = tail;
        else
            tail = n1;
    }
    print_deck(head);

    return 0;
}