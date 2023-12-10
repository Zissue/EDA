#include <iostream>
#include <queue>
using namespace std;

typedef priority_queue<int> Q;

int main () {
    
    Q q1;
    
    char op;
    while (cin >> op) {
        int x;
        
        if (op == 'S' and cin >> x) {
            q1.push(x);
        }
        
        else if (op == 'A') {
            if (not q1.empty()) {
                int max = q1.top();
                cout << max;
            }
            else cout << "error!";
            cout << endl;
        }
        
        else if (op == 'R') {
            if (not q1.empty()) {
                q1.pop();
            }
            else cout << "error!" << endl;
        }
        
        else if (op == 'I' and cin >> x) {
            
            if (not q1.empty()) {
                int top = q1.top() + x;
                q1.pop();
                q1.push(top);
            }
            else cout << "error!" << endl;
        }
        
        else if (op == 'D' and cin >> x) {
            
            if (not q1.empty()) {
                int top = q1.top() - x;
                q1.pop();
                q1.push(top);
            }
            else cout << "error!" << endl;
        }
    }
}