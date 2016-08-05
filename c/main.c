#include "filter.h"

int main (int argc, char* argv[]) {
    struct Filter *filter;
    int rule_count, i, j;
    vector *res;

    filter = (struct Filter *)malloc(sizeof(struct Filter) * RULE_MAX_COUNT);

    rule_count = init(filter, "/Users/gfxcc/Downloads/taobao_price_ranges.csv");

    res = (vector*)malloc(sizeof(vector) * rule_count);
    for (i = 0; i < rule_count; i++) {
        vector_init(res + i);
    }

    apply_rule(filter, rule_count, res, "/Users/gfxcc/Downloads/taobao");

    for (i = 0; i < rule_count; i++) {
        printf("%s:\n\t%s:[", (filter + i)->brand_id, (filter + i)->category);
        for (j = 0; j < vector_count(res + i); j++) {
            printf("%s,", vector_get(res + i, j));
        }
        printf("]\n\n\n");
    }
    free(filter);

    exit(EXIT_SUCCESS);
}
