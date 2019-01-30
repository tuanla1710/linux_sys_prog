#include <stdio.h>
#include <stdlib.h>

typedef int(*FP)(int, int);


// int add(int a, FP b){			//add 함수의 2번째 인자에 함수포인터를 전달받고자 하는 경우
int add(int a, int(*b)(int, int)){	// typedef가 없는 경우 함수 선언으로 전환한 경우, 읨의의 변수 b로 선언
	int rst;
	rst=b(10,20);					//변수 b는 sub를 하는 함수포인터 -> 메인에서 add 호출시 넘김
	printf("RST= %d\n", rst);
	return a+rst;
}

int sub(int a, int b){
	return b-a;
}

// FP f1(int x){
// int(*)(int, int) f1(int x){
int(*f1(int x,int(*y)(int, int)))(int, int) {
	// if(x==1)
		// return add;
	// else if(x==2)
		return sub;
}

int main(){
	
	int a=10, b=20;
	FP rst1;
	int rst2;
	int number;

	rst2=add(20, sub);			//add 함수가 2번째 인자로 함수(함수포인터)를 받기 때문에 함수주소를 넘김)
	
	printf("rst2=%d\n", rst2);
	
	return 0;
}