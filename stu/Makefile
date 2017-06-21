CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi scadd.cgi scsel.cgi scmod.cgi scdel.cgi login_control.cgi recover.cgi screcover.cgi ddel.cgi scddel.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi

install:
	cp *.cgi /usr/lib/cgi-bin/sx/
	cp head.html footer.html /usr/lib/cgi-bin/sx/
