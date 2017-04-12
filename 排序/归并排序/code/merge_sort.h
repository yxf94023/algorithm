/**
 *\file merge_sort.h
 *\brief �鲢����
 *\date 2017/04/12
 */

#ifndef	__MERGE_SORT_H_2017_04_12__
#define	__MERGE_SORT_H_2017_04_12__

#ifdef 	__cplusplus
extern "C"{
#endif


/**
 *\brief �鲢������ ����merge_array�ĳ�ʼֵ
 *\param[in] len ����ʼ�������ݹ�ģ
 *\param[in] disoder_ary �ȴ����������
 *\param[in] merge_ary ��ʼ���Ķ���
 *\retval 1 ��ʼ���ɹ�
 *\retval 0 ��ʼ��ʧ��
 */
typedef int (*merge_set_fun)(unsigned int len, void *disoder_ary, void **merge_ary);

/**
 *\brief �鲢������ ����Ԫ�ضԱȺ���
 *\param[in] cmp1 �Ա�Ԫ��1
 *\param[in] cmp2 �Ա�Ԫ��2
 *\retval 1 cmp1 > cmp2
 *\retval 0 cmp1 = cmp2
 *\retval -1 cmp1 < cmp2
 */
typedef int (*merge_cmp_fun)(void *cmp1, void *cmp2);

/**
 *\brief �鲢������ ��ֵ����
 *\param[in] lopr ����ֵ�� �Ⱥ� ��ߵ���
 *\param[in] ropr ��ֵ�� �Ⱥ� �ұߵ���
 *\retval 1 ��ֵ�ɹ�
 *\retval 0 ��ֵʧ�� 
 */
typedef int (*merge_agn_fun)(void **lopr, void *ropr);

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
				merge_agn_fun f_agn);
				
/**
 *\brief ����
 */
void merge_destory(void);

/**
 *\brief �鲢����
 *\param[in] beg ��ʼλ���±�
 *\param[in] end ����λ���±�
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

static int s_len = 0;		///< ����������г���
static int s_ary[10000];	///< �������
static int s_buf[10000];	///< ��ʱ������

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
 *\brief �鲢����
 *\param[in] beg ��ʼλ���±�
 *\param[in] end ����λ���±�
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
		
		// �鲢 [beg, beg + mid]  �� [beg + mid + 1, end] ��������Ԫ
		for (i = beg, j = beg + mid + 1, k = beg; i <= beg + mid && j <= end; ++k){
			
			if (s_ary[i] < s_ary[j]){
				
				s_buf[k] = s_ary[i];
				++i;
			}else{
				
				s_buf[k] = s_ary[j];
				++j;
			}
		}
		
		while (i <= beg + mid){	// ��ʣ���ȫ������
			
			s_buf[k] = s_ary[i];
			++k;
			++i;
		}
		
		while(j <= end){	// ��ʣ���ȫ������
			
			s_buf[k] = s_ary[j];
			++k;
			++j;
		}
		memcpy(&s_ary[beg], &s_buf[beg], (end - beg + 1) * sizeof(int));
	}else if (end - beg == 1){
		
		// ����, ֱ�ӽ���
		if (s_ary[beg] > s_ary[end]){
			
			s_ary[beg] += s_ary[end];
			s_ary[end] = s_ary[beg] - s_ary[end];
			s_ary[beg] = s_ary[beg] - s_ary[end];
		}
	}else{
		
		// end == beg ��ʾֻ��һ���� ������
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