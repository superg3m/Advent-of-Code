import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day1_1 {
	public static void main (String[] args) {
		int previous = Integer.MAX_VALUE;
		File file = new File("../../Resource/Day1.txt");
		int occur = 0;
		try {
			Scanner scan = new Scanner(file);
			while(scan.hasNextLine()) {
				int current = scan.nextInt();
				if(current > previous) {
					occur++;
				}
				previous = current;
			}
			scan.close();
			System.out.println(occur);
		} catch (FileNotFoundException e) {
			System.out.println("Err");
		}
	}
}