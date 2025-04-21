#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void upper(char input_name[][6], int num); //ù���� �빮�ڷ� ��ȯ�ϴ� �Լ�
char* depart_output(char* input_depart); //�μ� ��ȯ�ϴ� �Լ�
char* rank_output(int input_rank); //���� ��ȯ�ϴ� �Լ�
char* gander(char input_gander[15]); //���� ��ȯ �Լ�
void output_salary(int tm[], int t[], int num, int* output_salary, int* output_tax, int* tax_num); //�ѱ޿�, ����, �����ѱ޿� ���ϴ� �Լ�
void array(char arr_dipart[], char arr_name[][6], char arr_gender[][15], int arr_rank[], int arr_total[], int arr_tax[], int arr_total_tax[], int num); //�����ϴ� �Լ�
void array_1(int* x, int* y); //���� ����
void array_2(char* x, char* y); //���ڿ� ����
void array_3(char* x, char* y);//���� ����
void avg_print(int avg_rank[], int avg_total[], int num); //���޺� ��� ���Ѵ� �Լ�
void max_salay(int num, int m_salay[], char m_name[][6], int m_rank[]); //�ִ� �ѱ޿� ���� ���
void max_hours(int num, char h_dep[], char h_name[][6], char h_social[][15], int h_rank[], int h_time[]); //�ִ� �ð� ���� ���� ���

int main()
{
	//�Է� �޴� �ڵ�

	char name[100][6]; //�Է¹޴� �̸�
	char social_security_number[100][15]; //�Է¹޴� �ֹι�ȣ
	char department_code[100]; //�Է¹޴� �μ��ڵ�
	int rank_code[100]; //�Է¹޴� �����ڵ�
	int time_money[100]; //�Է¹޴� �ð��� �޿�
	int time[100]; //�Է¹޴� �ٹ��ð�
	int employee_number; //�Է¹��� ��� ��
	int i; //�ݺ����� �����ϴ� ��
	int total[100]; //�� �޿�
	int tax[100]; //����
	int total_tax[100]; //���� �� �޿�

	printf("������� �Է��Ͻÿ� : ");
	scanf("%d", &employee_number);

	if (employee_number > 0)
		for (i = 0; i < employee_number; i++)
		{
			printf("�̸� �ֹι�ȣ �μ��ڵ� �����ڵ� �ð���޿� �ٹ��ð��� ������� �Է��Ͻÿ� : \n");
			scanf("%s %s %c %d %d %d", name[i], social_security_number[i], &department_code[i], &rank_code[i], &time_money[i], &time[i]);
			putchar('\n');
		}
	else
		printf("������ �����ϴ�.\n");

	upper(name, employee_number);
	output_salary(time_money, time, employee_number, &total, &total_tax, &tax);
	array(department_code, name, social_security_number, rank_code, total, tax, total_tax, employee_number);

	printf("�μ���\t�̸�\t����\t���޸�\t�ѱ޿�(����)\t����\t�ѱ޿�(����)\n");
	printf("-------------------------------------------------------------------------------\n");
	for (i = 0; i < employee_number; i++)
		printf("%s\t%s\t%s\t%s\t%d\t\t%d\t%d\n", depart_output(department_code[i]), name[i], gander(social_security_number[i]), rank_output(rank_code[i]), total[i], tax[i], total_tax[i]);

	avg_print(rank_code, total, employee_number);
	max_salay(employee_number, total, name, rank_code);
	max_hours(employee_number, department_code, name, social_security_number, rank_code, time);
}

void upper(char input_name[][6], int num)
{
	//�̸� ù���� �빮�ڷ� ��ȯ�ϴ� �ڵ�

	int i;
	if (strlen(input_name) < 6)
	{
		for (i = 0; i < num; i++)
			input_name[i][0] = toupper(input_name[i][0]);
	}
	else
		input_name = "X";
}

char* depart_output(char* input_depart)
{
	//�μ��ڵ�

	char* part;

	switch (toupper(input_depart))
	{
	case 'A': part = "��ȹ��"; break;
	case 'B': part = "���ߺ�"; break;
	case 'C': part = "�����"; break;
	case 'D': part = "�λ��"; break;
	case 'E': part = "�濵��"; break;
	case 'F': part = "������"; break;
	default: part = "�̵�� �μ�";
	}
	return part;
}

char* rank_output(int input_rank)
{
	//�����ڵ�

	char* position;

	switch (input_rank)
	{
	case 1: position = "����"; break;
	case 2: position = "����"; break;
	case 3: position = "����"; break;
	case 4: position = "�븮"; break;
	case 5: position = "����"; break;
	case 6: position = "���"; break;
	default: position = "�ش� ������ �������� �ʽ��ϴ�.";
	}
	return position;
}

