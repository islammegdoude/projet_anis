#
# Makefile.c++
#
# Instructions:
#
# 1. Edit Makefile using vi or emacs:
#    a. rename target, if desired
#    b. add list of source files at SRCS = ...
# 2. % touch Makefile.dep
# 3. % make depend
# 4. % make
#

TARGET = borne
CC = gcc
CFLAGS = -Wall -O -g 

#Version materielle
INCLDIRS = -I .
LIBDIRS = 

#dependance librairie libsmartcard_borne (voir git)
LIBS64 = -lsmartcard_borne_x64 -lpcsclite

SRCS = lecteurcarte.c borne.c voyant_bouton.c timer.c prise_trappe.c generateur_save.c base_clients.c

OBJS = ${SRCS:.c=.o} 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLDIRS) -o $@ $(OBJS) $(LIBS64)

$(OBJS):
	$(CC) $(CFLAGS) $(INCLDIRS) -c $*.c

depend:
	$(CC) -MM $(SRCS) $(INCLDIRS) > Makefile.dep

clean:
	rm -f $(OBJS) core

veryclean: clean
	rm -f $(TARGET) a.out *.*~

include Makefile.dep

