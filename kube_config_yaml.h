#ifndef _KUBE_CONFIG_YAML_H
#define _KUBE_CONFIG_YAML_H

#include "kube_config_model.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * kubeyaml_loadkubeconfig
 *
 * Description:
 *
 * Load the kubeconfig file specified by kubeconfig->fileName
 * and get the kuberntes configuration for other fields of kubeconfig.
 *
 * Parameter:
 *
 * IN:
 * kubeconfig->fileName: kubernetes cluster configuration file name
 *
 * OUT:
 * kubeconfig: kubernetes cluster configuration
 */
extern int kubeyaml_loadkubeconfig(kubeconfig_t *kubeconfig);

#ifdef  __cplusplus
}
#endif

#endif /* _KUBE_CONFIG_YAML_H */