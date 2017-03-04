/******************************************************************************
 *\file isa_max_weight.cc
 *\brief 最大权重区间调度：计算带权区间最大不重叠区间和
 *\date 2017/03/01
 *****************************************************************************/

 
#include <stdio.h>
#include <string.h>
 
/**
 *\struct
 *\brief 区间结构体
 */
typedef struct interval_schedule_st{
	 
	unsigned int	uint_beg;	///< 区间 起始位置
	unsigned int	uint_end;	///< 区间 终止位置
	unsigned int	uint_weight;	///< 区间 权重
}interval_schedule_st;

/**
 *\struct
 *\brief 最长区间调度算法 结果集
 */
typedef struct isa_result_set{
	
	unsigned int 	max_length;		///< 最大长度
	unsigned int 	uint_cnt;		///< 包含的区间数量
	unsigned int	isa_array[30];	///< 区间的具体信息， 排序后的下标值
}isa_result_set;

static interval_schedule_st	s_isa_array[30];	///< 输入缓冲区
static unsigned int s_isa_cnt = 0;				///< 输入区间个数
static isa_result_set s_isa_res[30];			///< 最终的结果集

/**
 *\brief 获取输入信息
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
 *\brief 打印信息
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
 *\brief 排序
 *\detail  根据区间的结束时间进行排序操作
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
 *\brief 获取不覆盖的区间
 *\detail 从排序好的 区间中找到不覆盖的那个区间， 返回区间下标志
 *\param[in] idx 待查找的下标值
 *\retval >= 0 下标志 
 *\retval < 0 不存在不覆盖的区间
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
 *\brief 进行区间选取
 *\detail 算法采用动态规划（dp）求解，思路是，对于区间i选取与否，\
 *	1. 如果选取区间i，表示第i区间存在与前面i-1个区间不重叠的情况，那么需要在i-1个区间中找到一个位置不和第i个区间有覆盖的位置，
 *	假设这个区间为k，那么区间i被选中后的取值就是 max(dp[k] + 1,dp[i-1])取其中较大的；如果都不冲突那么k = i-1了，结论依然成立。
 *	2. 如果不选择区间i， 表示区间i不存在和前面i-1个区间不重叠的情况，那么最大值就是max(dp[i-1], Ei - Bi)，取其中较大的。
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
		if (k > 0){/* 表示 存在不重叠的情况 */
			
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
	
	/** 输出结果 */
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