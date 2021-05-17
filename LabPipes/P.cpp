#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int element = -1;
    cin >> element;
    while(element != -1){
        cout << pow(element,3) << " ";
        cin >> element;
    }
    
    cout << -1;
    return 0;
}
