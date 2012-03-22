#include "stdafx.h"
#include "BinarySearch.h"

/*

the first x for which p(x) is true

binary_search(lo, hi, p):
   while lo < hi:
      mid = lo + (hi-lo)/2
      if p(mid) == true:
         hi = mid
      else:
         lo = mid+1
          
   if p(lo) == false:
      complain                // p(x) is false for all x in S!
      
   return lo         // lo is the least x for which p(x) is true



   The condition in the main theorem is satisfied because the array is sorted in ascending order: 
   if A[x] is greater than or equal to the target value, all elements after it are surely also greater than or equal to the target value. 

			If we take the sample sequence from before: 

			0	5	13	19	22	41	55	68	72	81	98


			With the search space (indices): 

			1	2	3	4	5	6	7	8	9	10	11


			And apply our predicate (with a target value of 55) to it we get: 

			no	no	no	no	no	no	yes	yes	yes	yes	yes


	This is a series of no answers followed by a series of yes answers, as we were expecting. 
	Notice how index 7 (where the target value is located) is the first for which the predicate yields yes, 
	so this is what our binary search will find. 

*/

int getMostWork(vector <int> folders, int workers) {
    int lo = 0, hi = 20000;
    int best = 20000;
    while (hi - lo > 1) {
      int mid = (lo+hi) / 2;
      int x = workers;
      int i = 0, j = mid;
	  //////////////////////////////////////////////////////////
	  // Testing p(mid) starts here ------------->
	  
      for (i = 0; i < folders.size() && x > 0; i++) {
        if (j < folders[i]) {
          x--;
          if (!x) break;
          j = mid - folders[i];  // This line and the next is poor code. Basically, it resets the j for testing against new worker.
          if (j < 0) break;		// A test for j is required. So.
        } else {
          j -= folders[i];
        }
      }
	  // <------------------------ Testing p(mid) ends here
	  ////////////////////////////////////////////////////////////
      if (i == folders.size()) {
		  if(best > mid)			// Now, modify best to reflect the current load.
			  best = mid;
          hi = mid;
	  }
        else 
          lo = mid;
    }
    return best;
}


 
double interestRate(double price, double monthlyPayment, int loanTerm) {
	double lo = 1e-16, hi = 1000, m;
	while (hi / lo > 1+1e-14) {
		m = (hi+lo)/2;
		double P = price;
		bool over = 0;
		//////////////////////////////////////////////////////////
		// Testing p(mid) starts here ------------->
		for (int i = 0; i < loanTerm; i++) {
			P *= 1+m;
			P -= monthlyPayment;
			if (P < 0) {
				over = 1; 
				break;
			}
		}
		// <------------------------ Testing p(mid) ends here
		////////////////////////////////////////////////////////////
		if (over) 
			lo = m;
		else 
			hi = m;
	}
	return m*100*12;
}