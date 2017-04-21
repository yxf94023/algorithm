/******************************************************************************
 *\file closest_pair.h
 *\brief 二维平面上求给出的n个点中 找出邻近距离最小的点对
 *\date 2017/04/21
 *****************************************************************************/
#ifndef __CLOSEST_PAIR_H_2017_04_21__
#define	__CLOSEST_PAIR_H_2017_04_21__

#ifdef __cplusplus
extern "C"{
#endif


#define MAX_POINTS	(100)	///< 最大支持的点的输入

/**
 *\brief 二维坐标点的结构
 */
typedef struct point_st{
	
	double	x;	///< 坐标x
	double  y;	///< 坐标y
}point_st;

/**
 *\brief 邻近点对结构
 */
typedef struct closest_pair_st{
	
	point_st p1;	///< 第一个点
	point_st p2;	///< 第二个点
	double 	 d;		///< 两点间的距离
}closest_pair_st;

/**
 *\brief 点的表结构，按照x或y轴进行排序时使用
 */
typedef struct ptables_st{
	
	unsigned int	idx;	///< 点在点的集合中位置
	double			xy;		///< x轴 或 y轴的坐标
}ptables_st;

/**
 *\brief 获取最邻近的点对
 *\param[in] plist 待处理的点信息
 *\param[in] pnum 待处理的点数量
 *\param[out] pair 获取得到的结果
 *\retval 1 成功
 *\retval 0 失败
 */
int get_closest_pair(point_st *plist, unsigned int pnum, closest_pair_st *pair);

#ifdef __cplusplus
}
#endif

#endif//__CLOSEST_PAIR_H_2017_04_21__