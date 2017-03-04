/******************************************************************************
 *\file unweight_b_graph.cc
 *\brief 无权二部图 最大匹配问题【匈牙利算法(Hungarian algorithm)】
 *	概念：
 *		1. 匹配：一个匹配是一个边的集合，其中任意两条边都没有公共顶点。
 *		2. 最大匹配：一个图所有匹配中， 所含匹配边数最多的匹配，称为这个图的最大匹配。
 *		3. 完美匹配：一个图的某个匹配中，所有的顶点都是匹配点， 那么他就是一个完美匹配。
 *
 *	下面简单介绍下匈牙利算法
 *		1. 匈牙利算法是用来求二部图最大匹配的，核心是找增广路径，算法的时间复杂度为O(VE)\
 *			其中V为二部图左边的顶点数，E为二部图中边的数目。
 *		2. 交替路：从一个未匹配点出发，一次经过非匹配边、匹配边、非匹配边。。。形成的\
 *			路径叫交替路。
 *		3. 增广路：从一个未匹配点出发，走交替路，如果途径另一个未匹配点，则这条交替\
 *			路称为增广路。 增广路具有下面一些特征
 *				. 有奇数条边
 *				. 起点在二部图的左边，终点在二部图的右边
 *				. 路径上的点一定是一个在左边，一个在右边，交替出现
 *				. 整条路径中没有重复的点
 *				. 起点和中横店都是目前还没有配对的点，而其它所有点都是已经配对好的
 *\date 2017/03/04
 *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 	(20)	///< 支持的图最大节点数

typedef int arc_type;			///< 弧的类型
typedef char ver_tex_type[5];	///< 节点的文本表示， 最大长度是四字节

/**
 *\enum
 *\brief 图的类型
 */
typedef enum
{
    DG, 	///< 有向图
	DN, 	///< 有向带权图
	UDG, 	///< 无向图
	UDN,	///< 无向带权图
}Graph_Kind;

/**
 *\struct
 *\brief 弧的定义
 */
typedef struct acr_cell_st
{
    arc_type adj;
    //Info_Type *info;
}acr_cell_st;

