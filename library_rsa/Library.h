#ifndef LIBRARY_H
#define LIBRARY_H


//����� ����
#define L 16 

//������� �����
#define LOWORD(T) ((unsigned short)(T))

//������� �����
#define HIWORD(T) ((unsigned short)(T>>16))

//�������� �����
#define MAKEWORD(a,b) ((((unsigned short)(a))<<8)+b)

#define MAKEDWORD(a,b) ((((unsigned long)(a))<<16)+b)

//������� ����
#define LOBYTE(T) ((unsigned char)(T))

//������� �������� ���� �����
unsigned short add(unsigned short * a, unsigned short * b, unsigned short size, unsigned short * c);

//������� ��������� ������ ����� �� �������
unsigned short sub(unsigned short * a, unsigned short * b, unsigned short size, unsigned short * c);

unsigned short * mul(unsigned short * a, unsigned short size_a, unsigned short * b, unsigned short size_b, unsigned short * c);

//������� ��������� �����
int cmp(unsigned short * a, unsigned short * b, unsigned short size);

//������� ��������� ���������� �������� �����
unsigned short * generate(unsigned short * a, unsigned short size);

//������� ������ �������� ����� 
void print_result(unsigned short * a, unsigned short size);

//��������� �������� �����
void zeroing(unsigned short * number, unsigned short size_number);

//���������� a = b
void assign(unsigned short * a, unsigned short * b, unsigned short size);

//��������� �������� ����� �� �����
unsigned short mul_word(unsigned short * a, unsigned short size_a, unsigned short b, unsigned short * c);

//������� �������� ����� �� �����
unsigned short div_word(unsigned short * a, unsigned short size, unsigned short b, unsigned short * c, unsigned short * r);

//������� �������� ����� �� ������� �����
void div(unsigned short * U, unsigned short * V, unsigned short* const Q, unsigned short* const R, unsigned short sizeU, unsigned short sizeV);

//��������� ������� ����� �� ������
void mod_mul(unsigned short * a, unsigned short * b, unsigned short * n, unsigned short * c, unsigned long size);

//���������� �������� ����� � ������� �� ������
void mod_pow(unsigned short * a, unsigned long size_a, unsigned short * b, unsigned long size_b, unsigned short * n, unsigned short * c);

void rsa_encrypt(unsigned short * M, unsigned long s, unsigned short * e, unsigned short * n, unsigned short * C, unsigned long k);

void rsa_decrypt(unsigned short * C, unsigned short * d, unsigned short * n, unsigned short * M, unsigned long  k);



#endif 