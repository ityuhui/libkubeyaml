#include <stdio.h>
#include <stdlib.h>
#include "kubeconfigyaml.h"

int main()
{
    printf("hello,yuhui!\n");

    kubeconfig_t * kubeconfig = calloc(1,sizeof(kubeconfig_t));
    kubeyaml_loadkubeconfig(kubeconfig, "./config");

    if (kubeconfig->apiVersion) {
        printf("apiVer=%s\n", kubeconfig->apiVersion);
    }
    if (kubeconfig->kind) {
        printf("kind=%s\n", kubeconfig->kind);
    }

    if (kubeconfig->clusters ) {

        for (int i = 0; i < kubeconfig->clusters_count; i++) {
            if (kubeconfig->clusters[i]) {
                if (kubeconfig->clusters[i]->name &&
                    kubeconfig->clusters[i]->server &&
                    kubeconfig->clusters[i]->certificate_authority_data) {
                    printf("name=%s, server=%s, ca=%s\n", kubeconfig->clusters[i]->name, kubeconfig->clusters[i]->server, kubeconfig->clusters[i]->certificate_authority_data);
                }
            }
        }
    }

    return 0;
}
