#include <iostream>
#include <thread>

using namespace std;
static int count = 0;
void mFunc1() {
        cout << "this is mFunc1" << endl;
}

void mFunc2() {
        cout << "this is mFunc2" << endl;
}

int main() {
        thread t1(mFunc1);
        thread t2(mFunc2);
        t1.detach();
        t2.detach();
        cout << "count is: " << ::count << endl;
        return 0;
}