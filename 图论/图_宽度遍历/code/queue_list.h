/******************************************************************************
 *\file queue_list.h
 *\brief ���в�����صĽṹ�ͷ���
 *\date 2017/03/16
 *****************************************************************************/

#ifndef __QUEUE_LIST_H_2017_03_16__
#define	__QUEUE_LIST_H_2017_03_16__

#include <stdio.h>


/** 
 *\brief �����еĽ����Ϣ
 *
 *		- ����������Ա
 *			+ ָ��ѹջ����Ϣָ��(�ⲿ�ռ�)
 *			+ ָ����һ�����н���ָ��
 */
typedef struct qnode_st{
	
	void				*p_info;	///< ����а�������Ϣ
	struct qnode_st		*p_next;	///< ָ���̽��
}qnode_st;

/**
 *\brief ���нṹ
 *
 *		���ж�ͷ �� ��β������Ա����
 */
typedef struct queue_st{
	
	qnode_st	*p_front;	///< ��ͷ
	qnode_st	*p_rear;	///< ��β
}queue_st;

/**
 *\brief ���г�ʼ��
 *\param [in,out] p_que ����ʼ���Ķ��о��
 *\warning �������p_que����ΪNULL 
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int queue_init(queue_st *p_que);

/**
 *\brief �����в���
 *\param[in,out] p_que ���о��
 *\param[in] pinfo ����ջ����Ϣ
 *\warning �������p_que����ΪNULL 
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int queue_enter(queue_st *p_que, void *pinfo);

/**
 *\brief �����в���
 *\param[in,out] p_que ���о��
 *\param[out] pinfo ��ȡ������Ϣ
 *\warning �������p_que����ΪNULL  
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int queue_outer(queue_st *p_que, void **pinfo);

/**
 *\brief ���пյ��ж�
 *\param[in] p_que ���о��
 *\warning �������p_que����ΪNULL  
 *\retval 1 ����Ϊ��
 *\retval 0 ���в�Ϊ��
 */
int queue_empty(queue_st *p_que);

#endif// __QUEUE_LIST_H_2017_03_16__
