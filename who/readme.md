# who's copy - gwho

## sys call 
* open
* read
* write
* create
* lseek
* close
* perror

## near cmd
* man
* who 
* cp
* login

## copy 思路: 
有那么一个文件，记录了所有登录的用户。所以，读取出那个文件内容。显示出来即可

## 仿照&学习的思路依旧是。 使用 -> 阅读手册 -> 阅读源码 -> 仿造实现

## 信息入手( 非互联网 )
1. 阅读手册 man
2. 搜索手册 man -k | grep
3. 查阅.h文件 （find 使用）
4. man词条的SeeAlso

**eg: who**
man 1 who (因为是用户命令who，所以是1册)
-> 得到保存登录用户信息的文件路径在 /var/run/utmp

man -k utmp (刷拉一大屏幕), -> man -k utmp | grep who
-> 得到
```
➜  who man -k utmp |grep login
login (3)            - write utmp and wtmp entries
utmp (5)             - login records
utmpx (5)            - login records
```

-> 从输出就可以得到 在man的第五卷有utmp文件的格式描述（因为man的第五卷是文件格式描述卷)

man 5 utmp 得到格式， 开发仿造who的所有需要知道的信息都知道了

