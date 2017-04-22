/******************************************************************************
 *\file closest_pair.cc
 *\brief 二维平面上求给出的n个点中 找出邻近距离最小的点对
 *\date 2017/04/21
 *****************************************************************************/

#include "closest_pair.h"
#include "merge_sort.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

static ptables_st x_ptables[MAX_POINTS];	// x轴排序列表
static ptables_st y_ptables[MAX_POINTS];	// y轴排序列表
static unsigned int s_spnum;
static ptables_st s_ptables[MAX_POINTS];	// 与垂直线相距特定距离点的列表

/**
 *\brief 归并排序中 设置merge_array的初始值
 *\param[in] len 待初始化的数据规模
 *\param[in] disoder_ary 等待排序的数据
 *\param[in] merge_ary 初始化的对象
 *\retval 1 初始化成功
 *\retval 0 初始化失败
 */
int set_fun(unsigned int len, void *disoder_ary, void **merge_ary)
{
    unsigned int i = 0;
    ptables_st *ary1 = NULL, **ary2 = NULL;
    
    assert((void**)0 != disoder_ary);
    assert((void**)0 != merge_ary);
    
    ary1 = (ptables_st *)disoder_ary;
    ary2 = (ptables_st **)merge_ary;
    
    for (i = 0; i < len; ++i){
        
        ary2[i] = &ary1[i];
    }
    
    return 1;
}

/**
 *\brief 归并排序中 两个元素对比函数
 *\param[in] cmp1 对比元素1
 *\param[in] cmp2 对比元素2
 *\retval 1 cmp1 > cmp2
 *\retval 0 cmp1 = cmp2
 *\retval -1 cmp1 < cmp2
 */
int cmp_fun(void *cmp1, void *cmp2)
{
    int *int_cmp1 = NULL;
    int *int_cmp2 = NULL;

    assert(NULL != cmp1);
    assert(NULL != cmp2);
    
    int_cmp1 = (ptables_st*)cmp1;
    int_cmp2 = (ptables_st*)cmp2;
    if (int_cmp1->xy > int_cmp2->xy){
        
        return 1;
    }else if (int_cmp1->xy == int_cmp2->xy){
        
        return 0;
    }
    
    return -1;
}

/**
 *\brief 归并排序中 赋值操作
 *\param[in] lopr 被赋值的 等号 左边的数
 *\param[in] ropr 赋值的 等号 右边的数
 *\retval 1 赋值成功
 *\retval 0 赋值失败 
 */
int agn_fun(void **lopr, void *ropr)
{
    ptables_st **int_lopr = NULL;
    ptables_st *int_ropr = NULL;
    
    assert((void**)0 != lopr);
    assert(NULL != ropr);
    
    int_lopr = (ptables_st **)lopr;
    int_ropr = (ptables_st *)ropr;
    *int_lopr = int_ropr;
    
    return 1;
}

/**
 *\brief 归并排序中 获取排序结果
 *\param[in] len 获取结果的数据规模 
 *\param[in,out] res_ary 等待排序的数据
 *\param[in] merge_ary 归并排序后的结果
 *\retval 1 获取结果成功
 *\retval 0 获取结果失败
 */
int get_res_fun(unsigned int len, void *res_ary, void **merge_ary)
{
    ptables_st *buf = NULL, **ary = (int**)0, *res = NULL;
    unsigned int i = 0;
    
    assert(0 <= len);
    assert(NULL != res_ary);
    assert((void**)0 != merge_ary);
    
    buf = (ptables_st*) malloc (len * sizeof(ptables_st)); // 这里需要开辟空间 merge_ary，指向的内存地址就是res_ary的元素地址
    if (NULL == buf){
        
        printf("malloc failed, errno(%d)\n", errno);
        return 0;
    }
    ary = (ptables_st **)merge_ary;
    res = (ptables_st *)res_ary;
    
    for (i = 0; i < len; ++i){
        
        memcpy(&buf[i], ary[i], sizeof(ptables_st));    // 取指针指向的内容
    }
    
    memcpy(res, buf, len * sizeof(ptables_st));
    
	free(buf);
	buf = NULL;

    return 1;
}
	
/**
 *\brief 获取两点间的距离
 *\brief[in] plist 点的列表
 *\param[in] i 第一个点在点的列表中下标值
 *\param[in] j 第二个点在点的列表中下标值
 *\retval 2点间的距离值
 */
static double __get_2points_dist(point_st *plist, unsigned int i, unsigned int j)
{
    double x, y;
    
    x = pow(plist[i].x - plist[j].x, 2.0);
    y = pow(plist[i].y - plist[j].y, 2.0);
    
    return sqrt(x + y);
}

