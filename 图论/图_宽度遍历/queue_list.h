/******************************************************************************
 *\file queue_list.h
 *\brief 队列操作相关的结构和方法
 *\date 2017/03/16
 *****************************************************************************/

#ifndef __QUEUE_LIST_H_2017_03_16__
#define	__QUEUE_LIST_H_2017_03_16__

#include <stdio.h>


/** 
 *\brief 队列中的结点信息
 *
 *		- 含有两个成员
 *			+ 指向压栈的信息指针(外部空间)
 *			+ 指向下一个队列结点的指针
 */
typedef struct qnode_st{
	
	void				*p_info;	///< 结点中包含的信息
	struct qnode_st		*p_next;	///< 指向后继结点
}qnode_st;

/**
 *\brief 队列结构
 *
 *		含有对头 和 队尾两个成员变量
 */
typedef struct queue_st{
	
	qnode_st	*p_front;	///< 队头
	qnode_st	*p_rear;	///< 队尾
}queue_st;

/**
 *\brief 队列初始化
 *\param [in,out] p_que 待初始化的队列句柄
 *\warning 传入参数p_que不能为NULL 
 *\retval 1 成功
 *\retval 0 失败
 */
int queue_init(queue_st *p_que);

/**
 *\brief 进队列操作
 *\param[in,out] p_que 队列句柄
 *\param[in] pinfo 待入栈的信息
 *\warning 传入参数p_que不能为NULL 
 *\retval 1 成功
 *\retval 0 失败
 */
int queue_enter(queue_st *p_que, void *pinfo);

/**
 *\brief 出队列操作
 *\param[in,out] p_que 队列句柄
 *\param[out] pinfo 获取出队信息
 *\warning 传入参数p_que不能为NULL  
 *\retval 1 成功
 *\retval 0 失败
 */
int queue_outer(queue_st *p_que, void **pinfo);

/**
 *\brief 队列空的判断
 *\param[in] p_que 队列句柄
 *\warning 传入参数p_que不能为NULL  
 *\retval 1 队列为空
 *\retval 0 队列不为空
 */
int queue_empty(queue_st *p_que);

#endif// __QUEUE_LIST_H_2017_03_16__
