# Huffman compression & decompression 

## How to use 
Compile it with : **g++ -Wall Huffman.cpp main.cpp -o (your .exe name)** 

## Run 
The program needs 2 arguments to run, in that order :  
*text to encode* *frequences file*

## Frequences file
For example, with the following text : *This is an example of a Huffman tree*  
This file should be organised like this :  

18      *(number of characters)*  
  7  
H 1     *(character + frequence)*  
T 1  
a 4  
e 5  
f 3  
h 1  
i 2  
l 1  
m 2  
n 2  
o 1  
p 1  
r 1  
s 2  
t 1  
u 1  
x 1  

