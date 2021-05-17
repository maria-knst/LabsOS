#include <iostream>

using namespace std;

int main() {
    int element = -1;
    int sum = 0;
    cin >> element;
    while(element != -1){
        sum += element;
        cin >> element;
    }

    cout << sum << '\n';
    return 0;
}
