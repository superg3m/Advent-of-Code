import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day1_1 {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\superg3m\\eclipse-workspace\\AdventofCode (2020)\\src\\Day1.txt");
		ArrayList<Integer> dataSet = new ArrayList<Integer>();
		
		try {
			Scanner scan = new Scanner(file);
			while(scan.hasNextLine()) {
				int data = scan.nextInt();
				dataSet.add(data);
				for(int i = 0; i < dataSet.size(); i++) {
					if(dataSet.contains(2020 - dataSet.get(i))) {
						System.out.println((2020 - dataSet.get(i)) * dataSet.get(i));
						System.exit(0);
					}
				}
			}
	
		} catch (FileNotFoundException e) {
			System.out.println("Err");
		}
	}
}