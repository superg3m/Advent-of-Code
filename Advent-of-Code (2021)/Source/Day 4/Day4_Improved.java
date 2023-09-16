import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Day4_Improved {
    public static void main(String[] args) {
        String[] currentNumber = "93,18,74,26,98,52,94,23,15,2,34,75,13,31,39,76,96,16,84,12,38,27,8,85,86,43,4,79,57,19,40,59,14,21,35,0,90,11,32,17,78,83,54,42,66,82,99,45,55,63,24,5,89,46,80,49,3,48,67,47,50,60,81,51,71,33,72,6,9,30,56,20,77,29,28,69,25,36,91,92,65,22,62,58,64,88,10,7,87,41,44,37,73,70,68,97,61,95,53,1".split(",");
        ArrayList<String[][]> winningBoards = new ArrayList<>();

        // Scans text file
        ArrayList<String[]> fileData = ScanTextFile();

        // Generates all the boards
        ArrayList<String[][]> allBingoBoards = GenerateBoards(fileData);

        String[][] winningBoard;

        String[] numb = new String[allBingoBoards.size()];

        int index = 0;

        Scanner question = new Scanner(System.in);
        System.out.print("Do you want the numbers to be random | yes or no: ");
        String ans = question.nextLine();
        if(ans.equals("yes")) RandomizeBallNumberArray(currentNumber);
        question.close();

        for (String s : currentNumber) {
            for (int i = 0; i < allBingoBoards.size(); i++) {
                int boardNumber = allBingoBoards.indexOf(allBingoBoards.get(i));

                MarkBoardsWithX(allBingoBoards.get(i), s);

                winningBoard = CheckBoard(allBingoBoards.get(i), s);

                if(winningBoard != null && !winningBoards.contains(winningBoard)) {
                    winningBoards.add(winningBoard);
                    allBingoBoards.remove(boardNumber);
                    numb[index] = s;
                    index++;
                    i--;
                }
            }
        }

        for(int i = 0; i < winningBoards.size(); i++) {
            String[] temp = CalculateAnswer(winningBoards.get(i), numb[i]).split(" ");
            String factors = temp[0];
            int answer = Integer.parseInt(temp[1]);
            for(int j = 0; j < 5; j++) {
                System.out.println(Arrays.toString(winningBoards.get(i)[j]));
            }
            System.out.println(factors + " --> " + answer + " | Board# " + (i+1) + " | Winning#: " + numb[i]);
            System.out.println(" ");
        }
    }

    // ============== SCANS THE TEXT FILE ==============
    public static ArrayList<String[]> ScanTextFile() {
        File file = new File("../../Resource/Day4.txt");
        ArrayList<String[]> data = new ArrayList<>();
        Scanner scan;

        try {
            scan = new Scanner(file);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        // Reads the file until no lines are left
        while (scan.hasNextLine()) {
            // Removes the WhiteSpace using regex EX: (1,     2, 3) --> (1, 2, 3)
            String[] currentLine = scan.nextLine().trim().replaceAll(" +", " ").split(" ");
            // If the line contains data copy it
            if(!currentLine[0].equals("")) data.add(currentLine);
        }

        // Closes the Scanner
        scan.close();

        // Returns data from text file
        return data;
    }

    // ============== RANDOMIZES THE BALL NUMBERS ==============
    public static String[] RandomizeBallNumberArray(String[] currentNumber) {
        String[] ret = currentNumber;
        for (int i = 0; i < ret.length; i++) {
            Random rand = new Random();
            int randomIndexToSwap = rand.nextInt(ret.length);
            int temp = Integer.parseInt(ret[randomIndexToSwap]);
            ret[randomIndexToSwap] = ret[i];
            ret[i] = String.valueOf(temp);
        }
        System.out.println(Arrays.toString(ret));
        return ret;
    }

    // ============== GENERATES THE BINGO BOARDS ==============
    public static ArrayList<String[][]> GenerateBoards(ArrayList<String[]> fileData) {
        ArrayList<String[][]> boards = new ArrayList<>();
        for (int i = 0; i < fileData.size();) {
            if(fileData.get(i)[0].equals("NEXT_BOARD")) continue;
            String[][] singleBoard = new String[5][5];
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    singleBoard[j][k] = fileData.get(i)[k];
                }
                i++;
            }

            boards.add(singleBoard);
        }
        return boards;
    }

    // ============== MARKS THE BINGO CARD WITH X ==============
    public static void MarkBoardsWithX(String[][] board, String s) {
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (board[row][col].equals(s)) {
                    board[row][col] = "x";
                }
            }
        }
    }

    // ============== CHECKS THE BINGO CARD ==============
    public static String[][] CheckBoard(String[][] board, String s) {
        // Declare xCount variable
        int xCount;

        // CHECKS ROWS
        for (int row = 0; row < 5; row++) {
            xCount = 0;
            for (int col = 0; col < 5; col++) {
                if (board[row][col].equals("x")) xCount++;
                if(xCount == 5) return board;
            }
        }

        // CHECKS COLUMNS
        for (int col = 0; col < 5; col++) {
            xCount = 0;
            for (int row = 0; row < 5; row++) {
                if (board[row][col].equals("x")) xCount++;
                if(xCount == 5) return board;
            }
        }

        return null;
    }

    // ============== Calculates THE ANSWER ==============
    public static String CalculateAnswer(String[][] board, String s) {
        int sum = 0;
        int answer;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (!board[row][col].equals("x")) sum += Integer.parseInt(board[row][col]);
            }
        }
        answer = sum * Integer.parseInt(s);
        return String.valueOf(sum) + "*" + s + " " + String.valueOf(answer);
    }
}