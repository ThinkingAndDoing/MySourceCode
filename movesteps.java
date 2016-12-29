package mypro;

import java.io.*;
import java.util.Scanner;

public class Main {
	int x;
	int y;
	
	public Main(){
		x =0;
		y =0;
	}
	
	public void reset(){
		x =0;
		y =0;
	}
	
	public void moveOneStep(String action){
		
		if(action.charAt(0)=='A'){
			action = action.replace('A', ' ').trim();
			x = x - Integer.parseInt(action);
		}else if(action.charAt(0)=='D'){
			action = action.replace('D', ' ').trim();
			x = x + Integer.parseInt(action);
		}else if(action.charAt(0)=='W'){
			action = action.replace('W', ' ').trim();
			y = y + Integer.parseInt(action);
		}else if(action.charAt(0)=='S'){
			action = action.replace('S', ' ').trim();
			y = y - Integer.parseInt(action);
		}
		
	}
	
	public void startMove(String instr){
		String[] list= instr.split(";");
		for(String action:list){
			boolean isStep = false;
			if(!action.isEmpty()){
				if (action.charAt(0) == 'A' || action.charAt(0) == 'D'
						|| action.charAt(0) == 'W' || action.charAt(0) == 'S') {
					
					if(action.length()==2){
						if(action.charAt(1)>='0' && action.charAt(1)<='9'){
							isStep = true;
						}
					}else if(action.length()==3){
						if(action.charAt(2)>='0' && action.charAt(2)<='9'||
								action.charAt(2)>='0' && action.charAt(2)<='9'){
							isStep = true;
						}
					}
				}
			}
			if(isStep){
				moveOneStep(action);
			}
		}
	}
	
	public void printPos(){
		System.out.println(String.valueOf(x)+","+String.valueOf(y));
	}
	
	public static void main(String args[]) throws IOException {
		Main m = new Main();
		Scanner in = new Scanner(System.in);
		String inStr;
		while (in.hasNextLine()) {
			inStr = in.nextLine();
			m.reset();
			m.startMove(inStr);
			m.printPos();
		}
	}
}