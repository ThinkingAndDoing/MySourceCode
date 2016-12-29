package mypro;

import java.io.*;
import java.util.Scanner;

public class Main {
	
	public void sort0_1(int[][]a, int num)
	{
		int start = 0;
		int end = num - 1;
		while (start < end) {
			while (start < end && a[start][2] == 0) {
				start++;
			}
			while (start < end && a[end][2] != 0) {
				end--;
			}
			if (start < end) {
				int[] temp = new int[3];
				temp[0] = a[start][0];
				temp[1] = a[start][1];
				temp[2] = a[start][2];
				a[start][0] = a[end][0];
				a[start][1] = a[end][1];
				a[start][2] = a[end][2];
				a[end][0] = temp[0];
				a[end][1] = temp[1];
				a[end][2] = temp[2];
				for (int i = 0; i < num; i++) {
					if (a[i][2] == end + 1) {
						a[i][2] = start + 1;
					}
				}
				start++;
				end--;
			}
		}
	}

	//此算法，找路径部分可以优化，节省空间
	public int maxValueOfSpecial0_1bag(int[][] a, int num, int M) {
		int[][][] array = new int[num + 1][M + 1][num + 1];// 可以用函数计算来判断主件是否已经加入，这样一个二维数组就足够
		for (int i = 0; i < num + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				for (int k = 0; k < num + 1; k++) {
					array[i][j][k] = 0;
				}
			}
		}
		// 扫描，移动，将主件全部移到前面
		sort0_1(a, num);
		for (int i = 0; i < num + 1; i++) {
			array[i][0][0] = 0;
		}
		for (int i = 0; i < M + 1; i++) {
			array[0][i][0] = 0;
		}
		for (int i = 1; i < num + 1; i++) {
			for (int j = 1; j < M + 1; j++) {
				if (j < a[i-1][0]) {
					array[i][j][0] = array[i - 1][j][0];
					array[i][j][i] = 0;
					for (int k = 1; k <= i; k++) {
						array[i][j][k] = array[i - 1][j][k];
					}
				} else {
					boolean hasMasterDev = false;
					if (1 == array[i - 1][j - a[i-1][0]][a[i-1][2]]) {
						hasMasterDev = true;
					}
					if (a[i-1][2] == 0 || (a[i-1][2] != 0 && hasMasterDev)) {// 主件/附件但主件已经加入
						if (array[i - 1][j][0] < array[i - 1][j - a[i-1][0]][0]
								+ a[i-1][0] * a[i-1][1]) {
							array[i][j][0] = array[i - 1][j - a[i-1][0]][0]
									+ a[i-1][0] * a[i-1][1];
							array[i][j][i] = 1;
							for (int k = 1; k <= i; k++) {
								array[i][j][k] = array[i - 1][j - a[i-1][0]][k];
							}
						} else {
							array[i][j][0] = array[i - 1][j][0];
							array[i][j][i] = 0;
							for (int k = 1; k <= i; k++) {
								array[i][j][k] = array[i - 1][j][k];
							}
						}
					} else {// 附件并且主件没有加入
						int i_master = a[i-1][2] - 1; // 主件和附件值的和
						if (j < a[i-1][0] + a[i_master][0]) {
							array[i][j][0] = array[i - 1][j][0];
							array[i][j][i] = 0;
							for (int k = 1; k <= i; k++) {
								array[i][j][k] = array[i - 1][j][k];
							}
						} else {
							if (array[i - 1][j][0] < array[i - 1][j - a[i-1][0]
									+ a[i_master][0]][0]
									+ a[i-1][0]
									* a[i-1][1]
									+ a[i_master][0]
									* a[i-1][1]) {
								array[i][j][0] = array[i - 1][j - a[i-1][0]
										+ a[i_master][0]][0]
										+ a[i-1][0]
										* a[i-1][1]
										+ a[i_master][0]
										* a[i-1][1];
								array[i][j][i] = 1;
								for (int k = 1; k <= i; k++) {
									array[i][j][k] = array[i - 1][j - a[i-1][0]
											+ a[i_master][0]][k];
								}
								array[i][j][i_master + 1] = 1;
							} else {
								array[i][j][0] = array[i - 1][j][0];
								array[i][j][i] = 0;
								for (int k = 1; k <= i; k++) {
									array[i][j][k] = array[i - 1][j][k];
								}
							}
						}
					}
				}

			}
		}
		return array[num][M][0];
	}
	
	public int maxValueOf0_1bag(int num, int M, int[] v,int[] w) throws FileNotFoundException, IOException
	{//普通 0-1背包问题
		int[][] array = new int[num+1][M+1];
		for(int i=0; i<M+1; i++){
			array[0][i] = 0;
		}
		for(int i=0; i<num+1; i++){
			array[i][0] = 0;
		}
		for (int i = 1; i < num + 1; i++) {
			for (int j = 1; j < M + 1; j++) {
				if (j < w[i-1]) {
					array[i][j] = array[i - 1][j];
				} else {
					if (array[i - 1][j] < array[i - 1][j - w[i-1]] + v[i-1]) {
						array[i][j] = array[i - 1][j - w[i-1]] + v[i-1];
					} else {
						array[i][j] = array[i - 1][j];
					}
				}
			}
		}
		return array[num][M];
	}

	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
		//maxValueOf0_1bag
//		int M = in.nextInt();
//		int num = in.nextInt();
//		int[] v = new int[num];
//		int[] w = new int[num];
//		for(int i=0; i<num; i++){
//			w[i] = in.nextInt();
//			v[i] = in.nextInt();
//		}
//		for(int i=0; i<num; i++){
//			v[i] = v[i]*w[i];
//		}
//		System.out.println(m.maxValueOf0_1bag(num,M,v,w));
		
		//
//		int money = 1000;
//		int num = 5;
		int money = in.nextInt();
		int num = in.nextInt();
		if(money>32000){
			money = 32000;
		}
		if(num>60){
			num = 60;
		}
		int[][] goods = new int[num][3]; //value, weight, q
		for(int i=0; i<num; i++){
			goods[i][0] = in.nextInt();
			goods[i][1] = in.nextInt();
			goods[i][2] = in.nextInt();
		}
//		goods[0][1]=2; goods[0][0]=800; goods[0][2]=0;
//		goods[1][1]=5; goods[1][0]=400; goods[1][2]=1;
//		goods[2][1]=5; goods[2][0]=300; goods[2][2]=1;
//		goods[3][1]=3; goods[3][0]=400; goods[3][2]=0;
//		goods[4][1]=2; goods[4][0]=500; goods[4][2]=0;
		System.out.println(m.maxValueOfSpecial0_1bag(goods, num, money));
	}
}

测试用例:
1738 55
20 3 0
50 2 0
120 3 0
40 3 0
100 4 0
220 2 0
40 2 0
200 3 0
90 3 0
10 3 0
230 2 0
300 1 0
70 2 0
270 1 0
300 3 0
70 5 0
300 2 0
200 1 0
210 1 0
270 2 0
180 2 0
40 2 0
110 4 0
170 4 0
110 1 0
280 4 0
50 4 0
160 2 0
10 3 0
320 3 0
10 5 0
50 2 0
230 4 0
230 1 0
150 5 0
160 5 0
90 5 0
140 3 0
140 3 0
250 5 0
330 2 0
190 3 0
230 1 0
70 2 0
50 3 0
170 5 0
100 5 0
230 5 0
120 1 0
70 2 0
50 3 0
240 1 0
220 1 0
20 5 0
20 3 0
