/**
 *\file merge_sort.cc
 *\brief �鲢����
 *\date 2017/04/10
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

static int s_len = 0;		///< ����������г���
static int s_ary[10000];	///< �������

/** 
 *\brief �������� �������
 */
static void creat_ary(void)
{
	int i = 0;
	
	printf("��������������е�����:");
	scanf("%d", &s_len);
	
	assert(s_len > 1 && s_len < 10000);
	
	srand(time(0));
	
	for (i = 0; i < s_len; ++i){
			
		s_ary[i] = rand();
	}
}

/**
 *\brief ����������������
 */
static void print_ary(void)
{
	int i = 0;
	
	for (i = 0; i < s_len; ++i){
		
		printf("%d ", s_ary[i]);
	}
}

/**
 *\brief �鲢����
 */
static void merge_sort()
{
	
}

int main(int argc, char **argv)
{
	creat_ary();
	
	print_ary();
	
	merge_sort();
	
	print_ary();
	
	return 0;
}