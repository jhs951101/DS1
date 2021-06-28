#include<iostream>

using namespace std;

struct FractionType{  // 분수를 의미하는 구조체
   long long num;
   long long den;
};

long long gcd(long long n, long long m){  // 두 수의 최대공약수를 구하는 함수

	while(n%m != 0){  // n과 m의 최대공약수를 구함(n,m: 정수)
		long long rem = n%m;
		n = m;
		m = rem;
	}

	return m;
}

long long lcm(long long m, long long n){  // 두 수의 최소공배수를 구하는 함수

	return m * n / gcd(m, n);  // n과 m의 최대공약수를 먼저 구한 후 최소공배수를 계산
}

void Reduction(FractionType& a){  // 약분하는 함수

	long long n = gcd(a.num, a.den);  // num과 den의 최대공약수를 구함

	a.num = a.num / n;  // num과 den을 최대공약수로 나눔으로써 약분이 됨
	a.den = a.den / n;

}
 
FractionType Add(FractionType a, FractionType b){  // 분수의 덧셈

   FractionType result;
   result.den = lcm(a.den, b.den);  // 덧셈 후의 분모를 구함
   result.num = a.num*(result.den/a.den) + b.num*(result.den/b.den);  // 덧셈 후의 분자를 구함

   Reduction(result);  // 분수를 약분해줌

   return result;

}

FractionType Sub(FractionType a, FractionType b){  // 분수의 뻴셈

	FractionType result;
	result.den = lcm(a.den, b.den);  // 뻴셈 후의 분모를 구함
	result.num = a.num*(result.den/a.den) - b.num*(result.den/b.den);  // 뻴셈 후의 분자를 구함

	Reduction(result);  // 분수를 약분해줌

	return result;

}

FractionType Mpy(FractionType a, FractionType b){  // 분수의 곱셈

	FractionType result;
	result.den = a.den * b.den;  // 곱셈 후의 분모를 구함
	result.num = a.num * b.num;  // 곱셈 후의 분자를 구함

	Reduction(result);  // 분수를 약분해줌

	return result;

}

FractionType Div(FractionType a, FractionType b, bool& possible){  // 분수의 나눗셈

	long long swap = b.den;  // 두번째 분수의 분자와 분모를 서로 맞바꿈
	b.den = b.num;
	b.num = swap;

	FractionType result;
	result.den = a.den * b.den;  // 나눗셈 후의 분모를 구함
	result.num = a.num * b.num;  // 나눗셈 후의 분자를 구함

	if(result.den == 0)  // 분모가 0일 경우 false로 지정, 아니면 약분 진행
		possible = false;
	else
		Reduction(result);  // 분수를 약분해줌

	return result;

}

int main(){

	FractionType f1, f2;  // f1: 연산할 첫번째 분수
						  // f2: 연산할 두번째 분수
	bool div_pos = true;  // div_pos: 나눗셈을 통해 분모가 0이 되었을 경우 false로 바뀜

	cout << "Assignment1-2" << endl;
	cout << "Input two fractions: ";
	cin >> f1.num >> f1.den >> f2.num >> f2.den;  // "3 6 2 5" 이런 식으로 입력받음

	if(f1.den == 0 || f2.den == 0){  // 분모가 0일 경우 프로그램을 종료함
			cout << "(0으로 나눌수 없습니다)" << endl;
			return 1;
	}

	for(int i=1; i<=4; i++){  // 루프가 4번 진행됨으로써 4가지의 연산이 모두 진행됨

		FractionType c;  // c: 연산 후의 분수를 저장

		cout << "(" << f1.num << "/" << f1.den << ") ";  // 선 출력문

		if(i == 1){  // 1. 덧셈

			c = Add(f1, f2);  // 덧셈 함수로부터 결과값을 받음
			cout << "+";	
		}
		else if(i == 2){  // 2. 뻴셈

			c = Sub(f1, f2);  // 뻴셈 함수로부터 결과값을 받음
			cout << "-";
		}
		else if(i == 3){  // 3. 곱셈

			c = Mpy(f1, f2);  // 곱셈 함수로부터 결과값을 받음
			cout << "*";
		}
		else{  // 4. 나눗셈

			c = Div(f1, f2, div_pos);  // 나눗셈 함수로부터 결과값을 받음
			cout << "/";
		}

		cout << " (" << f2.num << "/" << f2.den << ") = ";

		if(div_pos == false){  // 나눗셈 결과 분모가 0일 경우 종료함
			cout << "(0으로 나눌수 없습니다)" << endl;
			break;
		}

		cout << c.num;

		if(c.den != 1)  // 분모가 1이면 분자만 출력시킴
			cout << "/" << c.den << endl;
		else
			cout << endl;

		c.num = 0;  // 돌아갈 때 마다 c의 모든 값을 0으로 초기화
		c.den = 0;

	}

	return 0;
}