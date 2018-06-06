


  Introduction:

  This digital convolution algorithm replace each element in a  multi-dimensional grid by a weighted sum of its neighbors. The serial code is written in C and parallelized with OpenMP. Two 2D arrays (x, y) were defined. (x) was Initialized with random numbers between 0 and 1. The elements of the second array (y) were derived from (x) by smoothing over the elements using the constants a, b and c. We then counted the elements that are smaller than a threshold t in both arrays and print the number for both arrays. 


  note: 

  Data was allocated on the heap:

  All are subroutine /void function calls 

  All information through subprogram parameters 

  No global variables 

  Compiled with the flags-O2 -xHost –qopenmp

  Tests were run using dynamic and  static scheduling with 1, 2, 4, 8, 16, 32 and 64threads 
   


  Sample output:


Summary  -------  
Number of elements in a row/column       :: 16386  
Number of inner elements in a row/column :: 16384  
Total number of elements                 :: 268500996  
Total number of inner elements           :: 268435456  
Memory (GB) used per array               :: 1.00024  
Threshold                                :: 0.10  
Smoothing constants (a, b, c)            :: 0.05 0.10 0.40  
Number of elements below threshold (X)   :: 26847453  
Fraction of elements below threshold     :: 1.00015E-01  
Number of elements below threshold (Y)   :: 2950  
Fraction of elements below threshold     :: 1.09896E-05  
Action       :: time/s Time resolution = 1.0E-04  
------  
CPU: Alloc-X :: 0.000  
CPU: Alloc-Y :: 0.000  
CPU: Init-X  :: 3.904  
CPU: Smooth  :: 1.434  
CPU: Count-X :: 0.397  
CPU: Count-Y :: 0.384  

  
 
