#include <stdio.h>
#include <stdlib.h>

typedef int(*FP)(int, int);


int add(int a, int b){
	return a+b;
}

int sub(int a, int b){
	return b-a;
}

// FP f1(int x){				// 1) 함수를 담고 있는 함수포인터를 return하는 
								//    함수 f1을 선언하는 경우의 기본원칙 (typedef을 한 경우)
// int(*)(int, int) f1(int x){	// 2) typedef가 없이 선언하고자 한다면 
								//    typedef에서 FP만을 제외한 나머지를 그대로 대입한 것과 같다
int(*f1(int x))(int, int) {		// 3) 문법상 완성을 위해서 fi(int x)를 함수포인터 안의 괄호에 그대로 대입
	if(x==1)
		return add;
	else if(x==2)
		return sub;
}

int main(){
	
	int a=10, b=20;
	FP rst1;
	int rst2;
	int number;

	printf("Input number: \n");
	scanf("%d", &number);			//입력을 받아들인다
	
	rst1=f1(number);				//입력받은 값을 함수 f1의 인자로 넘긴후 값을 rst1으로 받는다
	rst2 = rst1(a,b);
	
	printf("rst2=%d\n", rst2);
	
	return 0;
}