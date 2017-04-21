/******************************************************************************
 *\file closest_pair.h
 *\brief ��άƽ�����������n������ �ҳ��ڽ�������С�ĵ��
 *\date 2017/04/21
 *****************************************************************************/
#ifndef __CLOSEST_PAIR_H_2017_04_21__
#define	__CLOSEST_PAIR_H_2017_04_21__

#ifdef __cplusplus
extern "C"{
#endif


#define MAX_POINTS	(100)	///< ���֧�ֵĵ������

/**
 *\brief ��ά�����Ľṹ
 */
typedef struct point_st{
	
	double	x;	///< ����x
	double  y;	///< ����y
}point_st;

/**
 *\brief �ڽ���Խṹ
 */
typedef struct closest_pair_st{
	
	point_st p1;	///< ��һ����
	point_st p2;	///< �ڶ�����
	double 	 d;		///< �����ľ���
}closest_pair_st;

/**
 *\brief ��ı�ṹ������x��y���������ʱʹ��
 */
typedef struct ptables_st{
	
	unsigned int	idx;	///< ���ڵ�ļ�����λ��
	double			xy;		///< x�� �� y�������
}ptables_st;

/**
 *\brief ��ȡ���ڽ��ĵ��
 *\param[in] plist ������ĵ���Ϣ
 *\param[in] pnum ������ĵ�����
 *\param[out] pair ��ȡ�õ��Ľ��
 *\retval 1 �ɹ�
 *\retval 0 ʧ��
 */
int get_closest_pair(point_st *plist, unsigned int pnum, closest_pair_st *pair);

#ifdef __cplusplus
}
#endif

#endif//__CLOSEST_PAIR_H_2017_04_21__