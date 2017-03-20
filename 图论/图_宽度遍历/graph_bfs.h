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
 *\struct
 *\brief �����ߣ��Ľṹ
 */
typedef struct arc_st{
	
	unsigned int	index;		///< �����±�ֵ
	struct arc_st	*p_next;	///< ָ����һ����
}arc_st;

/**
 *\struct
 *\brief ��� �Ľṹ
 */
typedef struct ver_st{
	
	ver_type	ver_name;	///< �������
	arc_st		*p_arc;		///< ��
}ver_st;

/**
 *\struct
 *\brief ͼ�Ľṹ
 */
typedef struct adj_graph_st{
	
	unsigned int	arc_cnt;	///< ͼ�� �ߵ�����
	unsigned int	ver_cnt;	///< ͼ�� ��������
	
	ver_st			*ver_list;	///< ��� �б�   ��̬����
}adj_graph_st;

#endif//__GRAPH_BFS_H_2017_03_20__