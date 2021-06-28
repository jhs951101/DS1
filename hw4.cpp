#include<iostream>

using namespace std;

bool div_pos = true;  // div_pos: �������� ���� �и� 0�� �Ǿ��� ��� false�� �ٲ� (��������)

long long gcd(long long a, long long b){  // �� ���� �ִ������� ���ϴ� �Լ�
	
	while(a%b != 0){  // n�� m�� �ִ������� ����(n,m: ����)
		long long rem = a%b;
		a = b;
		b = rem;
	}

	return b;

}

class FractionType  // �м��� ���� Ŭ����
{
public:
	void Initialize(long long num, long long den){  // num�� den�� ���� ������

		this->num = num;
		this->den = den;
	}

	void Reduction(FractionType& r){  // ����ϴ� �Լ�

		long long n = gcd(r.num, r.den);  // num�� den�� �ִ������� ����
		r.num = r.num / n;  // num�� den�� �ִ������� �������ν� ����� ��
		r.den = r.den / n;
	}

	FractionType operator + (FractionType second){  // �м��� ����

		FractionType result;  // result: ���� ���� ������� ����
		result.Initialize(0, 0);  // result�� num�� den�� ��������

		result.den = this->den * second.den;  // ���� ���� �и� ����
		result.num = this->num * second.den + this->den * second.num;  // ���� ���� ���ڸ� ����

		Reduction(result);  // �м��� �������

		return result;

	}

	FractionType operator - (FractionType second){  // �м��� �y��

		FractionType result;  // result: ���� ���� ������� ����
		result.Initialize(0, 0);  // result�� num�� den�� ��������

		result.den = this->den * second.den;  // �y�� ���� �и� ����
		result.num = this->num * second.den - this->den * second.num;  // �y�� ���� ���ڸ� ����

		Reduction(result);  // �м��� �������

		return result;

	}

	FractionType operator * (FractionType second){  // �м��� ����

		FractionType result;  // result: ���� ���� ������� ����
		result.Initialize(0, 0);  // result�� num�� den�� ��������

		result.den = this->den * second.den;  // ���� ���� �и� ����
		result.num = this->num * second.num;  // ���� ���� ���ڸ� ����

		Reduction(result);  // �м��� �������

		return result;

	}

	FractionType operator / (FractionType second){  // �м��� ������

		FractionType result;  // result: ���� ���� ������� ����
		result.Initialize(0, 0);  // result�� num�� den�� ��������

		long long swap = second.den;  // �ι�° �м��� ���ڿ� �и� ���� �¹ٲ�
		second.den = second.num;
		second.num = swap;

		result.den = this->den * second.den;  // ������ ���� �и� ����
		result.num = this->num * second.num;  // ������ ���� ���ڸ� ����

		if(result.den == 0)  // �и� 0�� ��� false�� ����, �ƴϸ� ��� ����
			div_pos = false;
		else
			Reduction(result);  // �м��� �������

		return result;

	}

	void Print(){  // ������� �����

		cout << this->num;
			
		if(this->den != 1)  // �и� 1�̸� ���ڸ� ��½�Ŵ
			cout << "/" << this->den << endl;
		else
			cout << endl;

	}


private:
	long long num;  // num: �м��� ����
	long long den;  // num: �м��� �и�
};


int main(){

	long long n1, n2, d1, d2;  // n1, n2: �� �Է¹��� ������ ���� ������
						 // d1, d2: �� �Է¹��� �и��� ���� ������

	cout << "Assignment1-4" << endl;
	cout << "Input two fractions: ";
	cin >> n1 >> d1 >> n2 >> d2;  // "3 6 2 5" �̷� ������ �Է¹���

	if(d1 == 0 || d2 == 0){  // �и� 0�� ��� ���α׷��� ������
			cout << "(0���� ������ �����ϴ�)" << endl;
			return 1;
	}

	FractionType f1;  // f1: ù ��° �м��� ����
	f1.Initialize(n1, d1);  // ù ��° �м��� num�� den�� ������ ��

	FractionType f2;  // f2: �� ��° �м��� ����
	f2.Initialize(n2, d2);  // �� ��° �м��� num�� den�� ������ ��

	FractionType r1, r2, r3, r4;  // r1: �м��� ���� ����� ����
								  // r2: �м��� �y�� ����� ����
								  // r3: �м��� ���� ����� ����
								  // r4: �м��� ������ ����� ����
	
	r1 = f1 + f2;  // �м� ���� ������ ����
	r2 = f1 - f2;  // �м� �y�� ������ ����
	r3 = f1 * f2;  // �м� ���� ������ ����
	r4 = f1 / f2;  // �м� ������ ������ ����

	for(int i=1; i<=4; i++){  // ������ 4�� ��������ν� 4������ �������� ��� �����

		cout << "(" << n1 << "/" << d1 << ") ";  // ù ��° �м� ���

		if(i == 1) cout << "+ ";  // ������ ���
		else if(i == 2) cout << "- ";
		else if(i == 3) cout << "* ";
		else cout << "/ ";

		cout << "(" << n2 << "/" << d2 << ") = ";  // �� ��° �м� ���

		if(i == 1) r1.Print();  // ���� ����� ���
		else if(i == 2) r2.Print();
		else if(i == 3) r3.Print();
		else if(i == 4 && div_pos == true) r4.Print();
		else cout << "(0���� ������ �����ϴ�)" << endl;
	}

	return 0;
}