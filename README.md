# OSLab
Lab1
    lab1_1进程的创建: 
           lab1_1_1.c 编写一段源程序，使系统调用fork()创建两个子进程，当此程序运行时，在系统中 有 一个父进程和两个子进程活动。让每一个进程在屏幕上显示一个字符:父进程显示字符 “a”;子进程分别显示字符“b”和字符“c”。试观察记录屏幕上的显示结果，并分析原 因。 
           lab1_1_2.c 修改已编写的程序，将每个进程输出一个字符改为每个进程输出一句话，在观察程序 执行时屏幕出现的现象，并分析原因。 
    lab1_2进程的控制:
           lab1_2_1.c 用fork()创建一个进程，再调用exec()用新的程序替换该子进程的内 容。
           lab1_2_2.c 利用wait()来控制进程执行顺序。 
           
           
Lab2
    lab2_1使用消息缓冲队列来实现 client 进程和 server 进程之间的通信: 
           lab2_1.c server 进程先建立一个关键字为 SVKEY(如 75)的消息队列，然后等待接收类型 为 REQ (例如 1)的消息;在收到请求消息后，它便显示字符串“serving for client”和接 收到 的 client 进程的进程标识数，表示正在为 client 进程服务;然后再向 client 进程发 送应答消息，该消息的类型是 client 进程的进程标识数，而正文则是 server 进程自己的 标识 ID。client 进程则向消息队列发送类型为 REQ 的消息(消息的正文为自己的进程标 识 ID) 以取得 sever 进程的服务， 并等待 server 进程发来的应答;然后显示字符串 “receive reply from”和接收到的 server 进程的标识 ID。
    lab2_2使用共享存储区来实现两个进程之间的进程通信:
           lab2_2.c 进程 A 创建一个长度为 512 字节的共享内存，并显示写入该共享内存的数据;进程 B 将共享内存附加到自己的地址空间，并向共享内存中写入数据。
