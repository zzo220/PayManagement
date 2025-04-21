#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void upper(char input_name[][6], int num); //첫글자 대문자로 변환하는 함수
char* depart_output(char* input_depart); //부서 변환하는 함수
char* rank_output(int input_rank); //직급 변환하는 함수
char* gander(char input_gander[15]); //성별 변환 함수
void output_salary(int tm[], int t[], int num, int* output_salary, int* output_tax, int* tax_num); //총급여, 세금, 세후총급여 구하는 함수
void array(char arr_dipart[], char arr_name[][6], char arr_gender[][15], int arr_rank[], int arr_total[], int arr_tax[], int arr_total_tax[], int num); //정렬하는 함수
void array_1(int* x, int* y); //정수 스왑
void array_2(char* x, char* y); //문자열 스왑
void array_3(char* x, char* y);//문자 스왑
void avg_print(int avg_rank[], int avg_total[], int num); //직급별 평균 구한는 함수
void max_salay(int num, int m_salay[], char m_name[][6], int m_rank[]); //최대 총급여 직원 출력
void max_hours(int num, char h_dep[], char h_name[][6], char h_social[][15], int h_rank[], int h_time[]); //최대 시간 직원 정보 출력

int main()
{
	//입력 받는 코드

	char name[100][6]; //입력받는 이름
	char social_security_number[100][15]; //입력받는 주민번호
	char department_code[100]; //입력받는 부서코드
	int rank_code[100]; //입력받는 직급코드
	int time_money[100]; //입력받는 시간당 급여
	int time[100]; //입력받는 근무시간
	int employee_number; //입력받을 사람 수
	int i; //반복에서 증가하는 수
	int total[100]; //총 급여
	int tax[100]; //세금
	int total_tax[100]; //세후 총 급여

	printf("사원수를 입력하시오 : ");
	scanf("%d", &employee_number);

	if (employee_number > 0)
		for (i = 0; i < employee_number; i++)
		{
			printf("이름 주민번호 부서코드 직급코드 시간당급여 근무시간을 순서대로 입력하시오 : \n");
			scanf("%s %s %c %d %d %d", name[i], social_security_number[i], &department_code[i], &rank_code[i], &time_money[i], &time[i]);
			putchar('\n');
		}
	else
		printf("직원이 없습니다.\n");

	upper(name, employee_number);
	output_salary(time_money, time, employee_number, &total, &total_tax, &tax);
	array(department_code, name, social_security_number, rank_code, total, tax, total_tax, employee_number);

	printf("부서명\t이름\t성별\t직급명\t총급여(세전)\t세금\t총급여(세후)\n");
	printf("-------------------------------------------------------------------------------\n");
	for (i = 0; i < employee_number; i++)
		printf("%s\t%s\t%s\t%s\t%d\t\t%d\t%d\n", depart_output(department_code[i]), name[i], gander(social_security_number[i]), rank_output(rank_code[i]), total[i], tax[i], total_tax[i]);

	avg_print(rank_code, total, employee_number);
	max_salay(employee_number, total, name, rank_code);
	max_hours(employee_number, department_code, name, social_security_number, rank_code, time);
}

void upper(char input_name[][6], int num)
{
	//이름 첫글자 대문자로 변환하는 코드

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
	//부서코드

	char* part;

	switch (toupper(input_depart))
	{
	case 'A': part = "기획부"; break;
	case 'B': part = "개발부"; break;
	case 'C': part = "감사부"; break;
	case 'D': part = "인사부"; break;
	case 'E': part = "경영부"; break;
	case 'F': part = "지원부"; break;
	default: part = "미등록 부서";
	}
	return part;
}

char* rank_output(int input_rank)
{
	//직급코드

	char* position;

	switch (input_rank)
	{
	case 1: position = "팀장"; break;
	case 2: position = "부장"; break;
	case 3: position = "과장"; break;
	case 4: position = "대리"; break;
	case 5: position = "주임"; break;
	case 6: position = "사원"; break;
	default: position = "해당 직급은 존재하지 않습니다.";
	}
	return position;
}

char* gander(char input_gander[15])
{
	//성별 구분 코드
	int* a = "남자";
	int* b = "여자";

	if (input_gander[7] == '1' || input_gander[7] == '3')
		return a;
	if (input_gander[7] == '2' || input_gander[7] == '4')
		return b;
	else
		return 0;
}

void output_salary(int tm[], int t[], int num, int* output_salary, int* output_tax, int* tax_num)
{
	//총 급여와 세후 급여 구하는 코드

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
	//정렬 코드
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
	//정수 스왑

	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void array_2(char* x, char* y)
{
	//문자열 스왑

	char temp[50];

	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

void array_3(char* x, char* y)
{
	//문자 스왑
	char temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void avg_print(int avg_rank[], int avg_total[], int num)
{
	//직급별 평균 구하는 함수

	int i, total = 0, avg=0, em_num=0;
	int position;

	putchar('\n');
	printf("[1]팀장 [2]부장 [3]과장 [4]대리 [5]주임 [6]사원\n");
	printf("출력할 직급의 번호를 쓰시오 : ");
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
		printf("-%s 평균총급여액 : %d원\n\n", rank_output(position), avg);
	}
	else
		printf("입력한 직급은 없습니다\n\n");
}

void max_salay(int num, int m_salay[],char m_name[][6], int m_rank[])
{
	//최대 총급여 직원 정보 출력

	int i, max=0, m=0;

	for (i = 0; i < num; i++)
		if (max < m_salay[i])
		{
			max = m_salay[i];
			m = i;
		}

	printf("이름\t직급명\t월급여액\n");
	printf("---------------------------------------\n");
	printf("%s\t%s\t%d\n\n", m_name[m], rank_output(m_rank[m]), max);
}

void max_hours(int num, char h_dep[], char h_name[][6], char h_social[][15], int h_rank[], int h_time[])
{
	//최대 시간 직원 정보 출력

	int i, h=0, max=0;

	for (i = 0; i < num; i++)
		if (max < h_time[i])
		{
			max = h_time[i];
			h = i;
		}

	printf("부서명\t이름\t성별\t직급\t근무시간\n");
	printf("---------------------------------------------------------------\n");
	printf("%s\t%s\t%s\t%s\t%d", depart_output(h_dep[h]), h_name[h], gander(h_social[h]), rank_output(h_rank[h]), max);
}