/**
 *\file main.cc
 *\brief 归并排序
 *\date 2017/04/10
 */
#include "merge_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>

static int s_len = 0;		///< 待排序的数列长度
static int s_ary[10000];	///< 存放数列

/** 
 *\brief 根据输入 随机创建
 */
static void creat_ary(void)
{
	int i = 0;
	
	printf("输入随机生成数列的数量:");
	scanf("%d", &s_len);
	
	assert(s_len > 1 && s_len < 10000);
	
	srand(time(0));
	
	for (i = 0; i < s_len; ++i){
			
		s_ary[i] = rand()%10000;
	}
}

/**
 *\brief 输出随机产生的数列
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
 *\brief 归并排序中 设置merge_array的初始值
 *\param[in] len 待初始化的数据规模
 *\param[in] disoder_ary 等待排序的数据
 *\param[in] merge_ary 初始化的对象
 *\retval 1 初始化成功
 *\retval 0 初始化失败
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
 *\brief 归并排序中 两个元素对比函数
 *\param[in] cmp1 对比元素1
 *\param[in] cmp2 对比元素2
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
 *\brief 归并排序中 赋值操作
 *\param[in] lopr 被赋值的 等号 左边的数
 *\param[in] ropr 赋值的 等号 右边的数
 *\retval 1 赋值成功
 *\retval 0 赋值失败 
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
 *\brief 归并排序中 获取排序结果
 *\param[in] len 获取结果的数据规模 
 *\param[in,out] res_ary 等待排序的数据
 *\param[in] merge_ary 归并排序后的结果
 *\retval 1 获取结果成功
 *\retval 0 获取结果失败
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
		
		buf[i] = *ary[i];	// 取指针指向的内容
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