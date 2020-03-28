#ifndef _KUBE_CONFIG_H
#define _KUBE_CONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct kube_cluster_t {
    char *name;
    char *server;
    char *certificate_authority_data;
} kube_cluster_t ;

typedef struct kube_auth_provider_config_t {
    char *id_token;
    char *cmd_path;
    char *access_token;
    char *expires_on;
    char *expiry;
    char *idp_certificate_authority_data;
} kube_auth_provider_config_t ;

typedef struct kube_auth_provider_t {
    char *name;
    kube_auth_provider_config_t *config;
} kube_auth_provider_t ;

typedef struct kube_config_exec_t {

} kube_config_exec_t;

typedef struct kube_user_t {
    char *name;
    char *client_certificate_data;
    char *client_key_data;
    kube_auth_provider_t *auth_provider;
    kube_config_exec_t *exec;
    int insecure_skip_tls_verify;
    char *username;
    char *password;
} kube_user_t ;

typedef struct kube_context_t {
    char *name;
    char *cluster;
    char *user;
} kube_context_t ;

typedef struct kubeconfig_t {
    char *fileName;
    char *apiVersion;
    char *preferences;
    char *kind;
    kube_context_t *current_context;
    kube_context_t **contexts;
    int  num_contexts;
    kube_cluster_t **clusters;
    int  num_clusters;
    kube_user_t **users;
    int  num_users;
    char **extensions;
    int  num_extensions;
} kubeconfig_t;


extern int free_kube_config(char *basePath, sslConfig_t *sslConfig, list_t *apiKeys);

#ifdef  __cplusplus
}
#endif


#endif /* _KUBE_CONFIG_H */
