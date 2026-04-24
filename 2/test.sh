# ! /bin/bash

g++ main.cpp social_network.cpp -o main;
./main > main.out;
cat main.out;
echo;
echo "--------------------------------------------------";
echo;
cat correct.out;
echo "--------------------------------------------------";
diff main.out correct.out