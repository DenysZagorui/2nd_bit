#include <iostream>
#include <bitset>
#include <stdio.h>

using namespace std;

bool equals(double a, double b, uint8_t precision);
void setBit(int &src, uint8_t bit);
void revertBit(int &src, uint8_t bit);
bool addVector(const int *src1, const int *src2, int size, int *dst);

int main()
{
	double a, b;

	a = 123456789123456789123456789123456789123456789123456789.1234567891234567;
	b = 123456789123456789123456789123456789.123;

	cout << "a: " << a << " equals b: " << b << " " << equals(a, b, 3) << endl;

	int c, d;

	c = 1;
	d = -1;

	setBit(c, 4);

	cout << "test setBit: c: " << c << endl;

	revertBit(d, 3);

	cout << "test revertBit d: " << d << endl;

	int src1[] = {1,2,4,8,16};
	int src2[] = {32,64,128,256,512};

	int dst[sizeof(src1)/sizeof(int)] = {0};

	addVector(src1, src2, sizeof(src1)/sizeof(int), dst);

	for (int i = 0; i < sizeof(src1)/sizeof(int); i++){
		cout << src1[i] << " + " <<  src2[i] << " = " << dst[i] << endl;
	}

	return 0;
}


bool addVector(const int *src1, const int *src2, int size, int *dst)
{
	for (int i = 0; i < size; i++){
		dst[i] = src1[i] + src2[i];
	}

	return true;
}

void setBit(int &src, uint8_t bit)
{
/*    src != 1 << bit; c-style */
	bitset<sizeof(int)*8> bs(src);
	bs.set(bit);
	src = bs.to_ulong();	
}

void revertBit(int &src, uint8_t bit)
{
/*    src ^= ~(1 << bit) c-style */
	bitset<sizeof(int)*8> bs(src);
	bs.flip(bit);
	src = bs.to_ulong();
}

bool equals(double a, double b, uint8_t precision)
{
#define STR_SIZE  50

#define STR_(X) #X
#define STR(X) STR_(X)
	char num1[STR_SIZE];
	char num2[STR_SIZE];

	snprintf(num1, STR_SIZE, "%f", a);
	snprintf(num2, STR_SIZE, "%f", b);

	int i = 0;

	//check if we are trying to compare negative with negative or
	//negative with positive value
	if (num1[i] == '-' || num2[i] == '-')
	{
		if ((num1[i] == '-' && num2[i] != '-') || (num1[i] != '-' && num2[i] == '-'))
			return false;

		i++;
	}

	for (; i < STR_SIZE - 1; i++)
	{
		if (num1[i] == '.' || num2[i] == '.')
		{
			if ((num1[i] == '.' && num2[i] != '.') || (num1[i] != '.' && num2[i] == '.')) {
				return false;
			} else {
				i++;
				for (int y = 0; y < precision && i < STR_SIZE - 1; i++, y++)
				{
					if ((num1[i] > num2[i]) || (num1[i] < num2[i])) {
						return false;
					}
				}

				return true;
			}
		}

		if (num1[i] > num2[i] || num1[i] < num2[i])
			return false;
	}

    return true;
}


