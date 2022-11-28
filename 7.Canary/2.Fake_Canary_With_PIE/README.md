* The following is a list of exploits that details my progression of understanding as I learned more about binary exploitation. 
	* Each exploit is better than the last and I think going through the differences may help with understanding of different concepts.

* `exploit.py` is meant for if you have access to the actual binary and can open the process in gdb

* `altExploit.py` uses a more traditional bruteforce method, which is for when you don't have access to the binary

* `finalExploit.py` is a much more efficient bruteforce method that I made after realizing I only have to bruteforce half of one byte of the address. It also addresses a logical error that my previous exploits were based on, which is that we cannot simply go through all the bytes, but must instead go through them repeatedly, as the nibble we are bruteforcing is random.
	* [This](https://www.youtube.com/watch?v=SBqERAbDdAk&ab_channel=pwn.college) video is what gave me the idea.

