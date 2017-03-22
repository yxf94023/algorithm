/******************************************************************************
 *\file queue_list.cc
 *\brief 队列的实现
 *\date 2017/03/16
 *****************************************************************************/

#include "queue_list.h"
#include <stdlib.h>
#include <errno.h>

#define	RET_SUCCESS		(1)		///< 成功状态
#define	RET_FAILED		(0)		///< 失败状态


int queue_init(queue_st *p_que)
{
	if (NULL == p_que){
		
		printf("param error can not equal NULL!\n");
		return RET_FAILED;
	}
	
	p_que->p_front = p_que->p_rear = NULL;

	return RET_SUCCESS;
}

int queue_enter(queue_st *p_que, void* pinfo)
{
	qnode_st *tmp_pnode = NULL;
	
	if (NULL == p_que){
		
		printf("param error can not equal NULL!\n");
		return RET_FAILED;
	}
	
	tmp_pnode = (qnode_st *)malloc(sizeof(qnode_st));
	if (NULL == tmp_pnode){
		
		printf("call malloc failed, error[%d]", errno);
		return RET_FAILED;		
	}
	tmp_pnode->p_next = NULL;
	tmp_pnode->p_info = pinfo;
	
	// 将信息压到队尾
	if (queue_empty(p_que)){
		
		p_que->p_front = p_que->p_rear = tmp_pnode;
	}else{
		
		p_que->p_rear->p_next = tmp_pnode;
		p_que->p_rear = tmp_pnode;
	}
	
	return RET_SUCCESS;
}

int queue_outer(queue_st *p_que, void **pinfo)
{
	qnode_st *tmp_pnode = NULL;
	
	if (queue_empty(p_que)){
		
		printf("queue is empty!\n");
		return RET_FAILED;
	}
	
	// 获取信息
	tmp_pnode = p_que->p_front;
	*pinfo = tmp_pnode->p_info;
	
	if (p_que->p_front == p_que->p_rear){// 将要出队的节点是最后一个， 需要同时调整对头 和 对尾
		
		p_que->p_front = p_que->p_rear = NULL;
	}else{
		
		p_que->p_front = p_que->p_front->p_next;
	}
	
	// 释放空间， 防止内存泄漏
	free(tmp_pnode);
	tmp_pnode = NULL;
	
	return RET_SUCCESS;
}

int queue_empty(queue_st *p_que)
{
	if (NULL == p_que || (NULL == p_que->p_front && NULL == p_que->p_rear)){
		
		return 1;
	}
	
	return 0;
}