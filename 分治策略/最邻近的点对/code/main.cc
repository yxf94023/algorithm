/******************************************************************************
 *\file main.cc
 *\brief 二维平面上求给出的n个点中 找出邻近距离最小的点对
 *\date 2017/04/21
 *****************************************************************************/

#include "closest_pair.h"
#include <stdio.h>
#include <assert.h>


static unsigned int s_points_num;		///< 点的数量
static point_st s_points[MAX_POINTS];	///< 点的列表


/**
 *\brief 捕获终端输入信息
 *\retval 1 成功
 *\retval 0 失败
 */
static int get_input(void)
{
	unsigned int i = 0;
	
	printf("输入点的数量:");
	scanf("%u", &s_points_num);
	
	assert(MAX_POINTS >= s_points_num);
	
	printf("一行一个点 例如：4,5   其中4为x轴坐标 5为y轴坐标\n");
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
	
		// 输出结果
	}
	
	return 0;
}


