# -*- coding: utf-8 -*-

from django.contrib.auth.models import User
from django.shortcuts import redirect
from projeto.models import Projeto
from desenvolvedor.models import Trabalha_em
from django.contrib import messages
from django.contrib.auth.forms import UserCreationForm

class Desenvolvedor_helper:
    @staticmethod
    def trabalha(u_id, p_id):
        try:
            Projeto.objects.get(id=p_id)
            Trabalha_em.objects.get(user=u_id, projeto=p_id)
        except Trabalha_em.DoesNotExist:
            return False
        return True

    @staticmethod
    def get_working_projects(u_id):
        return Trabalha_em.objects.raw("SELECT p.* FROM desenvolvedor_trabalha_em as t, projeto_projeto as p WHERE t.user_id={0} and p.id=t.projeto_id".format(u_id))

    @staticmethod
    def get_users_project(p_id):
        return Trabalha_em.objects.raw("SELECT a.* FROM desenvolvedor_trabalha_em as t, auth_user as a WHERE t.projeto_id = {0} and a.id = t.user_id".format(p_id))

    @staticmethod
    def must_work_at(func):
        def new_func(request,*args,**options):
            if Desenvolvedor_helper.trabalha(request.user.id, options.get("p_id")):
                return func(request,*args,**options)
            else:
                messages.error(request, "Você não trabalha nesse projeto e/ou este projeto não existe.")
                return redirect("/")
        return new_func

class CreateUserForm(UserCreationForm):
    class Meta:
        model = User
        fields = ('username', 'first_name', 'last_name', 'email')

    def __init__(self, rqt=None):
        if rqt != None:
            super(CreateUserForm, self).__init__(rqt)
        else:
            super(CreateUserForm, self).__init__()
            
        self.fields['username'].label   = 'Nome de usuário'
        self.fields['first_name'].label = 'Nome'
        self.fields['last_name'].label  = 'Sobrenome'
        self.fields['email'].label      = 'E-mail'
        self.fields['password1'].label  = 'Senha'
        self.fields['password2'].label  = 'Confirmar Senha'
