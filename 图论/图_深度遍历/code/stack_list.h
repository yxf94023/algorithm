/******************************************************************************
 *\file stack_list.h
 *\brief 栈 结构信息 和 操作相关的接口
 *\date 2017/03/22
 *****************************************************************************/

#ifndef	__STACK_LIST_H_2017_03_22__
#define __STACK_LIST_H_2017_03_22__

/**
 *\brief 状态信息
 */
enum{
	
	STACK_RET_FAILED = 0,	///< 返回失败状态
	STACK_RET_SUCCESS = 1,	///< 返回成功状态
	STACK_IS_NOEMPTY = 0,	///< 栈不为空
	STACK_IS_EMPTY = 1,		///< 栈为空
};

/**
 *\brief 栈 中的 结点信息
 *
 *	- 包含两个成员变量
 *		+ 指向 压栈的信息 的指针
 *		+ 指向栈中下一个结点的指针
 */
typedef struct stack_node_st{
	
	void					*p_info;	///< 指向 压栈的信息 的指针
	struct stack_node_st	*p_next;	///< 指向栈中下一个结点的指针
}stack_node_st;

/**
 *\brief 栈 结构信息
 */
typedef struct stack_st{
	
	stack_node_st		*p_top;		///< 栈顶
	stack_node_st		*p_base;	///< 栈底
}stack_st;

/**
 *\brief 栈 初始化
 *\param[in,out] p_stk 栈的句柄
 *\retval STACK_RET_SUCCESS 初始化成功
 *\retval STACK_RET_FAILED 初始化失败
 */
int stack_init(stack_st *p_stk);

/**
 *\brief 栈 的进栈操作
 *\param[in,out] p_stk 栈的句柄
 *\param[in] pinfo 待入栈的信息
 *\retval STACK_RET_SUCCESS 进栈成功
 *\retval STACK_RET_FAILED 进栈失败
 */
int stack_push(stack_st *p_stk, void *pinfo);

/**
 *\brief 栈 的出栈操作
 *\param[in,out] p_stk 栈的句柄
 *\param[out] pinfo 待返回的出栈信息
 *\retval STACK_RET_SUCCESS 出栈成功
 *\retval STACK_RET_FAILED 出栈失败
 */
int stack_pop(stack_st *p_stk, void **pinfo);

/**
 *\brief 栈 获取栈顶信息（不出栈）
 *\param[in] p_stk 栈的句柄
 *\param[out] pinfo 待返回栈顶信息
 *\retval STACK_RET_SUCCESS 获取栈顶成功
 *\retval STACK_RET_FAILED 获取栈顶失败
 */
int stack_get_top(stack_st *p_stk, void **pinfo);

/**
 *\brief 栈 的栈空判断
 *\param[in] p_stk 栈的句柄
 *\retval STACK_IS_EMPTY 栈空
 *\retval STACK_IS_NOEMPTY 非空
 */
int stack_empty(stack_st *p_stk);

#endif//__STACK_LIST_H_2017_03_22__
