# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.contrib.auth.models import User

from django.db import models

# Create your models here.

#class Desenvolvedor(models.Model):
#    email = models.CharField(max_length=50, primary_key=True)
#    nome = models.CharField(max_length=30)
#    cpf = models.CharField(max_length=20)
#    hash_senha = models.CharField(max_length=30)

# hash senha : pbkdf2_sha256$36000$jeS1Szfpl2YX$Kc1Y18vL1hatIBnUIq8AkFYqIvQOJ8eb4QzeLWvzB1M=
# senha : abc123456

class Trabalha_em(models.Model):
    user = models.ForeignKey(
        User
    )
    projeto = models.ForeignKey(
        'projeto.Projeto'
    )
