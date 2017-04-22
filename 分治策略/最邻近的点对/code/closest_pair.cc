/******************************************************************************
 *\file closest_pair.cc
 *\brief ��άƽ�����������n������ �ҳ��ڽ�������С�ĵ��
 *\date 2017/04/21
 *****************************************************************************/

#include "closest_pair.h"
#include "merge_sort.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

static ptables_st x_ptables[MAX_POINTS];	// x�������б�
static ptables_st y_ptables[MAX_POINTS];	// y�������б�
static unsigned int s_spnum;
static ptables_st s_ptables[MAX_POINTS];	// �봹ֱ������ض��������б�

/**
 *\brief �鲢������ ����merge_array�ĳ�ʼֵ
 *\param[in] len ����ʼ�������ݹ�ģ
 *\param[in] disoder_ary �ȴ����������
 *\param[in] merge_ary ��ʼ���Ķ���
 *\retval 1 ��ʼ���ɹ�
 *\retval 0 ��ʼ��ʧ��
 */
int set_fun(unsigned int len, void *disoder_ary, void **merge_ary)
{
    unsigned int i = 0;
    ptables_st *ary1 = NULL, **ary2 = NULL;
    
    assert((void**)0 != disoder_ary);
    assert((void**)0 != merge_ary);
    
    ary1 = (ptables_st *)disoder_ary;
    ary2 = (ptables_st **)merge_ary;
    
    for (i = 0; i < len; ++i){
        
        ary2[i] = &ary1[i];
    }
    
    return 1;
}

/**
 *\brief �鲢������ ����Ԫ�ضԱȺ���
 *\param[in] cmp1 �Ա�Ԫ��1
 *\param[in] cmp2 �Ա�Ԫ��2
 *\retval 1 cmp1 > cmp2
 *\retval 0 cmp1 = cmp2
 *\retval -1 cmp1 < cmp2
 */
int cmp_fun(void *cmp1, void *cmp2)
{
    int *int_cmp1 = NULL;
    int *int_cmp2 = NULL;

    assert(NULL != cmp1);
    assert(NULL != cmp2);
    
    int_cmp1 = (ptables_st*)cmp1;
    int_cmp2 = (ptables_st*)cmp2;
    if (int_cmp1->xy > int_cmp2->xy){
        
        return 1;
    }else if (int_cmp1->xy == int_cmp2->xy){
        
        return 0;
    }
    
    return -1;
}

/**
 *\brief �鲢������ ��ֵ����
 *\param[in] lopr ����ֵ�� �Ⱥ� ��ߵ���
 *\param[in] ropr ��ֵ�� �Ⱥ� �ұߵ���
 *\retval 1 ��ֵ�ɹ�
 *\retval 0 ��ֵʧ�� 
 */
int agn_fun(void **lopr, void *ropr)
{
    ptables_st **int_lopr = NULL;
    ptables_st *int_ropr = NULL;
    
    assert((void**)0 != lopr);
    assert(NULL != ropr);
    
    int_lopr = (ptables_st **)lopr;
    int_ropr = (ptables_st *)ropr;
    *int_lopr = int_ropr;
    
    return 1;
}

/**
 *\brief �鲢������ ��ȡ������
 *\param[in] len ��ȡ��������ݹ�ģ 
 *\param[in,out] res_ary �ȴ����������
 *\param[in] merge_ary �鲢�����Ľ��
 *\retval 1 ��ȡ����ɹ�
 *\retval 0 ��ȡ���ʧ��
 */
int get_res_fun(unsigned int len, void *res_ary, void **merge_ary)
{
    ptables_st *buf = NULL, **ary = (int**)0, *res = NULL;
    unsigned int i = 0;
    
    assert(0 <= len);
    assert(NULL != res_ary);
    assert((void**)0 != merge_ary);
    
    buf = (ptables_st*) malloc (len * sizeof(ptables_st)); // ������Ҫ���ٿռ� merge_ary��ָ����ڴ��ַ����res_ary��Ԫ�ص�ַ
    if (NULL == buf){
        
        printf("malloc failed, errno(%d)\n", errno);
        return 0;
    }
    ary = (ptables_st **)merge_ary;
    res = (ptables_st *)res_ary;
    
    for (i = 0; i < len; ++i){
        
        memcpy(&buf[i], ary[i], sizeof(ptables_st));    // ȡָ��ָ�������
    }
    
    memcpy(res, buf, len * sizeof(ptables_st));
    
	free(buf);
	buf = NULL;

    return 1;
}
	
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
	__do_closest_pair(plist, pnum, beg, num/2, &l_pair);
	__do_closest_pair(plist, pnum, beg + num/2, num - num/2, &r_pair);
	if (l_pair.d < r_pair.d){
		
		memcpy(&min_pair, &l_pair, sizeof(closest_pair_st));
	}else{
		
		memcpy(&min_pair, &r_pair, sizeof(closest_pair_st));
	}
	
	// ��������һ���������� һ�������Ұ�ߵ������ ͳ�������봹ֱֱ�� x = plist[beg + num/2].x ��� min_pair.d �ľ���ĵ�
	for (i = 0, s_spnum = 0; i < pnum ; ++i){
		
		double dis = fabs(plist[beg + num/2].x - plist[y_ptables[i].idx].x);
		if (min_pair.d > dis){
			
			s_ptables[s_spnum].idx = y_ptables[i].idx;
			s_ptables[s_spnum].xy = y_ptables[i].xy;
			++s_spnum;
		}
	}
	
	if (s_spnum < 2){
	
		memcpy(pair, &min_pair, sizeof(closest_pair_st));
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
		
		memcpy(pair, &min_pair, sizeof(closest_pair_st));
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
	
	
	assert(NULL != plist);
	assert(NULL != pair);
	assert(MAX_POINTS >= pnum);
	
	// 1. ��plist�ĵ� ����x�� �� y�����򣨹鲢���� �õ����ű�
	for (i = 0; i < pnum; ++i){
		
		x_ptables[i].xy = plist[i].x;
		y_ptables[i].xy = plist[i].y;
		x_ptables[i].idx = i;
		y_ptables[i].idx = i;
	}
	// ���ù鲢����
    merge_init(pnum, (void *)x_ptables, set_fun, cmp_fun, agn_fun);
    merge_sort(pnum, (void *)x_ptables, get_res_fun);
    merge_destory();
    merge_init(pnum, (void *)y_ptables, set_fun, cmp_fun, agn_fun);
    merge_sort(pnum, (void *)y_ptables, get_res_fun);
    merge_destory();	
		
	// 2.������С�ٽ����
	__do_closest_pair(plist, pnum, 0, pnum, pair);
	
	return 0;
}


