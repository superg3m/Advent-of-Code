import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day2_1 {
    public static void main(String[] args) {
        File file = new File("../../Resource/Day2.txt");
        int xPos = 0;
        int yPos = 0;
        try {
            Scanner scan = new Scanner(file);
            
            while(scan.hasNextLine()) {
                String data = scan.nextLine();
                String direction = data.split(" ", 2)[0];
                String numS = data.split(" ", 2)[1];
                int num = Integer.parseInt(numS);
                if(direction.equals("down")) {
                    yPos += num;
                }
                if(direction.equals("up")) {
                    yPos -= num;
                }
                if(direction.equals("forward")) {
                    xPos += num;
                }
            }
            scan.close();
            int result = xPos * yPos;
            System.out.println("x: " + xPos);
            System.out.println("y: " + yPos);
            System.out.println("final: " + result);
        } catch (FileNotFoundException e) {
            System.out.println("Err");
        }
    }
}