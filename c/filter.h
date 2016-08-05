#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON.h"
#include "vector.h"

#define RULE_MAX_COUNT 100
#define TOKEN_MAX_LENGTH 64
#define PRODUCT_ID_MAX_LENGTH 30

struct Filter {
    char *brand_id;
    char *category;
    double min_price;

};

void doit(char *text);
int init(struct Filter *rule, char *rule_file_path);
void apply_rule(struct Filter *rule, int rule_count,
        vector *res, char *input_file_path);

