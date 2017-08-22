#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv){
    vector<int> a(10);


    for(int i=0;i<10;++i){
        a[i] = i+10;
        cout<<a[i]<<" ";
    }

    return 0;

}
