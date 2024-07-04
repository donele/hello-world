#include <vector>
#include <iostream>
#include <myinclude.h>
using namespace std;
int main() {
    vector<int> a {1,2,3};
    double sum2 {0};
    for(int x : a) {
        sum2 += x*x;
        std::cout << x << ' ' << sum2 << std::endl;
    }
    return sum2;
}
