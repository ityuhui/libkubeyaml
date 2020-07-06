COMMON_OBJS:=kube_config_yaml.o kube_config_model.o
CFLAGS:=-g -I./include
LIBS:=-lyaml

readkubeconfig: parse.o $(COMMON_OBJS)
	gcc $(CFLAGS) -o readkubeconfig $(OBJS) $(LIBS)

updatekubeconfig: update.o $(COMMON_OBJS)
	gcc $(CFLAGS) -o readkubeconfig $(OBJS) $(LIBS)

parse.o:
	gcc $(CFLAGS) -c parse.c

update.o:
	gcc $(CFLAGS) -c update.c

kube_config_yaml.o:
	gcc $(CFLAGS) -c kube_config_yaml.c

kube_config_model.o:
	gcc $(CFLAGS) -c kube_config_model.c

.PHONY: clean

clean:
	rm $(OBJS) ./readkubeconfig ./updatekubeconfig
