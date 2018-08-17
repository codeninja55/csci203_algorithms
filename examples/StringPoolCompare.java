import java.lang.Math; 

//	This simple program implements a string pool with three words to demonstrate word comparison and printing.
//
//	Methods are implemented to:
//
//				1.	compare two words in the pool
//				2.	print a word from the pool
//
//	Both of these methods are used inside the printWordOrder method.
//
//	NOTE: the words are hard-coded (this is not ideal but will do for this example). 
//        In a real-world application, the pool would be created from an input file by sequentially 
//        processing characters. E.g. by using a fileInputStream object.
//
//	NOTE: this example used a lot of nested array access inside the inner loops. This is not efficient!
//		  It was done to make it clear exactly what was going on in the program.
//		  Fixing this is left as an exercise for the reader. (Hint: use local variables)
//
// Authors I. Piper, A. Piper.

public class StringPoolCompare
{

  public static void main(String[] args)
  {
    char pool[] = new char[1000];
    int start[] = new int[10];
    
    start[0]=0;    
    
    pool[0]='a';
    pool[1]='c';
    pool[2]='t';
    pool[3]='s';

    start[1]=4;
    
    pool[4]='a';
    pool[5]='n';
    pool[6]='t';
    
    start[2]=7;
    
    pool[7]='a';
    pool[8]='c';
    pool[9]='t';
    
    start[3]=10;
     
    printWordOrder(0,1,start, pool);
    printWordOrder(0,2,start, pool);
    printWordOrder(1,1,start, pool);
  } 
  
  // This method prints two words from the pool, specified by word1 and word2, with 
  // 	an indication of their relative lexical order.
  //
  public static void printWordOrder(int word1, int word2, int start[], char pool[])
  {
    int order;
    
    order = compareWord(word1,word2,start,pool);
   	printWord(word1,start,pool);
    if (order < 0)
   		System.out.print(" is less than ");
    else if (order == 0)
      	System.out.print(" is equal to ");
    else
    	System.out.print(" is greater than ");
    printWord(word2,start,pool);
    System.out.println();
    
  }
  
  // This method compares two words in the string pool and returns an integer:
  //	-1 if the first word is lexically less than the second
  //	0  if the two words are identical
  //	+1 if the first word is lexically greater than the second
  //
  public static int compareWord(int word1, int word2, int[] start, char[] pool)
  {
    int length1, length2;
    int i;
    
    length1=start[word1+1]-start[word1];
    length2=start[word2+1]-start[word2];
    
    // Only compare as many characters as the length of the shortest word
    
    for (i=0; i < Math.min(length1, length2); i++)
    {  
      if (pool[start[word1]+i] < pool[start[word2]+i])
      	return -1;
      if (pool[start[word1]+i] > pool[start[word2]+i])
        return 1;
    } 
    
    // the substrings we have compared so far are equal so the shorter of the two words is smaller
    
    if (length1 < length2)
      	return -1;
    if (length1 > length2)
      	return 1;
    return 0;
  }
  
  // This method prints a word from the pool, specified by word
  //
  public static void printWord(int word, int[] start, char[] pool)
  {
    int length;
    int i;
    
    length = start[word+1]-start[word];
    
    for (i=0; i< length; i++)
      System.out.print(pool[start[word]+i]);
  }
}

