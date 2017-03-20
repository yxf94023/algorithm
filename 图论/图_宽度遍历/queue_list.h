/******************************************************************************
 *\file queue_list.h
 *\brief ���в�����صĽṹ�ͷ���
 *\date 2017/03/16
 *****************************************************************************/

#ifndef __QUEUE_LIST_H_2017_03_16__
#define	__QUEUE_LIST_H_2017_03_16__

#include <stdio.h>


/**
 *\struct
 *\brief �����еĽڵ���Ϣ
 */
typedef struct qnode_st{
	
	void				*p_info;	///< �ڵ��а�������Ϣ
	struct qnode_st		*p_next;	///< ָ���̽ڵ�
}qnode_st;

/**
 *\struct
 *\brief ���нṹ
 */
typedef struct queue_st{
	
	qnode_st	*p_front;	///< ��ͷ
	qnode_st	*p_rear;	///< ��β
}queue_st;

/**
 *\fn
 *\brief ���еĳ�ʼ��
 *\param[in/out] p_que ����ʼ���Ķ��о��
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int queue_init(queue_st *p_que);

/**
 *\fn
 *\brief ������
 *\param[in/out] p_que ���о��
 *\param[in] pinfo ����ջ����Ϣ
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int queue_enter(queue_st *p_que, void *pinfo);

/**
 *\fn
 *\brief ������
 *\param[in/out] p_que ���о��
 *\param[out] pinfo ��ȡ������Ϣ
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int queue_outer(queue_st *p_que, void **pinfo);

/**
 *\fn
 *\brief �ӿ��ж�
 *\param
 *\retval 1 ����Ϊ��
 *\retval 0 ���в�Ϊ��
 */
int queue_empty(queue_st *p_que);

#endif// __QUEUE_LIST_H_2017_03_16__
