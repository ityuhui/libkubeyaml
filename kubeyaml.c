#include <yaml.h>

static void process_the_event(yaml_event_t *event)
{
    switch (event->type) {
        case YAML_NO_EVENT:
            puts("No event!");
            break;
        /* Stream start/end */
        case YAML_STREAM_START_EVENT:
            puts("STREAM START");
            break;
        case YAML_STREAM_END_EVENT:
            puts("STREAM END");
            break;
        /* Block delimeters */
        case YAML_DOCUMENT_START_EVENT:
            puts("<b>Start Document</b>");
            break;
        case YAML_DOCUMENT_END_EVENT:
            puts("<b>End Document</b>");
            break;
        case YAML_SEQUENCE_START_EVENT:
            puts("<b>Start Sequence</b>");
            break;
        case YAML_SEQUENCE_END_EVENT:
            puts("<b>End Sequence</b>");
            break;
        case YAML_MAPPING_START_EVENT:
            puts("<b>Start Mapping</b>");
            break;
        case YAML_MAPPING_END_EVENT:
            puts("<b>End Mapping</b>");
            break;
        /* Data */
        case YAML_ALIAS_EVENT:
            printf("Got alias (anchor %s)\n", event.data.alias.anchor);
            break;
        case YAML_SCALAR_EVENT:
            printf("Got scalar (value %s)\n", event.data.scalar.value);
            break;
    }
}

int kubeyaml_loadkubeconfig(const char* kubeConfigFile)
{
    yaml_parser_t parser;
    yaml_event_t event;

    int done = 0;

    /* Create the Parser object. */
    yaml_parser_initialize(&parser);

    /* Set a file input. */
    FILE* input = fopen(kubeConfigFile, "r");

    yaml_parser_set_input_file(&parser, input);

    /* Read the event sequence. */
    while (!done) {

        /* Get the next event. */
        if (!yaml_parser_parse(&parser, &event))
            goto error;

        /*
          ...
          Process the event.
          ...
        */
        process_the_event(&event);

        /* Are we finished? */
        done = (event.type == YAML_STREAM_END_EVENT);

        /* The application is responsible for destroying the event object. */
        yaml_event_delete(&event);

    }

    /* Cleanup */
    yaml_parser_delete(&parser);
    fclose(fh);
    return 0;

error:
    yaml_parser_delete(&parser);
    fclose(fh);
    reurn -1;
}