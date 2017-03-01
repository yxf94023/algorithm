/******************************************************************************
 *\file isa_max_weight.cc
 *\brief ���Ȩ��������ȣ������Ȩ��������ص������
 *\date 2017/03/01
 *****************************************************************************/

 
#include <stdio.h>
#include <string.h>
 
/**
 *\struct
 *\brief ����ṹ��
 */
typedef struct interval_schedule_st{
	 
	unsigned int	uint_beg;	///< ���� ��ʼλ��
	unsigned int	uint_end;	///< ���� ��ֹλ��
	unsigned int	uint_weight;	///< ���� Ȩ��
}interval_schedule_st;

/**
 *\struct
 *\brief ���������㷨 �����
 */
typedef struct isa_result_set{
	
	unsigned int 	max_length;		///< ��󳤶�
	unsigned int 	uint_cnt;		///< ��������������
	unsigned int	isa_array[30];	///< ����ľ�����Ϣ�� �������±�ֵ
}isa_result_set;

static interval_schedule_st	s_isa_array[30];	///< ���뻺����
static unsigned int s_isa_cnt = 0;				///< �����������
static isa_result_set s_isa_res[30];			///< ���յĽ����

/**
 *\brief ��ȡ������Ϣ
 */
static void isa_get_inputs(void){

	unsigned int s = 0, e = 0, w = 0, i = 0;
	
	while (3 == scanf("%u,%u,%u", &s, &e, &w))
	{
		s_isa_array[i].uint_end = e;
		s_isa_array[i].uint_beg = s;
		s_isa_array[i].uint_weight = w;
		++i;
	}
	
	s_isa_cnt = i;
}

/**
 *\brief ��ӡ��Ϣ
 */
static void isa_print_inputs(void){

	unsigned int i = 0;
	
	for (i = 0; i < s_isa_cnt; ++i)
	{
		printf("(%02u): %u - %u, %u\n", i, s_isa_array[i].uint_beg, 
				s_isa_array[i].uint_end, s_isa_array[i].uint_weight);
	}	
}

/**
 *\brief ����
 *\detail  ��������Ľ���ʱ������������
 */
static void isa_sort_by_endpoint(void){
		
	unsigned int i = 0, j = 0;
	
	for (; i < s_isa_cnt; ++i)
	{
		for (j = i; j < s_isa_cnt; ++j)
		{
			if (s_isa_array[i].uint_end > s_isa_array[j].uint_end)
			{
				unsigned int tmp = s_isa_array[j].uint_end;
				s_isa_array[j].uint_end = s_isa_array[i].uint_end;
				s_isa_array[i].uint_end = tmp;
				
				
				tmp = s_isa_array[j].uint_beg;
				s_isa_array[j].uint_beg = s_isa_array[i].uint_beg;
				s_isa_array[i].uint_beg = tmp;
				
				tmp = s_isa_array[j].uint_weight;
				s_isa_array[j].uint_weight = s_isa_array[i].uint_weight;
				s_isa_array[i].uint_weight = tmp;				
			}
		}
	}
}


/**
 *\brief ��ȡ�����ǵ�����
 *\detail ������õ� �������ҵ������ǵ��Ǹ����䣬 ���������±�־
 *\param[in] idx �����ҵ��±�ֵ
 *\retval >= 0 �±�־ 
 *\retval < 0 �����ڲ����ǵ�����
 */
static int get_noncover_interval(unsigned int idx){
	
	unsigned int i = 0;
	for (i = idx - 1; i >= 0; --i){
		
		if (s_isa_array[idx].uint_beg > s_isa_array[i].uint_end || 
			s_isa_array[idx].uint_end < s_isa_array[i].uint_beg){
				
			return i;
		}
	}
	
	return -1;
}
/**
 *\brief ��������ѡȡ
 *\detail �㷨���ö�̬�滮��dp����⣬˼·�ǣ���������iѡȡ���\
 *	1. ���ѡȡ����i����ʾ��i���������ǰ��i-1�����䲻�ص����������ô��Ҫ��i-1���������ҵ�һ��λ�ò��͵�i�������и��ǵ�λ�ã�
 *	�����������Ϊk����ô����i��ѡ�к��ȡֵ���� max(dp[k] + 1,dp[i-1])ȡ���нϴ�ģ����������ͻ��ôk = i-1�ˣ�������Ȼ������
 *	2. �����ѡ������i�� ��ʾ����i�����ں�ǰ��i-1�����䲻�ص����������ô���ֵ����max(dp[i-1], Ei - Bi)��ȡ���нϴ�ġ�
 */
static void isa_do_work(void){
	
	unsigned int i = 0, max = 0;
	
	if (s_isa_cnt <= 0){
		
		return;
	}
	
	s_isa_res[0].max_length = (s_isa_array[0].uint_end - s_isa_array[0].uint_beg) * s_isa_array[0].uint_weight;
	s_isa_res[0].uint_cnt = 1;
	s_isa_res[0].isa_array[0] = 0;
	for (i = 1; i < s_isa_cnt; ++i){
		
		int k = get_noncover_interval(i);
		isa_result_set tmp_set;
		if (k > 0){/* ��ʾ ���ڲ��ص������ */
			
			max = s_isa_res[k].max_length + (s_isa_array[i].uint_end - s_isa_array[i].uint_beg) * s_isa_array[i].uint_weight;;
			memcpy(&tmp_set, &s_isa_res[k], sizeof(isa_result_set));
			tmp_set.max_length = max;
			tmp_set.uint_cnt += 1;
			tmp_set.isa_array[tmp_set.uint_cnt - 1] = i;
		}else{
			
			max = (s_isa_array[i].uint_end - s_isa_array[i].uint_beg)  * s_isa_array[i].uint_weight;;
			tmp_set.max_length = max;
			tmp_set.uint_cnt = 1;
			tmp_set.isa_array[0] = i;			
		}
		
		if (s_isa_res[i-1].max_length > max){
			
			memcpy(&s_isa_res[i], &s_isa_res[i - i], sizeof(isa_result_set));
		}else{
			
			memcpy(&s_isa_res[i], &tmp_set, sizeof(isa_result_set));
		}
	}
	
	/** ������ */
	printf("\nresult\n max_lenght[%u]\n", s_isa_res[s_isa_cnt - 1].max_length);
	for (i = 0; i < s_isa_res[s_isa_cnt - 1].uint_cnt; ++i){
		
		printf("%02u - %02u, %02u\n", s_isa_array[s_isa_res[s_isa_cnt - 1].isa_array[i]].uint_beg,
				s_isa_array[s_isa_res[s_isa_cnt - 1].isa_array[i]].uint_end,
				s_isa_array[s_isa_res[s_isa_cnt - 1].isa_array[i]].uint_weight);
	}
	printf("\n");
}

int main(void){
	
	isa_get_inputs();
	
	isa_print_inputs();
	
	isa_sort_by_endpoint();
	
	isa_print_inputs();
	
	isa_do_work();
	
	return 0;
}