import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Day4_2 {

	public static void main(String[] args) {
	    try{
	      File input = new File("C:\\Users\\superg3m\\eclipse-workspace\\AdventofCode (2021)\\src\\Day4.txt");
	      Scanner scan = new Scanner(input);

	      String stuff = "";
	      
	      String nxtln;
	      
	      while(scan.hasNextLine()) {
	    	  nxtln = scan.nextLine();
	    	  if(nxtln.equals("")) stuff += "KYLE KRAUSE";
	    	  else stuff += nxtln + "delete this";
	      }
	      System.out.println("done scanning" + stuff);
	      scan.close(); 

	      String[] nums = stuff.split("KYLE KRAUSE");
	      playbingo(nums);

	    } catch(FileNotFoundException e){
	      System.out.println("err");
	    }
	  }

	  public static void playbingo(String[] nums){
		  System.out.println("playing bingo");
		  int points = 0;
		  //boolean inside; //for winning numbers, so we don't end up checking boards when they're full

      /***** NUMBERS TO PLAY BINGO WITH *****/
      nums[0].replaceAll("delete this", "");
		  String[] pickstr = nums[0].split(",");

      /***** BINGO BOARDS *****/
		  ArrayList<ArrayList<String>> boards = new ArrayList<ArrayList<String>>();

      ArrayList<String> nonew = new ArrayList<String>();
      for(int i = 1; i < nums.length; i++){
        nonew.add(nums[i].replaceAll("delete this", " "));
      }
      
      String[] nospace = new String[nonew.size()];
      for(int i = 0; i < nonew.size(); i++) nospace[i] = nonew.get(i);
		  for(int i = 0; i < nospace.length; i++) {
        boards.add(new ArrayList<String>(Arrays.asList(nospace[i].split(" "))));
      }

		  for(int i = 0; i < boards.size(); i++) {
			  for(int j = 0; j < boards.get(i).size();) {
				  if(boards.get(i).get(j).equals("")) {
					  boards.get(i).remove(j);
				  }
				  else j++;
			  }
		  }

      /***** CACHE BOARDS(for points) *****/
		  ArrayList<ArrayList<String>> cachedboards = new ArrayList<ArrayList<String>>();
		  //this part so that cachedboards isn't a reference to boards at all, so it doesn't change with it
		  for(int i = 0; i < boards.size(); i++) {
			  cachedboards.add(new ArrayList<String>());
			  for(int j = 0; j < boards.get(i).size(); j++) {
				  cachedboards.get(i).add(boards.get(i).get(j));
			  }
		  }
		  
      /***** GOING THROUGH LIST OF NUMBERS TO PICK, FINDING FIRST WINNER *****/
		  boolean[] haswon = new boolean[boards.size()];
		  for(int i = 0; i < haswon.length; i++) {
			  haswon[i] = false;
		  }
		  
		  for(int i = 0; i < pickstr.length; i++){
			  for(int j = 0; j < boards.size(); j++) {
				  if(!haswon[j]) {
					  points = checkboard(boards.get(j), cachedboards.get(j), pickstr[i]);
					  if(points != 0) {
						  System.out.println(points);
						  haswon[j] = true;
						  //break;
				  	}
				  }
			  }
			  if(points != 0) break; 
		  }
		  
		  
		/***** END OF METHOD *****/
	  }

	  
	  
	  
	  
	  
	  
	  
	  public static int checkboard(ArrayList<String> board, ArrayList<String> cboard, String numstr){
		  //go through the board and add an x where the picked number is
		  boolean addedone = false;
		  for(int i = 0; i < board.size(); i++){
			  if(board.get(i).equals(numstr)){
				  board.set(i, "x");
				  addedone = true;
				  break;
	      		}
		  }
		  
		  
		  //if we added an x
		  ArrayList<String> winner = new ArrayList<String>();
		  int ret = 0;
		  boolean inside = false;

		  
		  if(addedone){
			  winner = checkrowsandcols(board, cboard);
			  if(!winner.get(0).equals("a")) {
				  for(int i = 0; i < winner.size(); i++) {
					  if(winner.get(i).equals(numstr)) {
						  inside = true;
						  break;
					  }
				  }
				  //inside = true;
				  
				  if(inside) {
					  System.out.println(winner + " winning number: " + numstr);
					  for(int i = 0; i < board.size(); i++) {
						  if(!board.get(i).equals("x")) ret += Integer.parseInt(board.get(i));
					  }
					  System.out.println(ret + "*" + numstr);
					  ret *= Integer.parseInt(numstr);
					  inside = false;
				  }
				  else ret = 0;
			  }
		  }
	    
		  return ret;
	  }

	  public static ArrayList<String> checkrowsandcols(ArrayList<String> board, ArrayList<String> cboard){
		  int columnind = 0;
		  int rowind = 0;
		  boolean colfull;
		  boolean rowfull;
		  ArrayList<String> col = new ArrayList<String>();
		  ArrayList<String> row = new ArrayList<String>();

		  for(int i = 0; i < board.size(); i++){
			  //if we have an x, check this row and this column
			  if(board.get(i).equals("x")) {
				  //adding all of the numbers in each column
				  columnind = i % 5;
				  rowind = 5 * (int)((i * 2) / 10);
				  for(int j = 0; j < 5; j++){
					  col.add(board.get(columnind + (5 * j)));
					  row.add(board.get(rowind + j));
				  }
				  
				  //checking if everything is the same in the given columns/rows
				  colfull = isAllSame(col);
				  rowfull = isAllSame(row);
				  
				  //if so, return the numbers of the full column
				  if(colfull) {
					  col = new ArrayList<String>();
					  for(int j = 0; j < 5; j++) {
						  col.add(cboard.get(columnind + (5 * j)));
					  }
					  return col;
				  }
				  else if(rowfull) {
					  row = new ArrayList<String>();
					  for(int j = 0; j < 5; j++) {
						  row.add(cboard.get(rowind + j));
					  }
					  return row;
				  }

			  }
			  col = new ArrayList<String>();
			  row = new ArrayList<String>();
		  }
		  //if no winner, give dummy alist
		  ArrayList<String> ret = new ArrayList<String>();
		  ret.add("a");
		  return ret;
	  }

	  public static boolean isAllSame(ArrayList<?> list){
		  Object first=list.get(0);
		  for(int i=1;i<list.size();i++){
			  if(!list.get(i).equals(first))return false;
		  }
		  return true;
	  }

}