#include <yaml.h>
#include "kubeconfigyaml.h"

#define KEY_APIVERSION "apiVersion"
#define KEY_KIND "kind"
#define KEY_CURRENT_CONTEXT "current-context"
#define KEY_CLUSTERS "clusters"
#define KEY_CONTEXTS "contexts"
#define KEY_USERS "users"
#define KEY_NAME "name"
#define KEY_CERTIFICATE_AUTHORITY_DATA "certificate-authority-data"
#define KEY_SERVER "server"
/*
The Parser produces while the Emitter accepts the following types of events :

STREAM - START
STREAM - END
DOCUMENT - START
DOCUMENT - END
ALIAS
SCALAR
SEQUENCE - START
SEQUENCE - END
MAPPING - START
MAPPING - END

A valid sequence of events should obey the grammar :

stream :: = STREAM - START document * STREAM - END
document :: = DOCUMENT - START node DOCUMENT - END
node :: = ALIAS | SCALAR | sequence | mapping
sequence :: = SEQUENCE - START node * SEQUENCE - END
mapping :: = MAPPING - START(node node) * MAPPING - END
*/


int parse_kubeconfig_yaml_clusterinfo_mapping(kube_cluster_t* cluster, yaml_document_t* document, yaml_node_t* node)
{
    yaml_node_pair_t* pair;
    yaml_node_t* key;
    yaml_node_t* value;

    for (pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++) {
        key = yaml_document_get_node(document, pair->key);
        value = yaml_document_get_node(document, pair->value);
    
        if (key->type != YAML_SCALAR_NODE) {
            printf("the key node is not YAML_SCALAR_NODE\n");
            return -1;
        }

        if (value->type == YAML_SCALAR_NODE) {
            if (0 == strcmp(key->data.scalar.value, KEY_CERTIFICATE_AUTHORITY_DATA)) {
                cluster->certificate_authority_data = strdup(value->data.scalar.value);
            }else if (0 == strcmp(key->data.scalar.value, KEY_SERVER)) {
                cluster->server = strdup(value->data.scalar.value);
            }
        }
    }

    return 0;
}

int parse_kubeconfig_yaml_cluster_mapping(kube_cluster_t *cluster, yaml_document_t* document, yaml_node_t* node)
{
    yaml_node_pair_t* pair;
    yaml_node_t* key;
    yaml_node_t* value;

    for (pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++) {
        key = yaml_document_get_node(document, pair->key);
        value = yaml_document_get_node(document, pair->value);
        
        if (key->type != YAML_SCALAR_NODE) {
            printf("the key node is not YAML_SCALAR_NODE\n");
            return -1;
        }

        if (value->type == YAML_SCALAR_NODE) {
            if (0 == strcmp(key->data.scalar.value, KEY_NAME)) {
                cluster->name = strdup(value->data.scalar.value);
            }
        }
        else if (value->type == YAML_MAPPING_NODE){
            parse_kubeconfig_yaml_clusterinfo_mapping(cluster, document, value);
        }
    }

    return 0;
}

int parse_kubeconfig_yaml_clusters_sequence(kubeconfig_t* kubeconfig, yaml_document_t* document, yaml_node_t* node)
{
    yaml_node_item_t* item;
    yaml_node_t* value;
    int item_count;
    int i;

    for (item = node->data.sequence.items.start, item_count = 0; item < node->data.sequence.items.top; item++, item_count++) {
        ;
    }

    kubeconfig->clusters_count = item_count;
    kubeconfig->clusters = (kube_cluster_t **)calloc(kubeconfig->clusters_count, sizeof(kube_cluster_t *));
    for (i = 0; i < kubeconfig->clusters_count; i++) {
        kubeconfig->clusters[i] = (kube_cluster_t *)calloc(1, sizeof(kube_cluster_t));
    }

    for (item = node->data.sequence.items.start, i = 0; item < node->data.sequence.items.top; item++, i++) {
        value = yaml_document_get_node(document, *item);

        parse_kubeconfig_yaml_cluster_mapping(kubeconfig->clusters[i], document, value);

    }

    return 0;

}

int parse_kubeconfig_yaml_top_mapping(kubeconfig_t* kubeconfig, yaml_document_t* document, yaml_node_t* node)
{
    yaml_node_pair_t* pair;
    yaml_node_t* key;
    yaml_node_t* value;

    for (pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++) {
        key = yaml_document_get_node(document, pair->key);
        value = yaml_document_get_node(document, pair->value);

        if (key->type != YAML_SCALAR_NODE) {
            printf("the key node is not YAML_SCALAR_NODE\n");
            return -1;
        }

        if (value->type == YAML_SCALAR_NODE) {
            if (0 == strcmp(key->data.scalar.value, KEY_APIVERSION)) {
                kubeconfig->apiVersion = strdup(value->data.scalar.value);
            }
            else if (0 == strcmp(key->data.scalar.value, KEY_KIND)) {
                kubeconfig->kind = strdup(value->data.scalar.value);
            }
            else if (0 == strcmp(key->data.scalar.value, KEY_CURRENT_CONTEXT)) {
                kubeconfig->current_context = strdup(value->data.scalar.value);
            }
        } else {
            if (0 == strcmp(key->data.scalar.value, KEY_CLUSTERS)) {
                parse_kubeconfig_yaml_clusters_sequence(kubeconfig, document, value);
            }else if (0 == strcmp(key->data.scalar.value, KEY_CONTEXTS)) {
                //parse_kubeconfig_yaml_contexts_sequence(kubeconfig, document, value);
            }else if (0 == strcmp(key->data.scalar.value, KEY_USERS)) {
                //parse_kubeconfig_yaml_users_sequence(kubeconfig, document, value);
            }
        }
    }

    return 0;

}

void parse_kubeconfig_yaml_node(kubeconfig_t* kubeconfig, yaml_document_t* document, yaml_node_t *node)
{
    if (YAML_MAPPING_NODE == node->type) {
        parse_kubeconfig_yaml_top_mapping(kubeconfig, document,node);
    }
}

int parse_kubeconfig_yaml_document(kubeconfig_t* kubeconfig, yaml_document_t *document)
{
    yaml_node_t* root;
    root = yaml_document_get_root_node(document);
    if (root == NULL) {
        printf("The document is null\n");
        return -1;
    }

    parse_kubeconfig_yaml_node(kubeconfig,document,root);
    
    return 0;
}

int kubeyaml_loadkubeconfig(kubeconfig_t* kubeconfig, const char* kubeConfigFile)
{
    yaml_parser_t parser;
    yaml_document_t document;

    int done = 0;

    /* Create the Parser object. */
    yaml_parser_initialize(&parser);

    /* Set a file input. */
    FILE* input = fopen(kubeConfigFile, "r");

    yaml_parser_set_input_file(&parser, input);

    /* Read the event sequence. */
    while (!done) {

        if (!yaml_parser_load(&parser, &document)) {
            goto error;
        }

        done = (!yaml_document_get_root_node(&document));

        if (!done) {
            parse_kubeconfig_yaml_document(kubeconfig, &document);
        }

        yaml_document_delete(&document);

    }

    /* Cleanup */
    yaml_parser_delete(&parser);
    fclose(input);
    return 0;

error:
    yaml_parser_delete(&parser);
    fclose(input);
    return -1;
}