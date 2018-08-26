# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.http import HttpResponse
from django.shortcuts import render, redirect
from django.contrib.auth import authenticate, login, logout
from desenvolvedor.helper import Desenvolvedor_helper, CreateUserForm
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from django.contrib.auth.hashers import make_password
from django.contrib import messages
from desenvolvedor.models import Trabalha_em

def index(request):
    if request.user.is_authenticated:
        projetos = list(Desenvolvedor_helper.get_working_projects (request.user.id))
        return render(request, "desenvolvedor/home.html", {"projetos": projetos})
    else:
        return render(request, "desenvolvedor/index.html")

def signup(request):
    if request.method == 'POST':
        form = CreateUserForm(request.POST)
        if form.is_valid():
            form.save()
            user = authenticate(
                username = form.cleaned_data.get('username'),
                password = form.cleaned_data.get('password1'))

            login(request, user)
            return redirect('/')
    else: form = CreateUserForm()
    return render(request, 'desenvolvedor/signup.html', {'form': form})

def edit(request):
    user = request.user
    can_delete = len(Trabalha_em.objects.filter(user_id = user.id)) == 0
    if request.method == 'POST':
        form = request.POST

        raw_pass = form.get('password')

        user.first_name = form.get('first_name')
        user.last_name  = form.get('last_name')
        user.email      = form.get('email')
        user.password   = make_password(raw_pass) if raw_pass != None and len(raw_pass) > 0 else user.password

        if form.get('password') == form.get('confirm_password'):
            user.save()
            login(request, user)
            return redirect('index')

    return render(request, 'desenvolvedor/edit.html',
                  {'username':   user.username,
                   'first_name': user.first_name,
                   'last_name':  user.last_name,
                   'email':      user.email,
                   'can_delete': can_delete})

def delete(request):
    current_user = request.user
    if request.method == 'POST' and len(Trabalha_em.objects.filter(user_id = current_user.id)) == 0:
        current_user.delete()
        logout(request)
    return redirect('/')
