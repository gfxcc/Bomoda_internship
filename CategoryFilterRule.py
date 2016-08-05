#! encoding: utf-8
#!/usr/bin/python

#Filename:CategoryFilterRule.py
import BaseRule


class CategoryFilterRule(BaseRule.BaseRule):


    def __init__(self, brand_id, category, *args, **kwargs):
        super(CategoryFilterRule, self).__init__(brand_id=brand_id)
        self._category = category


    @property
    def category(self):
        return self._category

    @classmethod
    def load_configuration(cls, data):
        return cls(
            brand_id=data["brand_id"],
            category=data["category"]
            )

    def apply_rule(self, input_rows):
        return_list = []
        for row in input_rows:
            try :
                if (self._brand_id in row["brand"].lower() and self._category in row["title"].lower() ) : 
                    return_list.append({
                        "product_id": row["product_id"],
                        "brand_id": row["brand"],
                        "title": row["title"],
                        "category": row["category"],
                        "price": row["price"],
                        })
            except:
                pass

        return return_list

 #and key[1] == "\"\xe9\x95\x9c\""
# CategoryFilterRule.load_configuration({"brand_id":"gucci", "category":u"香水"})