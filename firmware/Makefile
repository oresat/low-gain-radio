
.PHONY: dev test flight clean

#all: dev test flight
all: dev test

dev:
	$(MAKE) -s -w -C $@ rebuild

test: 
	$(MAKE) -s -w -C $@ rebuild
	
flight: 
	$(MAKE) -s -w -C $@ rebuild

clean:
	$(MAKE) -s -w -C dev clean
	$(MAKE) -s -w -C test clean
#	$(MAKE) -s -w -C flight clean

