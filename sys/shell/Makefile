SRC = shell.c
OBJ = $(SRC:%.c=$(BINDIR)%.o)
DEP = $(SRC:%.c=$(BINDIR)%.d)

MODULE =shell

$(BINDIR)$(MODULE).a: $(OBJ)
	$(AD)$(AR) rc $(BINDIR)$(MODULE).a $(OBJ)

# pull in dependency info for *existing* .o files
-include $(OBJ:.o=.d)

# compile and generate dependency info
$(BINDIR)%.o: %.c
	$(AD)$(CC) $(CFLAGS) $(INCLUDES) -c $*.c -o $(BINDIR)$*.o
	@$(CC) $(CFLAGS) $(INCLUDES) -MM $*.c > $(BINDIR)$*.d
	@printf "$(BINDIR)"|cat - $(BINDIR)$*.d > /tmp/riot_out && mv /tmp/riot_out $(BINDIR)$*.d

# remove compilation products
clean::
	@rm -f $(BINDIR)$(MODULE).a $(OBJ) $(DEP) $(ASMOBJ)
