#! encoding: utf-8
#!/usr/bin/python

#Filename:PriceFilterRule.py
import BaseRule


class PriceFilterRule(BaseRule.BaseRule):


    def __init__(self, brand_id, category_min_price, *args, **kwargs):
        super(PriceFilterRule, self).__init__(brand_id=brand_id)
        self._category_min_price = category_min_price


    @property
    def category_min_price(self):
        return self._category_min_price

    @classmethod
    def load_configuration(cls, data):
        return cls(
            brand_id=data["brand_id"],
            category_min_price=float(data["min_price"])
            )

    def apply_rule(self, input_rows):
        return_list = []
        for row in input_rows:
            try :
                if row["price"] >= self._category_min_price:
                    return_list.append({
                        "product_id": row["product_id"],
                        "brand_id": row["brand_id"],
                        "title": row["title"],
                        "category": row["category"],
                        "price": row["price"],
                        })
            except:
                pass
        return return_list

 #and key[1] == "\"\xe9\x95\x9c\""
# CategoryFilterRule.load_configuration({"brand_id":"gucci", "category":u"香水"})