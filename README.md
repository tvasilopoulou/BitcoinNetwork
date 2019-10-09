# BitcoinNetwork
Implementation of Bitcoin Network Using Hash Table

READ ME

System Programming 2019


The program's requirements are the implementation of a bitcoin exchange system and
all related functions that a user might choose to carry out. These include:
1.requestTransaction(s)
2.findEarnings
3.findPayments
4.walletStatus
5.bitCoinStatus
6.traceCoin
7.exit.

Suggested execution:
./bitcoin -a bitCoinBalancesFile.txt -t transactionsFile.txt -v 25 -h1 2 -h2 3 -b 3

At first the program checks the command line data and receives the basic data needed
to start building the bitcoin system( bitcoinBalancesFile, transactionsFile, 
bitcoinValue, senderEntries, receiverEntries, bucketSize) as specified by hypothesis.
Next, the first file is opened and while parsed line by line, the following is formed:
a list of walletListNodes (users) which include a walletID (e.g. richard) and a list of
bitcoins along with 3 integer values, the summed balance the user has every moment,
the earned amount of dollars and the spent amount of dollars. Also for every bitcoin,
a binary tree is implemented to show every transaction it's been involved in. Evey users 
balance  is the amount of bitcoins they own multiplied by the value of the bitcoins 
(acceptance:in the beginning, when a user is assigned a bitcoin, they own the whole 
amount ofdollars and not some unspecified fraction.). If a user does not own any 
bitcoins, they are assigned a bitcoin with ID=0.

Once the first file is closed, the transactions file is opened and is read again
line by line. Two separate hash tables are created, one that uses as key the sender
and the receiver of each transaction, respectively. Every line is considered a separate
transaction and is stored in both hash tables, after checking every sender for enough
balance to carry it out. After this, according to the amount needed and the value of 
each bitcoin, the number of affected sender bitcoins is calculated (acceptance:
bitcoins are affected serially). These transactions are also inserted in both hash
tables. For every affected bitcoin, it is transfered in the bitcoin list of the 
receiver and the tree connected to the bitcoin is formed accordingly. Following the 
step of freeing whatever memory was allocated for the needs of the basic implementation
the user is now called to decide what information they want to acquire from the 
system.

After scanning input (acceptance: input must be limited to 300 characters) one of 
the above functions can be called.

1.requestTransaction(s):
If a user requests a single transaction, the system looks for the walletListNode
corresponding with the specified sender. The data of the input are copied in a 
new transaction and if date or time have not been specified, the system assigns
current date and time. Afterwards, a check for available sender balance occurs,
the transaction is inserted into the hash tables its details are printed for the 
user to check. 

If more than one transactions are requested from input, for every ; encoutered between
them, the system follows the above tactic. 

Else if a file is specified, we assume that it's written in the way that the
input would be, and consequently work the same way.

2.findEarnings:
Since for every transaction, the "added" variable is increased by the amount of
the transaction, in the end every user has a total sum of earnings. So after finding
the receiving node the user specifies, a message with the acquired dollars is 
printed.

3.findPayments:
As above, only now the variable printed is the "reduced". In actuality, since 
a user is supposed to be able to set a date and time range, we should work as follows:

Search the hash table with sender/receiver the one specified and for that chain
go through the ones with acceptable time stamp, while adding the amounts sent/
received. Lack of time is the cause for lack of correct implementation.

4.walletStatus:
Every walletID has a variable "balance", which marks current amount of dollars in
wallet. So after finding specified wallet, we print the balance.

5.bitCoinStatus:
Every bitcoin has a variable "traninv", which is a counter of the transactions involving
the bitcoin. So if while the above transactions occur and this bitcoin is affected,
its counter is increased. Also, among the requested variables are the initial value,
which as a result of bove acceptance will always be equal to bitcoin value and the
unspent amount, which is the bottom right leaf node of the tree of said bitcoin.

6.traceCoin:
This is also one of the functions not fully implemented. While the request was the
whole history, the implementation only searches for the bitcoin and lets the user know 
if the bitcoin is registered in the system. For the cause of correct implementation
a postorder print is also implemented. So what is left undone, is the search inside
the hash table for mutual transaction details as the ones in the tree.

7.exit:
This function is used to free all allocated (and not yet freed) structures and pointers.

