---
# Proof Of Reservers

### Hand Shake by Server
- Description
    - This code is concept proto type of Hand Shake by Server
    - You can edit this code to test send message and meassurment.
- How to build
    1. Change directory
        ```
        $ cd Proof-Of-Reserves/HandShakebyServer
        ```
    2. Edit this code to test send message and meassurment.
        ```
        [example]
        sever.c
        /*
            send(client_socket, buffer, strlen(buffer), 0);
        */
        client.c
        /*
            recv(server_socker, buffer, sizeof(buffer), 0);
            printf("Server response: %s", buffer);
        */
        ```
    3. Build with Makefile
        ```
        $ make
        gcc -Wall -pthread -o server server.c
        gcc -Wall -pthread -o client client.c
        ```
    4. Excute server first then client
        ```
        $ ./server
        Waiting for connections...
        ---------------------------------
        $ ./client
        ```

---

### Hand Shake by User

- Description
    - This code is concept proto type of Hand Shake by User
    - You can edit this code to test send message and meassurment.
- How to build
    1. Change directory
        ```
        $ cd Proof-Of-Reserves/HandShakebyUser
        ```
    2. Edit this code to test send message and meassurment.
        ```
        [example]
        main.c
        
        nodes[0] = (Node){"127.0.0.1", 8001, {8002, 8003}, 2, -1};
        nodes[1] = (Node){"127.0.0.1", 8002, {8004, 8005}, 2, 8001};
        nodes[2] = (Node){"127.0.0.1", 8003, {8006, 8007}, 2, 8001};
        /*
            Set More nodes
        */
        
        // set start node
        nodes[i] = (Node){"127.0.0.1", port, {8001}, 0, nodes[parent_idx].port};
        ```
    
    3. Build with Makefile
        ```
        $ make
        gcc -Wall -pthread -o main main.c
        ```
    4. Excute main
        ```
        $ ./main
        ```
---
### Processing Delay & Transmission Delay
- What is Processing Delay?
    - The time it takes for a computer system or communication system to handle and process data or signals. It is the time elapsed between sending or receiving data and the system completing the processing to produce the desired output.
- What is Transmission Delay?
    - The time it takes for a computer system or communication system to handle and process data or signals. It is the time elapsed between sending or receiving data and the system completing the processing to produce the desired output.
- What for this code?
    - Mearsure Delay Using OMNeT++ (https://omnetpp.org/), INET Framework (https://inet.omnetpp.org/)
- How to use?
    1. Install OMNeT++ from (https://omnetpp.org/download/)
    2. Excute OMNet++
    3. Patch using the code in this repository