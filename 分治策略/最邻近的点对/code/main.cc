/******************************************************************************
 *\file main.cc
 *\brief ��άƽ�����������n������ �ҳ��ڽ�������С�ĵ��
 *\date 2017/04/21
 *****************************************************************************/

#include "closest_pair.h"
#include <stdio.h>
#include <assert.h>


static unsigned int s_points_num;		///< �������
static point_st s_points[MAX_POINTS];	///< ����б�


/**
 *\brief �����ն�������Ϣ
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
static int get_input(void)
{
	unsigned int i = 0;
	
	printf("����������:");
	scanf("%u", &s_points_num);
	
	assert(MAX_POINTS >= s_points_num);
	
	printf("һ��һ���� ���磺4,5   ����4Ϊx������ 5Ϊy������\n");
	for (i = 0; i < s_points_num; ++i){
		
		scanf("%d,%d", &s_points[i].x, &s_points[i].y);
	}
	
	return 0;
}

int main(void)
{
	closest_pair_st pair;
	
	get_input();
	
	if (get_closest_pair(s_points, s_points_num, &pair)){
	
		// ������
	}
	
	return 0;
}


