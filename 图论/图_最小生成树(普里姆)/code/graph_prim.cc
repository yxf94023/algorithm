/******************************************************************************
 *\file graph_prim.cc
 *\brief 图的最小生成树
 *		Prim算法
 *		图 采用 邻接表（Adjacency list） 形式存储
 *\date 2017/04/03
 *****************************************************************************/

#include "graph_prim.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


#define	RET_SUCCESS		(1)		///< 成功状态
#define	RET_FAILED		(0)		///< 失败状态


/**
 *\brief 查询结点在向量中的下标
 *\param[in] pg 图的句柄
 *\param[in] ver 待查询的结点
 *\retval 返回下标志， 无失败可能
 */
static unsigned int find_vers_idx(adj_graph_st *pg, ver_type ver)
{
	unsigned int i = 0;
	unsigned int find_ok = 0;
	
	assert(NULL != pg);
	
	for (i = 0; i < pg->ver_cnt; ++i){
		
		if (strcmp(pg->ver_list[i].ver_name, ver) == 0){
			
			find_ok = 1;
			break;
		}
	}
		
	assert(find_ok);
	
	return i;
}

/**
 *\brief 向图中 增添边的信息
 *\param[in,out] pg 图的句柄
 *\param[in] s_pos 边的起始点
 *\param[in] e_pos 边的终止点
 *\param[in] weight 边的权重
 *\retval 1 成功
 *\retval 0 失败
 */
static int add_graph_arc(adj_graph_st *pg, unsigned int s_pos, unsigned int e_pos, unsigned int weight)
{
	arc_st *p_tmparc = NULL, *exchg_tmp = NULL;
	
	assert(NULL != pg);
	assert(s_pos < pg->ver_cnt && e_pos < pg->ver_cnt);
	
	p_tmparc = (arc_st *) malloc (sizeof(arc_st));
	if (NULL == p_tmparc){
		
		printf("call malloc failed, error[%d]", errno);
		return RET_FAILED;
	}
	
	p_tmparc->index = e_pos;
	p_tmparc->weight = weight;
	p_tmparc->p_next = NULL;
	
	///< 头部插入
	exchg_tmp = pg->ver_list[s_pos].p_arc;
	pg->ver_list[s_pos].p_arc = p_tmparc;
	p_tmparc->p_next = exchg_tmp;
	
	p_tmparc = (arc_st *) malloc (sizeof(arc_st));
	if (NULL == p_tmparc){
		
		printf("call malloc failed, error[%d]", errno);
		return RET_FAILED;
	}
	
	p_tmparc->index = s_pos;
	p_tmparc->weight = weight;	
	p_tmparc->p_next = NULL;

	exchg_tmp = pg->ver_list[e_pos].p_arc;
	pg->ver_list[e_pos].p_arc = p_tmparc;
	p_tmparc->p_next = exchg_tmp;

	return RET_SUCCESS;	
}

/**
 *\brief 构造 图
 *\param[in,out] pg 图的句柄
 *\retval 0 失败
 *\retval 1 成功
 */
static int creat_graph(adj_graph_st *pg)
{
	unsigned int i = 0;
	ver_type start_ver, end_ver;	///< 一条边上 其实和终止结点
	unsigned int start_pos = 0, end_pos = 0;	///< 启始 和 终止结点所对应的下标
	unsigned int weight = 0;
	
	assert(NULL != pg);
	
	printf("输入图的结点数:");
	scanf("%u", &pg->ver_cnt);
	printf("输入图的边数:");
	scanf("%u", &pg->arc_cnt);
	
	pg->ver_list = (ver_st *) malloc (sizeof(ver_st) * pg->ver_cnt);
	memset(pg->ver_list, 0, (sizeof(ver_st) * pg->ver_cnt));
	
	printf("输入结点序列（例如：v1 v2 v3）：\n");
	for (i = 0; i < pg->ver_cnt; ++i){
		
		scanf("%s", pg->ver_list[i].ver_name);
	}
	
	printf("输入边信息（例如：v1 - v2 5）：\n");
	for (i = 0; i < pg->arc_cnt; ++i){
		
		scanf("%s %*s %s %u", start_ver, end_ver, &weight);
		
		start_pos = find_vers_idx(pg, start_ver);
		end_pos = find_vers_idx(pg, end_ver);
		
		if (!add_graph_arc(pg, start_pos, end_pos, weight)){	///< 向图中增加边信息
		
			return RET_FAILED;
		}
	}
	
	return RET_SUCCESS;
}

