#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kube_config_yaml.h"

int main()
{

    kubeconfig_t * kubeconfig = calloc(1,sizeof(kubeconfig_t));
    kubeconfig->fileName = strdup("./config");
    kubeyaml_load_kubeconfig(kubeconfig);

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

    if (kubeconfig->contexts) {

        for (int i = 0; i < kubeconfig->contexts_count; i++) {
            if (kubeconfig->contexts[i]) {
                if (kubeconfig->contexts[i]->name &&
                    kubeconfig->contexts[i]->cluster &&
                    kubeconfig->contexts[i]->user) {
                    printf("name=%s, cluster=%s, user=%s\n", kubeconfig->contexts[i]->name, kubeconfig->contexts[i]->cluster, kubeconfig->contexts[i]->user);
                }
            }
        }
    }

    if (kubeconfig->users) {

        for (int i = 0; i < kubeconfig->users_count; i++) {
            if (kubeconfig->users[i]) {
                if (kubeconfig->users[i]->name &&
                    kubeconfig->users[i]->client_certificate_data &&
                    kubeconfig->users[i]->client_key_data) {
                    printf("name=%s, client-cert=%s, client-key=%s\n", kubeconfig->users[i]->name, kubeconfig->users[i]->client_certificate_data, kubeconfig->users[i]->client_key_data);
                }
            }
        }
    }

    return 0;
}
