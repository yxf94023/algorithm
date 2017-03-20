/******************************************************************************
 *\file graph_bfs.h
 *\brief 定义图相关的结构体
 *\date 2017/03/20
 *****************************************************************************/
#ifndef __GRAPH_BFS_H_2017_03_20__
#define	__GRAPH_BFS_H_2017_03_20__


#define VER_CHAR_SIZE	(10)	///< 结点的字符串长度

typedef char ver_type[VER_CHAR_SIZE];	///< 定义节点类型

/**
 *\struct
 *\brief 弧（边）的结构
 */
typedef struct arc_st{
	
	unsigned int	index;		///< 结点的下标值
	struct arc_st	*p_next;	///< 指向下一个弧
}arc_st;

/**
 *\struct
 *\brief 结点 的结构
 */
typedef struct ver_st{
	
	ver_type	ver_name;	///< 结点名称
	arc_st		*p_arc;		///< 弧
}ver_st;

/**
 *\struct
 *\brief 图的结构
 */
typedef struct adj_graph_st{
	
	unsigned int	arc_cnt;	///< 图中 边的数量
	unsigned int	ver_cnt;	///< 图中 结点的数量
	
	ver_st			*ver_list;	///< 结点 列表   动态数组
}adj_graph_st;

#endif//__GRAPH_BFS_H_2017_03_20__