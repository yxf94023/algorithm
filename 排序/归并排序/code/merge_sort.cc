/**
 *\file merge_sort.cc
 *\brief �鲢����
 *\date 2017/04/10
 */
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