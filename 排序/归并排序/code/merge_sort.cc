/**
 *\file merge_sort.cc
 *\brief 归并排序
 *\date 2017/04/10
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

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
			
		s_ary[i] = rand();
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
}

/**
 *\brief 归并排序
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