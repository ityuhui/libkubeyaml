#ifndef _KUBE_CONFIG_MODEL_H
#define _KUBE_CONFIG_MODEL_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct kubeconfig_cluster_t {
    char *name;
    char *server;
    char *certificate_authority_data;
} kubeconfig_cluster_t ;

typedef struct kubeconfig_auth_provider_config_t {
    char *id_token;
    char *cmd_path;
    char *access_token;
    char *expires_on;
    char *expiry;
    char *idp_certificate_authority_data;
} kubeconfig_auth_provider_config_t ;

typedef struct kubeconfig_auth_provider_t {
    char *name;
    kubeconfig_auth_provider_config_t *config;
} kubeconfig_auth_provider_t ;

typedef struct kubeconfig_exec_t {
    char *command;
} kubeconfig_exec_t;

typedef struct kubeconfig_user_t {
    char *name;
    char *client_certificate_data;
    char *client_key_data;
    kubeconfig_auth_provider_t *auth_provider;
    kubeconfig_exec_t *exec;
    int insecure_skip_tls_verify;
    char *username;
    char *password;
} kubeconfig_user_t;

typedef struct kubeconfig_context_t {
    char *name;
    char *cluster;
    char *user;
} kubeconfig_context_t ;

typedef struct kubeconfig_t {
    char *fileName;
    char *apiVersion;
    char *preferences;
    char *kind;
    char *current_context;
    kubeconfig_context_t **contexts;
    int  contexts_count;
    kubeconfig_cluster_t **clusters;
    int  clusters_count;
    kubeconfig_user_t **users;
    int  users_count;
} kubeconfig_t;

#ifdef  __cplusplus
}
#endif


#endif /* _KUBE_CONFIG_MODEL_H */
