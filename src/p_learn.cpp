#include <iostream>
#include <string>
#define PNUM 23
#define 
using namespace std;

// Keep packet property
class P_property{
protected:
	int property[PNUM];
public:
	P_property(){
		property[0] = 10;
	}
	~P_property(){}
};


class AllData : public P_property{
private:
	int 
public:
	AllData() : P_property(){}
	~AllData(){}
	

int main(int argc, char **argv){
	P_property A;
	
	cout << A.property[0] << endl;
	A.Test();
	cout << A.property[0] << endl;
}
