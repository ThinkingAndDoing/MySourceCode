
import java.io.*;
//import java.util.Scanner;
import java.util.*;


public class Main {
//	String[] outcome;
//	int number;
	int[] list;
	int length;
	
	public Main(){
		reset();
	}
	
	public void reset(){
//		outcome = new String("");
//		number = 0;
	}
	
	public void parse(int len, int sublen, int[] intArr){
		list = new int[sublen];
		length = sublen;
		GetMinK(len, intArr, sublen, list);
	}
	
	public boolean GetMinK(int uiInputNum, int[] pInputArray, int uiK, int[] pOutputArray){
		sort(pInputArray, 0, uiInputNum-1);
		for(int i=0; i<uiK ; i++){
			pOutputArray[i] = pInputArray[i];
		}
		return true;
	}
	
	public void sort(int[] s, int start, int end){
		if(start<end){
			int base = s[start];
			int i= start, j= end;
			while(i<j){
				while(j>start && base<s[j]){
					j --;
				}
				if(i<j){
					int temp = s[i];
					s[i] = s[j];
					s[j] = temp;
					i ++;
				}
				while(i<end && base>s[i]){
					i ++;
				}
				if(i<j){
					int temp = s[i];
					s[i] = s[j];
					s[j] = temp;
					j --;
				}
			}
			if(i<end)sort(s, i+1, end);
			if(j>start)sort(s, start, j-1);
		}
	}
	
	//done
	public void print(){
//		System.out.println("");
//		System.out.println(number);
		for(int i=0; i<length-1; i++){
			System.out.print(list[i]);
			System.out.print(" ");
		}
		if(length-1>=0){
			System.out.print(list[length-1]);
		}
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
//		Stack<Record> s = new Stack<Record>();
//		long inLong=0L;
//		String inStr="";
//		int inInt =0;
		int[] intArr;
//		String[] StrArr;
//		long inLong = 0L;
//		inStr = in.nextLine();
		while (in.hasNextInt()) {
			int len = in.nextInt();
			int sublen = in.nextInt();
			intArr = new int[len];
			for(int i=0; i<len; i++)
			{
				intArr[i] = in.nextInt();
			}
			m.reset();
			m.parse(len, sublen, intArr);
			m.print();
//			System.out.println("hello");
			}
	}
}
