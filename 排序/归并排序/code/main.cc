/**
 *\file main.cc
 *\brief �鲢����
 *\date 2017/04/10
 */
#include "merge_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>

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
			
		s_ary[i] = rand()%10000;
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
	printf("\n");
}

/**
 *\brief �鲢������ ����merge_array�ĳ�ʼֵ
 *\param[in] len ����ʼ�������ݹ�ģ
 *\param[in] disoder_ary �ȴ����������
 *\param[in] merge_ary ��ʼ���Ķ���
 *\retval 1 ��ʼ���ɹ�
 *\retval 0 ��ʼ��ʧ��
 */
int set_fun(unsigned int len, void *disoder_ary, void **merge_ary)
{
	unsigned int i = 0;
	int *ary1 = NULL, **ary2 = NULL;
	
	assert((void**)0 != disoder_ary);
	assert((void**)0 != merge_ary);
	
	ary1 = (int *)disoder_ary;
	ary2 = (int **)merge_ary;
	
	for (i = 0; i < len; ++i){
		
		ary2[i] = &ary1[i];
	}
	
	return 1;
}

/**
 *\brief �鲢������ ����Ԫ�ضԱȺ���
 *\param[in] cmp1 �Ա�Ԫ��1
 *\param[in] cmp2 �Ա�Ԫ��2
 *\retval 1 cmp1 > cmp2
 *\retval 0 cmp1 = cmp2
 *\retval -1 cmp1 < cmp2
 */
int cmp_fun(void *cmp1, void *cmp2)
{
	int *int_cmp1 = NULL;
	int *int_cmp2 = NULL;

	assert(NULL != cmp1);
	assert(NULL != cmp2);
	
	int_cmp1 = (int*)cmp1;
	int_cmp2 = (int*)cmp2;
	if (*int_cmp1 > *int_cmp2){
		
		return 1;
	}else if (*int_cmp1 == *int_cmp2){
		
		return 0;
	}
	
	return -1;
}

/**
 *\brief �鲢������ ��ֵ����
 *\param[in] lopr ����ֵ�� �Ⱥ� ��ߵ���
 *\param[in] ropr ��ֵ�� �Ⱥ� �ұߵ���
 *\retval 1 ��ֵ�ɹ�
 *\retval 0 ��ֵʧ�� 
 */
int agn_fun(void **lopr, void *ropr)
{
	int **int_lopr = NULL;
	int *int_ropr = NULL;
	
	assert((void**)0 != lopr);
	assert(NULL != ropr);
	
	int_lopr = (int **)lopr;
	int_ropr = (int *)ropr;
	*int_lopr = int_ropr;
	
	return 1;
}

/**
 *\brief �鲢������ ��ȡ������
 *\param[in] len ��ȡ��������ݹ�ģ 
 *\param[in,out] res_ary �ȴ����������
 *\param[in] merge_ary �鲢�����Ľ��
 *\retval 1 ��ȡ����ɹ�
 *\retval 0 ��ȡ���ʧ��
 */
int get_res_fun(unsigned int len, void *res_ary, void **merge_ary)
{
	int *buf = NULL, **ary = (int**)0, *res = NULL;
	unsigned int i = 0;
	
	assert(0 <= len);
	assert(NULL != res_ary);
	assert((void**)0 != merge_ary);
	
	buf = (int*) malloc (len * sizeof(int));
	if (NULL == buf){
		
		printf("malloc failed, errno(%d)\n", errno);
		return 0;
	}
	ary = (int **)merge_ary;
	res = (int *)res_ary;
	
	for (i = 0; i < len; ++i){
		
		buf[i] = *ary[i];	// ȡָ��ָ�������
	}
	
	memcpy(res, buf, len * sizeof(int));
	
	free(buf);
	buf = NULL;
	
	return 1;
}

int main(int argc, char **argv)
{
	creat_ary();
	
	print_ary();
	
	merge_init(s_len, (void *)s_ary, set_fun, cmp_fun, agn_fun);
	
	merge_sort(s_len, (void *)s_ary, get_res_fun);
	
	merge_destory();
	
	print_ary();
	
	return 0;
}