#include <iostream>
#include <string>
using namespace std;


int main(){

    string a;
    void* mem = malloc(8000000);
    cout<<"Presionar cualquier tecla para terminar"<<"\n";
    cin>>a;
    free(mem);
    return 0;
}