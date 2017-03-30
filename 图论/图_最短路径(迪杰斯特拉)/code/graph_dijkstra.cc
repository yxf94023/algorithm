/******************************************************************************
 *\file graph_dijkstra.cc
 *\brief ͼ�����·��
 *		�Ͻ�˹�����㷨
 *		ͼ ���� �ڽӱ�Adjacency list�� ��ʽ�洢
 *\date 2017/03/22
 *****************************************************************************/

#include "graph_dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


#define	RET_SUCCESS		(1)		///< �ɹ�״̬
#define	RET_FAILED		(0)		///< ʧ��״̬


/**
 *\brief ��ѯ����������е��±�
 *\param[in] pg ͼ�ľ��
 *\param[in] ver ����ѯ�Ľ��
 *\retval �����±�־�� ��ʧ�ܿ���
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
 *\brief ��ͼ�� ����ߵ���Ϣ
 *\param[in,out] pg ͼ�ľ��
 *\param[in] s_pos �ߵ���ʼ��
 *\param[in] e_pos �ߵ���ֹ��
 *\param[in] weight �ߵ�Ȩ��
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
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
	
	///< ͷ������
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
 *\brief ���� ͼ
 *\param[in,out] pg ͼ�ľ��
 *\retval 0 ʧ��
 *\retval 1 �ɹ�
 */
static int creat_graph(adj_graph_st *pg)
{
	unsigned int i = 0;
	ver_type start_ver, end_ver;	///< һ������ ��ʵ����ֹ���
	unsigned int start_pos = 0, end_pos = 0;	///< ��ʼ �� ��ֹ�������Ӧ���±�
	unsigned int weight = 0;
	
	assert(NULL != pg);
	
	printf("����ͼ�Ľ����:");
	scanf("%u", &pg->ver_cnt);
	printf("����ͼ�ı���:");
	scanf("%u", &pg->arc_cnt);
	
	pg->ver_list = (ver_st *) malloc (sizeof(ver_st) * pg->ver_cnt);
	memset(pg->ver_list, 0, (sizeof(ver_st) * pg->ver_cnt));
	
	printf("���������У����磺v1 v2 v3����\n");
	for (i = 0; i < pg->ver_cnt; ++i){
		
		scanf("%s", pg->ver_list[i].ver_name);
	}
	
	printf("�������Ϣ�����磺v1 - v2 5����\n");
	for (i = 0; i < pg->arc_cnt; ++i){
		
		scanf("%s %*s %s %u", start_ver, end_ver, &weight);
		
		start_pos = find_vers_idx(pg, start_ver);
		end_pos = find_vers_idx(pg, end_ver);
		
		if (!add_graph_arc(pg, start_pos, end_pos, weight)){	///< ��ͼ�����ӱ���Ϣ
		
			return RET_FAILED;
		}
	}
	
	return RET_SUCCESS;
}

/**
 *\brief ���ͼ�Ľṹ��Ϣ
 *\param[in] pg ͼ�ľ��
 */
