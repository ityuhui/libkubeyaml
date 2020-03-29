OBJS:=main.o kubeconfigyaml.o
CFLAGS:=-g
LIBS:=-lyaml

readkubeconfig: $(OBJS)
	gcc $(CFLAGS) -o readkubeconfig $(OBJS) $(LIBS)

main.o:
	gcc $(CFLAGS) -c main.c

kubeconfigyaml.o:
	gcc $(CFLAGS) -c kubeconfigyaml.c

.PHONY: clean

clean:
	rm $(OBJS) ./readkubeconfig
