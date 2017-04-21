/******************************************************************************
 *\file closest_pair.cc
 *\brief 二维平面上求给出的n个点中 找出邻近距离最小的点对
 *\date 2017/04/21
 *****************************************************************************/

#include "closest_pair.h"
#include <assert.h>
#include <math.h>


static int __do_closest_pair(point_st *plist, unsigned int beg, unsigned int num, closest_pair_st *pair)
{
	closest_pair_st l_pair, r_pair, min_pair;
	
	if (num <= 3){
		
		// 直接计算两点间的距离
		
		return 1;
	}
	
	// 拆分成[1, pnum/2] 和 [pnum/2 + 1, pnum]
	__do_closest_pair(beg, pnum/2, &l_pair);
	__do_closest_pair(beg + pnum/2, pnum - pnum/2, &r_pair);
	if (l_pair.d < r_pair.d){
		
		memset(&min_pair, &l_pair, sizeof(closest_pair_st));
	}else{
		
		memset(&min_pair, &r_pair, sizeof(closest_pair_st));
	}
	
	// 计算两点一点落在左半边 一点落在右半边的情况
	
	
	
}

/**
 *\brief 获取最邻近的点对
 *\param[in] plist 待处理的点信息
 *\param[in] pnum 待处理的点数量
 *\param[out] pair 获取得到的结果
 *\retval 1 成功
 *\retval 0 失败
 */
int get_closest_pair(point_st *plist, unsigned int pnum, closest_pair_st *pair)
{
	ptables_st x_ptables[MAX_POINTS];	// x轴排序列表
	ptables_st y_ptables[MAX_POINTS];	// y轴排序列表
	unsigned int i = 0;
	
	
	assert(NULL != plist)
	assert(NULL != pair)
	assert(MAX_POINTS >= pnum);
	
	// 1. 将plist的点 按照x轴 和 y轴排序（归并排序） 得到两张表
	for (i = 0; i < pnum; ++i){
		
		x_ptables[i].xy = plist[i].x;
		y_ptables[i].xy = plist[i].y;
		x_ptables[i].idx = i;
		y_ptables[i].idx = i;
	}
	// 调用归并排序
	
	// 2.查找最小临近点对
	__do_closest_pair(plist, 0, pnum, pair);
	
	return 0;
}


