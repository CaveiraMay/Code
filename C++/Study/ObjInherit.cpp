#include <iostream>
#include <string>

using namespace std;

class mObj{
        public:
        mObj(string name) {
                this->mObjName = name;
                cout << "mObj create Func, mObjName is: " << name << endl;
        }
        ~mObj() {
                cout << "mObj destory Func" << endl;
        }
        virtual void printInfo() {
                cout << "mObj printInfo Func, mObjName is: " << this->mObjName << endl;
        }
        private:
        string mObjName;
};

int main() {
        mObj *p = new mObj("test1");
        p->printInfo();
        delete p;
        return 0;
}