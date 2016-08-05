#!/usr/bin/python
#Filename:BaseRule.py
class BaseRule(object):

    @property
    def brand_id(self):
        return self._brand_id

    def __init__(self, brand_id, *args, **kwargs):
        self._brand_id = brand_id

    @classmethod
    def load_configuration(cls, input_path):
        """
        Constructs a new rule object given a rule configuration file
        """

        raise NotImplementedError(
            "Child classes must define a class-specific loading mechanism")

    def apply_rule(input, *args, **kwargs):
        """
        Processes input to find all records that match the defined criteria
        """

        raise NotImplementedError(
            "Child classes must define a rule")
