最小生成树(Prim)
	
	在连通图中， 通过最小的代价将图中的顶点串连起来，算法非常类似迪杰斯特拉，
	两者的区别在于， 迪杰斯特拉是求2个顶点间的距离， 而Prim算法是求整个图中构成连通的最小代价， 可见Prim算法实际上比迪杰斯特拉算法更加的简单， 因为在求最小生成树的过程中最要选取最短的和已选择的顶点相连的边即可。
	
	算法的核心是： 无向带权图G(V,E)，已经被选择在最小生成树中的顶点集合记为S，S的初始状态为空（S={}），任意选取一个顶点v，加入S中（S={v}），下一个顶点的选取规则，选取所有边中，与S中相连的边权重最小的边， 其中边的一个顶点属于S，另一个顶点属于V-S， 一直这样循环下去， 直到S = V 算法结束
	
例如：图G 有顶点信息为(v1,v2,v3,v4,v5,v6) 边的权重分别为
v1 - v2 7
v1 - v3 9
v1 - v6 14
v2 - v4 15
v2 - v3 10
v3 - v4 11
v3 - v6 2
v4 - v5 6
v5 - v6 9
假设图G从v1顶点开始搜索，演示如下：
步骤1、将v1加入到已发现顶点集合S{v1}
步骤2、遍历与集合S相连的所有边, 找去其中权重最小的边，将另一个顶点加入到集合S中，从v2,v3,v6中选出v2,S{v1,v2}
步骤3、遍历与集合S相连的所有边, 找去其中权重最小的边，将另一个顶点加入到集合S中，从v3,v4,v6中选出v3,S{v1,v2,v3}
步骤4、遍历与集合S相连的所有边, 找去其中权重最小的边，将另一个顶点加入到集合S中，从v4,v6中选出v6,S{v1,v2,v3,v6}
步骤5、遍历与集合S相连的所有边, 找去其中权重最小的边，将另一个顶点加入到集合S中，从v4,v5中选出v5,S{v1,v2,v3,v6,v5}
步骤6、遍历与集合S相连的所有边, 找去其中权重最小的边，将另一个顶点加入到集合S中，从v4中选出v4,S{v1,v2,v3,v6,v5,v4}
------+-----------+-----------+-----------+------------+-----------+------------+--------------------
      |    v1     |    v2     |    v3     |    v4      |    v5     |    v6      | S
------+-----------+-----------+-----------+------------+-----------+------------+--------------------
步骤1 | (v1,v1) 0 | (v1,v2) 7 | (v1,v3) 9 |    Na      |    Na     | (v1,v6) 14 | {v1}
------+-----------+-----------+-----------+------------+-----------+------------+--------------------
步骤2 | (v1,v1) 0 | (v1,v2) 0 | (v1,v3) 9 | (v2,v4) 15 |    Na     | (v1,v6) 14 | {v1,v2}
------+-----------+-----------+-----------+------------+-----------+------------+--------------------
步骤3 | (v1,v1) 0 | (v1,v2) 0 | (v1,v3) 0 | (v3,v4) 10 |    Na     | (v3,v6) 2  | {v1,v2,v3}
------+-----------+-----------+-----------+------------+-----------+------------+--------------------
步骤4 | (v1,v1) 0 | (v1,v2) 0 | (v1,v3) 0 | (v3,v4) 10 | (v6,v5) 9 | (v3,v6) 0  | {v1,v2,v3,v6}
------+-----------+-----------+-----------+------------+-----------+------------+--------------------
步骤5 | (v1,v1) 0 | (v1,v2) 0 | (v1,v3) 0 | (v5,v4) 6  | (v6,v5) 0 | (v3,v6) 0  | {v1,v2,v3,v6,v5}
------+-----------+-----------+-----------+------------+-----------+------------+--------------------
步骤6 | (v1,v1) 0 | (v1,v2) 0 | (v1,v3) 0 | (v5,v4) 0  | (v6,v5) 0 | (v3,v6) 0  | {v1,v2,v3,v6,v5,v4}
------+-----------+-----------+-----------+------------+-----------+------------+--------------------

$ ./graph_prim 
输入图的结点数:6
输入图的边数:9
输入结点序列（例如：v1 v2 v3）：
v1 v2 v3 v4 v5 v6
输入边信息（例如：v1 - v2 5）：
v1 - v2 7
v1 - v3 9
v1 - v6 14
v2 - v4 15
v2 - v3 10
v3 - v4 11
v3 - v6 2
v4 - v5 6
v5 - v6 9
输出图的链接信息：
v1 ->5(14)->2(9)->1(7)
v2 ->2(10)->3(15)->0(7)
v3 ->5(2)->3(11)->1(10)->0(9)
v4 ->4(6)->2(11)->1(15)
v5 ->5(9)->3(6)
v6 ->4(9)->2(2)->0(14)

result: 
0(0) 1(7) 2(9) 5(2) 4(9) 3(6) 
total_weight[33]
----------------------------------------
$ ./graph_prim 
输入图的结点数:4
输入图的边数:3
输入结点序列（例如：v1 v2 v3）：
v1 v2 v3 v4
输入边信息（例如：v1 - v2 5）：
v1 - v2 1
v1 - v3 2
v1 - v4 3
输出图的链接信息：
v1 ->3(3)->2(2)->1(1)
v2 ->0(1)
v3 ->0(2)
v4 ->0(3)

result: 
0(0) 1(1) 2(2) 3(3) 
total_weight[6]
-----------------------------------------------
