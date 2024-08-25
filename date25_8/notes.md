

# System call 
- a systems call is a request for service that a program makes of the kernel (the brain
of the operating system)
  - the services is generally something that only the kernel have a privilege to do
- So we can treat the system call like the SVC(SuperVisor Call ) in mcu, in SVC which
also request a services from the CPU

- Each process has its own identify number, which called the PID (Process ID)
- In C, we use the Standard library call <sys/types.h>, and <unistd.h>
  - function get_pid() return the pid number which type is pid_t


## IPC (Inter Process Communication)

# Process

- Process is a program in execution
- Program is a file containing the information of the process
  - when you start execution of the program, it is loaded into RAM and start execution
- each process has its own address space and (usually) one thread of control
- you can have multiple processes executing the same program
  - But each process has its own copy of the program within its own address space and 
  executes it independently of the other copies.

- a process can be of two types
 - Independent process:
    - not affectted by the execution of other process
    - does not interact with other programs
  - Co-operate Process:
    - affected by other process
    - can be used for increasing computational speed, convenience, and modularity
- What if you want to send specific data to process or read its output?
  - So the IPC lets processes work together.

# IPC

- IPC (inter-process communication), it has 2 type: 
  - 1 is communication between processes which initiating from the parent process (main()) 
  - 2 is communication between 2 or more different unrelated processes.

# What is Thead?
- We can treat the thread like the lightweight process, we can think like the process itself
has so many thing, but the lightweight process is a little bit lighter than process, means 
we dont have to manage many things like process
- so we can treat any threads(tasks) in RTOS like an lightweight process.
- so in RTOS, since most MCUs have one core, so we can assume that we only have one process,
and any thread create in the process(main()), can be treat like a lightweight process.


## Exercise 2

we have a struct IntList:


- in <insert> function:
  - case 1 is insert in the first:
    - we have to make the head point to the new Node, and the next of head Node point to 
    the first node
      - be careful that if we assign the head point to the new node first, we will lose 
      the entire of Node:
        - so our algorithm will be:
          - assign the next of new node to the first node, then assign the head point to
          the new node
  - case 2 will be insert at the rest index:
    - go the the position of index - 1;
    - assign the new_node->next = node[index]->next;
    - assign the node[index]->next = new
- in <push_front> function
  - we also have 2 cases:
    - case 1: if head is nullptr
      - just create the new node, and assign the head to the new node
      - update the tail to the head
    - case 2: head is not
      - assign the new node to the head->next
      - assign the head to the new node

- in <push_back> function
  - we also have 2 cases:
    - case1: if head is nullptr
      - just create the new node, and assign the head to the new node
      - update the tail to the head
    - case2: head is not
      - just update the tail->next = new
      - tail = new

- in <At>, <Front>, <Back>
  - we just traverse to the position an return the data
  - <Front>, and <Back> we have to check if this is the last node by
  check the condition (head == tail)
- in <Erase> function:
  - we have several cases:
    - 1: someone do not want to use function pop_front, and pop_back:
      - use the coresponding function PopBack, PopFront
    - 2: index < size - 1
      - traverse to the node[index]
      - prevNode->next = node[index]->next;
      - node[index]->next = nullptr
      - delete node[index]

      

