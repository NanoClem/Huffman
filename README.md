# Huffman compression & decompression 

## How to use 
Compile it with : **g++ -Wall Huffman.cpp main.cpp -o (your .exe name)** 

## Run 
The program needs 2 arguments to run, in that order :  
*text_to_encode* and *frequences_file*  
Notice that the frequences file could be empty or non existant, because the program would create a new one in that case.  

## Frequences file
The current "frequences.dat" was made with the "example_text.txt" file.  
It should be organised like this if you want to decode.  
**For the line feed case**, the program is made to read it this way :  
*number of char*  
*line feed char*  
*its frequence*  
*normal behavior*  

