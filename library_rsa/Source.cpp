#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Library.h"

//Подпрограмма сложеие двух длинных чисел
//a и b - слагаемые размером size слов
//с - сумма размером size слов
//возвращаемое значение - бит переноса
unsigned short add(unsigned short * a, unsigned short * b, unsigned short size, unsigned short * c)
{
	//бит переноса старшего разряда при сложении
	unsigned short d = 0;

	//промежутчный результат сложения слов
	unsigned int T;

	for (int i = 0; i < size; ++i)
	{
		T = unsigned int(a[i]) + unsigned int(b[i]) + unsigned int(d);
		c[i] = LOWORD(T);
		d = HIWORD(T);
	}

	c[size] = d;

	return d;
}

//Подпрограмма вычитания двух длинных беззнаковых чисел
// a, b - числа, разность которых нужно посчитать, длинной size слов
//c - разность a и b размером size слов
//возвращаемое значение - бит переноса
unsigned short sub(unsigned short * a, unsigned short * b, unsigned short size, unsigned short * c)
{
	//бит переноса разряда при вычитании
	unsigned short d = 0;

	//промежуточный результат вычитания слов
	unsigned int T;

	for (int i = 0; i< size; ++i)
	{
		T = (unsigned int)(a[i]) - (unsigned int)(b[i]) - (unsigned int)(d);
		c[i] = LOWORD(T);
		d = (HIWORD(T) == 0) ? 0 : 1;
	}

	c[size] = d;

	return d;
}

//Подпрограмма сравнения двух длинных беззнаковых чисел
// a, b - сравниваемые числа длинной size слов
//возвращаемые значения:
//0: a == b
//1: a > b
//-1: b > a
int cmp(unsigned short * a, unsigned short * b, unsigned short size)
{
	for (int i = size - 1; i >= 0; --i)
	{
		//a > b
		if (a[i] > b[i]) return 1;

		//a < b
		if (a[i] < b[i]) return -1;
	}
	return 0;
}

//Подпрограмма генерации случайного длинного беззнакового числа
//a - массив для записи числа размером size слов
unsigned short * generate(unsigned short * a, unsigned short size)
{
	for (int i = 0; i < size; i++)
	{
		//8 бит + 8 бит = 16 бит => профит, иначе 
		//(a[i] == rand()) <= (RAND_MAX == 32767)
		a[i] = MAKEWORD(LOBYTE(rand()), LOBYTE(rand()));
	}

	return a;
}

//Подпрограмма вывода длинного беззнакового числа в шестандцатиричном формате (начиная со старших разрядов)
//а - число размером size слов
void print_result(unsigned short * a, unsigned short size)
{
	for (int i = size - 1; i >= 0; --i)
	{
		printf("%04x", a[i]);
	}
	printf("\n");
}

//Подпрограмма обнуления длинного беззнакового числа number размером size_number
void zeroing(unsigned short * number, unsigned short size_number)
{
	for (int i = 0; i < size_number; ++i) number[i] = 0;
}

//Подпрограмма присвоения одного длинного числа другому
void assign(unsigned short * a, unsigned short * b, unsigned short size)
{
	for (int i = 0; i < size; ++i)
	{
		a[i] = b[i];
	}
}

//Подпрограмма умножения двух длинных беззнаковых чисел
//a, b - умножаемые числа длинной size_a и size_b слов соответственно
//c - произведение a и b, размером size_a + size_b слов
unsigned short * mul(unsigned short * a, unsigned short size_a, unsigned short * b, unsigned short size_b, unsigned short * c)
{
	unsigned short d = 0, size_c;
	unsigned long T;

	size_c = size_a + size_b;

	zeroing(c, size_c);

	for (unsigned long i = 0; i < size_a; i++)
	{
		for (unsigned long j = 0; j < size_b; j++)
		{
			T = (unsigned long)c[i + j] + (unsigned long)a[i] * (unsigned long)b[j] + (unsigned long)d;
			c[i + j] = LOWORD(T);
			d = HIWORD(T);
		}

		c[i + size_b] = d;
	}

	return c;
}

//Подпрограмма умножения длинного беззнакового числа на слово
//a - умножаемое число длинной size слов
//b - множитель длинной в 1 слово
//c - произведение a и b, размером size слов
//возвращаемое значение - слово переноса
unsigned short mul_word(unsigned short * a, unsigned short size_a, unsigned short b, unsigned short * c)
{
	unsigned long T;
	unsigned short d = 0;

	for (int i = 0; i < size_a; i++)
	{
		T = (unsigned long)a[i] * (unsigned long)b + (unsigned long)d;
		c[i] = LOWORD(T);
		d = HIWORD(T);
	}

	return d;
}

//Подпрограмма деления длинного беззнакового числа на слово
//a - делимое число длинной size слов
//b - делитель длинной в 1 слово
//c [Nullable] - частное a и b, размером size слов
//r [Nullable] - остаток от деления a на b, размером 1 слово
//возвращаемое значение - остаток от деления
unsigned short div_word(unsigned short * a, unsigned short size, unsigned short b, unsigned short * c, unsigned short * r)
{
	unsigned long T = 0;

	if (b == 0) exit(0);

	for (int i = size; i > 0; i--)
	{
		T <<= sizeof(unsigned short) * 8;
		T |= a[i - 1];
		if (c != NULL) c[i - 1] = LOWORD(T / (unsigned long)b);
		T %= b;
	}

	if (r != NULL) *r = LOWORD(T);

	return LOWORD(T);
}

