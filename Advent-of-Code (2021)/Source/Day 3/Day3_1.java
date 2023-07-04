import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day3_1 {
	public static void main(String[] args) {
		File file = new File("../../Resource/Day3.txt");
		ArrayList<String> data = new ArrayList<String>();
		String gamma = "";
		String epsilon = "";
		int counter = 0;
		try {
			Scanner scan = new Scanner(file);
			while(scan.hasNextLine()) data.add(scan.nextLine());
			for(int i = 0; i < data.get(0).length(); i++) {
				for(int j = 0; j < data.size(); j++) {
					String current = data.get(j);
					if(current.charAt(i) == '1') {
						counter++;
					}
				}
				if(counter > data.size()/2) {
					gamma += "1";
				}
				else {
					gamma += "0";
				}
				
				if(counter < data.size()/2) {
					epsilon += "1";
				}
				else {
					epsilon += "0";
				}
				counter = 0;
			}
			scan.close();
			int g = Integer.parseInt(gamma, 2);
			int e = Integer.parseInt(epsilon, 2);
			int p = g * e;
			System.out.println(g + " * " + e + " = " + p);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
