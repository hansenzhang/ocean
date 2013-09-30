===Writeup for p2===

The average speedup calculated for P2 ended up 
at around 2.4 for the default gridsize and 2.2 
for a gridsize of 1026, averaged over 10 tests. You can 
see this output by running the script at ./run.sh and
run.sh -g 1026 (note that P2 needs to be in your 
path for this to work...)

A couple things noticed through this experiment is 
the aggressive use of vectorization with -O3 for the 
sequential model.  Using the -ftree-vectorizer-verbose=2
flag points out that all loops for both the sequential 
and parallel model are heavily vectorized.  Attempts at
using sse2 using __m128 address slowed down sequential 
times by about 4 and parallel by 1.5, so I chose to 
remove them from this test.  The same issue occured using
loop blocking and unrolling.

Another obeservation is that when using non-pointers as 
the data structure (I tested with tbb::concurrent_vector)
the performance for the sequential model was drastically lower
so I stayed with using pointers.

Using the affinity partitioner instead of the auto partitoner
provided an additional speedup for the parallel model by about
0.1.  

One thought I had was that using the stencil pattern would be 
more efficent for this algorithm, although I could be wrong as 
I didn't actually get to test it.
