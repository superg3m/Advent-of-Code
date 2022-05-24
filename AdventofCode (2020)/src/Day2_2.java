import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day2_2 {
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
				
				if(String.valueOf(password.charAt(min-1)).equals(letter) && !String.valueOf(password.charAt(max-1)).equals(letter)) {
					valid++;
				}
				if(!String.valueOf(password.charAt(min-1)).equals(letter) && String.valueOf(password.charAt(max-1)).equals(letter)) {
					valid++;
				}			
			}
			System.out.println(valid);
	
		} catch (FileNotFoundException e) {
			System.out.println("Err");
		}
	}
}
