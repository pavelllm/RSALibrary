#ifndef LIBRARY_H
#define LIBRARY_H


//число слов
#define L 16 

//младшее слово
#define LOWORD(T) ((unsigned short)(T))

//старшее слово
#define HIWORD(T) ((unsigned short)(T>>16))

//получить слово
#define MAKEWORD(a,b) ((((unsigned short)(a))<<8)+b)

#define MAKEDWORD(a,b) ((((unsigned long)(a))<<16)+b)

//младший байт
#define LOBYTE(T) ((unsigned char)(T))

//функция сложения двух чисел
unsigned short add(unsigned short * a, unsigned short * b, unsigned short size, unsigned short * c);

//функция вычитания одного числа из другого
unsigned short sub(unsigned short * a, unsigned short * b, unsigned short size, unsigned short * c);

unsigned short * mul(unsigned short * a, unsigned short size_a, unsigned short * b, unsigned short size_b, unsigned short * c);

//функция сравнения чисел
int cmp(unsigned short * a, unsigned short * b, unsigned short size);

//функция генерации рандомного длинного числа
unsigned short * generate(unsigned short * a, unsigned short size);

//функция печати длинного числа 
void print_result(unsigned short * a, unsigned short size);

//Обнуление длинного числа
void zeroing(unsigned short * number, unsigned short size_number);

//Присвоение a = b
void assign(unsigned short * a, unsigned short * b, unsigned short size);

//Умножение длинного числа на слово
unsigned short mul_word(unsigned short * a, unsigned short size_a, unsigned short b, unsigned short * c);

//Деление длинного числа на слово
unsigned short div_word(unsigned short * a, unsigned short size, unsigned short b, unsigned short * c, unsigned short * r);

//Деление длинного числа на длинное число
void div(unsigned short * U, unsigned short * V, unsigned short* const Q, unsigned short* const R, unsigned short sizeU, unsigned short sizeV);

//Умножение длинных чисел по модулю
void mod_mul(unsigned short * a, unsigned short * b, unsigned short * n, unsigned short * c, unsigned long size);

//Возведение длинного числа в степень по модулю
void mod_pow(unsigned short * a, unsigned long size_a, unsigned short * b, unsigned long size_b, unsigned short * n, unsigned short * c);

void rsa_encrypt(unsigned short * M, unsigned long s, unsigned short * e, unsigned short * n, unsigned short * C, unsigned long k);

void rsa_decrypt(unsigned short * C, unsigned short * d, unsigned short * n, unsigned short * M, unsigned long  k);



#endif 