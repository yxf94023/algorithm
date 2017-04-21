/******************************************************************************
 *\file closest_pair.cc
 *\brief ��άƽ�����������n������ �ҳ��ڽ�������С�ĵ��
 *\date 2017/04/21
 *****************************************************************************/

#include "closest_pair.h"
#include <assert.h>
#include <math.h>


static int __do_closest_pair(point_st *plist, unsigned int beg, unsigned int num, closest_pair_st *pair)
{
	closest_pair_st l_pair, r_pair, min_pair;
	
	if (num <= 3){
		
		// ֱ�Ӽ��������ľ���
		
		return 1;
	}
	
	// ��ֳ�[1, pnum/2] �� [pnum/2 + 1, pnum]
	__do_closest_pair(beg, pnum/2, &l_pair);
	__do_closest_pair(beg + pnum/2, pnum - pnum/2, &r_pair);
	if (l_pair.d < r_pair.d){
		
		memset(&min_pair, &l_pair, sizeof(closest_pair_st));
	}else{
		
		memset(&min_pair, &r_pair, sizeof(closest_pair_st));
	}
	
	// ��������һ���������� һ�������Ұ�ߵ����
	
	
	
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
	ptables_st x_ptables[MAX_POINTS];	// x�������б�
	ptables_st y_ptables[MAX_POINTS];	// y�������б�
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
	__do_closest_pair(plist, 0, pnum, pair);
	
	return 0;
}


