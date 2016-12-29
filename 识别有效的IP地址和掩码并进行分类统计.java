
import java.io.*;
import java.util.Scanner;

public class Main {
	int A;
	int B;
	int C;
	int D;
	int E;
	int error;
	int privates;
	
	public Main(){
		reset();
	}
	
	public void reset(){
		A =0;
		B =0;
		C =0;
		D =0;
		E =0;
		error =0;
		privates =0;
	}
	
	//done
	public boolean countErrors(String ip, String mask){
		
		if("255.255.255.255".equals(mask)){
			error ++;
			return true;
		}
		
		String ipstr="";
		String[] ips = ip.split("\\.");
		String[] masks = mask.split("\\.");

		for(String section:ips){
			if(section.isEmpty()){
				error ++;
				return true;
			}
		}

		for(String section:masks){
			String temp;
			if(section.isEmpty()){
				error ++;
				return true;
			}else{
				temp = Integer.toBinaryString(Integer.parseInt(section));
				while(temp.length()<8){
					temp = "0"+temp;
				}
				ipstr = ipstr + temp;
			}
		}
		for(int i=0; i<ipstr.length()-1; i++){
			if(ipstr.charAt(i)<ipstr.charAt(i+1)){
				error ++;
				return true;
			}
		}
		
		return false;
	}
	
	//done
	public void countIPs(String ipstr){
		long ipL = 0L;
		long ipStart = 0L;
		long ipEnd = 0L;
		ipL = str2long(ipstr);
		ipStart = str2long("1.0.0.0");
		ipEnd = str2long("126.255.255.255");
		if(ipL>=ipStart && ipL<=ipEnd){
			A ++;
			if(ipL>=str2long("10.0.0.0") && ipL<=str2long("10.255.255.255")){
				privates ++;
			}
		}
		ipStart = str2long("128.0.0.0");
		ipEnd = str2long("191.255.255.255");
		if(ipL>=ipStart && ipL<=ipEnd){
			B ++;
			if(ipL>=str2long("172.16.0.0") && ipL<=str2long("172.31.255.255")){
				privates ++;
			}
		}
		ipStart = str2long("192.0.0.0");
		ipEnd = str2long("223.255.255.255");
		if(ipL>=ipStart && ipL<=ipEnd){
			C ++;
			if(ipL>=str2long("192.168.0.0") && ipL<=str2long("192.168.255.255")){
				privates ++;
			}
		}
		ipStart = str2long("224.0.0.0");
		ipEnd = str2long("239.255.255.255");
		if(ipL>=ipStart && ipL<=ipEnd){
//			System.out.println(ipstr);
			D ++;
		}
		ipStart = str2long("240.0.0.0");
		ipEnd = str2long("255.255.255.255");
		if(ipL>=ipStart && ipL<=ipEnd){
			E ++;
		}
	}
	
	//done
	public long str2long(String ipstr){
		String[] list = ipstr.split("\\.");
		long ipL = 0L;
		for(String section:list){
			ipL = ipL*256 + Long.parseLong(section);
		}
		return ipL;
	}
	
	//done
	public void print(){
		System.out.println(String.valueOf(A)+" "+String.valueOf(B)+" "+String.valueOf(C)+" "+String.valueOf(D)+" "+
				String.valueOf(E)+" "+String.valueOf(error)+" "+String.valueOf(privates));
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
		String inStr;
		while (in.hasNextLine()) {
			inStr = in.nextLine();
			inStr = inStr.trim();
			if (inStr.isEmpty()) {
				break;
			}
			String[] list = inStr.split("\\~");
			if (!m.countErrors(list[0], list[1])) {
				m.countIPs(list[0]);
			}
		}
		m.print();
	}
}

