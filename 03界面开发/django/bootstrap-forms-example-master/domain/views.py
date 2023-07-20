from django.views.generic import ListView, CreateView, UpdateView
from django.urls import reverse_lazy

from domain.models import Rule
from domain.forms import PersonForm


class PersonListView(ListView):
    model = Rule
    context_object_name = "domain"


class PersonCreateView(CreateView):
    model = Rule
    fields = ("name", "email", "job_title", "bio")
    success_url = reverse_lazy("person_list")


class PersonUpdateView(UpdateView):
    model = Rule
    form_class = PersonForm
    template_name = "domain/rule_update_form.html"
    success_url = reverse_lazy("person_list")
