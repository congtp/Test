## config to use the debug in remote vscode
- sudo apt install gdb in wsl
- create a launch.json file and paste the contain below:
{
// Use IntelliSense to learn about possible attributes.
// Hover to view descriptions of existing attributes.
// For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
"version": "0.2.0",
"configurations": [
    {
        "name": "(gdb) Launch",
        "type": "cppdbg",
        "request": "launch",
        "program":  "${fileDirname}/a.out",
        "args": [],
        "stopAtEntry": false,
        "cwd": "${fileDirname}",
        "environment": [],
        "externalConsole": false,
        "MIMode": "gdb",
        "miDebuggerPath": "/usr/bin/gdb",
        "setupCommands": [
            {
                "description": "Enable pretty-printing for gdb",
                "text": "-enable-pretty-printing",
                "ignoreFailures": true
            }
        ]
    },  
    
]


## Deque
- Deque is useful when we want to sliding the array with a window. Example:
  - the algorithm to find the largest number in sub array k is:
  - 1: we will have a deque with hold the index of the max value in the front:
    - let push the first value of the arr to front and assume it is the current max value:
    - for (i = 1; i < arr.size(); i++)
      - check if the size of i - k = value of the front (which is the index)
        - pop the value at the front
      - check if the new value is >= the back
        - pop all (clean all) the value at the back because it is useless (while)
      - push the i_th value of the arr to the deque
      - if (i >= k - 1)
        - push the front value to the result vector

  - if we just want to sliding the array, we can do like this:
    - create a deque <int> dq(arr, arr + k);
    - for(int i = 0; i < arr.size() - k; i++)
      - dq.push_back()
      - dq.pop_front()
      - do some thing


## Attribute Parser
- N: numbers of line, each line seperate by the ' ', if there is no attribute, it will has no ' '
- Q: numbers of queries, contain the string that reference to the attribute, tag1, tag2,... tagm 
will be the valid input, there is no tag0 here
  - 1: try to receive the input
  - 2: every <tag> wil have its coresponding </tag> so, if we receive n, let say with the I/P:
  we will have a structure like:
  "
  <tag1 value = "HelloWorld">
  <tag2 name = "Name1">
  </tag2>
  </tag1>
  tag1.tag2~name
  tag1~name
  tag1~value2
  "
   we will have a data structure like:
    - {
        {// tag1
          "value": "HelloWorld", // pair
        },
        {// tag2
          "name": "Name1",
        }
      }
  - we dont actually care about those last 2 </tag>.
  - So the problem here is how to extract those key, and value
    - key might be the one that after the tag and before the '='
    - value might be the one that inside two " "
    - maybe we can do the trick like:
      - we know that the sequence of the string always like:
      key->value->key->value (while in the string)
        - so our algorithm can be:
          
          (if isFindKey == true)
            - find the first ' ' or '\t'
            - find the second ' ' or '\t'
            - assign the substring for key
            - isFindKey == false
          else
            - find the first '\"'
            - find the second '\"'
            - assign the substring for value
            - isFindKey == true
            - after we find the key, and value, we add its into the map
  - after we have an std::vector<vector<std::pair<string, sring>>>, we will test the queries
  - Example the I/P will be: "tag1.tag2~name"
  - we know that the numbers of the '.' will be the numbers of nestest, so we can 
  count the number of '.' then it will be the index of the vector.
  - after we have an index, we will try to find the key:
    - so the key will be after the '~' so the substr will be:
    the start of the '~' + 1 and the end of the string

Notes: 
  - some syntax useful in exercise, std::string::find_the_first(character2find, startPos);
    - the 'character2Find' can be " \t", it mean will find both character ' ' and '\t'
  std::string::npos is the index (-1) of the string
  

- The above way maybe not work for all of the problems
- so we will approach by using the streamstring
  - some of feature of streamstring:
    - stream string is extremely useful for parsing the input string
  - some of useful syntaxs of stream string
    - std::stringstream ss;
    - ss.str(); // return the set of string in stream string
    - <<, >>: using for import and export from the sstring
  



### C
## Structure Doc

- The Doc will have some paragraphs, each paragraph will be seperated by the '\n',
the last paragraphs will not have the '\n'
- Inside each paragraphs will have some sentences, each sentence will be seperated
by the '.'
- Inside each sentence will have some words, each word will be seperated by the ' '
, last word will not have the ' '.
  - Example I/P:
  "Learning C is fun.\n
  Learning pointers is more fun.It is good to have pointers.\0"
- we will have 3 tokens here:
  - 1: ' '
  - 2: '\n'
  - 3: '.'

