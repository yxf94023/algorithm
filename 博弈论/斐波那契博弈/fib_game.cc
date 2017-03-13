/******************************************************************************
 *\file fib_game.cc
 *\brief 斐波那契博弈
 *		有一堆个数为 n 的石子， 游戏双方轮流取石子， 满足：
 *		（1）先手不能在第一次把所有的石子取完；
 *		（2）之后每次可以取的石子数介于1到对手刚取的石子数的两倍之间（闭区间）；
 *		（3）约定取走最后一个石子的人为赢家。
 *\date 2017/03/13
 *****************************************************************************/
 
#include <stdio.h>

/**
 *\fn
 *\brief 判断参数是不是斐波那契数列中的数字
 *\param[in] n待判定的数字
 *\retval 0 不是斐波那契数列中的数字
 *\retval 1 是斐波那契数列中的数字
 */
static unsigned int is_fib_list(unsigned int n){
	
	unsigned int i = 1, j = 1, tmp = 0;
	
	for (;;){
		
		i += j;
		if (i == n){
			
			return 1;
		}
		
		if (i > n){
			
			return 0;
		}
		
		tmp = j;
		j = i;
		i = tmp;
	}
}

int main(void)
{
	unsigned int n = 0;
	
	while (scanf("%u", &n)){
		
		if (is_fib_list(n)){	///< 判断是否为 斐波那契 数列， 如果是 则 先手败
			
			printf("后手胜！\n");
		}else{
			
			printf("先手胜！\n");
		}
	}

	return 0;
}
 