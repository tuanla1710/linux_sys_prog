#include <stdio.h>
#include <stdlib.h>

int add(int a, int b){
	return a+b;
}

int sub(int a, int b){
	return b-a;
}

int main(){
	
	int a=10, b=20;
	int *ap;
	
	ap=&a;			// a 변수의 주소를 담는다, 이 때 a 변수의 주소를 담는 포인터는 변수 a 타입이어야 한다
	
	printf("a=%d\n", a);
	
	return 0;
}