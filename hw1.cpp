#include<iostream>

using namespace std;

long long gcd(long long n, long long m){  // 두 수의 최대공약수를 구하는 함수

   while (n % m != 0)  // n과 m의 최대공약수를 구함(n,m: 정수)
   {  long long rem;
      rem = n % m;
      n = m;
      m = rem ;     
   }
   return m;

}

long long lcm(long long m, long long n){  // 두 수의 최소공배수를 구하는 함수

   long long temp = gcd(m, n);  // n과 m의 최대공약수를 먼저 구한 후 최소공배수를 계산
   return m * n / temp;

}

void Reduction(long long num, long long den, long long& result_num, long long& result_den){  // 약분하는 함수

	num = result_num;  // num, den을 서로 약분하기 위해 우선 값을 넣어줌
	den = result_den;

	result_num = result_num / gcd(num, den);  // num과 den의 최대공약수를 구한 후 나눔으로써 약분이 됨
	result_den = result_den / gcd(num, den);

}

void Add(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den){  // 더하는 함수

    result_den = lcm(den1, den2);  // 덧셈 후의 분모를 구함
    result_num = num1*(result_den/den1) + num2*(result_den/den2);  // 덧셈 후의 분자를 구함 

	Reduction(0, 0, result_num, result_den);  // 분수를 약분해줌

}

void Sub(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den){  // 빼는 함수

	result_den = lcm(den1, den2);  // 뻴셈 후의 분모를 구함
    result_num = num1*(result_den/den1) - num2*(result_den/den2);  // 뻴셈 후의 분자를 구함

	Reduction(0, 0, result_num, result_den);  // 분수를 약분해줌

}

void Mpy(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den){  // 곱하는 함수

	result_den = den1 * den2;  // 곱셈 후의 분모를 구함
	result_num = num1 * num2;  // 곱셈 후의 분자를 구함

	Reduction(0, 0, result_num, result_den);  // 분수를 약분해줌

}

void Div(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den, bool& possible){  // 나누는 함수

	long long swap = den2;  // 두번째 분수의 분자와 분모를 서로 맞바꿈
	den2 = num2;
	num2 = swap;

	result_den = den1 * den2;  // 곱셈 후의 분모를 구함
	result_num = num1 * num2;  // 곱셈 후의 분자를 구함

	if(result_den == 0)  // 분모가 0일 경우 false로 지정, 아니면 연산 진행
		possible = false;
	else
		Reduction(0, 0, result_num, result_den);

}

int main(){

	long long n1, n2;  // n1, n2: 각 입력받은 분자의 값을 저장함
	long long d1, d2;  // d1, d2: 각 입력받은 분모의 값을 저장함
	long long result_n=0, result_d=0;  // result_n: 연산 후의 분자를 저장
								 // result_d: 연산 후의 분모를 저장
	bool div_pos = true;  // div_pos: 나눗셈을 통해 분모가 0이 되었을 경우 false로 바뀜

	cout << "Assignment1-1" << endl;
	cout << "Input two fractions: ";
	cin >> n1 >> d1 >> n2 >> d2;  // "3 6 2 5" 이런 식으로 입력받음

	if(d1 == 0 || d2 == 0){  // 분모가 0일 경우 프로그램을 종료함
			cout << "(0으로 나눌수 없습니다)" << endl;
			return 1;
	}

	for(int i=1; i<=4; i++){  // 루프가 4번 진행됨으로써 4가지의 연산이 모두 진행됨

		cout << "(" << n1 << "/" << d1 << ") ";  // 선 출력문

		if(i == 1){  // 1. 덧셈

			Add(n1, d1, n2, d2, result_n, result_d);  // 덧셈 함수로 접근함으로써 새로운 결과값을 가짐
			cout << "+";

		}
		else if(i == 2){  // 2. 뻴셈

			Sub(n1, d1, n2, d2, result_n, result_d);  // 뻴셈 함수로 접근함으로써 새로운 결과값을 가짐
			cout << "-";

		}
		else if(i == 3){  // 3. 곱셈

			Mpy(n1, d1, n2, d2, result_n, result_d);  // 곱셈 함수로 접근함으로써 새로운 결과값을 가짐
			cout << "*";

		}
		else{  // 4. 나눗셈

			Div(n1, d1, n2, d2, result_n, result_d, div_pos);  // 나눗셈 함수로 접근함으로써 새로운 결과값을 가짐
			cout << "/";

		}

		cout << " (" << n2 << "/" << d2 << ") = ";

		if(div_pos == false){  // 나눗셈 결과 분모가 0일 경우 종료함
			cout << "(0으로 나눌수 없습니다)" << endl;
			break;
		}

		cout << result_n;

		if(result_d != 1)  // 분모가 1이면 분자만 출력시킴
			cout << "/" << result_d << endl;
		else
			cout << endl;
		
		result_n = 0;  // 돌아갈 때 마다 result값을 0으로 초기화
		result_d = 0;
	}

	return 0;
}