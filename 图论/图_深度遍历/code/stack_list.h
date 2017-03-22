/******************************************************************************
 *\file stack_list.h
 *\brief ջ �ṹ��Ϣ �� ������صĽӿ�
 *\date 2017/03/22
 *****************************************************************************/

#ifndef	__STACK_LIST_H_2017_03_22__
#define __STACK_LIST_H_2017_03_22__

/**
 *\brief ״̬��Ϣ
 */
enum{
	
	STACK_RET_FAILED = 0,	///< ����ʧ��״̬
	STACK_RET_SUCCESS = 1,	///< ���سɹ�״̬
	STACK_IS_NOEMPTY = 0,	///< ջ��Ϊ��
	STACK_IS_EMPTY = 1,		///< ջΪ��
};

/**
 *\brief ջ �е� �����Ϣ
 *
 *	- ����������Ա����
 *		+ ָ�� ѹջ����Ϣ ��ָ��
 *		+ ָ��ջ����һ������ָ��
 */
typedef struct stack_node_st{
	
	void					*p_info;	///< ָ�� ѹջ����Ϣ ��ָ��
	struct stack_node_st	*p_next;	///< ָ��ջ����һ������ָ��
}stack_node_st;

/**
 *\brief ջ �ṹ��Ϣ
 */
typedef struct stack_st{
	
	stack_node_st		*p_top;		///< ջ��
	stack_node_st		*p_base;	///< ջ��
}stack_st;

/**
 *\brief ջ ��ʼ��
 *\param[in,out] p_stk ջ�ľ��
 *\retval STACK_RET_SUCCESS ��ʼ���ɹ�
 *\retval STACK_RET_FAILED ��ʼ��ʧ��
 */
int stack_init(stack_st *p_stk);

/**
 *\brief ջ �Ľ�ջ����
 *\param[in,out] p_stk ջ�ľ��
 *\param[in] pinfo ����ջ����Ϣ
 *\retval STACK_RET_SUCCESS ��ջ�ɹ�
 *\retval STACK_RET_FAILED ��ջʧ��
 */
int stack_push(stack_st *p_stk, void *pinfo);

/**
 *\brief ջ �ĳ�ջ����
 *\param[in,out] p_stk ջ�ľ��
 *\param[out] pinfo �����صĳ�ջ��Ϣ
 *\retval STACK_RET_SUCCESS ��ջ�ɹ�
 *\retval STACK_RET_FAILED ��ջʧ��
 */
int stack_pop(stack_st *p_stk, void **pinfo);

/**
 *\brief ջ ��ȡջ����Ϣ������ջ��
 *\param[in] p_stk ջ�ľ��
 *\param[out] pinfo ������ջ����Ϣ
 *\retval STACK_RET_SUCCESS ��ȡջ���ɹ�
 *\retval STACK_RET_FAILED ��ȡջ��ʧ��
 */
int stack_get_top(stack_st *p_stk, void **pinfo);

/**
 *\brief ջ ��ջ���ж�
 *\param[in] p_stk ջ�ľ��
 *\retval STACK_IS_EMPTY ջ��
 *\retval STACK_IS_NOEMPTY �ǿ�
 */
int stack_empty(stack_st *p_stk);

#endif//__STACK_LIST_H_2017_03_22__
