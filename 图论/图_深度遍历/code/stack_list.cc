/******************************************************************************
 *\file stack_list.cc
 *\brief 栈的相关操作实现
 *\date 2017/03/22
 *****************************************************************************/

#include "stack_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int stack_init(stack_st *p_stk)
{
	assert(NULL != p_stk);
	
	p_stk->p_top = p_stk->p_base = NULL;
	
	return STACK_RET_SUCCESS;
}

int stack_push(stack_st *p_stk, void *pinfo)
{
	stack_node_st *p_tmp = NULL;
	
	assert(NULL != p_stk);
	assert(NULL != pinfo);
	
	// 申请空间
	p_tmp = (stack_node_st*) malloc (sizeof(stack_node_st));
	if (NULL == p_tmp){
		
		return STACK_RET_FAILED;
	}
	memset(p_tmp, 0, sizeof(stack_node_st));
	p_tmp->p_info = pinfo;
	
	p_tmp->p_next = p_stk->p_top;
	p_stk->p_top = p_tmp;
	
	return STACK_RET_SUCCESS;
}

int stack_pop(stack_st *p_stk, void **pinfo)
{
	stack_node_st *p_tmp = NULL;
	
	assert(NULL != p_stk);
	assert(NULL != pinfo);
	
	if (stack_empty(p_stk)){
		
		return STACK_RET_FAILED;
	}
	
	p_tmp = p_stk->p_top;
	*pinfo = p_tmp->p_info;
	p_stk->p_top = p_stk->p_top->p_next;
	
	free(p_tmp);
	
	return STACK_RET_SUCCESS;
}

int stack_get_top(stack_st *p_stk, void **pinfo)
{
	assert(NULL != p_stk);
	assert(NULL != pinfo);
	
	if (stack_empty(p_stk)){
		
		return STACK_RET_FAILED;
	}
	
	*pinfo =  p_stk->p_top->p_info;
	
	return STACK_RET_SUCCESS;	
}

int stack_empty(stack_st *p_stk)
{
	if (p_stk->p_base == p_stk->p_top){
		
		return STACK_IS_EMPTY;
	}
	
	return STACK_IS_NOEMPTY;
}