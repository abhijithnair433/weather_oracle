from django.urls import path

from . import views

urlpatterns = [
    path("readings/", views.readings, name="readings"),
    path("predicted/", views.predicted, name="predicted"),
]