# CS1_PA5
 Binary Search Tables

Soccer Match Ticket Management
Background Story
The Monster Country Soccer Tournament has sold a large number of tickets to various fans and now
needs an efficient system to track ticket ownership and usage. Fans can purchase additional tickets and
use them to attend matches. The tournament organizer has greatly benefited from the systems you
developed in the previous four assignments and is now looking to build a new system to track tickets
and their owners. As you learned in class, using a binary search tree (BST) for data storage can enhance
search efficiency, making it an ideal opportunity to apply that knowledge.

In this new system, fans can buy tickets and use them to watch matches. The system should be able to
check a fan’s ticket balance at any given time. Additionally, a fan can be removed from the system once
they no longer own any tickets. The system should also support analytical queries, such as calculating
the total and average number of tickets, etc.
In your BST implementation, each node will store the fan's name and the number of tickets they own.
The fan’s name will be the key for the BST, with comparisons made alphabetically. As you develop this
application, you may also want to implement debugging queries to better understand the tree’s structure.

Problem
Develop a program that processes input commands to manage the fans and their tickets. The program
should respond appropriately to each command, as outlined below:
   • Add tickets to a fan
   • Deduct tickets from a fan
   • Search for a fan’s record
   • Calculate the mean ticket count per fan in the system
   • Calculate the total amount of tickets still not used in the system
   • Determine the balance of the tree in terms of height
   • Calculate the total number of tickets for fans whose names are alphabetically smaller than a
     given name

Input (must be standard input using scanf (no file i/o is allowed))
The first line of input contains a single positive integer: n (n ≤ 300,000), the number of commands to
process.
The next n lines will each contain a single command. Note that all strings in this assignment are assumed to be
single-word strings. Therefore, using scanf with %s should be sufficient to capture each string input. Below is the
format for each of the possible input lines:

Command 1
buy <name> <count>
   • <name> A lowercase alphabetic string containing no more than 30 characters.
   • <count> A positive integer, less than or equal to 100.
Behavior:
This command adds <count> number of tickets to the fan with name <name>. If the fan with the
specified name (<name>)is not in the tree, this name will be added to the tree. If the fan already exists
in the system, the command will increase the fan's number of tickets by the given count (<count>).

Command 2
use <name> <count>
   • <name> A lowercase alphabetic string containing no more than 30 characters.
   •  <count> A positive integer, less than or equal to 100.
Behavior:
   • This command is to use the <count> number of tickets of the fan with the name <name>
   • This command will reduce the number of tickets for the fan by <count>. If the fan has less than
     the specified number of tickets to be used, then the number of tickets owned by the fan will be
     reduced to zero.
   • If the fan's number of tickets becomes zero or negative after the use, the fan is removed from the
     tree.

Command 3
find <name>
   • <name> A lowercase alphabetic string containing no more than 30 characters.
Behavior:
   • This command searches for the fan with the specified name <name>) in the tree.
   • If the fan is found, the command will report:
     o The remaining number of tickets belong to the fan.
     o The depth (or level) of the node in the tree that stores that fan's record.
          The depth refers to the number of edges from the root node to the node storing the fan’s record.

Command 4
mean_tickets
This command calculates the average number of tickets per fan in the tree.

Command 5
height_balance
This command calculates and compares the heights of the left and right subtrees of the root node.
Behavior:
   • The command will calculate the height of the left subtree starting from the left child of the root node.
   • It will also calculate the height of the right subtree starting from the right child of the root node.
   • If the heights of the left and right subtrees are the same, the command will output that the tree is
     "balanced."
   • If the heights are different, the command will output that the tree is "not balanced."

Command 6
count_before <name>
   • <name> A lowercase alphabetic string containing no more than 30 characters.
Behavior:
   • This command calculates the total count of available tickets for all the fans whose names come
     alphabetically before the specified <name>.
   • The calculation includes only those owners whose names are lexicographically smaller than
     equal to <name>, based on alphabetical order.

Output (standard output. No file i/o allowed)
For each input command, output a single line as described below:

Commands 1
Print out a single line with the format:
     <name> <count> <depth>
The <name> refers to the fan name who is buying tickets, <count> represents the updated total
count of tickets owned by the fan, and <depth> indicates the depth of the node in the tree where the
fan’s record is stored. If the fan does not already exist in the tree, the program should insert the fan and
then display the message with the fan's name, ticket count, and the depth of the corresponding node in
the tree.

Commands 2
Print out a single line with the format:
     <name> <count> <depth>
The <name> represents the fan name who is using tickets, <count> is the updated total count of
tickets of the fan, and <depth> is the depth of the node where their record is stored.
If the deduction causes the fan's total tickets to reach zero or become negative, the fan should be
removed from the tree, and the following message should be printed:
     <name> deleted
If the fan does not exist in the tree when the “use” command is executed, the program should print:
     <name> not found
Important note: If the deduction results in deleting a fan from the tree, and the fan’s node has two
children, replace the deleted node with the maximum node from the left subtree. This ensures a
consistent and correct result for each test case.

Command 3
If the fan in question wasn't found in the binary search tree, output the following line:
     <name> not found
If the name is found, output a line with the following format:
     <name> <count> <depth>
The <name> refers to the fan’s name being searched for, <count> is the total count of tickets they
own, and <depth> indicates the depth of the node where their record is stored in the tree.

Command 4
Show the average up to two decimal places. Please use double data type for all fractional calculations
and also make sure not to do int division by mistake.
     <mean>
where <mean> is the average number of tickets per fan in the tree.

Command 5
This command prints a line with the left height, right height and a message whether it is balanced or not.
     left height = <lh> right height = <rh> <balance status>
where <lh> is the height of the left subtree, <rh> is the height of the right subtree, and <balance
status> is either “balanced” or “not balanced”.

Command 6
     <total>
Where <total> is the total count of tickets by the fans whose names are lexicographically less than
or equal to the name provided in the command. Note that the name entered in the command does not
necessarily have to be present in the tree. The total should include the count of tickets for all fans
whose names come before or are the same as the given name in alphabetical order.

Implementation Requirements/Run Time Requirements
1. Declare a node structure for binary search tree and store all the required items inside the node. Do not
use any malloc to store the name of a fan. Use static size array for the name with the appropriate size
based on the max length.

2. The run-time for processing buy, use, find, and height_balance commands should be O(h), where h
is the current height of the tree.

3. You must use the delete function we have discussed in our class/recording and modify the code to
fulfill the requirements of this assignment. It is fine to update the list of parameters and a few logic inside
the function. However, the structure of the code and use of utility functions must be the same and the
logic of dealing with 3 cases must be handled in the exact same way discussed in the coding explanation.
Not doing this will result in 50% penalty on your assignment.
