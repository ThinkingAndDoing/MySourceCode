package mypro;

import java.io.*;
//import java.util.Scanner;
import java.util.*;

import java.nio.charset.Charset;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;

public class WarningPopupText {
//	String[] outcome;
	String outcome;
//	int number;
//	int[] list;
//	int length;
	
	public WarningPopupText(){
		reset();
	}
	
	public void reset(){
		outcome = new String("");
//		number = 0;
	}
	
	public int getNextKey(byte[] bts, int index, byte[] nextKey){
		int nextKeyLen =0;
		
		if(index>=bts.length || index==bts.length-1&&bts[index]<0){
			return nextKeyLen;
		}
		
		if(bts[index]>0){
			int j =0;
			while(index<bts.length && bts[index]>0){
				nextKey[j] = bts[index];
				index ++;
				j ++;
			}
			nextKeyLen = j;
		}else{
			nextKey[0] =  bts[index];
			nextKey[1] =  bts[index+1];
			nextKeyLen = 2;
		}
		
		return nextKeyLen;
	}
	
	public void getOutcomeOfChinese(String str, int byteNum){
		byte[] bts = str.getBytes();
		byte[] nextKey = new byte[20];
		int nextKeyLen = 0;
		byte[] dist = new byte[1000];
		
		int i =0;
		int j =0;
		int count =0;
		while(i<bts.length){
			nextKeyLen = getNextKey(bts, i, nextKey);
			if(nextKeyLen + count<=byteNum){
				for(int k=0; k<nextKeyLen; k++){
					dist[j++] = bts[i++];
				}
				count = count + nextKeyLen;
			}else{
				dist[j++] = '\\';
				dist[j++] = 'n';
				count =0;
			}
		}
		Charset charset = Charset.defaultCharset();
        ByteBuffer buf = ByteBuffer.wrap(dist);
        CharBuffer cBuf = charset.decode(buf);
        outcome = cBuf.toString();
        outcome = outcome.trim();
	}
	
	public void getOutcomeOfEnglish(String str, int byteNum){
		String[] words = str.split("\\s");
		
		if(words.length<1){
			return ;
		}
		outcome = words[0];
		int len = outcome.length();
		for(int i=1; i<words.length; i++){
			if(words[i].length()+len+1<byteNum){
				outcome += " "+ words[i];
				len += words[i].length() +1;
			}else{
				outcome += "\\n";
				outcome += words[i];
				len = words[i].length();
			}
		}
	}
	
	public void parse(String str, int byteNum){
		int lang =0; //0-english, 1-chinese
		byte[] bts = str.getBytes();
		for(int i=0; i<bts.length; i++){
			if(bts[i]<0){
				lang = 1;
				break;
			}
		}
		if(lang==0){
			getOutcomeOfEnglish(str, byteNum);
		}else{
			getOutcomeOfChinese(str, byteNum);
		}
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
		WarningPopupText m = new WarningPopupText();
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
			m.parse(inStr, 28);
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
