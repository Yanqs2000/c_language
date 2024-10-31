SP=server
C=client

all:$(SP) $(C) 

$(SP):$(SP).c
	gcc $^  -o  $@
$(C):$(C).c
	gcc $^  -o  $@

clean:
	rm -f $(SP)  $(C)
