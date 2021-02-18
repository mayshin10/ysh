# ysh, Yonsei-Shell
This is simple shell program for unix/unix-like system. 


Supporting functions
--------------------------------------
* A single command
example)
<pre><code>{$ date}</code></pre>
<pre><code>{$ ls}</code></pre>

* Serialized commands
<pre><code>{$ cd /; ls -l}</code></pre>
<pre><code>{$ echo EEE3535; echo Operating; echo Systems}</code></pre>

* A series of piped commands
<pre><code>{$ ps | grep ysh}</code></pre>
<pre><code>{$ nslookup www.yonsei.ac.kr | awk /yonsei/, 0}</code></pre>
<pre><code>{$ ls /usr/bin | grep zip | wc -l}</code></pre>

* Invalid commands
<pre><code>{$ ext}</code></pre>
<pre><code>{Command not found ext}</code></pre>

* Exit command
<pre><code>{$ exit}</code></pre>
	

Run
--------------------------------------
	$ gcc -Wall -Werror -o ysh ysh.c
	$ ./ysh



 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 
