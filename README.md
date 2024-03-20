### First challenge
This is the folder containing code for first challenge of PACS course, there are three folders:
- **doc** it contains just the challenge pdf
- **lib** it contains all the *.hpp files that are used by the program
- **src** it contains main.cpp and the Makefile to run the program

The program relies on muParserX that is implemented in the avaiable git folder pacs-examples/.
To compile the program change **PACS_EXAMPLES_PATH** variable inside *Makefile* to set the right path to your local pacs-examples/ folder.

All parameters are passed by the user through the text file **data.txt** (and then read by the program using GetPot).
This is true for every possible variable **except** for the domain dimension **DIM**. Currently the program is set with *DIM=2*, to modify it change the variable **DIM** inside *main.cpp* and **recompile** everything using *Makefile*.
Remember to properly set the function, its gradient and the initial point inside *data.txt* if you change **DIM**

**Code features**
- The user can choose different minimization techniques to compute the minimum: Gradient, Heavy ball, Nesterov and Adam methods are implemented.
- The update of the step coefficient can be set using different strategies: Exponential, Inverse decay and Armijo strategies are implemented.
- One could choose not to provide a gradient for the function, in that case the gradient is computed numerically using a central different scheme. In this case an incremental step has to be provided

**useful note**:
Indeed changing the method provides slightly different results, in particular the step coefficient $\alpha_0$, the maximum number of iterations and the tolerances are crucial for the method to converge to the right solution. A bit of tuning might be necessary to obtain the right result.
Some good $\alpha_0$ choices are commented inside *data.txt* 



