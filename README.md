# Yonsei-Shell
This is simple shell program for unix/unix-like system.
<br>


Run
--------------------------------------
        $ gcc -Wall -Werror -o ysh ysh.c
        $ ./ysh

<br>

Supporting functions
--------------------------------------
* A single command<br>
```$ date```<br>
```$ ls```<br><br>

* Serialized commands<br>
```$ cd /; ls -l```<br>
```$ echo EEE3535; echo Operating; echo Systems```<br><br>

* A series of piped commands<br>
```$ ps | grep ysh```<br>
```$ nslookup www.yonsei.ac.kr | awk /yonsei/, 0```<br>
```$ ls /usr/bin | grep zip | wc -l```<br><br>
* Invalid commands<br>
```$ ext```<br>
```Command not found: ext```<br><br>

* Exit command<br>
```$ exit```<br>
	



 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 
