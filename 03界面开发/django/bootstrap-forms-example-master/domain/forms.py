from django import forms

from crispy_forms.helper import FormHelper
from crispy_forms.layout import Submit

from domain.models import Rule


class PersonForm(forms.ModelForm):
    class Meta:
        model = Rule
        fields = ("name", "email", "job_title", "bio")

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.helper = FormHelper()
        self.helper.form_method = "post"
        self.helper.add_input(Submit("submit", "Save person"))