/**
 *\brief 输出图的结构信息
 *\param[in] pg 图的句柄
 */
static void print_graph(adj_graph_st *pg)
{
	arc_st *p_tmparc = NULL;
	unsigned int i = 0;
	
	assert(NULL != pg);
	
	printf("输出图的链接信息：\n");
	
	for (i = 0; i < pg->ver_cnt; ++i){
		
		printf("%s ", pg->ver_list[i].ver_name);
		p_tmparc = pg->ver_list[i].p_arc;
		while (NULL != p_tmparc){
			
			printf("->%u(%u)", p_tmparc->index, p_tmparc->weight);
			p_tmparc = p_tmparc->p_next;
		}
		printf("\n");
	}
}

/**
 *\brief 图的 销毁
 *\param[in,out] pg 图的句柄
 */
static void destroy_graph(adj_graph_st *pg)
{
	arc_st *p_tmparc = NULL;
	unsigned int i = 0;
	
	assert(NULL != pg);
	
	///< 释放邻接表
	for (i = 0; i < pg->ver_cnt; ++i){
		
		while (NULL != pg->ver_list[i].p_arc){
			
			p_tmparc = pg->ver_list[i].p_arc;
			pg->ver_list[i].p_arc = p_tmparc->p_next;
			free(p_tmparc);
		}
	}
	
	///< 释放图的节点信息
	if (NULL != pg->ver_list){
		
		free(pg->ver_list);
		pg->ver_list = NULL;
	}
}

/**
 *\brief 调整边的辅助数组中边的状态
 *\param[in] pg 图的句柄
 *\param[in] prim_array 边的辅助数字
 *\param[in] idx刚加入S集的顶点下标
 */
static void adjust_arc_status(adj_graph_st *pg, prim_arc_st *prim_array, unsigned int idx)
{
	prim_arc_st *p_ret = NULL;
	unsigned int i = 0;
	
	for (i = 0; i < pg->arc_cnt; ++i){
		
		if ((prim_array[i].ver1 == idx || prim_array[i].ver2 == idx) && prim_array[i].status != 2){
			
			if (prim_array[i].status == 0){
				
				prim_array[i].status = 1;
			}else if (prim_array[i].status == 1){
				
				prim_array[i].status = 2;
			}else{
				
				assert(2 > prim_array[i].status);
			}
		}
	}
}
 
/**
 *\brief 找到和 S集合 顶点相连的最短边
 *\param[in] pg 图的句柄
 *\param[in] prim_array 边的辅助数字
 *\retval 返回最短边的地址
 */
static prim_arc_st *search_min_arc(adj_graph_st *pg, prim_arc_st *prim_array)
{
	prim_arc_st *p_ret = NULL;
	unsigned int i = 0;
	
	for (i = 0; i < pg->arc_cnt; ++i){
		
		if (prim_array[i].status == 1){
			
			if (NULL == p_ret){
				
				p_ret = &prim_array[i];
			}else{
				
				if (p_ret->weight > prim_array[i].weight){
					
					p_ret = &prim_array[i];
				}
			}
		}
	}
	
	assert(NULL != p_ret);
	
	return p_ret;
}

/**
 *\brief 输出dijkstra计算的最终结果
 *\param[in] pg 图的句柄
 *\param[in] prim_array 顶点的辅助数字
 */
