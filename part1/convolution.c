#include <time.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <omp.h>


/* create the timer class*/

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count();
    }
    

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;

};



void initialize( float* x, int n ) { 

  int n2 = n+2;   
  for (int i=0; i<n2; ++i)     
    for (int j=0; j<n2; ++j)       
      x[i*n2 + j] = random() / (float) RAND_MAX;

 } 

void smooth( float* y, float* x, int n, float a, float b, float c ) { 

  int n2 = n+2;

  #pragma omp parallel
  {
  #pragma omp for   
  for (int i=1; i<=n; ++i){     
    for (int j=1; j<=n; ++j)       
      y[i*n2 + j] = a * (x[(i-1)*n2 + (j-1)] + x[(i-1)*n2 + (j+1)] + x[(i+1)*n2 + (j-1)] +   x[(i+1)*n2 + (j+1)]) + b * (x[i*n2+(j-1)] + x[i*n2+(j+1)] + x[(i-1)*n2 + j] +  x[(i+1)*n2 + j]) + c * x[i*n2 +j]; 

    }
  }
}


void count( float* x, int n, float t, int &nbx ) { 
  nbx = 0; 
  int n2 = n+2;

  #pragma omp parallel
  {
  #pragma omp for   
  for (int i=1; i <= n; ++i){     
    for (int j=1; j <= n; ++j)   
      if (x[i*n2 + j] < t)       
        ++nbx;
    }

  }

 } 



int main() {


  int n,nbx,nby;
  float a,b,c,
         t,
         *x, *y;
/* n - number of elements in one direction */
  n = 1 << 15;

 /* 2^14 == 16384 */ /* a,b,c - smoothing constants */
  a = 0.05;
  b = 0.1;
  c = 0.4;

/* t - threshold */
  t = 0.1;


  double d1, d2, d3, d4, d5, d6;


   int n_threads, tid;
   int mts = 8;
   omp_set_num_threads(mts);

// Fork threads and have each report its number

   printf("\n");  

    #pragma omp parallel private(tid, n_threads)
      {
          tid = omp_get_thread_num();
          n_threads = omp_get_num_threads();

          printf("Hello World from thread %d / %d \n", tid, n_threads);
      
      }
                                    

  /*using timer */
  Timer timer;



  timer.start();

 /* allocate x */
  x = new float[(n+2)*(n+2)];
  timer.stop();
  d5 = timer.elapsedMilliseconds()/1000000;


  timer.start();
 /* allocate y */
  y = new float[(n+2)*(n+2)];
  timer.stop();
  d6 = timer.elapsedMilliseconds()/1000000;


  timer.start();
  /* initialize x */
  initialize(x, n);
  timer.stop();
  d1 = timer.elapsedMilliseconds()/1000000;


  timer.start();
  /* smooth x into y */
  smooth(y, x, n, a, b, c);
  timer.stop();
  d2 = timer.elapsedMilliseconds()/1000000;


  timer.start();
  /* count elements in first array */
  count(x, n, t, nbx);
  timer.stop();
  d3 = timer.elapsedMilliseconds()/1000000;

  timer.start();
  /* count elements in second array */
  count(y, n, t, nby);
  timer.stop();
  d4 = timer.elapsedMilliseconds()/1000000;


  std::cout << std::endl;
  std::cout << "Summary" << std::endl; 
  std::cout << "-------" << std::endl; 
  std::cout << "Number of elements in a row/column         :: " << n+2 << std::endl;
  std::cout << "Number of inner elements in a row/column   :: " << n << std::endl; std::cout << "Total number of elements                   :: " << (n+2)*(n+2) << std::endl; 
  std::cout << "Total number of inner elements             :: " << n*n << std::endl; std::cout << "Memory (GB) used per array                 :: " << (n+2)*(n+2)*sizeof(float) / (float)(1024*1024*1024) << std::endl;
  std::cout << "Threshold                                  :: " << t << std::endl; std::cout << "Smoothing constants (a, b, c)              :: " << a << " " << b << " " << c << std::endl; 
  std::cout << "Number   of elements below threshold (X)   :: " << nbx << std::endl; std::cout << "Fraction of elements below threshold       :: " << nbx / (float)(n*n) << std::endl; 
  std::cout << "Number   of elements below threshold (Y)   :: " << nby << std::endl; std::cout << "Fraction of elements below threshold       :: " << nby / (float)(n*n) << std::endl;

  std::cout << std::endl;
  std::cout << "Action       :: time/s Time resolution = 1.0E-06  " << std::endl;
  std::cout << "-------" << std::endl; 
  std::cout << "CPU: Alloc-X :: "  << d5 << std::endl;
  std::cout << "CPU: Alloc-Y :: "  << d6 << std::endl;
  std::cout << "CPU: Init-X  :: "  << d1 << std::endl;
  std::cout << "CPU: Smooth  :: "  << d2 << std::endl;
  std::cout << "CPU: Count-X :: "  << d3 << std::endl;
  std::cout << "CPU: Count-Y :: "  << d4 << std::endl;
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "Threads " << std::endl;
  std::cout << "-------" << std::endl;
  std::cout << "The number of threads is " << mts  << std::endl;
  std::cout << std::endl;


  } 


