xiong-chiamiov-plus

# Shared Memory
## How OS manage the memory
- In computing, the minimum unit of the data that a processor can access at once is called a "word", 
The size of a word depends on the architecture of the system:
  - In 64 bit architecture, one word typically represents 8 bytes
  - In 32 bit architecture, one word typically represents 4 bytes
- This means the processor in 64 bit architecture can handle 8 bytes of data in single operations,
while a 32 bits systems handles 4 bytes in a single operation

### Struct Page
- Remember the const keyword in C say that, we cannot change the data of that memory, so how the OS 
can do this thing? Remember in file, we have the permission for every file, so the same thing happen
in memory.
- In memory, we have the unit of memory is called "page", typically each "page" will have 4KB,
- Each byte in the page will have the same attributes:
  - Example if the page is readonly, so all the bytes in page will be readonly
- However, It is not just simple like that, page not only save the permission, data, ... it also
save some info like: whose 's this byte?, whether this byte can be sharing between processes?, ...
- So comeback to the question: How the OS avoid to change the data in const memory? The answer is
that when the const variable initialized, it will save in some random page which have the permission
is readonly, so when we try to change the data, the OS will check the permission of that page and 
avoid that.

## Concept
- So the basic idea here is the OS will allocate a number of pages, which the flags is share_page.

### MMap API
- The idea of the mmap API is that it will map memory through the file, because each process will have
different address of memory, and has own diferent space of memory, and the OS use virtual memory to 
manages these address, so Example: In Space of memory of process A has share address 0x20 and the data is 10, 
so when the process B use the address 0x20, it can be differents. So it use the filesystem to map the memory, 
because the filesystem has global attribute.

#### There are some steps to achieve that:
- <1>
  - Create a file fd
- <2>
  - Set memory size
- <3>
  - Map shared mem to process
- <4>
  - Unmap shared mem
- <5>
  - remove the shared memory

Notes:
  - if the file you map is already exist, so the size of it file will be the size of share memory,
  however, if the file you map is unanonymous, so you have to pass the size at step [2].


#### PAGE TABLE
- Each process has its own <Page Table>
- <Page Table> has 2 cols:
  - First is Virtual address
  - Second is Physical address
- So example we have a variable a with the physical address on RAM is [0x2000], however the process
will use <Virtual Address>, example is [0x10] to represent this Physical Address, when the process
want to read the data of the 'a', it will use the address of <Virtual Address>
##### The question is why dont we have to use the Virtual address, and not use the actual physical address?
- So the answer is that if we use the physical address, we have to care whether if that physical adress be used or not.
- So the Virtual memory come and save us, we will be allocate virtual memory for my program, and
the OS will handle map the physical address for us

##### How the OS use the Virtual memory?
- Example we have the instruction: a++; and assume the virtual memory of a if [0x2000], and physical is [0x10]
- so it will be compile 3 assembly code:
  - LDR a 0x2000
  - ADD $1 a
  - STR a 0x2000
- So in OS, it has a peripherals called MMU (Memory manage unit), so before the address 0x2000 is load to bus to 
get data from the address, it will come through the MMU, so the MMU will be responsible for find the [0x2000] in 
the <PAGE TABLE> and send the <Physical address> to the bus.


### So the step <3> map shared memory to process
- is actually map the virtual address of the shared file to the second Col of the <Page Table> in Process
### <4> Unmap shared memory
- This step will unmap the virtual of the shared file, but notice here is that this virtual memory still 
be marked as share_map, it is only actually free when do the step 5
### <5> Remove the shared memory
