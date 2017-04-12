/**
 *\file merge_sort.cc
 *\brief 归并排序
 *\date 2017/04/10
 */

#include "merge_sort.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


static void **s_merge_array = (void**)0;	///< 交换的变量
static void **s_merge_swap = (void**)0;	///< 临时交换区
static unsigned int merge_len = 0;	///< 待排序的规模
static merge_cmp_fun mcmp_fun = NULL;	///< 对比函数
static merge_agn_fun magn_fun = NULL;	///< 赋值函数
static merge_set_fun mset_fun = NULL;	///< 设置merge_array的初始值

/**
 *\brief 初始化归并排序环境
 *\param[in] len 待排序的规模
 *\param[in] disorder_array 待排序的数组
 *\param[in] f_set 设置merge_array初始值函数
 *\param[in] f_cmp 排序过程中需要的比较函数
 *\param[in] f_agn 赋值操作函数
 *\retval 1 初始化成功
 *\retval 0 初始化失败
 */
int merge_init(unsigned int len, void *disorder_array,
				merge_set_fun f_set, 
				merge_cmp_fun f_cmp, 
				merge_agn_fun f_agn)
{
	assert(len > 1);
	assert((void**)0 != disorder_array);	
	assert(NULL != f_set);
	assert(NULL != f_set);
	assert(NULL != f_set);	
	
	s_merge_array = (void **) malloc (sizeof(void*) * len);
	s_merge_swap = (void **) malloc (sizeof(void*) * len);
	if ((void**)0 == s_merge_array || (void**)0 == s_merge_swap){
		
		printf("malloc failed errno(%d)!\n", errno);
		if (s_merge_array){
			
			free(s_merge_array);
			s_merge_array = (void**)0;
		}
		
		if (s_merge_swap){
			
			free(s_merge_swap);
			s_merge_swap = (void**)0;			
		}
		
		return 0;
	}
	merge_len = len;
	
	mset_fun = f_set;
	mcmp_fun = f_cmp;
	magn_fun = f_agn;
	
	return mset_fun(len, disorder_array, s_merge_array);
}

/**
 *\brief 归并排序
 *\param[in] beg 起始位置下标
 *\param[in] end 结束位置下标
 */
void merge_sort(unsigned int beg, unsigned int end)
{
	unsigned int mid = 0;
	unsigned int i = 0, j = 0, k = 0;
	int ret = 0;
	
	assert (end >= beg);
	
	if (end - beg >= 1){
		
		mid = (end - beg) / 2;
		merge_sort(beg, beg + mid);
		merge_sort(beg + mid + 1, end);
		
		// 归并 [beg, beg + mid]  和 [beg + mid + 1, end] 两个有序单元
		for (i = beg, j = beg + mid + 1, k = beg; i <= beg + mid && j <= end; ++k){
			
			ret = mcmp_fun(s_merge_array[i], s_merge_array[j]);
			if (-1 == ret){
				
				magn_fun(&s_merge_swap[k], s_merge_array[i]);
				++i;
			}else{
				
				magn_fun(&s_merge_swap[k], s_merge_array[j]);
				++j;
			}
		}
		
		while (i <= beg + mid){	// 将剩余的全部拷贝
			
			magn_fun(&s_merge_swap[k], s_merge_array[i]);
			++k;
			++i;
		}
		
		while(j <= end){	// 将剩余的全部拷贝
			
			magn_fun(&s_merge_swap[k], s_merge_array[j]);
			++k;
			++j;
		}
		memcpy(&s_merge_array[beg], &s_merge_swap[beg], (end - beg + 1) * sizeof(void*));
	}else{
		
		// end == beg 表示只有一个， 不处理
	}	
}

/**
 *\brief 销毁
 */
void merge_destory(void)
{
	if (s_merge_array){
		
		free(s_merge_array);
		s_merge_array = (void**)0;
	}
	
	if (s_merge_swap){
		
		free(s_merge_swap);
		s_merge_swap = (void**)0;			
	}	
	
	merge_len = 0;
	
	mset_fun = NULL;
	mcmp_fun = NULL;
	magn_fun = NULL;
}