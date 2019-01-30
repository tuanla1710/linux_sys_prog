#include <stdio.h>
#include <stdlib.h>

typedef int(*FP)(int, int);


int add(int a, int b){
	return a+b;
}

int sub(int a, int b){
	return b-a;
}

int main(){
	
	int a=10, b=20;
	int rst;
	// int (int, int) *fp;		// 1)포인터 변수를 만들고 변수에 함수 주소를 담고자 하는 경우 선언은?
	// int(*fp)(int, int);		// 2)문법적으로 허용할 수 있는 형식은 *fp를 괄호로 닫고 함수의 return 타입과
								//	 함수의 argument 사이에 두는 것
	FP fp;						// 3) typedef를 통해 FP를 선언한 경우에 간단하게 표현하는 방법
	
	// rst = add(a,b);			// add 함수를 기본적으로 호출하는 방법
	// fp=&add;					// 함수 주소를 담을 때는 &를 붙여도 되고 안붙여도 된다
	fp=add;
	rst = fp(a,b);
	printf("rst=%d\n", rst);
	
	fp=sub;
	rst=fp(a,b);
	printf("rst=%d\n", rst);
	
	return 0;
}