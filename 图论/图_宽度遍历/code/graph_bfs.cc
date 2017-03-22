/******************************************************************************
 *\file graph_bfs.cc
 *\brief ͼ�Ŀ������
 *		ͼ ���� �ڽӱ�Adjacency list�� ��ʽ�洢
 *\date 2017/03/16
 *****************************************************************************/

#include "queue_list.h"
#include "graph_bfs.h"
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


#define	RET_SUCCESS		(1)		///< �ɹ�״̬
#define	RET_FAILED		(0)		///< ʧ��״̬


/**
 *\fn
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
 *\fn
 *\brief ��ͼ�� ����ߵ���Ϣ
 *\param[in/out] pg ͼ�ľ��
 *\param[in] s_pos �ߵ���ʼ��
 *\param[in] e_pos �ߵ���ֹ��
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
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
	p_tmparc->p_next = NULL;

	exchg_tmp = pg->ver_list[e_pos].p_arc;
	pg->ver_list[e_pos].p_arc = p_tmparc;
	p_tmparc->p_next = exchg_tmp;

	return RET_SUCCESS;	
}

/**
 *\fn 
 *\brief ���� ͼ
 *\param[in/out] pg ͼ�ľ��
 *\retval 0 ʧ��
 *\retval 1 �ɹ�
 */
static int creat_graph(adj_graph_st *pg)
{
	unsigned int i = 0;
	ver_type start_ver, end_ver;	///< һ������ ��ʵ����ֹ���
	unsigned int start_pos = 0, end_pos = 0;	///< ��ʼ �� ��ֹ�������Ӧ���±�
	
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
	
	printf("�������Ϣ�����磺v1 - v2����\n");
	for (i = 0; i < pg->arc_cnt; ++i){
		
		scanf("%s %*s %s", start_ver, end_ver);
		
		start_pos = find_vers_idx(pg, start_ver);
		end_pos = find_vers_idx(pg, end_ver);
		
		if (!add_graph_arc(pg, start_pos, end_pos)){	///< ��ͼ�����ӱ���Ϣ
		
			return RET_FAILED;
		}
	}
	
	return RET_SUCCESS;
}

/**
 *\fn 
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
			
			printf("->%u ", p_tmparc->index);
			p_tmparc = p_tmparc->p_next;
		}
		printf("\n");
	}
}

/**
 *\fn
 *\brief ͼ�� ����
 *\param[in/out] pg ͼ�ľ��
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
 *\fn
 *\brief ִ��ͼ�Ŀ������
 *\param[in] pg ͼ�ľ��
 */
static void exec_bfs(const adj_graph_st *pg)
{
	unsigned int *express_flag = NULL;	///< ��ʶ�ڵ����������ı�־
	unsigned int i = 0;
	unsigned int cnt = 0;	///< ������ ��ͨ��֧����
	queue_st que;	///< ����
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
		queue_enter(&que, &pg->ver_list[i]);	///< ������
		++cnt;
		
		while (!queue_empty(&que)){
			
			queue_outer(&que, (void**)(&p_tmpver));	///< ������
			
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
	
	printf("��ͨ��֧��:%u\n", cnt);
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

