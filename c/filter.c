#include "filter.h"

int init(struct Filter *rule, char *rule_file_path) {
    FILE *fp;
    char *line = NULL, *token, *state;
    size_t len = 0;
    ssize_t read;
    int rule_count = 0, token_length, token_index;
    struct Filter *iter = rule;

    fp = fopen(rule_file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    /* get ride of first line */
    getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        for (token = strtok_r(line, ",", &state), token_index = 0;
                token != NULL; token = strtok_r(NULL, ",", &state), token_index++) {
            token_length = strlen(token);
            if (token_index == 0) {
                iter->brand_id = (char*)malloc(sizeof(char) * token_length);
                strcpy(iter->brand_id, token);
                //printf("%s\n", iter->brand_id);
            } else if (token_index == 1) {
                iter->category = (char*)malloc(sizeof(char) * token_length);
                strcpy(iter->category, token);
            } else {
                iter->min_price = atof(token);
            }
        }
        iter++;
        rule_count++;
    }

    fclose(fp);
    if (line)
        free(line);

    return rule_count;
}
void apply_rule(struct Filter *rule, int rule_count,
        vector *res, char *input_file_path) {
    FILE *fp;
    char *line = NULL, *p, *mem_tmp;
    size_t len = 0;
    ssize_t read;
    struct Filter *iter = NULL;
    cJSON *title, *brand, *product_id, *price;
    int i;

    fp = fopen(input_file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1) {
        cJSON *json, *out;
        json=cJSON_Parse(line);
        if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
        else
        {
            product_id = cJSON_GetObjectItem(json, "product_id");
            title = cJSON_GetObjectItem(json, "title");
            brand = cJSON_GetObjectItem(json, "brand");
            price = cJSON_GetObjectItem(json, "price");
            //printf("%.0f\n", product_id->valuedouble);
            for (i = 0, iter = rule; i < rule_count; i++, iter++) {
                p = iter->brand_id;
                for ( ; *p; ++p  ) *p = toupper(*p);

                if (title->valuestring && strstr(title->valuestring, iter->category) != NULL
                        && brand->valuestring && strstr(brand->valuestring, iter->brand_id) != NULL
                        && price->valuedouble && price->valuedouble >= iter->min_price) {
                    mem_tmp = (char*)malloc(sizeof(char*) * PRODUCT_ID_MAX_LENGTH);
                    sprintf(mem_tmp,"%.0f",product_id->valuedouble);
                    vector_add((res + i), mem_tmp);
                }
            }
            cJSON_Delete(json);
        }
        /*
           for (i = 0, iter = rule; i < rule_count; i++, rule++) {
           if (strstr(title, iter->category)
           && strstr(brand, iter->brand_id)) {

           }
           }*/
        /* parse line */
        /*
           for (token = strtok_r(line, ",", &state), token_index = 0;
           token != NULL; token = strtok_r(NULL, ",", &state), token_index++) {
           token_length = strlen(token);
           printf("i am in %s\n", token);
           for (i = 0, colon_index = 0; i < token_length; i++) {
           if (token[i] == ':') {
           colon_index = i;
           break;
           }
           }
           if (colon_index == 0)
           continue;

           if (token_index == 0) {
           key_length = colon_index - 2;
           key_offset = 2;
           value_length = token_length - colon_index;
           value_offset = colon_index + 1;
           } else {
           key_length = colon_index - 1;
           key_offset = 1;
           value_length = token_length - colon_index;
           value_offset = colon_index + 1;
           }
           printf("[debug] token:%s token_length:%i colon_index:%i", token, token_length, colon_index);
           key = (char*)malloc(sizeof(char) * key_length);
           strncpy(key, token + key_offset, key_length - 1);
           key[key_length - 1] = '\0';

           value = (char*)malloc(sizeof(char) * value_length);
           strncpy(value, token + value_offset, value_length - 1);
           value[value_length - 1] = '\0';

//printf("%i   %i\n", token_length, colon_index);
printf("key->%s   value->%s\n", key, value);


if (strcmp(key, "title") == 0) {
strcpy(title, value);
} else if (strcmp(key, "category") == 0) {
strcpy(category, value);
} else if (strcmp(key, "product_id") == 0) {
strcpy(product_id, value);
} else if (strcmp(key, "price")) {
price = atof(value);
}

free(key);
free(value);
}

iter = rule;
for (i = 0; i < rule_count; i++) {

}
*/
}

}

/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
    char *out;cJSON *json;

    json=cJSON_Parse(text);
    if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
    else
    {
        out=cJSON_Print(json);
        cJSON_Delete(json);
        printf("%s\n",out);
        free(out);
    }
}


