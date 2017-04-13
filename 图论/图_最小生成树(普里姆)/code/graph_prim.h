/******************************************************************************
 *\file graph_prim.h
 *\brief ����ͼ��صĽṹ��
 *\date 2017/04/03
 *****************************************************************************/
#ifndef __GRAPH_PRIM_H_2017_04_03__
#define	__GRAPH_PRIM_H_2017_04_03__

#ifdef __cplusplus
extern "C"{
#endif

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

/**
 *\brief �����ṹ�� ʵ��prim�㷨
 *
 *	��¼ѡȡ��˳��
 *	��Ƕ����Ƿ��Ѿ���ǹ�
 */
typedef struct prim_ver_st{

	unsigned int 	index;		///< ���㱻��ǵ�˳��λ��
	unsigned int	weight;		///< ѡ�������������Ȩ�ر�
	unsigned int 	isfinal;	///< �Ƿ񱻱�ǹ�Ĭ��Ϊ0δ��ǣ�1��ʾ���
}prim_ver_st;

/**
 *\brief �����ṹ�� ʵ��prim�㷨
 *
 *	��¼�ߣ��Ա߽�������
 */
typedef struct prim_arc_st{
	
	unsigned int	ver1;		///< ���϶���1
	unsigned int 	ver2;		///< ���϶���2
	unsigned int 	weight;		///< �ߵ�Ȩ��
	unsigned int 	status;		///< �ߵ�״̬ 0,1,2
}prim_arc_st;

#ifdef __cplusplus
}
#endif

#endif//__GRAPH_PRIM_H_2017_04_03__
