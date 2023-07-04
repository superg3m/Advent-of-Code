import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day1_2 {
	public static void main (String[] args) {
		File file = new File("../../Resource/Day1.txt");
		ArrayList<Integer> dataSet = new ArrayList<Integer>();
		ArrayList<Integer> done = new ArrayList<Integer>();
		int occur = 0;
		try {
			Scanner scan = new Scanner(file);
			while(scan.hasNextLine()) {
				int current = scan.nextInt();
				dataSet.add(current);
			}
			for(int i = 0; i < dataSet.size()-2; i++) {
				int sum = dataSet.get(i) + dataSet.get(i+1) + dataSet.get(i+2);
				done.add(sum);
			}
			for(int i = 0; i < done.size()-1; i++) {
				if(done.get(i+1) > done.get(i)) {
					occur++;
				}
			}
			scan.close();
			System.out.println(occur);
		} catch (FileNotFoundException e) {
			System.out.println("Err");
		}
		
		
	}
}