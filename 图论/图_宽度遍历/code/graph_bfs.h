/******************************************************************************
 *\file graph_bfs.h
 *\brief ����ͼ��صĽṹ��
 *\date 2017/03/20
 *****************************************************************************/
#ifndef __GRAPH_BFS_H_2017_03_20__
#define	__GRAPH_BFS_H_2017_03_20__


#define VER_CHAR_SIZE	(10)	///< �����ַ�������

typedef char ver_type[VER_CHAR_SIZE];	///< ����ڵ�����

/**
 *\brief ͼ�� �����ߣ��Ľṹ
 *
 *	-������Ա���� �ֱ���
 *		+ ͼ���� �ڶ��������е��±�ֵ��ֵ�Ǵ�0�±꿪ʼ��
 *		+ ָ����һ�������ߣ���ָ��
 */
typedef struct arc_st{
	
	unsigned int	index;		///< ������±�ֵ
	struct arc_st	*p_next;	///< ָ����һ����
}arc_st;

/**
 *\brief ͼ�� ���� �Ľṹ
 *
 *	-�����ڽӱ�ķ�ʽ�洢������������Ա����
 *		+ ���������
 *		+ ָ����һ�������ߣ���ָ��
 */
typedef struct ver_st{
	
	ver_type	ver_name;	///< ��������
	arc_st		*p_arc;		///< �����ߣ�
}ver_st;

/**
 *\brief ͼ�Ľṹ
 */
typedef struct adj_graph_st{
	
	unsigned int	arc_cnt;	///< ͼ�� �ߵ�����
	unsigned int	ver_cnt;	///< ͼ�� ��������
	
	ver_st			*ver_list;	///< ���� �б�   ��̬����
}adj_graph_st;

#endif//__GRAPH_BFS_H_2017_03_20__