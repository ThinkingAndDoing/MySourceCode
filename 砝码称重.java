
import java.io.*;
//import java.util.Scanner;
import java.util.*;


public class Main {
	int number;
	int[] sign;
	
	public Main(){
		reset();
	}
	
	public void reset(){
		number = 0;
	}
	
	public int fama(int n, int[] weight, int[] nums){
		int sum = 0;
		for(int i=0; i<n; i++){
			sum = sum + weight[i] * nums[i];
		}
		sign = new int[sum+1];
		for(int i=0; i<sum+1; i++){
			sign[i] = 0;
		}
		sign[0] = 1;
		for(int i=0; i<n; i++){
			for(int j=sum; j>=0; j--){
				for(int k=1; k<=nums[i]; k++){
					if(j>=k*weight[i]){
						if(sign[j-k*weight[i]]==1){
							sign[j] = 1;
							break;
						}
					}
				}
			}
		}
		
		for(int i=0; i<sign.length; i++){
			if(sign[i]==1){
				number ++;
			}
		}
		return 0;
	}
	
	//done
	public void print(){
		System.out.println(number);
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
//		Stack<Record> s = new Stack<Record>();
//		long inLong=0L;
//		String inStr="";
		int inInt =0;
		int[] a= new int[1];
		a[0] = 1;
//		inStr = in.nextLine();
		while (in.hasNextInt()) {
			inInt = in.nextInt();
			int[] Weight = new int[inInt];
			int[] Nums = new int[inInt];
			for(int i=0; i<inInt; i++){
				Weight[i] = in.nextInt();
			}
			for(int i=0; i<inInt; i++){
				Nums[i] = in.nextInt();
			}
			m.reset();
			m.fama(inInt, Weight, Nums);
			m.print();
//			System.out.println("hello");
		}

	}
}

