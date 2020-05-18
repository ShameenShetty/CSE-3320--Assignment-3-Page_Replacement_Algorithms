/*
* Name:	Shameen Shetty
* ID #:		1001429743
* Replacement Assignment
* Description: Implements the FIFO, Optimal, MFU, and LRU page-replacement algorithms
* to count the number of page faults for a given data of pages and returns the
* number of page faults, for each algorithm used
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024


/*
*	Function: FIFO
*
*	Parameters: 1) line - a pointer to a char, which represents the line that is
* read using fgets.
* 2) NumOfElems - an integer which represents the number of
* pages that are present.
* 3) pgArray an array  of ints, which stores all the 
* pages.
*
*	Returns: An int value of the pageFaults
*
*	Description: This function calculates the number of pageFaults
*	for a given input, using the FIFO Algorithm. That is First In First Out
* where we keep track of all the pages in memory, in an array, and the oldest
* array (first in) is in the front of the array. When we need to replace a page
* we remove the oldest on, hence First In (oldest page), is First Out (replaced)
*/
int FIFO(char * line, int NumOfElems, int pgArray[]) {
  int pageFaults = 0;
  int pageTableSize = line[0] - '0';
  int counter = 0;
  int pageFrame[50];
  int isAvailable;
  
  int position = 0;
  int i;
  int j;
  for (i = 0; i < NumOfElems; i++)
  {
        isAvailable = 0;
        for (j = 0; j < pageTableSize; j++) {
              if (pageFrame[j] == pgArray[i])
                    isAvailable = 1;
        }
        if (isAvailable == 0)
        {
              pageFrame[position] = pgArray[i];
              position = (position + 1) % pageTableSize;
              pageFaults++;
        }
  }

	printf("Page faults of FIFO: %d\n", pageFaults);
	return pageFaults;
}



/*
*	Function: LRU
*
*	Parameters: 1) line - a pointer to a char, which represents the line that is
* read using fgets.  2) NumOfElems - an integer which represents the number of
* pages that are present. 3) pgArray an array  of ints, which stores all the 
* pages.
*
*	Returns: An int value of the pageFaults
*
*	Description: This function calculates the number of pageFaults
*	for a given input, using the LRU Algorithm. That is, the Least
* Recently Used algorithm is where we replace the page that is
* the Least Recently Used.
*/
int LRU(char * line, int NumOfElems, int pgArray[]) {
  int pageFaults = 0;
  int pageTableSize = line[0] - '0';
  int pageFrame[4];

  int i, j, k;
  for(i = 0; i < NumOfElems; i++) {
    //the current page we are on, we can use this for comparision
    int currentPage = pgArray[i];

    /**
     * First we are filling up the table with the pages,
     * and because the table is empty, there will be page faults 100%
     * of the time, hence we increment pageFaults by 1.
     */
    if(i < pageTableSize) {
        pageFrame[i] = currentPage;
        pageFaults++;
      }
      
    //This var will check for duplicate pages
    int isAvailable = 0;
    for (j = 0; j < pageTableSize; j++) {
      int frame_Page = pageFrame[i];
      
      //If a duplicate page exists, isAvailible = 1
      if (frame_Page == currentPage) {
        isAvailable = 1;
      }
    }
    
    // This means that if there are no duplicates
    if(isAvailable == 0) {
      int counter = 0;
      int position = 0;

      // We have to go backwards and compare each page with the previous one
      // to see which one is the furthest away, hence we start from k, where k
      // is the current position, and we go backwards, hence k--
      for (k = i; k >= 0; k--) {
        // we are getting the page at position k, and backwards
        // and put it into an int called testPage (not the best name)
        int testPage = pgArray[k];
        int l;
        
        // For this for-loop we go over the pageFrame, and compare each val
        // with testPage, and if we hit a match, we increase the counter
        
        for(l = 0; l < pageTableSize; l++) {
          if(testPage == pageFrame[l]) {
            counter++;
          }
        }
        
        // If counter == pageTableSize meaning we searched the entire pageTableSize
        // and got a match, then we set position = k, meaning the furthest page
        // is at position k.
        // Then we get the page we need to replace, and search our pageFrame
        // to see where that page is, and once we find it, we replace the page with the
        // current page, and increase our page fault by one, since we are in the if-loop
        // of isAvailible == 0, meaning we dont have an existing page, and thus have a 
        // page miss.
        if(counter == pageTableSize) {
          position = k;
          int pageToBeReplaced = pgArray[position];
          for(l = 0; l < pageTableSize; l++) {
            if(pageFrame[l] == pageToBeReplaced) {
              pageFrame[l] = currentPage;
              pageFaults++;
            }
          }
        }
      }
    }
  }

  printf("Page faults of LRU: %d\n", pageFaults);
  return pageFaults;
}


/*
*	Function: MFU
*
*	Parameters: 1) line - a pointer to a char, which represents the line that is
* read using fgets.  2) NumOfElems - an integer which represents the number of
* pages that are present. 3) pgArray an array  of ints, which stores all the 
* pages.
*
*	Returns: An int value of the pageFaults
*
*	Description: This function calculates the number of pageFaults
*	for a given input, using the MFU Algorithm. That is, the Most
* Frequently Used algorithm, where we replace the page that is the
* Most Frequently Used.
*/
int MFU(char * line, int NumOfElems, int pgArray[]) {
	int pageFaults = 0;
	int pageTableSize = line[0] - '0';
	int counter = 0;
    
	printf("Page faults of MFU: %d\n", pageFaults);
	return pageFaults;
}


