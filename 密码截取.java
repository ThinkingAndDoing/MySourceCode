
import java.io.*;
//import java.util.Scanner;
import java.util.*;


public class Main {
//	String[] outcome;
	int number;
	
	public Main(){
		reset();
	}
	
	public void reset(){
//		outcome = new String("");
		number = 0;
	}
	
	public void parse(String str){
		int sum = 0;
		for(int i=2; i<=str.length(); i++){
			if(check(str,i-sum-2, i)){
				sum += 2;
			}
		}
		if(sum>number){
			number = sum;
		}
		sum = 1;
		for(int i=2; i<=str.length(); i++){
			if(check(str,i-sum-2, i)){
				sum += 2;
			}
		}
		if(sum>number){
			number = sum;
		}
	}
	
	public boolean check(String str, int start, int end){
//		System.out.println(str);
		if(start<0 || start>end){
			return false;
		}
		str = str.substring(start, end);
		for(int i=0; i<str.length()/2; i++){
			if(str.charAt(i)!=str.charAt(str.length()-1-i)){
				return false;
			}
		}
		return true;
	}
	
	public void sort(char[] s, int start, int end){
		if(start<end){
			char base = s[start];
			int i= start, j= end;
			while(i<j){
				while(j>start && base<s[j]){
					j --;
				}
				if(i<j){
					char temp = s[i];
					s[i] = s[j];
					s[j] = temp;
					i ++;
				}
				while(i<end && base>s[i]){
					i ++;
				}
				if(i<j){
					char temp = s[i];
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
		System.out.println(number);
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
//		Stack<Record> s = new Stack<Record>();
//		long inLong=0L;
		String inStr="";
//		int inInt =0;
//		int[] intArr;
//		String[] StrArr;
//		long inLong = 0L;
//		inStr = in.nextLine();
		while (in.hasNextLine()) {
			inStr = in.nextLine();
			m.reset();
			m.parse(inStr);
			m.print();
//			System.out.println("hello");
			}

	}
}

