#! encoding: utf-8
#!/usr/bin/python

#Filename:main.py
import json
import csv
from CategoryFilterRule import CategoryFilterRule
from PriceFilterRule import PriceFilterRule

def UnicodeDictReader(utf8_data, **kwargs):
    csv_reader = csv.DictReader(utf8_data, **kwargs)
    for row in csv_reader:
        yield {key: unicode(value, 'utf-8') for key, value in row.iteritems()}

with open("/Users/gfxcc/Downloads/taobao", "r") as fi:
	res = [json.loads(i) for i in fi.readlines()]
	with open("/Users/gfxcc/Downloads/taobao_price_ranges.csv") as f:
		config_list = UnicodeDictReader(f)
		for config in config_list:
			dic = {}
			category_rule = CategoryFilterRule.load_configuration(config)
			price_rule = PriceFilterRule.load_configuration(config)
			filtered_res = category_rule.apply_rule(res)
			final_res = price_rule.apply_rule(filtered_res)
			dic[config["brand_id"]] = {
				config["category"]: [ i["product_id"] for i in final_res ]
			}
			print dic