/******************************************************************************
 *\file graph_dijkstra.h
 *\brief 定义图相关的结构体
 *\date 2017/03/22
 *****************************************************************************/
#ifndef __GRAPH_DIJKSTRA_H_2017_03_29__
#define	__GRAPH_DIJKSTRA_H_2017_03_29__


#define VER_CHAR_SIZE	(10)	///< 结点的字符串长度

typedef char ver_type[VER_CHAR_SIZE];	///< 定义节点类型

/**
 *\brief 图中 弧（边）的结构
 *
 *	- 两个成员变量 分别是
 *		+ 图顶点 在顶点向量中的下标值，值是从0下标开始的
 *		+ 指向下一个弧（边）的指针
 */
typedef struct arc_st{
	
	unsigned int	index;		///< 顶点的下标值
	unsigned int	weight;		///< 权重
	struct arc_st	*p_next;	///< 指向下一个弧
}arc_st;

/**
 *\brief 图中 顶点 的结构
 *
 *	- 采用邻接表的方式存储，含有两个成员变量
 *		+ 顶点的名称
 *		+ 指向下一个弧（边）的指针
 */
typedef struct ver_st{
	
	ver_type	ver_name;	///< 顶点名称
	arc_st		*p_arc;		///< 弧（边）
}ver_st;

/**
 *\brief 图的结构
 */
typedef struct adj_graph_st{
	
	unsigned int	arc_cnt;	///< 图中 边的数量
	unsigned int	ver_cnt;	///< 图中 结点的数量
	
	ver_st			*ver_list;	///< 顶点 列表   动态数组
}adj_graph_st;

#define	DIJ_MAX_WEIGHT	(10000)	///< 最大权重，默认配置不会超过这个值

/**
 *\brief 辅助结构体 实现dijkstra算法
 *
 *	记录权重
 *	标记顶点是否已经标记过
 */
typedef struct dij_ver_st{

	unsigned int 	weight;		///< 路径总的权重
	unsigned int 	isfinal;	///< 是否被标记过默认为0未标记，1表示标记
}dij_ver_st;

/**
 *\brief 辅助结构体 实现dijkstra算法
 *
 *	记录边，对边进行排序
 */
typedef struct dij_arc_st{
	
	unsigned int	ver1;		///< 边上顶点1
	unsigned int 	ver2;		///< 边上顶点2
	unsigned int 	weight;		///< 边的权重
	unsigned int 	status;		///< 边的状态 0,1,2
}dij_arc_st;

#endif//__GRAPH_DIJKSTRA_H_2017_03_29__
