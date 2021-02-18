# ysh, Yonsei-Shell
This is simple shell program for unix/unix-like system.
<br><br><br><br> 


Run
--------------------------------------
        $ gcc -Wall -Werror -o ysh ysh.c
        $ ./ysh

<br><br>

Supporting functions
--------------------------------------
* A single command
```$ date```
```$ ls```

* Serialized commands
```$ cd /; ls -l```
```$ echo EEE3535; echo Operating; echo Systems```

* A series of piped commands
```$ ps | grep ysh```
```$ nslookup www.yonsei.ac.kr | awk /yonsei/, 0```
```$ ls /usr/bin | grep zip | wc -l```

* Invalid commands
```$ ext 
Command not found ext``` 

* Exit command
```$ exit```
	



 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 
