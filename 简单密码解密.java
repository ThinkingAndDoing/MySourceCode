
import java.io.*;
import java.util.*;
//import java.util.Scanner;

public class Main {
//	String[] outcome;
	String outcome;
//	int number;
//	int[] list;
//	int length;
	
	public Main(){
		reset();
	}
	
	public void reset(){
		outcome = new String("");
//		number = 0;
	}
	
	public void parse(String str){
		for(int i=0; i<str.length(); i++){
			char c = getDecodeChar(str.charAt(i));
			outcome += String.valueOf(c);
		}
	}
	
	public char getDecodeChar(char x){
		char c=x;
		if(c>='A'&&c<='Z'){
			c = (char)((c-'A'+1)%26 + 'a');
		}else if(c>='a'&&c<='z'){
			switch(c){
			case 'a':
			case 'b':
			case 'c':
				c = '2';
				break;
			case 'd':
			case 'e':
			case 'f':
				c = '3';
				break;
			case 'g':
			case 'h':
			case 'i':
				c = '4';
				break;
			case 'j':
			case 'k':
			case 'l':
				c = '5';
				break;
			case 'm':
			case 'n':
			case 'o':
				c = '6';
				break;
			case 'p':
			case 'q':
			case 'r':
			case 's':
				c = '7';
				break;
			case 't':
			case 'u':
			case 'v':
				c = '8';
				break;
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				c = '9';
				break;
			}
		}
		return c;
	}
	
	//done
	public void print(){
		System.out.println(outcome);
//		System.out.println("");
//		System.out.println(number);
//		for(int i=0; i<length-1; i++){
//			System.out.print(list[i]);
//			System.out.print(" ");
//		}
//		if(length-1>=0){
//			System.out.print(list[length-1]);
//		}
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
//		Stack<Record> s = new Stack<Record>();
//		long inLong=0L;
		String inStr="";
		int inInt =0;
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



//public void sort(int[] s, int start, int end){
//if(start<end){
//	int base = s[start];
//	int i= start, j= end;
//	while(i<j){
//		while(j>start && base<s[j]){
//			j --;
//		}
//		if(i<j){
//			int temp = s[i];
//			s[i] = s[j];
//			s[j] = temp;
//			i ++;
//		}
//		while(i<end && base>s[i]){
//			i ++;
//		}
//		if(i<j){
//			int temp = s[i];
//			s[i] = s[j];
//			s[j] = temp;
//			j --;
//		}
//	}
//	if(i<end)sort(s, i+1, end);
//	if(j>start)sort(s, start, j-1);
//}
//}
