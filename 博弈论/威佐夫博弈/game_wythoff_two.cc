/*******************************************************************************
 *\file game_wythoff_two.cc
 *\brief 威佐夫博弈 输出前n项的奇异局势
 *\date 2017/03/12
 *****************************************************************************/
 
#include <stdio.h>
#include <string.h>

#define MAX_NUM_LEN	(50000)

static unsigned int s_bmp[MAX_NUM_LEN];	///< 位图

int main(void){
	
	unsigned int i = 0, j = 0;
	unsigned int n = 0;
	
	while (scanf("%u", &n)){
		
		memset(s_bmp, 0, sizeof(s_bmp));	///< 初始化
		
		for (i = 1, j = 1; i+j < MAX_NUM_LEN && j < n; ++i){
			
			if (s_bmp[i] == 0){
				
				s_bmp[i] = i;
				s_bmp[i+j] = MAX_NUM_LEN;
				++j;
			}
		}
		
		for (i = 0, j = 0; i < MAX_NUM_LEN && j < n; ++i){
			
			if (s_bmp[i] == i){
				
				printf("(%u,%u)", s_bmp[i], s_bmp[i] + j);
				++j;
			}
		}
		printf("\n");
	}
	
	return 0;
}