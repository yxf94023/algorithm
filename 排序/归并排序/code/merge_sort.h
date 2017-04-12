/**
 *\file merge_sort.h
 *\brief 归并排序
 *\date 2017/04/12
 */

#ifndef	__MERGE_SORT_H_2017_04_12__
#define	__MERGE_SORT_H_2017_04_12__

#ifdef 	__cplusplus
extern "C"{
#endif


/**
 *\brief 归并排序中 设置merge_array的初始值
 *\param[in] len 待初始化的数据规模
 *\param[in] disoder_ary 等待排序的数据
 *\param[in] merge_ary 初始化的对象
 *\retval 1 初始化成功
 *\retval 0 初始化失败
 */
typedef int (*merge_set_fun)(unsigned int len, void *disoder_ary, void **merge_ary);

/**
 *\brief 归并排序中 两个元素对比函数
 *\param[in] cmp1 对比元素1
 *\param[in] cmp2 对比元素2
 *\retval 1 cmp1 > cmp2
 *\retval 0 cmp1 = cmp2
 *\retval -1 cmp1 < cmp2
 */
typedef int (*merge_cmp_fun)(void *cmp1, void *cmp2);

/**
 *\brief 归并排序中 赋值操作
 *\param[in] lopr 被赋值的 等号 左边的数
 *\param[in] ropr 赋值的 等号 右边的数
 *\retval 1 赋值成功
 *\retval 0 赋值失败 
 */
typedef int (*merge_agn_fun)(void **lopr, void *ropr);

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
				merge_agn_fun f_agn);
				
/**
 *\brief 销毁
 */
void merge_destory(void);

/**
 *\brief 归并排序
 *\param[in] beg 起始位置下标
 *\param[in] end 结束位置下标
 */
void merge_sort(unsigned int beg, unsigned int end);			

#ifdef	__cplusplus
}
#endif
#endif//__MERGE_SORT_H_2017_04_12__

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

static int s_len = 0;		///< 待排序的数列长度
static int s_ary[10000];	///< 存放数列
static int s_buf[10000];	///< 临时交换区

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
 *\brief 归并排序
 *\param[in] beg 起始位置下标
 *\param[in] end 结束位置下标
 */
static void merge_sort(int beg, int end)
{
	int mid = 0;
	int i = 0, j = 0, k = 0;
	
	assert (end >= beg);
	
	if (end - beg > 1){
		
		mid = (end - beg) / 2;
		merge_sort(beg, beg + mid);
		merge_sort(beg + mid + 1, end);
		
		// 归并 [beg, beg + mid]  和 [beg + mid + 1, end] 两个有序单元
		for (i = beg, j = beg + mid + 1, k = beg; i <= beg + mid && j <= end; ++k){
			
			if (s_ary[i] < s_ary[j]){
				
				s_buf[k] = s_ary[i];
				++i;
			}else{
				
				s_buf[k] = s_ary[j];
				++j;
			}
		}
		
		while (i <= beg + mid){	// 将剩余的全部拷贝
			
			s_buf[k] = s_ary[i];
			++k;
			++i;
		}
		
		while(j <= end){	// 将剩余的全部拷贝
			
			s_buf[k] = s_ary[j];
			++k;
			++j;
		}
		memcpy(&s_ary[beg], &s_buf[beg], (end - beg + 1) * sizeof(int));
	}else if (end - beg == 1){
		
		// 两个, 直接交换
		if (s_ary[beg] > s_ary[end]){
			
			s_ary[beg] += s_ary[end];
			s_ary[end] = s_ary[beg] - s_ary[end];
			s_ary[beg] = s_ary[beg] - s_ary[end];
		}
	}else{
		
		// end == beg 表示只有一个， 不处理
	}
}

int main(int argc, char **argv)
{
	creat_ary();
	
	print_ary();
	
	merge_sort(0, s_len - 1);
	
	print_ary();
	
	return 0;
}
#endif