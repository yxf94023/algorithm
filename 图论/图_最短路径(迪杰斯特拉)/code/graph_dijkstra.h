/******************************************************************************
 *\file graph_dijkstra.h
 *\brief ����ͼ��صĽṹ��
 *\date 2017/03/22
 *****************************************************************************/
#ifndef __GRAPH_DIJKSTRA_H_2017_03_29__
#define	__GRAPH_DIJKSTRA_H_2017_03_29__


#define VER_CHAR_SIZE	(10)	///< �����ַ�������

typedef char ver_type[VER_CHAR_SIZE];	///< ����ڵ�����

/**
 *\brief ͼ�� �����ߣ��Ľṹ
 *
 *	- ������Ա���� �ֱ���
 *		+ ͼ���� �ڶ��������е��±�ֵ��ֵ�Ǵ�0�±꿪ʼ��
 *		+ ָ����һ�������ߣ���ָ��
 */
typedef struct arc_st{
	
	unsigned int	index;		///< ������±�ֵ
	unsigned int	weight;		///< Ȩ��
	struct arc_st	*p_next;	///< ָ����һ����
}arc_st;

/**
 *\brief ͼ�� ���� �Ľṹ
 *
 *	- �����ڽӱ�ķ�ʽ�洢������������Ա����
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

#define	DIJ_MAX_WEIGHT	(10000)	///< ���Ȩ�أ�Ĭ�����ò��ᳬ�����ֵ

/**
 *\brief �����ṹ�� ʵ��dijkstra�㷨
 *
 *	��¼Ȩ��
 *	��Ƕ����Ƿ��Ѿ���ǹ�
 */
typedef struct dij_ver_st{

	unsigned int 	weight;		///< ·���ܵ�Ȩ��
	unsigned int 	isfinal;	///< �Ƿ񱻱�ǹ�Ĭ��Ϊ0δ��ǣ�1��ʾ���
}dij_ver_st;

/**
 *\brief �����ṹ�� ʵ��dijkstra�㷨
 *
 *	��¼�ߣ��Ա߽�������
 */
typedef struct dij_arc_st{
	
	unsigned int	ver1;		///< ���϶���1
	unsigned int 	ver2;		///< ���϶���2
	unsigned int 	weight;		///< �ߵ�Ȩ��
	unsigned int 	status;		///< �ߵ�״̬ 0,1,2
}dij_arc_st;

#endif//__GRAPH_DIJKSTRA_H_2017_03_29__
