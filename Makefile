## ----------------------------------------------------------------------
## @Author Andrew Sayegh
## @Date   Sept 2, 2021
## @Version 1.0
## ----------------------------------------------------------------------

include makefile.conf

## -g    Adds debuging info and flags for the complier.
## -Wall Turn on common complier warnings.
## For C++ define CC = g++.
CC = aarch64-linux-gnu=gcc-9
CFLAGS = -g -Wall

# Transfer a complied file to a given destination/hostname
.PHONY: transfer
transfer:
	$(echo Transfering to target)
	scp $(NAME) $(USER)@$(HOSTNAME): $(TARGET_DIR)