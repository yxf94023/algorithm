/**
 *\file merge_sort.cc
 *\brief �鲢����
 *\date 2017/04/10
 */

#include "merge_sort.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


static void **s_merge_array = (void**)0;	///< �����ı���
static void **s_merge_swap = (void**)0;	///< ��ʱ������
static unsigned int merge_len = 0;	///< ������Ĺ�ģ
static merge_cmp_fun mcmp_fun = NULL;	///< �ԱȺ���
static merge_agn_fun magn_fun = NULL;	///< ��ֵ����
static merge_set_fun mset_fun = NULL;	///< ����merge_array�ĳ�ʼֵ

/**
 *\brief ��ʼ���鲢���򻷾�
 *\param[in] len ������Ĺ�ģ
 *\param[in] disorder_array �����������
 *\param[in] f_set ����merge_array��ʼֵ����
 *\param[in] f_cmp �����������Ҫ�ıȽϺ���
 *\param[in] f_agn ��ֵ��������
 *\retval 1 ��ʼ���ɹ�
 *\retval 0 ��ʼ��ʧ��
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
 *\brief �鲢����
 *\param[in] beg ��ʼλ���±�
 *\param[in] end ����λ���±�
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
		
		// �鲢 [beg, beg + mid]  �� [beg + mid + 1, end] ��������Ԫ
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
		
		while (i <= beg + mid){	// ��ʣ���ȫ������
			
			magn_fun(&s_merge_swap[k], s_merge_array[i]);
			++k;
			++i;
		}
		
		while(j <= end){	// ��ʣ���ȫ������
			
			magn_fun(&s_merge_swap[k], s_merge_array[j]);
			++k;
			++j;
		}
		memcpy(&s_merge_array[beg], &s_merge_swap[beg], (end - beg + 1) * sizeof(void*));
	}else{
		
		// end == beg ��ʾֻ��һ���� ������
	}	
}

/**
 *\brief ����
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