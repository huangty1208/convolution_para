

  Introduction:


  The red-black(rb)program is an example of an update mechanism that might be encountered in various algorithms. In a red-black algorithm, red or black elements of an array are updated separately.  Two red-blackloops updatearray "a" withother elements of "a". In this red-black algorithmthe "red" elements of the “a” array,{1,3,5,7,...},are updated,and then the "black" elements of the array, {0,2,4,...}, are updated. 

  The objective here is to first parallelize loops in a simple manner (part a), and then reduce the number of parallel forks in part b. Part c also tried to optimize the code and check the performance of binding (affinity) schemes.




  Notes:


  For compiling execute:./compile my_prog.c

  The compilescript will make an executable named a.out_my_prog.

  To interactively run an executablewith various number of threads, execute:./dothis

  FYI: The timer.c and affinity.c codes are compiled withthe “-c” option in the compile script and creates just “object” files (timer.o, affinity.o).  These are loaded into code on the compile line like this:  icc-qopenmp timer.o affinity.o prb_d.c  -o a.out_prb_d

  



