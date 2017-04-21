/******************************************************************************
 *\file closest_pair.cc
 *\brief ��άƽ�����������n������ �ҳ��ڽ�������С�ĵ��
 *\date 2017/04/21
 *****************************************************************************/

#include "closest_pair.h"
#include <assert.h>
#include <math.h>

static ptables_st x_ptables[MAX_POINTS];	// x�������б�
static ptables_st y_ptables[MAX_POINTS];	// y�������б�
static unsigned int s_spnum;
static ptables_st s_ptables[MAX_POINTS];	// �봹ֱ������ض��������б�
	
/**
 *\brief ��ȡ�����ľ���
 *\brief[in] plist ����б�
 *\param[in] i ��һ�����ڵ���б����±�ֵ
 *\param[in] j �ڶ������ڵ���б����±�ֵ
 *\retval 2���ľ���ֵ
 */
static double __get_2points_dist(point_st *plist, unsigned int i, unsigned int j)
{
    double x, y;
    
    x = pow(plist[i].x - plist[j].x, 2.0);
    y = pow(plist[i].y - plist[j].y, 2.0);
    
    return sqrt(x + y);
}

/**
 *\brief �ݹ鴦�������֧
 *\param[in] plist ������е��б�
 *\param[in] pnum plist�б��е������
 *\param[in] beg ����������ʼ�±�
 *\param[in] num ������������ ��beg�±꿪ʼ����
 *\param[out] pair ����ڽ��ĵ��
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
static int __do_closest_pair(point_st *plist, 
							 unsigned int pnum,
							 unsigned int beg, 
							 unsigned int num, 
							 closest_pair_st *pair)
{
	unsigned int i = 0, j = 0;
	closest_pair_st l_pair, r_pair, min_pair;
	
	if (num <= 3){
		
		pair->p1.x = plist[beg].x;
		pair->p1.y = plist[beg].y;
		pair->p2.x = plist[beg+1].x;
		pair->p2.y = plist[beg+1].y;
		pair->d = __get_2points_dist(plist, beg, beg + 1);
		
		// ֱ�Ӽ��������ľ���
		for (i = 0; i < num; ++i){
			
			for (j = i + 1; j < num; ++j){
				
				if (pair->d > __get_2points_dist(plist, beg + i, beg + j)){
					
					pair->p1.x = plist[beg+i].x;
					pair->p1.y = plist[beg+i].y;
					pair->p2.x = plist[beg+j].x;
					pair->p2.y = plist[beg+j].y;
					pair->d = __get_2points_dist(plist, beg + i, beg + j);					
				}
			}
		}
		
		return 1;
	}
	
	// ��ֳ�[1, num/2] �� [num/2 + 1, num]
	__do_closest_pair(plist, beg, num/2, &l_pair);
	__do_closest_pair(plist, beg + num/2, num - num/2, &r_pair);
	if (l_pair.d < r_pair.d){
		
		memset(&min_pair, &l_pair, sizeof(closest_pair_st));
	}else{
		
		memset(&min_pair, &r_pair, sizeof(closest_pair_st));
	}
	
	// ��������һ���������� һ�������Ұ�ߵ������ ͳ�������봹ֱֱ�� x = plist[beg + num/2].x ��� min_pair.d �ľ���ĵ�
	for (i = 0, s_spnum = 0; i < pnum ; ++i){
		
		double dis = fabs(plist[beg + num/2].x - plist[y_ptables[i].idx].x);
		if (min_pair.d > dis){
			
			s_ptables[s_spnum].idx = y_ptables[i].idx;
			s_ptables[s_spnum].xy = y_ptablse[i].xy;
			++s_spnum;
		}
	}
	
	if (s_spnum < 2){
	
		memset(pair, &min_pair, sizeof(closest_pair_st));
		return 1;
	}
	
	pair->p1.x = plist[s_ptables[0].idx].x;
	pair->p1.y = plist[s_ptables[0].idx].y;
	pair->p2.x = plist[s_ptables[1].idx].x;
	pair->p2.y = plist[s_ptables[1].idx].y;
	pair->d = __get_2points_dist(plist, s_ptables[0].idx, s_ptables[1].idx);
	for (i = 0; i < s_spnum; ++i){
		
		for (j = i+1; j <= i + 8 && j < s_spnum; ++j){
			
			if (pair->d > __get_2points_dist(plist, s_ptables[i].idx, s_ptables[j].idx)){
				
				pair->p1.x = plist[s_ptables[i].idx].x;
				pair->p1.y = plist[s_ptables[i].idx].y;
				pair->p2.x = plist[s_ptables[j].idx].x;
				pair->p2.y = plist[s_ptables[j].idx].y;
				pair->d = __get_2points_dist(plist, s_ptables[i].idx, s_ptables[j].idx);				
			}		
		}
	}
	
	if (min_pair.d < pair->d){
		
		memset(pair, &min_pair, sizeof(closest_pair_st));
	}
	
	return 1;
}

/**
 *\brief ��ȡ���ڽ��ĵ��
 *\param[in] plist ������ĵ���Ϣ
 *\param[in] pnum ������ĵ�����
 *\param[out] pair ��ȡ�õ��Ľ��
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int get_closest_pair(point_st *plist, unsigned int pnum, closest_pair_st *pair)
{
	unsigned int i = 0;
	
	
	assert(NULL != plist)
	assert(NULL != pair)
	assert(MAX_POINTS >= pnum);
	
	// 1. ��plist�ĵ� ����x�� �� y�����򣨹鲢���� �õ����ű�
	for (i = 0; i < pnum; ++i){
		
		x_ptables[i].xy = plist[i].x;
		y_ptables[i].xy = plist[i].y;
		x_ptables[i].idx = i;
		y_ptables[i].idx = i;
	}
	// ���ù鲢����
	
	// 2.������С�ٽ����
	__do_closest_pair(plist, pnum, 0, pnum, pair);
	
	return 0;
}


