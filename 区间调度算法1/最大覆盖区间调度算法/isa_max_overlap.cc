/******************************************************************************
 *\file  isa_max_overlap.cc
 *\brief  ��������㷨�� ������串������
 *\date 2017/03/02
 *****************************************************************************/
 
#include <stdio.h>
#include <string.h>

/**
 *\enum
 *\brief λ������
 */
enum isa_pos_attr_en{
	
	POS_LEFT_SIDE = 1,	///< ��ʾ���λ��
	POS_RIGHT_SIDE = 2,	///< ��ʾ�ұ�λ��
};

/**
 *\struct
 *\brief λ�ýṹ
 */
typedef struct isa_pos_st{

	unsigned char	char_id;	///< ê��ֵ
	unsigned int	pos_beg;	///< ��ʼλ��
	unsigned int	pos_end;	///< ��ֹλ��
}isa_pos_st;

/**
 *\struct
 *\brief ������
 */
typedef struct isa_point_st{
	
	unsigned int 	p_side;	///< λ������  ȡֵ�� enum isa_pos_attr_en ö��	
	unsigned int	p_dis;	///< ����x�����ϵľ��루������Ⱥ�˳��
}isa_point_st;

static isa_pos_st s_pos_array[30];		///< λ����Ϣ
static unsigned int s_pos_array_len;	///< λ����Ϣ����
static isa_point_st s_point_array[60];

/**
 *\fn
 *\brief ��ȡ����
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
 *\brief �����ݴ�ӡ����
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
 *\brief �㷨˼��
 *\detail  �����е�λ�õ�������� Ȼ����ʼ�� �� ������ķ��� ����λ��ɨ�裬������һ��������ʼ�����1 \
 *			���Ƿ�������ֹ�����1�� ͨ��һ��ɨ�� ���Ի������ص�������
 */
static void isa_do_work(void){
	
	/** ��λ���е����е�������� */
	unsigned int i = 0, j = 0, max = 0;
	
	for (i = 0; i < s_pos_array_len; ++i){
		
		s_point_array[i * 2].p_dis = s_pos_array[i].pos_beg;
		s_point_array[i * 2].p_side = POS_LEFT_SIDE;
	
		s_point_array[i * 2 + 1].p_dis = s_pos_array[i].pos_end;
		s_point_array[i * 2 + 1].p_side = POS_RIGHT_SIDE;
	}
	
	/** ð������ */
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
	
	/** ð������ */
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