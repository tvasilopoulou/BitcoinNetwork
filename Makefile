#
# In order to execute this "Makefile" just type "make"
#

OBJS 	= main.o bitcoinList.o walletList.o transaction.o hash.o tree.o
SOURCE	= main.c bitcoinList.c walletList.c transaction.c hash.c tree.c
HEADER  = bitcoinList.h walletList.h transaction.h header.h hash.h tree.h
OUT  	= bitcoin
CC	= gcc
FLAGS   = -c -g
#-g -c -pedantic -ansi  -Wall
# -g option enables debugging mode
# -c flag generates object code for separate files

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c


bitcoinList.o: bitcoinList.c
	$(CC) $(FLAGS) bitcoinList.c

walletList.o: walletList.c
	$(CC) $(FLAGS) walletList.c

transaction.o: transaction.c
	$(CC) $(FLAGS) transaction.c

hash.o: hash.c
	$(CC) $(FLAGS) hash.c

tree.o: tree.c
	$(CC) $(FLAGS) tree.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)
