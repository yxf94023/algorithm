/******************************************************************************
 *\file graph_prim.cc
 *\brief ͼ����С������
 *		Prim�㷨
 *		ͼ ���� �ڽӱ�Adjacency list�� ��ʽ�洢
 *\date 2017/04/03
 *****************************************************************************/

#include "graph_prim.h"
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
 *\param[in] prim_array �ߵĸ�������
 *\param[in] idx�ռ���S���Ķ����±�
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
 *\brief �ҵ��� S���� ������������̱�
 *\param[in] pg ͼ�ľ��
 *\param[in] prim_array �ߵĸ�������
 *\retval ������̱ߵĵ�ַ
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
 *\brief ���dijkstra��������ս��
 *\param[in] pg ͼ�ľ��
 *\param[in] prim_array ����ĸ�������
 */
static void print_prim_result(adj_graph_st *pg, prim_ver_st *prim_array)
{
	unsigned int i = 0, j = 0;
	unsigned int total = 0;
	
	printf("\nresult: \n");
	
	// �Խ������ ������С���������Ⱥ�˳������
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
 *\brief �������·��
 *\param[in] pg ͼ�ľ��
 *\param[in] sidx ��ʼ�����Ķ���
 */
static void prim_graph(adj_graph_st *pg, unsigned int sidx)
{
	prim_ver_st *prim_ver_ary = NULL;
	prim_arc_st *prim_arc_ary = NULL;
	arc_st *p_tmparc = NULL;	
	unsigned int i = 0, j = 0, index = 1;
	
	assert(NULL != pg);
	assert(sidx < pg->ver_cnt);
	
	// ��ʼ����������
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
	}// ������ʵ���Բ��ö����� ���ٺ���Ĳ��ҹ���
	
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

		// ���Һ�S�������ӵ���С��
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
	
	// ������еľ�����Ϣ
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

