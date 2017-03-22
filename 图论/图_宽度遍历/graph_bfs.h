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
 *\brief 图中 弧（边）的结构
 *
 *	-两个成员变量 分别是
 *		+ 图顶点 在顶点向量中的下标值，值是从0下标开始的
 *		+ 指向下一个弧（边）的指针
 */
typedef struct arc_st{
	
	unsigned int	index;		///< 顶点的下标值
	struct arc_st	*p_next;	///< 指向下一个弧
}arc_st;

/**
 *\brief 图中 顶点 的结构
 *
 *	-采用邻接表的方式存储，含有两个成员变量
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

#endif//__GRAPH_BFS_H_2017_03_20__