/*
*	Function: Optimal
*
*	Parameters: 1) line - a pointer to a char, which represents the line that is
* read using fgets.  2) NumOfElems - an integer which represents the number of
* pages that are present. 3) pgArray an array  of ints, which stores all the 
* pages.
*
*	Returns: An int value of the pageFaults
*
*	Description: This function calculates the number of pageFaults
*	for a given input, using the Optimal Algorithm. Here we replace
* the page that is not used for the longest time.
*/
int Optimal(char * line, int NumOfElems, int pgArray[]) {
    int pageFaults = 0;
    int pageTableSize = line[0] - '0';
    int pageFrame[40];

    int i,j;
    // Since the pageFrame is currently empty, we first fill it up to its capacity
    // which is the pageTableSize (i.e working set), and because nothing was there
    // and we are adding new pages, we increment the counter.
    for(i = 0; i < pageTableSize; i++) {
        pageFrame[i] = pgArray[i];
        pageFaults++;
    }

    // checks if there is an existing page or not
    int isAvailable = 0;
    for(i = 0; i < NumOfElems; i++) {
        int currentPage = pgArray[i];

        // Here we start from the current value of i we are on, and go backwards
        // meaning, if we are on i=4 (i.e 3 pages are already there) then we go
        // back and find what pages are stored in pageFrame, and if they match the current
        // page that is being inserted, then that means it is already existing and it is a
        // page hit. Otherwise, we set isAvailible = 0, and we have a page fault.
        for(j = i; j >= 0; j--) {
            int stored_page = pageFrame[j];
            if(stored_page == currentPage) {
                isAvailable = 1;
            }
        }
        // This means that there is no existing page, and that we need to replace
        // one of our pages held in pageFrame with the new page, which is the currentPage
        // This will cause a page fault as we are replacing a page.
        
        // Here we go ahead and see what pages lie ahead, so that we can find out which page
        // is the furthest away, by comparing futurePosition to the max.
        if(isAvailable == 0) {
            int k;
            
            // we start at i+1, because we are going ahead, so there
            // is no need to compare starting from 0, or at i
            for(k = i+1; k < NumOfElems; k++) {
                int futurePage = pgArray[k];
                int futurePosition = 0;
                int max = 0;

                int temp;
                for(temp = 0; temp < pageTableSize; temp++) {
                    int current_stored_page = pageFrame[temp];
                    
                    if(futurePage == current_stored_page) {
                        futurePosition = k;
                        if(futurePosition > max) {
                            max = futurePosition;
                        }
                    }
                }

                int pageToBeReplaced = pgArray[max];
                for(temp = 0; temp < pageTableSize; temp++) {
                    if(pageToBeReplaced == pageFrame[temp]) {
                        pageFrame[temp] = currentPage;
                        pageFaults++;
                    }
                }
            }
        }
    }



	printf("Page faults of Optimal: %d\n", pageFaults);
	return pageFaults;
}




int main( int argc, char * argv[] ) 
{
  char * line = NULL;
  size_t line_length = MAX_LINE;
  char * filename;

  FILE * file;

  if( argc < 2 )
  {
    printf("Error: You must provide a datafile as an argument.\n");
    printf("Example: ./fp datafile.txt\n");
    exit( EXIT_FAILURE );
  }

  filename = ( char * ) malloc( strlen( argv[1] ) + 1 );
  line     = ( char * ) malloc( MAX_LINE );

  memset( filename, 0, strlen( argv[1] + 1 ) );
  strncpy( filename, argv[1], strlen( argv[1] ) );

  printf("Opening file %s\n", filename );
  file = fopen( filename , "r");

  if ( file ) 
  {
  	/**
     * NumOfElems is the number of pages that are in the text file, per line. We
     * use this to keep track of how many pages there are, which is important in
     * our algorithms.
     * 
     * pgArray is the array of integers that will store all the pages.
     */
  	int NumOfElems = 0;
    int pgArray[MAX_LINE];


    while ( fgets( line, line_length, file ) )
    {
      char * token;
      token = strtok( line, " ");
      int working_set_size = atoi( token );

      printf("\nWorking set size: %d\n", working_set_size );
 
      while( token != NULL )
      {
        token = strtok( NULL, " " );
        
        if( token != NULL )
        {
           // We add the pages - which have been converted to an int - 
           // to our pgArray
           pgArray[NumOfElems] = atoi( token );
           // increment the counter by one, as we have added a page
           NumOfElems++;
        }
      }
      printf("\n");

      /**
       * Setting up our page-replacement algorithm functions, which will
       * calculate the number of page faults, and print out the result.
       * We use line, NumOfElems, and pgArray as the inputs for our functions.
       */
      FIFO(line, NumOfElems, pgArray);
      LRU(line, NumOfElems, pgArray);
      MFU(line, NumOfElems, pgArray);
      Optimal(line, NumOfElems, pgArray);

      /*
       *  For the below line of code, we are setting numofelems to zero so that
       *  once we go over one set of data, and move on to the next line, we
       *  will overwrite the previous data, rather than trying to keep track
       *  of where the first pg numbers are where the next are, etc.
       */
      NumOfElems = 0;
    }

    free( line );
    fclose(file);
  }

  return 0;
}
