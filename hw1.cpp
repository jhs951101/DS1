#include<iostream>

using namespace std;

long long gcd(long long n, long long m){  // �� ���� �ִ������� ���ϴ� �Լ�

   while (n % m != 0)  // n�� m�� �ִ������� ����(n,m: ����)
   {  long long rem;
      rem = n % m;
      n = m;
      m = rem ;     
   }
   return m;

}

long long lcm(long long m, long long n){  // �� ���� �ּҰ������ ���ϴ� �Լ�

   long long temp = gcd(m, n);  // n�� m�� �ִ������� ���� ���� �� �ּҰ������ ���
   return m * n / temp;

}

void Reduction(long long num, long long den, long long& result_num, long long& result_den){  // ����ϴ� �Լ�

	num = result_num;  // num, den�� ���� ����ϱ� ���� �켱 ���� �־���
	den = result_den;

	result_num = result_num / gcd(num, den);  // num�� den�� �ִ������� ���� �� �������ν� ����� ��
	result_den = result_den / gcd(num, den);

}

void Add(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den){  // ���ϴ� �Լ�

    result_den = lcm(den1, den2);  // ���� ���� �и� ����
    result_num = num1*(result_den/den1) + num2*(result_den/den2);  // ���� ���� ���ڸ� ���� 

	Reduction(0, 0, result_num, result_den);  // �м��� �������

}

void Sub(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den){  // ���� �Լ�

	result_den = lcm(den1, den2);  // �y�� ���� �и� ����
    result_num = num1*(result_den/den1) - num2*(result_den/den2);  // �y�� ���� ���ڸ� ����

	Reduction(0, 0, result_num, result_den);  // �м��� �������

}

void Mpy(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den){  // ���ϴ� �Լ�

	result_den = den1 * den2;  // ���� ���� �и� ����
	result_num = num1 * num2;  // ���� ���� ���ڸ� ����

	Reduction(0, 0, result_num, result_den);  // �м��� �������

}

void Div(long long num1, long long den1, long long num2, long long den2, long long& result_num, long long& result_den, bool& possible){  // ������ �Լ�

	long long swap = den2;  // �ι�° �м��� ���ڿ� �и� ���� �¹ٲ�
	den2 = num2;
	num2 = swap;

	result_den = den1 * den2;  // ���� ���� �и� ����
	result_num = num1 * num2;  // ���� ���� ���ڸ� ����

	if(result_den == 0)  // �и� 0�� ��� false�� ����, �ƴϸ� ���� ����
		possible = false;
	else
		Reduction(0, 0, result_num, result_den);

}

int main(){

	long long n1, n2;  // n1, n2: �� �Է¹��� ������ ���� ������
	long long d1, d2;  // d1, d2: �� �Է¹��� �и��� ���� ������
	long long result_n=0, result_d=0;  // result_n: ���� ���� ���ڸ� ����
								 // result_d: ���� ���� �и� ����
	bool div_pos = true;  // div_pos: �������� ���� �и� 0�� �Ǿ��� ��� false�� �ٲ�

	cout << "Assignment1-1" << endl;
	cout << "Input two fractions: ";
	cin >> n1 >> d1 >> n2 >> d2;  // "3 6 2 5" �̷� ������ �Է¹���

	if(d1 == 0 || d2 == 0){  // �и� 0�� ��� ���α׷��� ������
			cout << "(0���� ������ �����ϴ�)" << endl;
			return 1;
	}

	for(int i=1; i<=4; i++){  // ������ 4�� ��������ν� 4������ ������ ��� �����

		cout << "(" << n1 << "/" << d1 << ") ";  // �� ��¹�

		if(i == 1){  // 1. ����

			Add(n1, d1, n2, d2, result_n, result_d);  // ���� �Լ��� ���������ν� ���ο� ������� ����
			cout << "+";

		}
		else if(i == 2){  // 2. �y��

			Sub(n1, d1, n2, d2, result_n, result_d);  // �y�� �Լ��� ���������ν� ���ο� ������� ����
			cout << "-";

		}
		else if(i == 3){  // 3. ����

			Mpy(n1, d1, n2, d2, result_n, result_d);  // ���� �Լ��� ���������ν� ���ο� ������� ����
			cout << "*";

		}
		else{  // 4. ������

			Div(n1, d1, n2, d2, result_n, result_d, div_pos);  // ������ �Լ��� ���������ν� ���ο� ������� ����
			cout << "/";

		}

		cout << " (" << n2 << "/" << d2 << ") = ";

		if(div_pos == false){  // ������ ��� �и� 0�� ��� ������
			cout << "(0���� ������ �����ϴ�)" << endl;
			break;
		}

		cout << result_n;

		if(result_d != 1)  // �и� 1�̸� ���ڸ� ��½�Ŵ
			cout << "/" << result_d << endl;
		else
			cout << endl;
		
		result_n = 0;  // ���ư� �� ���� result���� 0���� �ʱ�ȭ
		result_d = 0;
	}

	return 0;
}