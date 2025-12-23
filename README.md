For using you must write "generator.cpp" first. This is a code for generate random test cases. For more comfortable there is also sum functions for get random number or print arrays. But you can write yourself if you want.

Formally "generator.cpp" creates input for "correct.cpp" and "hack.cpp". And after that "stress.py" checks the ouputs and if they are not equal, process will stop.



You can run these files with using this code in terminal: "python3 stress_tester.py --max 200000 --timeout 2 --progress 100".

"--max 200000" in here 200000 is the number of test cases.

"--timeout 2" in here 2 is time limit. If one of the codes is running more than 2 seconds the process will stop.

"--progress 100" in here 100 is the report time. Every 100 test cases, code prints that: "100 test cases are correct.". SO you can change this number to whatever you want.
