/******************************************************************************
 *\file  isa_max_overlap.cc
 *\brief  区间调度算法， 最大区间覆盖数量
 *\date 2017/03/02
 *****************************************************************************/
 
#include <stdio.h>
#include <string.h>

/**
 *\enum
 *\brief 位置类型
 */
enum isa_pos_attr_en{
	
	POS_LEFT_SIDE = 1,	///< 表示左边位置
	POS_RIGHT_SIDE = 2,	///< 表示右边位置
};

/**
 *\struct
 *\brief 位置结构
 */
typedef struct isa_pos_st{

	unsigned char	char_id;	///< 锚点值
	unsigned int	pos_beg;	///< 起始位置
	unsigned int	pos_end;	///< 终止位置
}isa_pos_st;

/**
 *\struct
 *\brief 点属性
 */
typedef struct isa_point_st{
	
	unsigned int 	p_side;	///< 位置属性  取值见 enum isa_pos_attr_en 枚举	
	unsigned int	p_dis;	///< 点在x方向上的距离（输入的先后顺序
}isa_point_st;

static isa_pos_st s_pos_array[30];		///< 位置信息
static unsigned int s_pos_array_len;	///< 位置信息数量
static isa_point_st s_point_array[60];

/**
 *\fn
 *\brief 获取输入
 */
static void isa_get_input(void){
	
	char buf[1024];
	unsigned int i = 0, str_len = 0, j = 0;
	
	if (gets(buf) == NULL){
		
		return;
	}
	
	str_len = strlen(buf);
	for (i = 0; i < str_len; ++i){
		
		for (j = 0; j < s_pos_array_len; ++j){
			
			if (s_pos_array[j].char_id == buf[i]){
				
				if (s_pos_array[j].pos_beg == 0){
					
					s_pos_array[j].pos_beg = s_pos_array[j].pos_end = i + 1;
				}else{
					
					s_pos_array[j].pos_end = i + 1;
				}
				
				break;
			}
		}
		
		if (j >= s_pos_array_len){
			
			s_pos_array[s_pos_array_len].pos_beg = s_pos_array[s_pos_array_len].pos_end = i + 1;
			s_pos_array[s_pos_array_len].char_id = buf[i];
			s_pos_array_len += 1;
		}
	}
}

/**
 *\fn
 *\brief 将数据打印出来
 */
static void isa_print_input(void){

	unsigned int i = 0;
	
	for (i = 0; i < s_pos_array_len; ++i){
		
		printf("(%02u) %c [%u - %u]\n", i, s_pos_array[i].char_id, s_pos_array[i].pos_beg, s_pos_array[i].pos_end);
	}
	printf("\n");
}

/**
 *\fn
 *\brief 算法思想
 *\detail  将所有的位置点进行排序， 然后起始点 到 结束点的方向 进行位置扫描，当发现一个点事起始点则加1 \
 *			若是发现是终止点则减1， 通过一遍扫描 可以获得最大重叠数量。
 */
static void isa_do_work(void){
	
	/** 将位置中的所有点进行排序 */
	unsigned int i = 0, j = 0, max = 0;
	
	for (i = 0; i < s_pos_array_len; ++i){
		
		s_point_array[i * 2].p_dis = s_pos_array[i].pos_beg;
		s_point_array[i * 2].p_side = POS_LEFT_SIDE;
	
		s_point_array[i * 2 + 1].p_dis = s_pos_array[i].pos_end;
		s_point_array[i * 2 + 1].p_side = POS_RIGHT_SIDE;
	}
	
	/** 冒泡排序 */
	for (i = 0; i < s_pos_array_len * 2; ++i){
		
		for (j = i + 1; j < s_pos_array_len * 2; ++j){
			
			if (s_point_array[i].p_dis > s_point_array[j].p_dis){
				
				unsigned int tmp = s_point_array[i].p_dis;
				
				s_point_array[i].p_dis = s_point_array[j].p_dis;
				s_point_array[j].p_dis = tmp;
				
				tmp = s_point_array[i].p_side;
				s_point_array[i].p_side = s_point_array[j].p_side;
				s_point_array[j].p_side = tmp;
			}
		}
	}
	
	/** 冒泡排序 */
	j = 0;
	for (i = 0; i < s_pos_array_len * 2; ++i){
		
		if (s_point_array[i].p_side == POS_LEFT_SIDE){
			
			j += 1;
		}else{
			
			j -= 1;
		}
		
		if (max < j){
			
			max = j;
		}
	}
	
	printf("max overlap is: %u\n", max);
}

int main(void){
	
	isa_get_input();
	
	isa_print_input();
	
	isa_do_work();
	
	return 0;
}