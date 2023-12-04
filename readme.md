Author: Filippos Rafail Papadakis

## How to RUN
* Compilation

          gcc -fopenmp GameOfLife.c -O3

* Threads change from the definition at the start of the code text.

* The program to run needs:

        ./a.out {glidfile} {generations} {outputfile}

Where 
* glidfile : the input file (px glid1.txt)

* generations: the genes that we want to run

* outputfile: the file that we want to save the results.
##### If there isn't an output file then it prints the results to the stdout(not suggested).

###################################################################################################
###################################################################################################


### Question 1 && Question 2:
####################### Glid1.txt:####################################
 ---------------Glid1.txt OpenMp 100 generatios----------------------


          |Threads|  1    |    2   |   4    |
          |Run 1 |0.311684|0.176149|0.172323|
          |Run 2 |0.314219|0.177171|0.173309|
          |Run 3 |0.311158|0.177275|0.185494|
          |Run 4 |0.313540|0.176059|0.176722|
          |Run 5 |0.314247|0.176370|0.231407|
          |Avgtime|0.3129696|0.1766048|0.187851|
                                                                            |--Glid1.txt 100gens--          |
                                                                            |  AvgSpeedup                   |
                                                                            |  for 1 thread:0.608566455     |
                                                                            |  for 2 threads:1.078468988    |
                                                                            |  for 4 threads:1.013903573    |
   ---------------Glid1.txt Serial  100  generatios----------------------

          |Run 1 |0.188910|
          |Run 2 |0.191079|
          |Run 3 |0.191337|
          |Run 4 |0.190713|
          |Run 5 |0.190275|
          |Avgtime|0.1904628|

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------


  ---------------Glid1.txt OpenMp 1000 generatios----------------------

          |Threads|  1    |    2   |   4    |
          |Run 1 |3.291706|1.767861|1.724777|
          |Run 2 |3.098331|1.830074|1.726322|
          |Run 3 |3.099004|1.784506|1.729906|
          |Run 4 |3.089324|1.779635|1.759871|
          |Run 5 |3.093373|1.787236|1.738747|
          |Avgtime|3.1343476|1.7898624|1.7359246|
                                                                            |--Glid1.txt 1000gens--            |
                                                                            |   AvgSpeedup                     |
                                                                            |  for 1 thread:0.605885703        |
                                                                            |  for 2 threads:1.061006924       |
                                                                            |  for 4 threads:1.093974012       |


   ---------------Glid1.txt Serial  1000  generatios------------------------

          |Run 1 |1.898922|
          |Run 2 |1.896564|
          |Run 3 |1.895579|
          |Run 4 |1.896239|
          |Run 5 |1.907978|
          |Avgtime|1.8990564|



####################### Glid2.txt:####################################
 Glid2.txt:
 ---------------Glid2.txt OpenMp 100 generatios----------------------

    ---With OpenMp 100 generations---

          |Threads|  1    |    2   |   4    |
          |Run 1 |29.427307|16.355732|16.206581|
          |Run 2 |30.974263|22.130305|18.746058|
          |Run 3 |30.813816|18.057577|16.197502|
          |Run 4 |30.823456|17.932934|16.604132|
          |Run 5 |29.473456|20.559489|16.269669|
          |Avgtime|30.3024596|19.0072074|16.8047884|
                                                                                   |--Glid2.txt 100gens--              |
                                                                                   |  AvgSpeedup                       |
                                                                                   | for 1 thread:0.577837734          |
                                                                                   | for 2 threads:0.921224472         |
                                                                                   | for 4 threads:1.041959243         |
   ---------------Glid2.txt Serial  100  generatios----------------------

          |Run 1 |17.046607|
          |Run 2 |17.425670|
          |Run 3 |17.212356|
          |Run 4 |18.411424|
          |Run 5 |17.453466|
          |Avgtime|17.5099046|


--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

  ---------------Glid2.txt OpenMp 1000 generatios----------------------

          |Threads|  1    |    2   |   4    |
          |Run 1 |192.241491|141.776512|136.141133|
          |Run 2 |192.675345|142.125421|136.124552|
          |Run 3 |192.523213|142.125244|137.412424|
          |Run 4 |191.142552|141.135555|136.512523|
          |Run 5 |193.524412|143.251344|134.414515|
          |Avgtime|192.4214026|142.0828152|136.1210294|
                                                                            |  --Glid2.txt 1000gens--           |
                                                                            |   AvgSpeedup                      |
                                                                            |  for 1 thread:0.907259835         |
                                                                            |  for 2 threads:1.228693348        |
                                                                            |  for 4 threads:1.282507271        |


   ---------------Glid2.txt Serial  1000  generatios------------------------

          |Run 1 |174.501850|
          |Run 2 |173.423133|
          |Run 3 |178.512341|
          |Run 4 |174.421232|
          |Run 5 |172.022493|
          |Avgtime|174.57620992|


   ### Question 3:
The overhead of OpenMP program with parallelism 1 is due to 3 problems. (1) Because of implicit barriers at the end of the parallel regions, (2) Communication between processors works with
cache coherency mechanism. Where memory access is more expensive (3) Hardware resource contention, there are shared resources that, if all cores try to access
at the same time they do not scale.


    Question 4:
-->I notice that in both glid1 and glid2 the speedup depending on the repetitions (100-1000) remains almost unchanged.
-->On the other hand, depending on the size of the input, we notice (glid1,glid2) that as you increase the size of the input, the speedup also increases, so speedup_glid1<speedup_glid2.
