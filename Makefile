OBJS:=main.o kube_config_yaml.o
CFLAGS:=-g
LIBS:=-lyaml

readkubeconfig: $(OBJS)
	gcc $(CFLAGS) -o readkubeconfig $(OBJS) $(LIBS)

main.o:
	gcc $(CFLAGS) -c main.c

kubeconfigyaml.o:
	gcc $(CFLAGS) -c kube_config_yaml.c

.PHONY: clean

clean:
	rm $(OBJS) ./readkubeconfig
