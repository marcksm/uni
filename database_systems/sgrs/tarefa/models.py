# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.contrib.auth.models import User

from django.db import models

# Create your models here.

class Tarefa(models.Model):
    nome = models.CharField(max_length=30)
    descricao = models.TextField()
    deadline = models.DateTimeField()
    estado = models.BooleanField(default=False)
    user = models.ForeignKey(
        User
    )
    projeto = models.ForeignKey(
        'projeto.Projeto'
    )
