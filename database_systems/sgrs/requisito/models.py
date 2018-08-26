# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

# Create your models here.

class Requisito(models.Model):
    titulo = models.CharField(max_length=30)
    descricao = models.TextField ()
    projeto = models.ForeignKey(
        'projeto.Projeto',
         on_delete=models.CASCADE
    )

class Funcionalidades(models.Model):
    requisito = models.ForeignKey(
        'requisito.Requisito',
         on_delete=models.CASCADE
    )
    descricao = models.TextField()
