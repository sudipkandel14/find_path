
---------------------*
* Name: Sudip Kandel *
* UTA ID: 1001552835 *
* CSE 4308-001	     *
---------------------*

------------------*
* Code Structure: *
------------------*

	C++ as a programming language.

     *-------------------*
     *  ## find_path.cpp *
     *-------------------*
I have implemented all the function in single find_path.cpp file. Where appropriate functions are called base on the user input. 

If route_file.txt starting_city final_city is passed as arguments from main function parse_file is called, which will parse the route_file and save it to a vector of type path.
 Then Uniformed_search will be called which will perform the necessary action before calling extend and find path function. Once all the function are returned successfully print function is called to print the final result.

And same thing happens if route_file.txt starting_city final_city heuristic.txt only difference
Is that it also call get_heuristic to parse the heuristic_file to save it to the vectors.


--------------------------*
** To Compile the program *
--------------------------*
Step 1- g++ -o find_path find_path.cpp
Step 2- ./find_path route_file.txt initial_city final_city //for Uniformed search
	or
Step 3- ./find_path route_file.txt initial_city final_city heuristic.txt //for informed search 
