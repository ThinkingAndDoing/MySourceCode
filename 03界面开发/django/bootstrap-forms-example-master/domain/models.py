from django.db import models


class Rule(models.Model):  # db_tablename = appname + Rule
    name = models.CharField(max_length=130)
    email = models.EmailField(blank=True)
    job_title = models.CharField(max_length=30, blank=True)
    bio = models.TextField(blank=True)