//Подпрограмма деления двух длинных беззнаковых чисел
// U - делимое, размером sizeU слов
// V - делитель, размером sizeV слов
// Q [Nullable] - частное, размером sizeU слов
// R [Nullable] - остаток, размером sizeV слов
void div(unsigned short * U, unsigned short * V, unsigned short * Q, unsigned short * const R, unsigned short sizeU, unsigned short sizeV)
{
	unsigned short q, buf1, buf2;
	unsigned short U2[33], V2[33], R2[33];
	unsigned long inter;
	int i, j, k;
	unsigned short d;

	//Проверки, подготовка
	if (R != NULL) zeroing(R, sizeV);
	if (Q != NULL) zeroing(Q, sizeU);

	for (i = sizeV; (i > 0)&(!V[i - 1]); i--);
	sizeV = i;
	if (sizeV == 0) return;                  // исключение "Деление на ноль" (просто уходим)

	for (k = sizeU; (k > 0)&(!U[k - 1]); k--);
	sizeU = k;

	if (sizeV > sizeU)
	{
		if (R != NULL) assign(R, U, sizeU);
		return;
	}
	if (sizeV == 1)
	{
		div_word(U, sizeU, V[0], Q, R);
		return;
	}

	//Нормализация
	d = (unsigned short)(((unsigned long)65535 + 1) / ((unsigned long)V[sizeV - 1] + 1));
	if (d != 1)
	{
		V2[sizeV] = mul_word(V, sizeV, d, V2);
		U2[sizeU] = mul_word(U, sizeU, d, U2);
	}
	else
	{
		assign(V2, V, sizeV);
		V2[sizeV] = 0;
		assign(U2, U, sizeU);
		U2[sizeU] = 0;
	}

	//Основной цикл
	for (j = sizeU; j >= sizeV; j--)
	{
		//Очередное слово частного
		inter = MAKEDWORD(U2[j], U2[j - 1]);
		if (U2[j] == V2[sizeV - 1])
			q = 65535;
		else {
			q = (unsigned short)(inter / V2[sizeV - 1]);//j-е слово частного q находим делением

														//Коррекция слова частного
			if (((unsigned long)V2[sizeV - 2] * q) > (MAKEDWORD((unsigned short)(inter%V2[sizeV - 1]), U2[j - 2])))
			{
				q--;    //коррекция слова частного уменьшением q на 1
			}
		}

		//Вычитание кратного делителя
		buf1 = mul_word(V2, sizeV, q, R2);
		buf2 = sub(U2 + j - sizeV, R2, sizeV, U2 + j - sizeV);
		inter = (unsigned long)U2[j] - buf1 - buf2;

		//Коррекция остатка и частного
		if (HIWORD(inter))
		{
			add(U2 + j - sizeV, V2, sizeV, U2 + j - sizeV);

			q--;
		}
		if (Q != NULL)
			Q[j - sizeV] = q;
	}

	//Завершение
	if (R != NULL)
	{
		div_word(U2, sizeV, d, R, NULL);
	}
}

//Подпрограмма вычисления произведения двух длинных беззнаковых чисел по модулю длинного беззнакового числа
//a - первый сомножитель размером size слов
//b - второй сомножитель размером size слов
//n - модуль размером size слов
//c - a * b mod n размеров size слов
void mod_mul(unsigned short * a, unsigned short * b, unsigned short * n, unsigned short * c, unsigned long size)
{
	unsigned short d[32 * 2];
	mul(a, size, b, size, d);
	div(d, n, NULL, c, 2 * size, size);
}

//Подпрограмма возведения длинного беззнакового числа в степень длинного беззнакового числа по модулю длинного беззнакового числа
//a - основание размером size_a слов
//b - показатель размером size_b слов
//n - модуль размером size_a слов
//c - a ^ b mod n размеров size_a слов
void mod_pow(unsigned short * a, unsigned long size_a, unsigned short * b, unsigned long size_b, unsigned short * n, unsigned short * c)
{
	zeroing(c, size_a);

	c[0] = 1;

	for (int i = 16 * size_b; i > 0; i--)
	{
		mod_mul(c, c, n, c, size_a);
		if ((b[(i - 1) / 16] >> ((i - 1) % 16)) & 1)
		{
			mod_mul(c, a, n, c, size_a);
		}
	}
}

void rsa_encrypt(unsigned short * M, unsigned long s, unsigned short * e, unsigned short * n, unsigned short * C, unsigned long k)
{
	mod_pow(M, s / 2, e, s / 2, n, C);
}

void rsa_decrypt(unsigned short * C, unsigned short * d, unsigned short * n, unsigned short * M, unsigned long  k)
{
	mod_pow(C, k / 16, d, k / 16, n, M);
}