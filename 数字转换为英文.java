
import java.io.*;
//import java.util.Scanner;
import java.util.*;


public class Main {
	String outcome;
	
	public Main(){
		reset();
	}
	
	public void reset(){
		outcome = new String("");
	}
	
	public void parse(long num){
		if(num>1000000){
			parseLessThanThousand(num/1000000);
			outcome += " million";
			num %= 1000000;
		}
		if(num>1000){
			parseLessThanThousand(num/1000);
			outcome += " thousand";
			num %= 1000;
		}
		if(num!=0){
			parseLessThanThousand(num);
		}
		return ;
	}
	
	public void parseLessThanThousand(long num){
		if(num>=100){
			outcome += " "+ translateUnits(num/100) + " hundred";
			num = num %100;
			if(num!=0){
				outcome = outcome + " and";
			}
		}
		if(num>=20){
			outcome += " " + translateTens(num/10);
			num = num %10;
		}
		if(num!=0){
			outcome += " " + translateUnits(num);
		}
		return ;
	}
	
	public String translateUnits(long n){
		String value = new String("error");
		if(n<0){
			return value;
		}
		String[] basicNum = {"","one","two","three","four","five","six","seven","eight","nine","ten",
				"eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
		if(n<20){
			value = basicNum[(int)n];
		}
		return value;
	}
	
	public String translateTens(long n){
		String value = new String("error");
		if(n<2){
			return value;
		}
		String[] basicNum = {"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
		if(n<=9){
			value = basicNum[(int)n-2];
		}
		return value;
	}
	
	//done
	public void print(){
		outcome = outcome.trim();
		System.out.println(outcome);
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
//		Stack<Record> s = new Stack<Record>();
//		long inLong=0L;
//		String inStr="";
//		int inInt =0;
		long inLong = 0L;
//		inStr = in.nextLine();
		while (in.hasNextLong()) {
			inLong = in.nextLong();
			m.reset();
			m.parse(inLong);
			m.print();
//			System.out.println("hello");
		}

	}
}

