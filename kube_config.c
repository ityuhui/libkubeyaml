#include <kube_config.h>

#define KUBE_CONFIG_DEFAULT_LOCATION "~/.kube/config"
#define K8S_TOKEN_BUF_SIZE 1024
#define K8S_AUTH_KEY "Authorization"
#define K8S_AUTH_VALUE_TEMPLATE "Bearer %s"

/*
 *
 * Load Kubernetes cluster configuration from the file defined by configFileName
 * or default location: ~/.kube/config
 *
 * Parameter:
 *
 * IN
 *
 * configFileName
 * 
 *
 * OUT
 *
 * basePath
 * sslConfig
 * apiKeys
 *
 */

static int setBasePath()
{
    char *basePath = strdup();
    if(basePath){
        *pBasePath = basePath ;
    }else{
        rc = -1;
    }

}

static int setSslConfig(sslConfig_t **pSslConfig)
{
    int rc = 0;
    char *cafile;
    save2file(cafile);

    sslConfig_t *sc = sslConfig_create(clientCert,clientKey,caFile,0);
    if(sc){
        *pSslConfig = sc ;
    }else{
        rc = -1;
    }
    return rc ;
}

static int setApiKeys()
{
 list_t *apiKeys = list_create();
        if(apiKeys){
            char *keyToken = strdup(K8S_AUTH_KEY);
            char valueToken[K8S_TOKEN_BUF_SIZE];
            memset(valueToken, 0, sizeof(valueToken));
            sprintf(valueToken, K8S_AUTH_VALUE_TEMPLATE, token_out_of_cluster);

            keyValuePair_t *keyPairToken = keyValuePair_create(keyToken, valueToken);
            list_addElement(apiKeys, keyPairToken);

            *pApiKeys = apiKeys ;
        }else{
            rc = -1;
        }

}

static char *getConfigFileTakeEffect(const char *configFileName)
{
    char *_configFileName = NULL;
    if ( configFileName && configFileName[0] != '\0' ) {
        _configFileName = configFileName;
    } else {
        _configFileName = KUBE_CONFIG_DEFAULT_LOCATION;
    }
    return _configFileName;
}

static int loadKubeConfigFile(kubeconfig_t* kubeConfig, const char * configFileTakeEffect)
{
    int rc = 0;

    kubeyaml_loadkubeconfig(kubeConfig, configFileTakeEffect);

    return 0;
}

int load_kube_config(char **pBasePath, sslConfig_t **pSslConfig, list_t **pApiKeys, const char *configFileName)
{
    int rc = 0;

    char *configFileTakeEffect = getConfigFileTakeEffect(configFileName);

    kubeconfig_t* kubeConfig;
    loadKubeConfigFile(kubeConfig, configFileTakeEffect);

    if(){
        setBasePath();
    }

    if(){
        setSslConfig();
    }
    
    if( token_out_of_cluster ){
        setApiKeys();
    }

    return rc;
}

/*
 *
 * Free Kubernetes cluster configuration 
 *
 * Parameter:
 *
 * IN
 *
 * basePath
 * sslConfig
 * apiKeys
 *
 */

int free_kube_config(char *basePath, sslConfig_t *sslConfig, list_t *apiKeys)
{
    int rc = 0;

    if(basePath){
        free(basePath);
    }

    if(sslConfig){
        sslConfig_free(sslConfig);
    }

    return 0;
}

