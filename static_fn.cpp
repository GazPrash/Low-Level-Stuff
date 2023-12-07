#include<iostream>

class BaseClass{
	static const int stat_var1 = 23;	
	public:
	static int get_statvar1(){
		return stat_var1;
	}

};


int main() {
	std::cout << BaseClass :: get_statvar1();
	return 0;
}