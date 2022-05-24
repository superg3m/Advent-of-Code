import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day1_1 {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\superg3m\\eclipse-workspace\\AdventofCode (2019)\\src\\Day 1");
		ArrayList<Integer> numList = new ArrayList<Integer>();
		ArrayList<Integer> fuelRequirement = new ArrayList<Integer>();
		try {
			Scanner scan = new Scanner(file);
			while(scan.hasNextLine()) {
				int current = scan.nextInt();
				numList.add((int)Math.floor(current/3) - 2);
			}
			scan.close();
			int currentNum = 0;
			int total = 0;
			for(int i = 0; i < numList.size(); i++) {
				currentNum = numList.get(i);
				total += currentNum;
				for(int j = 0; currentNum >= 0; j++) {
					currentNum = (currentNum/3) - 2;
					if(currentNum < 0) break;
					total += currentNum;
				}
				fuelRequirement.add(total);
				total = 0;
			}
			int grandTotal = 0;
			for(int i = 0; i < fuelRequirement.size(); i++) {
				grandTotal += fuelRequirement.get(i);
				System.out.println(grandTotal);
			}
			
		} 
		catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
