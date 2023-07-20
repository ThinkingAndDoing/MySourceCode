# Generated by Django 2.2.7 on 2020-11-21 13:30

from django.db import migrations, models


class Migration(migrations.Migration):
    initial = True

    dependencies = []

    operations = [
        migrations.CreateModel(
            name="Rule",
            fields=[
                (
                    "id",
                    models.AutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("name", models.CharField(max_length=130)),
                ("email", models.EmailField(blank=True, max_length=254)),
                ("job_title", models.CharField(blank=True, max_length=30)),
                ("bio", models.TextField(blank=True)),
            ],
        ),
    ]
