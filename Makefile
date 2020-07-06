COMMON_OBJS:=kube_config_yaml.o kube_config_model.o
INCLUDE:=-I./
CFLAGS:=-g 
LIBS:=-lyaml

main: readkubeconfig updatekubeconfig

readkubeconfig: parse.o $(COMMON_OBJS)
	gcc $(CFLAGS) $(CFLAGS) -o readkubeconfig parse.o $(COMMON_OBJS) $(LIBS)

updatekubeconfig: update.o $(COMMON_OBJS)
	gcc $(CFLAGS) $(CFLAGS) -o updatekubeconfig update.o $(COMMON_OBJS) $(LIBS)

parse.o:
	gcc $(CFLAGS) $(CFLAGS) -c parse.c

update.o:
	gcc $(CFLAGS) $(CFLAGS) -c update.c

kube_config_yaml.o:
	gcc $(CFLAGS) $(CFLAGS) -c kube_config_yaml.c

kube_config_model.o:
	gcc $(CFLAGS) $(CFLAGS) -c kube_config_model.c

.PHONY: clean

clean:
	rm $(OBJS) ./*.o ./readkubeconfig ./updatekubeconfig