static void print_prim_result(adj_graph_st *pg, prim_ver_st *prim_array)
{
	unsigned int i = 0, j = 0;
	unsigned int total = 0;
	
	printf("\nresult: \n");
	
	// 对结果按照 加入最小生成树的先后顺序排序
	for (i = 0; i < pg->ver_cnt; ++i){
		
		for (j = 0; j < pg->ver_cnt; ++j){
			
			if (prim_array[j].index == i + 1){
				
				printf("%u(%u) ", j, prim_array[j].weight);
				total += prim_array[j].weight;
			}
		}
	}

	printf("\ntotal_weight[%u]\n", total);
}

/**
 *\brief 计算最短路径
 *\param[in] pg 图的句柄
 *\param[in] sidx 起始搜索的顶点
 */
static void prim_graph(adj_graph_st *pg, unsigned int sidx)
{
	prim_ver_st *prim_ver_ary = NULL;
	prim_arc_st *prim_arc_ary = NULL;
	arc_st *p_tmparc = NULL;	
	unsigned int i = 0, j = 0, index = 1;
	
	assert(NULL != pg);
	assert(sidx < pg->ver_cnt);
	
	// 初始化辅助变量
	prim_arc_ary = (prim_arc_st *)malloc(sizeof(prim_arc_st) * pg->arc_cnt);
	assert(NULL != prim_arc_ary);
	for (i = 0; i < pg->ver_cnt; ++i){
		
		p_tmparc = pg->ver_list[i].p_arc;
		while (NULL != p_tmparc){

			if (i < p_tmparc->index){
				
				prim_arc_ary[j].ver1 = i;
				prim_arc_ary[j].ver2 = p_tmparc->index;
				prim_arc_ary[j].weight = p_tmparc->weight;
				prim_arc_ary[j].status = 0;
				++j;
			}
			
			p_tmparc = p_tmparc->p_next;			
		}
	}// 这里其实可以采用堆排序 加速后面的查找过程
	
	prim_ver_ary = (prim_ver_st *)malloc(sizeof(prim_ver_st) * pg->ver_cnt);
	assert(NULL != prim_ver_ary);
	for (i = 0; i < pg->ver_cnt; ++i){
		
		prim_ver_ary[i].index = 0;
		prim_ver_ary[i].weight = 0;
		prim_ver_ary[i].isfinal = 0;
	}
	
	prim_ver_ary[sidx].index = index++;
	prim_ver_ary[sidx].weight = 0;
	prim_ver_ary[sidx].isfinal = 1;
	adjust_arc_status(pg, prim_arc_ary, sidx);
	
	for (i = 1; i < pg->ver_cnt; ++i){

		// 查找和S集合连接的最小边
		prim_arc_st *prim_arc = NULL;
		prim_arc = search_min_arc(pg, prim_arc_ary);
		
		if (!prim_ver_ary[prim_arc->ver1].isfinal){
			
			sidx = prim_arc->ver1;
			prim_ver_ary[prim_arc->ver1].isfinal = 1;
			prim_ver_ary[prim_arc->ver1].index = index++;
			prim_ver_ary[prim_arc->ver1].weight = prim_arc->weight;
		}else{
		
			sidx = prim_arc->ver2;
			prim_ver_ary[prim_arc->ver2].isfinal = 1;
			prim_ver_ary[prim_arc->ver2].index = index++;
			prim_ver_ary[prim_arc->ver2].weight = prim_arc->weight;
		}
		adjust_arc_status(pg, prim_arc_ary, sidx);		
	}
	
	// 输出所有的具体信息
	print_prim_result(pg, prim_ver_ary);
}

int main(void)
{
	adj_graph_st graph;
	
	creat_graph(&graph);
	
	print_graph(&graph);
	
	prim_graph(&graph, 0);
	
	destroy_graph(&graph);
	
	return 0;
}

