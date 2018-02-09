# IRCplusplus
IRC like in C++, client + server

For the C part :
- Client :

  ```$ gcc -o executable client.c -pthread ```
  
  ```$ ./executable ```

- Server :

  ```$ gcc -o executable server.c -lpthread ```
  
  ```$ ./executable ```

For the C++ part :
- Client :

  ```$ g++ client.cpp src/User.cpp -pthread ```
  
  ```$ ./a.out 127.0.0.1 8890 ```

- Server :

  ```$ g++ server.cpp -lpthread ```
  
  ```$ ./a.out 8890```

- Quick :

  ```$ g++ server.cpp -lpthread && clear && ./a.out 8890 ```

  ```$ g++ client.cpp src/User.cpp -pthread && clear && ./a.out 127.0.0.1 8890 ```

