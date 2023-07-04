import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day2_2 {
    public static void main(String[] args) {
        File file = new File("../../Resource/Day2.txt");

        int xPos = 0;
        int yPos = 0;
        int aim = 0;
        try {
            Scanner scan = new Scanner(file);
            
            while(scan.hasNextLine()) {
                String data = scan.nextLine();
                String direction = data.split(" ", 2)[0];
                String numS = data.split(" ", 2)[1];
                int num = Integer.parseInt(numS);
                if(direction.equals("down")) {
                    aim += num;
                }
                if(direction.equals("up")) {
                    aim -= num;
                }
                if(direction.equals("forward")) {
                    yPos += (num * aim);
                    xPos += num;
                }
                System.out.println(data + " | aim: " + aim + " = " + yPos);
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