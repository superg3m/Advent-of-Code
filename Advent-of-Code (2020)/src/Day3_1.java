import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day3_1 {
    public static void main(String[] args) {
        int pos = 0;
        int occur = 0;
        try {
            File file = new File("C:\\Users\\superg3m\\eclipse-workspace\\AdventofCode (2020)\\src\\Day3.txt");
            Scanner scan = new Scanner(file);
            
            ArrayList<String> data = new ArrayList<String>();
            String s = "";
            
            while(scan.hasNextLine()) data.add(scan.nextLine());
            
            for(int i = 0; i < data.size()-1; i++) {
            	pos+=3;
            	try {
            		s = data.get(i);
					if(s.charAt(pos) == '#') {
						occur++;
						System.out.println(s + "(" + occur + ")");
					}
					s = data.get(i+1);
					if(s.charAt(pos) == '#') {
						occur++;
						System.out.println(s + "(" + occur + ")");
					}
					
				} 
            	catch (Exception e) {
            		break;
				}
            }
         
            System.out.println(occur);
            
        } catch(FileNotFoundException e) {
            System.out.println("err");
        }
    }
}
