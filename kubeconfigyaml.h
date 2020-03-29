#ifndef _KUBEYAML_H
#define _KUBEYAML_H

#include "kube_config.h"

#ifdef  __cplusplus
extern "C" {
#endif

extern int kubeyaml_loadkubeconfig(kubeconfig_t *kubeconfig,const char* kubeConfigFile);

#ifdef  __cplusplus
}
#endif

#endif /* _KUBEYAML_H */