/**
 *\brief 递归处理各个分支
 *\param[in] plist 存放所有点列表
 *\param[in] pnum plist列表中点的数量
 *\param[in] beg 待处理点的起始下标
 *\param[in] num 待处理点的数量 从beg下标开始算起
 *\param[out] pair 输出邻近的点对
 *\retval 1 成功
 *\retval 0 失败
 */
static int __do_closest_pair(point_st *plist, 
							 unsigned int pnum,
							 unsigned int beg, 
							 unsigned int num, 
							 closest_pair_st *pair)
{
	unsigned int i = 0, j = 0;
	closest_pair_st l_pair, r_pair, min_pair;
	
	if (num <= 3){
		
		pair->p1.x = plist[beg].x;
		pair->p1.y = plist[beg].y;
		pair->p2.x = plist[beg+1].x;
		pair->p2.y = plist[beg+1].y;
		pair->d = __get_2points_dist(plist, beg, beg + 1);
		
		// 直接计算两点间的距离
		for (i = 0; i < num; ++i){
			
			for (j = i + 1; j < num; ++j){
				
				if (pair->d > __get_2points_dist(plist, beg + i, beg + j)){
					
					pair->p1.x = plist[beg+i].x;
					pair->p1.y = plist[beg+i].y;
					pair->p2.x = plist[beg+j].x;
					pair->p2.y = plist[beg+j].y;
					pair->d = __get_2points_dist(plist, beg + i, beg + j);					
				}
			}
		}
		
		return 1;
	}
	
	// 拆分成[1, num/2] 和 [num/2 + 1, num]
	__do_closest_pair(plist, pnum, beg, num/2, &l_pair);
	__do_closest_pair(plist, pnum, beg + num/2, num - num/2, &r_pair);
	if (l_pair.d < r_pair.d){
		
		memcpy(&min_pair, &l_pair, sizeof(closest_pair_st));
	}else{
		
		memcpy(&min_pair, &r_pair, sizeof(closest_pair_st));
	}
	
	// 计算两点一点落在左半边 一点落在右半边的情况， 统计所有与垂直直线 x = plist[beg + num/2].x 相距 min_pair.d 的距离的点
	for (i = 0, s_spnum = 0; i < pnum ; ++i){
		
		double dis = fabs(plist[beg + num/2].x - plist[y_ptables[i].idx].x);
		if (min_pair.d > dis){
			
			s_ptables[s_spnum].idx = y_ptables[i].idx;
			s_ptables[s_spnum].xy = y_ptables[i].xy;
			++s_spnum;
		}
	}
	
	if (s_spnum < 2){
	
		memcpy(pair, &min_pair, sizeof(closest_pair_st));
		return 1;
	}
	
	pair->p1.x = plist[s_ptables[0].idx].x;
	pair->p1.y = plist[s_ptables[0].idx].y;
	pair->p2.x = plist[s_ptables[1].idx].x;
	pair->p2.y = plist[s_ptables[1].idx].y;
	pair->d = __get_2points_dist(plist, s_ptables[0].idx, s_ptables[1].idx);
	for (i = 0; i < s_spnum; ++i){
		
		for (j = i+1; j <= i + 8 && j < s_spnum; ++j){
			
			if (pair->d > __get_2points_dist(plist, s_ptables[i].idx, s_ptables[j].idx)){
				
				pair->p1.x = plist[s_ptables[i].idx].x;
				pair->p1.y = plist[s_ptables[i].idx].y;
				pair->p2.x = plist[s_ptables[j].idx].x;
				pair->p2.y = plist[s_ptables[j].idx].y;
				pair->d = __get_2points_dist(plist, s_ptables[i].idx, s_ptables[j].idx);				
			}		
		}
	}
	
	if (min_pair.d < pair->d){
		
		memcpy(pair, &min_pair, sizeof(closest_pair_st));
	}
	
	return 1;
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
	unsigned int i = 0;
	
	
	assert(NULL != plist);
	assert(NULL != pair);
	assert(MAX_POINTS >= pnum);
	
	// 1. 将plist的点 按照x轴 和 y轴排序（归并排序） 得到两张表
	for (i = 0; i < pnum; ++i){
		
		x_ptables[i].xy = plist[i].x;
		y_ptables[i].xy = plist[i].y;
		x_ptables[i].idx = i;
		y_ptables[i].idx = i;
	}
	// 调用归并排序
    merge_init(pnum, (void *)x_ptables, set_fun, cmp_fun, agn_fun);
    merge_sort(pnum, (void *)x_ptables, get_res_fun);
    merge_destory();
    merge_init(pnum, (void *)y_ptables, set_fun, cmp_fun, agn_fun);
    merge_sort(pnum, (void *)y_ptables, get_res_fun);
    merge_destory();	
		
	// 2.查找最小临近点对
	__do_closest_pair(plist, pnum, 0, pnum, pair);
	
	return 0;
}


