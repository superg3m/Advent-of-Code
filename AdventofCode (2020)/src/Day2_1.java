import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day2_1 {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\superg3m\\eclipse-workspace\\AdventofCode (2020)\\src\\Day2.txt");
		int valid = 0;
		try {
			Scanner scan = new Scanner(file);
			while(scan.hasNextLine()) {
				int occur = 0;
				String data = scan.nextLine();
				String requiremnts = data.split(":", 2)[0];
				String password = data.split(": ", 2)[1];
				
				String min_max = requiremnts.split(" ", 2)[0];	
				String minS = min_max.split("-", 2)[0];
				String maxS = min_max.split("-", 2)[1];

				int min = Integer.parseInt(minS);
				int max = Integer.parseInt(maxS);
				
				String letter = requiremnts.split(" ", 2)[1];
				
				for(int i = 0; i < password.length(); i++) {
					if(String.valueOf(password.charAt(i)).equals(letter)) {
						occur++;
					}
				}
				if(occur >= min && occur <= max) {
					valid++;
				}
			}
			System.out.println(valid);
	
		} catch (FileNotFoundException e) {
			System.out.println("Err");
		}
	}
}