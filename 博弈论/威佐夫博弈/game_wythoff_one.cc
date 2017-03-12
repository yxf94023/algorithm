/*******************************************************************************
 *\file game_wythoff_one.cc
 *\brief 威佐夫博弈  判断输入是否为奇异局势
 *\data 2017/03/12
 ******************************************************************************/
 
#include <stdio.h>

int main(void){
	
	unsigned int a = 0, b = 0;
	
	while (2 == scanf("%u %u", &a, &b)){
		
		unsigned int tmp = (b - a) * 1.618;
		
		if (tmp == a){
			
			printf("后手胜!\n");
		}else{
			
			printf("先手胜!\n");
		}
	}
	
	return 0;
}