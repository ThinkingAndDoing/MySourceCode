package mypro;

import java.io.*;
//import java.util.Scanner;
import java.util.*;


public class Main {
	String[][] records;
	int index;
	
	public Main(){
		records = new String[8][3];
        for(int i=0; i<8; i++){
            for(int j=0; j<3; j++){
                records[i][j] = new String();
            }
        }
		reset();
	}
	
	public void reset(){
		for(int i=0; i<8; i++){
			for(int j=0; j<3; j++){
				if(j==2){
					records[i][j]="0";
				}else{
					records[i][j]="";
				}
			}
		}
		index = 0;
	}
	

	public void addRecord(String oneRecord){
		oneRecord = oneRecord.replace("\\s+", " ");
		String[] list= oneRecord.split(" ");
		String temp = new String();
		temp = list[0];
		String[] temps = temp.split("\\\\");
		temp = temps[temps.length-1];
		if(temp.length()>16){
			temp = temp.substring(temp.length()-16, temp.length());
		}
		list[0] = temp;
		for(int i=0; i<8; i++){
			if(records[i][0].equals(list[0]) && records[i][1].equals(list[1])){
				records[i][2] = String.valueOf(Integer.parseInt(records[i][2])+1);
				return ;
			}
		}
		records[index][0] = list[0];
		records[index][1] = list[1];
		records[index][2] = "1";
		index = (index + 1) % 8;
	}
	
	//done
	public void print(){
		for(int i=index; i<8+index; i++){
//			System.out.println("Print outcome");
			if(!records[i%8][0].equals("")){
				System.out.println(records[i%8][0]+ " "+ records[i%8][1] + " "+ records[i%8][2]);
			}
		}
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
//		Stack<Record> s = new Stack<Record>();
//		long inLong=0L;
		String inStr="";
//		int inInt =0;
//		inStr = in.nextLine();
		while (in.hasNextLine()) {
			inStr = in.nextLine();
//			System.out.println(inStr);
			if(inStr.isEmpty()){
				break;
			}else{
				m.addRecord(inStr);
			}
            
//			System.out.println("hello");
		}
        m.print();
//		System.out.println(m.multi2("1",15));
//		System.out.println(m.getResult(180));
	}
}