char* gander(char input_gander[15])
{
	//���� ���� �ڵ�
	int* a = "����";
	int* b = "����";

	if (input_gander[7] == '1' || input_gander[7] == '3')
		return a;
	if (input_gander[7] == '2' || input_gander[7] == '4')
		return b;
	else
		return 0;
}

void output_salary(int tm[], int t[], int num, int* output_salary, int* output_tax, int* tax_num)
{
	//�� �޿��� ���� �޿� ���ϴ� �ڵ�

	int i;

	for (i = 0; i < num; i++, output_salary++, tax_num++, output_tax++)
	{
		*output_salary = tm[i] * t[i];

		if (*output_salary < 500000)
		{
			*tax_num = *output_salary * 0.05;
			*output_tax = *output_salary - *tax_num;
		}
		else if (*output_salary >= 500000 && *output_salary < 1000000)
		{
			*tax_num = *output_salary * 0.07;
			*output_tax = *output_salary - *tax_num;
		}
		else if (*output_salary >= 1000000)
		{
			*tax_num = *output_salary * 0.1;
			*output_tax = *output_salary - *tax_num;
		}
		else
		{
			*output_salary = 0;
			*output_tax = 0;
			*tax_num = 0;
		}
	}
}

void array(char arr_dipart[], char arr_name[][6], char arr_gender[][15], int arr_rank[], int arr_total[], int arr_tax[], int arr_total_tax[], int num)
{
	//���� �ڵ�
	int i, j;

	for (i = 0; i < num; i++)
	{
		arr_dipart[i] = toupper(arr_dipart[i]);

	}

	for (i = 0; i < num - 1; i++) {
		for (j = i + 1; j < num; j++) {
			if (arr_total_tax[i] < arr_total_tax[j])
			{
				array_3(&arr_dipart[i], &arr_dipart[j]);
				array_1(&arr_rank[i], &arr_rank[j]);
				array_1(&arr_total[i], &arr_total[j]);
				array_1(&arr_tax[i], &arr_tax[j]);
				array_1(&arr_total_tax[i], &arr_total_tax[j]);
				array_2(arr_name[i], arr_name[j]);
				array_2(arr_gender[i], arr_gender[j]);
			}
		}
	}
}

void array_1(int* x, int* y)
{
	//���� ����

	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void array_2(char* x, char* y)
{
	//���ڿ� ����

	char temp[50];

	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

void array_3(char* x, char* y)
{
	//���� ����
	char temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void avg_print(int avg_rank[], int avg_total[], int num)
{
	//���޺� ��� ���ϴ� �Լ�

	int i, total = 0, avg=0, em_num=0;
	int position;

	putchar('\n');
	printf("[1]���� [2]���� [3]���� [4]�븮 [5]���� [6]���\n");
	printf("����� ������ ��ȣ�� ���ÿ� : ");
	scanf("%d", &position);

	
	for (i = 0; i < num; i++) {
		if (avg_rank[i] == position)
		{
			total += avg_total[i];
			em_num++;
		}
	}

	if (em_num > 0)
	{
		avg = total / em_num;
		printf("-%s ����ѱ޿��� : %d��\n\n", rank_output(position), avg);
	}
	else
		printf("�Է��� ������ �����ϴ�\n\n");
}

void max_salay(int num, int m_salay[],char m_name[][6], int m_rank[])
{
	//�ִ� �ѱ޿� ���� ���� ���

	int i, max=0, m=0;

	for (i = 0; i < num; i++)
		if (max < m_salay[i])
		{
			max = m_salay[i];
			m = i;
		}

	printf("�̸�\t���޸�\t���޿���\n");
	printf("---------------------------------------\n");
	printf("%s\t%s\t%d\n\n", m_name[m], rank_output(m_rank[m]), max);
}

void max_hours(int num, char h_dep[], char h_name[][6], char h_social[][15], int h_rank[], int h_time[])
{
	//�ִ� �ð� ���� ���� ���

	int i, h=0, max=0;

	for (i = 0; i < num; i++)
		if (max < h_time[i])
		{
			max = h_time[i];
			h = i;
		}

	printf("�μ���\t�̸�\t����\t����\t�ٹ��ð�\n");
	printf("---------------------------------------------------------------\n");
	printf("%s\t%s\t%s\t%s\t%d", depart_output(h_dep[h]), h_name[h], gander(h_social[h]), rank_output(h_rank[h]), max);
}