#include<iostream>

using namespace std;

bool div_pos = true;  // div_pos: 나눗셈을 통해 분모가 0이 되었을 경우 false로 바뀜 (전역변수)

long long gcd(long long a, long long b){  // 두 수의 최대공약수를 구하는 함수
	
	while(a%b != 0){  // n과 m의 최대공약수를 구함(n,m: 정수)
		long long rem = a%b;
		a = b;
		b = rem;
	}

	return b;

}

class FractionType  // 분수에 대한 클래스
{
public:
	void Initialize(long long num, long long den){  // num과 den의 값을 세팅함

		this->num = num;
		this->den = den;
	}

	void Reduction(FractionType& r){  // 약분하는 함수

		long long n = gcd(r.num, r.den);  // num과 den의 최대공약수를 구함
		r.num = r.num / n;  // num과 den을 최대공약수로 나눔으로써 약분이 됨
		r.den = r.den / n;
	}

	FractionType operator + (FractionType second){  // 분수의 덧셈

		FractionType result;  // result: 연산 후의 결과값을 저장
		result.Initialize(0, 0);  // result의 num과 den을 세팅해줌

		result.den = this->den * second.den;  // 덧셈 후의 분모를 구함
		result.num = this->num * second.den + this->den * second.num;  // 덧셈 후의 분자를 구함

		Reduction(result);  // 분수를 약분해줌

		return result;

	}

	FractionType operator - (FractionType second){  // 분수의 뻴셈

		FractionType result;  // result: 연산 후의 결과값을 저장
		result.Initialize(0, 0);  // result의 num과 den을 세팅해줌

		result.den = this->den * second.den;  // 뻴셈 후의 분모를 구함
		result.num = this->num * second.den - this->den * second.num;  // 뻴셈 후의 분자를 구함

		Reduction(result);  // 분수를 약분해줌

		return result;

	}

	FractionType operator * (FractionType second){  // 분수의 곱셈

		FractionType result;  // result: 연산 후의 결과값을 저장
		result.Initialize(0, 0);  // result의 num과 den을 세팅해줌

		result.den = this->den * second.den;  // 곱셈 후의 분모를 구함
		result.num = this->num * second.num;  // 곱셈 후의 분자를 구함

		Reduction(result);  // 분수를 약분해줌

		return result;

	}

	FractionType operator / (FractionType second){  // 분수의 나눗셈

		FractionType result;  // result: 연산 후의 결과값을 저장
		result.Initialize(0, 0);  // result의 num과 den을 세팅해줌

		long long swap = second.den;  // 두번째 분수의 분자와 분모를 서로 맞바꿈
		second.den = second.num;
		second.num = swap;

		result.den = this->den * second.den;  // 나눗셈 후의 분모를 구함
		result.num = this->num * second.num;  // 나눗셈 후의 분자를 구함

		if(result.den == 0)  // 분모가 0일 경우 false로 지정, 아니면 약분 진행
			div_pos = false;
		else
			Reduction(result);  // 분수를 약분해줌

		return result;

	}

	void Print(){  // 결과값만 출력함

		cout << this->num;
			
		if(this->den != 1)  // 분모가 1이면 분자만 출력시킴
			cout << "/" << this->den << endl;
		else
			cout << endl;

	}


private:
	long long num;  // num: 분수의 분자
	long long den;  // num: 분수의 분모
};


int main(){

	long long n1, n2, d1, d2;  // n1, n2: 각 입력받은 분자의 값을 저장함
						 // d1, d2: 각 입력받은 분모의 값을 저장함

	cout << "Assignment1-4" << endl;
	cout << "Input two fractions: ";
	cin >> n1 >> d1 >> n2 >> d2;  // "3 6 2 5" 이런 식으로 입력받음

	if(d1 == 0 || d2 == 0){  // 분모가 0일 경우 프로그램을 종료함
			cout << "(0으로 나눌수 없습니다)" << endl;
			return 1;
	}

	FractionType f1;  // f1: 첫 번째 분수를 저장
	f1.Initialize(n1, d1);  // 첫 번째 분수의 num과 den를 세팅해 줌

	FractionType f2;  // f2: 두 번째 분수를 저장
	f2.Initialize(n2, d2);  // 두 번째 분수의 num과 den를 세팅해 줌

	FractionType r1, r2, r3, r4;  // r1: 분수의 덧셈 결과를 저장
								  // r2: 분수의 뻴셈 결과를 저장
								  // r3: 분수의 곱셈 결과를 저장
								  // r4: 분수의 나눗셈 결과를 저장
	
	r1 = f1 + f2;  // 분수 덧셈 연산을 수행
	r2 = f1 - f2;  // 분수 뻴셈 연산을 수행
	r3 = f1 * f2;  // 분수 곱셈 연산을 수행
	r4 = f1 / f2;  // 분수 나눗셈 연산을 수행

	for(int i=1; i<=4; i++){  // 루프가 4번 진행됨으로써 4가지의 연산결과를 모두 출력함

		cout << "(" << n1 << "/" << d1 << ") ";  // 첫 번째 분수 출력

		if(i == 1) cout << "+ ";  // 연산자 출력
		else if(i == 2) cout << "- ";
		else if(i == 3) cout << "* ";
		else cout << "/ ";

		cout << "(" << n2 << "/" << d2 << ") = ";  // 두 번째 분수 출력

		if(i == 1) r1.Print();  // 연산 결과값 출력
		else if(i == 2) r2.Print();
		else if(i == 3) r3.Print();
		else if(i == 4 && div_pos == true) r4.Print();
		else cout << "(0으로 나눌수 없습니다)" << endl;
	}

	return 0;
}