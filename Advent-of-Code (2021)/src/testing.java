import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class testing {

	public static void main(String[] args) {

        ArrayList<String[]> bingoCardMarked = new ArrayList<>();
        ArrayList<String[]> bingoCardUnmarked = new ArrayList<>();
        int index = 0;

		ArrayList<String> dataFromFile = new ArrayList<>();
        
		scanFile(dataFromFile);
		String[] currentBallArray = returnBallNumberArray(dataFromFile, bingoCardMarked, bingoCardUnmarked);
		
		
		while(index != currentBallArray.length) {
			markBingoCardWithX(bingoCardMarked, currentBallArray, index);
			if(checkBingoCard(bingoCardMarked, bingoCardUnmarked, currentBallArray, index)) break;
			index++;
		}
	}

	static void scanFile(ArrayList<String> dataFromFile) {
		File file = new File("C:\\Users\\superg3m\\eclipse-workspace\\AdventofCode (2021)\\src\\Testing.txt");
		Scanner scan = null;

		try {
			scan = new Scanner(file);
            
			// Reads the file until no lines are left
			while(scan.hasNextLine()) {
                String currentFileLine = scan.nextLine().trim().replaceAll(" +", " ");
				dataFromFile.add(currentFileLine);
			}
		} catch(Exception e) {

			e.printStackTrace();
		} finally {

			// Closes the Scanner
            if(scan != null) scan.close();
        }

		// Removes the WhiteSpace EX: (1,     2, 3) --> (1, 2, 3)
        for(int i = 0; i < dataFromFile.size(); i++) {
			if(dataFromFile.get(i).equals("")) dataFromFile.set(i, "====Next_CARD====");
		}
	}

	// ============== Returns THE BALL NUMBERS FROM DATAFILE ==============
	static String[] returnBallNumberArray(ArrayList<String> dataFromFile, ArrayList<String[]> bingoCardMarked, ArrayList<String[]> bingoCardUnmarked) {
	
		// Bingo balls to play with
		String[] nums = dataFromFile.get(0).split(",");

		// Removes the playing numbers from ArrayList
		dataFromFile.remove(0);

		// Adds the data file to the bingoCard and turns the Strings into String[] via Split
		for(int i = 0; i < dataFromFile.size(); i++) {
			bingoCardMarked.add(dataFromFile.get(i).split(" "));
			bingoCardUnmarked.add(dataFromFile.get(i).split(" "));
		}

		return nums;
	}

	// ============== RANDOMIZES THE BALL NUMBERS ==============
	static void randomizeBallNumberArray() {
		// Doing stuff
	}

	// ============== MARKS THE BINGO CARD WITH X ==============
	static void markBingoCardWithX(ArrayList<String[]> bingoCardMarked, String[] currentBallArray, int index) {
		for(int i = 0; i < bingoCardMarked.size(); i++) {
			for(int j = 0; j < bingoCardMarked.get(i).length; j++) {
				if(bingoCardMarked.get(i)[j].equals(currentBallArray[index])) bingoCardMarked.get(i)[j] = "x";
			}
		}
		System.out.println(Integer.parseInt(currentBallArray[index]));
	}
	
	// ============== CHECKS THE BINGO CARD ==============
	static boolean checkBingoCard(ArrayList<String[]> bingoCardMarked, ArrayList<String[]> bingoCardUnmarked, String[] currentBallArray, int index) {
		int xCount = 0;
		boolean winner = false;
		// CHECK ROWS
		
		row:
		for(int i = 0; i < bingoCardMarked.size(); i++) {
			String[] row = bingoCardMarked.get(i);
			xCount = 0;
			for(int j = 0; j < bingoCardMarked.get(i).length; j++) {
				if(!row[j].equals("x")) break;
				else {
					xCount++;
				}
				if(xCount == row.length) {
					winner = true;
					while(true) {
						if(!bingoCardMarked.get(i)[0].equals("====Next_CARD====")) {
							i--;
						}
						else {
							int done = 0;
							j = 0;
							for(int k = i+1; k < i+6;) {
								System.out.println("winning: " + Arrays.toString(bingoCardMarked.get(k)) + " "  + Arrays.toString(bingoCardUnmarked.get(k)));
								while(true) {
									if(j == 5) {
										j = 0;
										k++;
										break;
									}
									if(!bingoCardMarked.get(k)[j].equals("x")) {
										String numS = bingoCardMarked.get(k)[j];
										int NUM = Integer.parseInt(numS);
										done += NUM;
									}
									j++;
								}
							}
							Scanner scan = new Scanner(System.in);
							String userInput;
							System.out.println("Do you want to see your final Score?");
							System.out.print("Type 'yes' otherwise type anything else: ");
							userInput = scan.next();
							userInput = userInput.toLowerCase();
							if(userInput.equals("yes")) {
								System.out.print(done * Integer.parseInt(currentBallArray[index]));
							}
							else {
								System.out.println("done");
							}
							scan.close();
							break row;
						}
					}
				}
			}
		}
		
		// CHECKS COLUMN
		column:
		for(int j = 0; j < 5; j++) {
			xCount = 0;
			for(int i = 0; i < bingoCardMarked.size(); i++) {
				if(bingoCardMarked.get(i).length == 1) {
					xCount = 0;
					continue;
				}
				if(!bingoCardMarked.get(i)[j].equals("x")) {
					continue;
				}
				else {
					xCount++;
				}
				if(!bingoCardMarked.get(i)[j].equals("x")) break;

				else {
					xCount++;
				}
				if(xCount == bingoCardMarked.get(i).length) {
					while(true) {
						if(!bingoCardMarked.get(i)[j].equals("Next_Board")) {
							i--;
						}
						else {
							int done = 0;
							j = 0;
							for(int k = i+1; k < i+6;) {
								System.out.println("winning: " + bingoCardMarked.get(k) + " "  + bingoCardUnmarked.get(k));
								while(true) {
									if(j == 5) {
										j = 0;
										k++;
										break;
									}
									if(!bingoCardMarked.get(k)[j].equals("x")) {
										String numS = bingoCardMarked.get(k)[j];
										int NUM = Integer.parseInt(numS);
										done += NUM;
									}
									j++;
								}
							}
							Scanner scan = new Scanner(System.in);
							String userInput;
							System.out.println("Do you want to see your final Score?");
							System.out.print("Type 'yes' otherwise type anything else: ");
							userInput = scan.next();
							userInput = userInput.toLowerCase();
							if(userInput.equals("yes")) {
								System.out.print(done * Integer.parseInt(currentBallArray[index]));
							}
							else {
								System.out.print("done");
							}
							scan.close();
							break column;
						}
					}
				}
			}  
		}
		
		return winner;
	}

    static int calculateAnswer(ArrayList<String[]> bingoCardMarked, String[] currentBallArray, int rowIndex, int index) {
        int answer = 0;
        for (int i = rowIndex; i < bingoCardMarked.size(); i++) {
            for (int j = 0; j < bingoCardMarked.get(i).length; j++) {
                if(!bingoCardMarked.get(i)[j].equals("====Next_CARD====")) {
					i--;
				}
				else {
					if(!bingoCardMarked.get(i)[j].equals("x")) {
						answer += Integer.parseInt(bingoCardMarked.get(i)[j]);
						System.out.println(answer);
					}
				}
            }
        }
        answer = answer * Integer.parseInt(currentBallArray[index]);
        return answer;
    }
}