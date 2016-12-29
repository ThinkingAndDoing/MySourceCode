
import java.io.*;
import java.util.Scanner;

public class Main {
	String value;
	
	public Main(){
		reset();
	}
	
	public void reset(){
		value = "";
	}
	
	
	//done
	public String Hex2Dec(String hstr){
		int i = hstr.length() -1;
		value = "0";
		int a =0;
		while(i>=2){
			if(hstr.charAt(i)>='0' && hstr.charAt(i)<='9'){
				a = hstr.charAt(i) - '0';
			}else{
				a = hstr.charAt(i) - 'A' + 10;
			}
			value = sum(value, poly(a,hstr.length()-1-i));
			i --;
		}
		return value;
	}
	
	public String poly(int a, int y){
		String z="1";
		int i=y;
		while(i>0){
			z = multi2(z,16);
			i --;
		}
		if(a>9){
			z = multi2(z,a);
		}else{
			z = multi(z,a);
		}
		return z;
	}
	
	//done
	public void print(){
		System.out.println(value);
	}
	
	//done
	public String multi(String x, int y){
		String z="";
		int i=x.length()-1;
		int delta= 0;
		int temp = 0;
		while(i>=0){
			temp = y*Integer.parseInt(String.valueOf(x.charAt(i))) + delta;
			z = String.valueOf(temp%10) + z;
			delta = temp/10;
			i --;
		}
		if(delta!=0){
			z = String.valueOf(delta) + z;
		}
		return z;
	}
	
	public String multi2(String x, int yy){
		String z="";
		z = sum(multi(x, yy%10), multi(x,yy/10)+"0");
//		System.out.println(z);
		return z;
	}
	
	//done
	public String sum(String x, String y){
		String z="";
		int i =x.length()-1;
		int j =y.length()-1;
		int temp =0;
		int delta =0;
		while(i>=0 || j>=0){
			if(i>=0 && j>=0){
				temp = Integer.parseInt(String.valueOf(x.charAt(i))) + Integer.parseInt(String.valueOf(y.charAt(j))) + delta;
				z = String.valueOf(temp%10) + z;
				delta = temp/10;
				i --;
				j --;
			}else if(i>=0){
				temp = Integer.parseInt(String.valueOf(x.charAt(i))) + delta;
				z = String.valueOf(temp%10) + z;
				delta = temp/10;
				i --;
			}else{
				temp = Integer.parseInt(String.valueOf(y.charAt(j))) + delta;
				z = String.valueOf(temp%10) + z;
				delta = temp/10;
				j --;
			}
		}
		if(delta!=0){
			z = String.valueOf(delta) + z;
		}
		return z;
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
		String inStr;
//		inStr = in.nextLine();
		while (in.hasNextLine()) {
			inStr = in.nextLine();
			m.reset();
			m.Hex2Dec(inStr);
			m.print();
		}
//		System.out.println(m.multi2("1",15));
//		System.out.println(m.Hex2Dec("0xF"));
	}
}

