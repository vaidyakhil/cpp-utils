#include<iostream>
using namespace std;

int main() {
	string name, work;

    cout << "Name" << endl;
    // can take a single word 
	cin>>name;
	cout << "Work" << endl;
	cin>>work;

	cout << "Hi " << name << "you are " << work;
	return 0;
}