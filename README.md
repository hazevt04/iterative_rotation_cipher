# iterative_rotation_cipher

Based on Code Kata on CodeWars.com:

https://www.codewars.com/kata/5a3357ae8058425bde002674/train/cpp

In this kata, your task is to implement what I call Iterative Rotation Cipher (IRC). To complete the task, you will create an object with two methods, encode and decode. (For non-JavaScript versions, you only need to write the two functions without the enclosing dict)
Input

The encode method will receive two arguments — a positive integer n and a string value.

The decode method will receive one argument — a string value.
Output

Each method will return a string value.
How It Works

Encoding and decoding are done by performing a series of character and substring rotations on a string input.

Encoding: The number of rotations is determined by the value of n. The sequence of rotations is applied in the following order:
 Step 1: remove all spaces in the string (but remember their positions)
 Step 2: shift the order of characters in the new string to the right by n characters
 Step 3: put the spaces back in their original positions
 Step 4: shift the characters of each substring (separated by one or more consecutive spaces) to the right by n

Repeat this process until it has been completed n times in total.
The value n is then prepended to the resulting string with a space.

Decoding: Decoding simply reverses the encoding process.
Test Example

let quote = `If you wish to make an apple pie from scratch, you must first invent the universe.`;
let solution = `10 hu fmo a,ys vi utie mr snehn rni tvte .ysushou teI fwea pmapi apfrok rei tnocsclet`;
IterativeRotationCipher.encode(10,quote) === solution; //true