static void print_graph(adj_graph_st *pg)
{
	arc_st *p_tmparc = NULL;
	unsigned int i = 0;
	
	assert(NULL != pg);
	
	printf("���ͼ��������Ϣ��\n");
	
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
 *\brief ͼ�� ����
 *\param[in,out] pg ͼ�ľ��
 */
static void destroy_graph(adj_graph_st *pg)
{
	arc_st *p_tmparc = NULL;
	unsigned int i = 0;
	
	assert(NULL != pg);
	
	///< �ͷ��ڽӱ�
	for (i = 0; i < pg->ver_cnt; ++i){
		
		while (NULL != pg->ver_list[i].p_arc){
			
			p_tmparc = pg->ver_list[i].p_arc;
			pg->ver_list[i].p_arc = p_tmparc->p_next;
			free(p_tmparc);
		}
	}
	
	///< �ͷ�ͼ�Ľڵ���Ϣ
	if (NULL != pg->ver_list){
		
		free(pg->ver_list);
		pg->ver_list = NULL;
	}
}

/**
 *\brief �����ߵĸ��������бߵ�״̬
 *\param[in] pg ͼ�ľ��
 *\param[in] dij_array �ߵĸ�������
 *\param[in] idx�ռ���S���Ķ����±�
 */
static void adjust_arc_status(adj_graph_st *pg, dij_arc_st *dij_array, unsigned int idx)
{
	dij_arc_st *p_ret = NULL;
	unsigned int i = 0;
	
	for (i = 0; i < pg->arc_cnt; ++i){
		
		if ((dij_array[i].ver1 == idx || dij_array[i].ver2 == idx) && dij_array[i].status != 2){
			
			if (dij_array[i].status == 0){
				
				dij_array[i].status = 1;
			}else if (dij_array[i].status == 1){
				
				dij_array[i].status = 2;
			}else{
				
				assert(2 > dij_array[i].status);
			}
		}
	}
}
 
/**
 *\brief �ҵ��� idx ������������̱�
 *\param[in] pg ͼ�ľ��
 *\param[in] dij_array �ߵĸ�������
 *\param[in] idx�ռ���S���Ķ����±�
 *\retval ������̱ߵĵ�ַ
 */
static dij_arc_st *search_min_arc(adj_graph_st *pg, dij_arc_st *dij_array, unsigned int idx)
{
	dij_arc_st *p_ret = NULL;
	unsigned int i = 0;
	
	for (i = 0; i < pg->arc_cnt; ++i){
		
		if ((dij_array[i].ver1 == idx || dij_array[i].ver2 == idx) && dij_array[i].status == 1){
			
			if (NULL == p_ret){
				
				p_ret = &dij_array[i];
			}else{
				
				if (p_ret->weight > dij_array[i].weight){
					
					p_ret = &dij_array[i];
				}
			}
		}
	}
	
	assert(NULL != p_ret);
	
	return p_ret;
}

/**
 *\brief ���dijkstra��������ս��
 *\param[in] pg ͼ�ľ��
 *\param[in] dij_array ����ĸ�������
 *\param[in] idx ��ʼ�� 
 */
static void print_dijkstra_result(adj_graph_st *pg, dij_ver_st *dij_array, unsigned int idx)
{
	unsigned int i = 0;
	
	for (i = 0; i < pg->ver_cnt; ++i){
		
		printf("%u - %u(%u)\n", idx, i, dij_array[i].weight);
	}	
}

/**
 *\brief �������·��
 *\param[in] pg ͼ�ľ��
 *\param[in] sidx ��ʼ�����Ķ���
 */
static void dijkstra_graph(adj_graph_st *pg, unsigned int sidx)
{
	dij_ver_st *dij_ver_ary = NULL;
	dij_arc_st *dij_arc_ary = NULL;
	arc_st *p_tmparc = NULL;	
	unsigned int i = 0, j = 0;
	
	assert(NULL != pg);
	assert(sidx < pg->ver_cnt);
	
	// ��ʼ����������
	dij_arc_ary = (dij_arc_st *)malloc(sizeof(dij_arc_st) * pg->arc_cnt);
	assert(NULL != dij_arc_ary);
	for (i = 0; i < pg->ver_cnt; ++i){
		
		p_tmparc = pg->ver_list[i].p_arc;
		while (NULL != p_tmparc){

			if (i < p_tmparc->index){
				
				dij_arc_ary[j].ver1 = i;
				dij_arc_ary[j].ver2 = p_tmparc->index;
				dij_arc_ary[j].weight = p_tmparc->weight;
				dij_arc_ary[j].status = 0;
				++j;
			}
			
			p_tmparc = p_tmparc->p_next;			
		}
	}// ������ʵ���Բ��ö����� ���ٺ���Ĳ��ҹ���
	
	dij_ver_ary = (dij_ver_st *)malloc(sizeof(dij_ver_st) * pg->ver_cnt);
	assert(NULL != dij_ver_ary);
	for (i = 0; i < pg->ver_cnt; ++i){
		
		dij_ver_ary[i].weight = DIJ_MAX_WEIGHT;
		dij_ver_ary[i].isfinal = 0;
	}
	
	dij_ver_ary[sidx].weight = 0;
	dij_ver_ary[sidx].isfinal = 1;
	adjust_arc_status(pg, dij_arc_ary, sidx);
	
	for (i = 1; i < pg->ver_cnt; ++i){

		// ��������ľ���
		p_tmparc = pg->ver_list[sidx].p_arc;
		while (NULL != p_tmparc){
			
			if (dij_ver_ary[p_tmparc->index].weight > dij_ver_ary[sidx].weight + p_tmparc->weight){
				
				dij_ver_ary[p_tmparc->index].weight = dij_ver_ary[sidx].weight + p_tmparc->weight;
			}
			
			p_tmparc = p_tmparc->p_next;
		}

		// ���Һ�S�������ӵ���С��
		dij_arc_st *dij_arc = NULL;
		dij_arc = search_min_arc(pg, dij_arc_ary, sidx);
		
		if (!dij_ver_ary[dij_arc->ver1].isfinal){
			
			sidx = dij_arc->ver1;
			dij_ver_ary[dij_arc->ver1].isfinal = 1;
		}else{
		
			sidx = dij_arc->ver2;
			dij_ver_ary[dij_arc->ver2].isfinal = 1;
		}
		adjust_arc_status(pg, dij_arc_ary, sidx);		
	}
	
	// ������еľ�����Ϣ
	print_dijkstra_result(pg, dij_ver_ary, 0);
}

int main(void)
{
	adj_graph_st graph;
	
	creat_graph(&graph);
	
	print_graph(&graph);
	
	dijkstra_graph(&graph, 0);
	
	destroy_graph(&graph);
	
	return 0;
}