typedef acr_cell_st acr_st[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/**
 *\struct
 *\brief 图的定义
 */
typedef struct graph_st
{
    ver_tex_type 	vexs[MAX_VERTEX_NUM];	///< 图上节点 的字符形式 
	unsigned int	vexs_left[MAX_VERTEX_NUM];
	unsigned int	left_vertex_cnt;
	unsigned int	vexs_right[MAX_VERTEX_NUM];
	unsigned int	right_vertex_cnt;
    acr_st    		arcs;					///< 图上边（弧）
    unsigned int 	vertex_cnt;				///< 节点数量
    unsigned int 	arc_cnt;				///< 弧的数量
    Graph_Kind 		kind;					///< 图的类型
}graph_st;

static graph_st s_graph;		///< 图

/**
 *\fn
 *\brief 获取需要的信息，用于后面创建 二部图
 */
static void hga_get_input(void)
{
	unsigned int i = 0, j = 0;
	
    printf("输入二部图的左定点数:");
    scanf("%u", &s_graph.left_vertex_cnt);
    printf("输入二部图的右定点数:");
    scanf("%u", &s_graph.right_vertex_cnt);	
	s_graph.vertex_cnt = s_graph.left_vertex_cnt + s_graph.right_vertex_cnt;
	 
    printf("输入图的边数:");
    scanf("%u", &s_graph.arc_cnt);
    //printf("输入图的类型(DG:0 DN:1 UDG:2 UDN:3):");
    //scanf("%d", &G.kind);
	s_graph.kind = UDG;

    printf("输入二部图的左节点向量(定点之间用空格隔开):");
    for (i = 0; i < s_graph.left_vertex_cnt; ++i){
			
        scanf("%s", s_graph.vexs[i]);
		s_graph.vexs_left[i] = 1;
	}

    printf("输入二部图的右节点向量(定点之间用空格隔开):");
    for (i = s_graph.left_vertex_cnt; i < s_graph.vertex_cnt; ++i){
			
        scanf("%s", s_graph.vexs[i]);
		s_graph.vexs_right[i] = 1;	
	}
	
    for (i = 0; i < s_graph.vertex_cnt; ++i){
		
        for(j = 0; j < s_graph.vertex_cnt; ++j){
			
            s_graph.arcs[i][j].adj = 0;
		}
	}
}

/**
 *\fn
 *\brief 返回节点的下标志， 在节点集合中
 *\param[in] vtx 待查询的节点
 *\retval 返回下标值
 */
unsigned int hga_get_vertex_pos(const ver_tex_type vtx)
{
    unsigned int i;
	
    for (i = 0; i < s_graph.vertex_cnt; ++i){
		
        if (strcmp(vtx, s_graph.vexs[i]) == 0){
			
            return i;
		}
	}
	
    exit(0);
}

/**
 *\fn
 *\brief 创建二部图
 */
static void hga_create_bgraph(void)
{
    unsigned int i, v1_site, v2_site;
    ver_tex_type v1, v2;
	
    hga_get_input();
	
    printf("输入与弧相关联的顶点(形如v1 - v2):\n");
    for (i = 0; i < s_graph.arc_cnt; ++i){
		
        scanf("%s %*s %s", v1, v2);
        v1_site = hga_get_vertex_pos(v1);
        v2_site = hga_get_vertex_pos(v2);
		
        switch (s_graph.kind){
			
        case DG:
            s_graph.arcs[v1_site][v2_site].adj = 1;
            break;
			
        case DN:
            printf("输入权值:");
            scanf("%d", &s_graph.arcs[v1_site][v2_site].adj);
            break;
			
        case UDG:
            s_graph.arcs[v1_site][v2_site].adj = s_graph.arcs[v2_site][v1_site].adj = 1;
            break;
			
        case UDN:
            printf("输入权值:");
            scanf("%d", &s_graph.arcs[v1_site][v2_site].adj);
            s_graph.arcs[v2_site][v1_site].adj = s_graph.arcs[v1_site][v2_site].adj ;
            break;
			
        default:
            exit(0);
        }
    }
}

/**
 *\fn
 *\brief 输出图的结构， 以边的形式
 */
static void hga_print_graph_as_arc(void)
{
    unsigned int i = 0, j = 0;

    printf("输出弧:\n");
    for(i = 0; i < s_graph.vertex_cnt; ++i){
		
		if (!s_graph.vexs_left[i]){
			
			continue;
		}
		
        for (j = 0; j < s_graph.vertex_cnt; ++j){
			
			if (!s_graph.vexs_right[j]){
				
				continue;
			}
			
            if (s_graph.arcs[i][j].adj){
				
                printf("(%s--", s_graph.vexs[i]);
                printf("%s)\n", s_graph.vexs[j]);
            }
		}
	}
}

/**
 *\fn
 *\brief 输出图的结构， 以邻接矩阵的形式
 */
static void hga_print_graph_as_matrix(void)
{
    unsigned int i = 0, j = 0;
	
    printf("图的邻接矩阵为:\n");
    for (i = 0; i < s_graph.vertex_cnt; ++i){
    
		if (!s_graph.vexs_left[i]){
			
			continue;
		}
		
        for (j = 0; j < s_graph.vertex_cnt; ++j){

			if (!s_graph.vexs_right[j]){
				
				continue;
			}		
			
            printf(" %d", s_graph.arcs[i][j].adj);
		}
        printf("\n");
    }
}

static unsigned int invalid[MAX_VERTEX_NUM];	///< 被占用状态
static unsigned int right_cp[MAX_VERTEX_NUM];	///< 右边待匹配的

/**
 *\fn
 *\brief
 *\param[in] i
 *\retval 1 成功找到增广路
 *\retval 0 没有找到增广路
 */
unsigned int hga_dfs_rec(unsigned int i){
	
	unsigned int j = 0;
	
	for (j = s_graph.left_vertex_cnt; j < s_graph.vertex_cnt; ++j){ /** 遍历所有的 右边节点 */
		
		if (s_graph.arcs[i][j].adj && !invalid[j]){/** 左右节点存在边(即有关系)，且右节点没有被占用 */
			
			invalid[j] = 1;	/** 被占用了  打上标记 */
			if (right_cp[j] == 255 || hga_dfs_rec(right_cp[j])){/** 右节点没有被占用 或者 右节点被占用但是位置还可以进行调整 */
				
				right_cp[j] = i;
				return 1;
			}
		}
	}
	
	return 0;
}

/**
 *\fn
 *\brief 采用深度搜索
 */
static void hga_dfs(void){
	
	unsigned int i = 0;
	
	for (i = 0; i < MAX_VERTEX_NUM; ++i){
		
		right_cp[i] = 255;
	}
	
	for (i = 0; i < s_graph.left_vertex_cnt; ++i){
		
		memset(invalid, 0, sizeof(unsigned int)*MAX_VERTEX_NUM);
		hga_dfs_rec(i);
	}
}
 
/**
 *\fn
 *\brief 输出匹配结果
 */
static void hga_print_match_res(void){

    unsigned int i = 0;

    printf("输出匹配结果:\n");
    for(i = 0; i < s_graph.vertex_cnt; ++i){
		
		if (right_cp[i] != 255){
			
			printf("(%s--", s_graph.vexs[right_cp[i]]);
            printf("%s)\n", s_graph.vexs[i]);
		}
	}	
}

int main(void)
{
    hga_create_bgraph();

    hga_print_graph_as_arc();
    hga_print_graph_as_matrix();
	
	hga_dfs();
	
	hga_print_match_res();

    return 0;
}