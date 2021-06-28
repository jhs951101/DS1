#include<iostream>

using namespace std;

struct FractionType{  // �м��� �ǹ��ϴ� ����ü
   long long num;
   long long den;
};

long long gcd(long long n, long long m){  // �� ���� �ִ������� ���ϴ� �Լ�

	while(n%m != 0){  // n�� m�� �ִ������� ����(n,m: ����)
		long long rem = n%m;
		n = m;
		m = rem;
	}

	return m;
}

long long lcm(long long m, long long n){  // �� ���� �ּҰ������ ���ϴ� �Լ�

	return m * n / gcd(m, n);  // n�� m�� �ִ������� ���� ���� �� �ּҰ������ ���
}

void Reduction(FractionType& a){  // ����ϴ� �Լ�

	long long n = gcd(a.num, a.den);  // num�� den�� �ִ������� ����

	a.num = a.num / n;  // num�� den�� �ִ������� �������ν� ����� ��
	a.den = a.den / n;

}
 
FractionType Add(FractionType a, FractionType b){  // �м��� ����

   FractionType result;
   result.den = lcm(a.den, b.den);  // ���� ���� �и� ����
   result.num = a.num*(result.den/a.den) + b.num*(result.den/b.den);  // ���� ���� ���ڸ� ����

   Reduction(result);  // �м��� �������

   return result;

}

FractionType Sub(FractionType a, FractionType b){  // �м��� �y��

	FractionType result;
	result.den = lcm(a.den, b.den);  // �y�� ���� �и� ����
	result.num = a.num*(result.den/a.den) - b.num*(result.den/b.den);  // �y�� ���� ���ڸ� ����

	Reduction(result);  // �м��� �������

	return result;

}

FractionType Mpy(FractionType a, FractionType b){  // �м��� ����

	FractionType result;
	result.den = a.den * b.den;  // ���� ���� �и� ����
	result.num = a.num * b.num;  // ���� ���� ���ڸ� ����

	Reduction(result);  // �м��� �������

	return result;

}

FractionType Div(FractionType a, FractionType b, bool& possible){  // �м��� ������

	long long swap = b.den;  // �ι�° �м��� ���ڿ� �и� ���� �¹ٲ�
	b.den = b.num;
	b.num = swap;

	FractionType result;
	result.den = a.den * b.den;  // ������ ���� �и� ����
	result.num = a.num * b.num;  // ������ ���� ���ڸ� ����

	if(result.den == 0)  // �и� 0�� ��� false�� ����, �ƴϸ� ��� ����
		possible = false;
	else
		Reduction(result);  // �м��� �������

	return result;

}

int main(){

	FractionType f1, f2;  // f1: ������ ù��° �м�
						  // f2: ������ �ι�° �м�
	bool div_pos = true;  // div_pos: �������� ���� �и� 0�� �Ǿ��� ��� false�� �ٲ�

	cout << "Assignment1-2" << endl;
	cout << "Input two fractions: ";
	cin >> f1.num >> f1.den >> f2.num >> f2.den;  // "3 6 2 5" �̷� ������ �Է¹���

	if(f1.den == 0 || f2.den == 0){  // �и� 0�� ��� ���α׷��� ������
			cout << "(0���� ������ �����ϴ�)" << endl;
			return 1;
	}

	for(int i=1; i<=4; i++){  // ������ 4�� ��������ν� 4������ ������ ��� �����

		FractionType c;  // c: ���� ���� �м��� ����

		cout << "(" << f1.num << "/" << f1.den << ") ";  // �� ��¹�

		if(i == 1){  // 1. ����

			c = Add(f1, f2);  // ���� �Լ��κ��� ������� ����
			cout << "+";	
		}
		else if(i == 2){  // 2. �y��

			c = Sub(f1, f2);  // �y�� �Լ��κ��� ������� ����
			cout << "-";
		}
		else if(i == 3){  // 3. ����

			c = Mpy(f1, f2);  // ���� �Լ��κ��� ������� ����
			cout << "*";
		}
		else{  // 4. ������

			c = Div(f1, f2, div_pos);  // ������ �Լ��κ��� ������� ����
			cout << "/";
		}

		cout << " (" << f2.num << "/" << f2.den << ") = ";

		if(div_pos == false){  // ������ ��� �и� 0�� ��� ������
			cout << "(0���� ������ �����ϴ�)" << endl;
			break;
		}

		cout << c.num;

		if(c.den != 1)  // �и� 1�̸� ���ڸ� ��½�Ŵ
			cout << "/" << c.den << endl;
		else
			cout << endl;

		c.num = 0;  // ���ư� �� ���� c�� ��� ���� 0���� �ʱ�ȭ
		c.den = 0;

	}

	return 0;
}