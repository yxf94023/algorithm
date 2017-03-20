/******************************************************************************
 *\file queue_list.h
 *\brief 队列操作相关的结构和方法
 *\date 2017/03/16
 *****************************************************************************/

#ifndef __QUEUE_LIST_H_2017_03_16__
#define	__QUEUE_LIST_H_2017_03_16__

#include <stdio.h>


/**
 *\struct
 *\brief 队列中的节点信息
 */
typedef struct qnode_st{
	
	void				*p_info;	///< 节点中包含的信息
	struct qnode_st		*p_next;	///< 指向后继节点
}qnode_st;

/**
 *\struct
 *\brief 队列结构
 */
typedef struct queue_st{
	
	qnode_st	*p_front;	///< 队头
	qnode_st	*p_rear;	///< 队尾
}queue_st;

/**
 *\fn
 *\brief 队列的初始化
 *\param[in/out] p_que 待初始化的队列句柄
 *\retval 1 成功
 *\retval 0 失败
 */
int queue_init(queue_st *p_que);

/**
 *\fn
 *\brief 进队列
 *\param[in/out] p_que 队列句柄
 *\param[in] pinfo 待入栈的信息
 *\retval 1 成功
 *\retval 0 失败
 */
int queue_enter(queue_st *p_que, void *pinfo);

/**
 *\fn
 *\brief 出队列
 *\param[in/out] p_que 队列句柄
 *\param[out] pinfo 获取出队信息
 *\retval 1 成功
 *\retval 0 失败
 */
int queue_outer(queue_st *p_que, void **pinfo);

/**
 *\fn
 *\brief 队空判断
 *\param
 *\retval 1 队列为空
 *\retval 0 队列不为空
 */
int queue_empty(queue_st *p_que);

#endif// __QUEUE_LIST_H_2017_03_16__
