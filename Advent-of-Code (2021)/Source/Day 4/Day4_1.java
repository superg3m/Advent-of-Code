import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Day4_1 {
	static File file = new File("../../Resource/Day4.txt");
	static ArrayList<String> data = new ArrayList<String>();
	static ArrayList<ArrayList<String>> board = new ArrayList<ArrayList<String>>();
	static ArrayList<ArrayList<String>> placeHolder = new ArrayList<ArrayList<String>>();
	//TODO fix String numbers to be random unique numbers from day4.text
	static String nums = "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1";
	static int counter = 0;
	static String[] currentPull = nums.split(",");
	public static void main(String[] args) {
		Scanner scan;
		try {
			scan = new Scanner(file);
			while(scan.hasNextLine()) {
				data.add(scan.nextLine().trim().replaceAll(" +", " ")); // Uses a process called regex or regular expression to replace all white spaces (do more)
			}
			scan.close();
		} 
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		for(int i = 0; i < data.size(); i++) {
			String current = data.get(i);
			if(current.equals("")) {
				data.set(i, "Next_Board");
			}
			board.add(new ArrayList<String>(Arrays.asList(data.get(i).split(" "))));
			placeHolder.add(new ArrayList<String>(Arrays.asList(data.get(i).split(" "))));
		}
		bingo(currentPull);
	}
	
	public static void bingo(String[] currentPull) {
	algorithm:
		for(int count = 0; count < currentPull.length; count++) {
			for(int i = 0; i < board.size(); i++) {
				for(int j = 0; j < board.get(i).size(); j++) {
					if(board.get(i).get(j).equals(currentPull[count])) {
						board.get(i).set(j, "x");
	 				}
				}
			}
			// CHECK ROWS
			for(int i = 0; i < board.size(); i++) {
				System.out.println(board.get(i));
				for(int j = 0; j < board.get(i).size(); j++) {
					if(!board.get(i).get(j).equals("x")) {
						continue;
					}
					else {
						counter++;
					}
					if(counter == board.get(i).size()) {
						while(true) {
							if(!board.get(i).get(0).equals("Next_Board")) {
								i--;
							}
							else {
								int done = 0;
								j = 0;
								for(int k = i+1; k < i+6;) {
									System.out.println("winning: " + board.get(k) + " "  + placeHolder.get(k));
									while(true) {
										if(j == 5) {
											j = 0;
											k++;
											break;
										}
										if(!board.get(k).get(j).equals("x")) {
											String numS = board.get(k).get(j);
											int NUM = Integer.parseInt(numS);
											done += NUM;
										}
										j++;
									}
								}
								Scanner scan = new Scanner(System.in);
								String userInput;
								System.out.println("Do you want to see your final Score?");
								System.out.print("Type 'yes' otherwise type anything else: ");
								userInput = scan.next();
								userInput = userInput.toLowerCase();
								if(userInput.equals("yes")) {
									System.out.print(done * Integer.parseInt(currentPull[count]));
								}
								else {
									System.out.print("done");
								}
								scan.close();
								break algorithm;
							}
						}
					}
				}  
				counter = 0;
			}
			// CHECK COLUMNS
			for(int j = 0; j < 5; j++) {
				for(int i = 0; i < board.size(); i++) {
					if(board.get(i).size() == 1) {
						counter = 0;
						continue;
					}
					if(board.get(i).get(j).equals(currentPull[count])) {
						board.get(i).set(j, "x");
	 				}
					if(!board.get(i).get(j).equals("x")) {
						continue;
					}
					else {
						counter++;
					}
					if(counter == board.get(i).size()) {
						while(true) {
							if(!board.get(i).get(0).equals("Next_Board")) {
								i--;
							}
							else {
								int done = 0;
								j = 0;
								for(int k = i+1; k < i+6;) {
									System.out.println("winning: " + board.get(k) + " "  + placeHolder.get(k));
									while(true) {
										if(j == 5) {
											j = 0;
											k++;
											break;
										}
										if(!board.get(k).get(j).equals("x")) {
											String numS = board.get(k).get(j);
											int NUM = Integer.parseInt(numS);
											done += NUM;
										}
										j++;
									}
								}
								Scanner scan = new Scanner(System.in);
								String userInput;
								System.out.println("Do you want to see your final Score?");
								System.out.print("Type 'yes' otherwise type anything else: ");
								userInput = scan.next();
								userInput = userInput.toLowerCase();
								if(userInput.equals("yes")) {
									System.out.print(done * Integer.parseInt(currentPull[count]));
								}
								else {
									System.out.print("done");
								}
								scan.close();
								break algorithm;
							}
						}
					}
				}  
				counter = 0;
			}
		}		
	}
}