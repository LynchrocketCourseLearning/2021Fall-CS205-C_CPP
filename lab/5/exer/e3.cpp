#include<iostream>
using std::cout;
using std::endl;

// naive approach to see if num is a prime number
bool isPrime( int num ) {
	for( int i = 1; i <= num; ++ i )
    //for( int i = 2; i < num; ++ i )
		if( num % i == 0 )
			return false;
	//return true;
    return false;
}

int main() {
	int a = 23;
	cout<<isPrime(a)<<endl;
    return 0;
}
