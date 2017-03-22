/******************************************************************************
 *\file graph_bfs.cc
 *\brief 图的宽度搜索
 *		图 采用 邻接表（Adjacency list） 形式存储
 *\date 2017/03/16
 *****************************************************************************/

#include "queue_list.h"
#include "graph_bfs.h"
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


#define	RET_SUCCESS		(1)		///< 成功状态
#define	RET_FAILED		(0)		///< 失败状态


/**
 *\fn
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
 *\fn
 *\brief 向图中 增添边的信息
 *\param[in/out] pg 图的句柄
 *\param[in] s_pos 边的起始点
 *\param[in] e_pos 边的终止点
 *\retval 1 成功
 *\retval 0 失败
 */
static int add_graph_arc(adj_graph_st *pg, unsigned int s_pos, unsigned e_pos)
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
	p_tmparc->p_next = NULL;

	exchg_tmp = pg->ver_list[e_pos].p_arc;
	pg->ver_list[e_pos].p_arc = p_tmparc;
	p_tmparc->p_next = exchg_tmp;

	return RET_SUCCESS;	
}

/**
 *\fn 
 *\brief 构造 图
 *\param[in/out] pg 图的句柄
 *\retval 0 失败
 *\retval 1 成功
 */
static int creat_graph(adj_graph_st *pg)
{
	unsigned int i = 0;
	ver_type start_ver, end_ver;	///< 一条边上 其实和终止结点
	unsigned int start_pos = 0, end_pos = 0;	///< 启始 和 终止结点所对应的下标
	
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
	
	printf("输入边信息（例如：v1 - v2）：\n");
	for (i = 0; i < pg->arc_cnt; ++i){
		
		scanf("%s %*s %s", start_ver, end_ver);
		
		start_pos = find_vers_idx(pg, start_ver);
		end_pos = find_vers_idx(pg, end_ver);
		
		if (!add_graph_arc(pg, start_pos, end_pos)){	///< 向图中增加边信息
		
			return RET_FAILED;
		}
	}
	
	return RET_SUCCESS;
}

/**
 *\fn 
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
			
			printf("->%u ", p_tmparc->index);
			p_tmparc = p_tmparc->p_next;
		}
		printf("\n");
	}
}

/**
 *\fn
 *\brief 图的 销毁
 *\param[in/out] pg 图的句柄
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
 *\fn
 *\brief 执行图的宽度搜索
 *\param[in] pg 图的句柄
 */
static void exec_bfs(const adj_graph_st *pg)
{
	unsigned int *express_flag = NULL;	///< 标识节点有搜索到的标志
	unsigned int i = 0;
	unsigned int cnt = 0;	///< 计数器 连通分支数量
	queue_st que;	///< 队列
	arc_st *p_tmparc = NULL;
	ver_st *p_tmpver = NULL;
	
	assert(NULL != pg);
	
	queue_init(&que);
	express_flag = (unsigned int *) malloc (sizeof(unsigned int) * pg->ver_cnt);
	memset(express_flag, 0, sizeof(unsigned int) * pg->ver_cnt);
	
	for (unsigned int i = 0; i < pg->ver_cnt; ++i){
		
		if (express_flag[i] != 0){
			
			continue;
		}
		
		express_flag[i] = 1;
		queue_enter(&que, &pg->ver_list[i]);	///< 进队列
		++cnt;
		
		while (!queue_empty(&que)){
			
			queue_outer(&que, (void**)(&p_tmpver));	///< 出队列
			
			p_tmparc = p_tmpver->p_arc;
			while (NULL != p_tmparc){
			
				if (express_flag[p_tmparc->index] == 0){
					
					express_flag[p_tmparc->index] = 1;
					queue_enter(&que, &pg->ver_list[p_tmparc->index]);
				}
				p_tmparc = p_tmparc->p_next;
			}
		}		
	}
	
	printf("连通分支数:%u\n", cnt);
}

int main(void)
{
	adj_graph_st graph;
	
	creat_graph(&graph);
	
	print_graph(&graph);
	
	exec_bfs(&graph);
	
	destroy_graph(&graph);
	
	return 0;
}

