# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render, redirect
from projeto.models import Projeto
from tarefa.models import Tarefa
from django.contrib import messages
from django.contrib.auth.decorators import login_required
from desenvolvedor.helper import Desenvolvedor_helper
from django.contrib.auth.models import User

@login_required
@Desenvolvedor_helper.must_work_at
def index (request, p_id):
    try:
        projeto = Projeto.objects.get(id=p_id)
    except Projeto.DoesNotExist:
        messages.error (request, "Este projeto não existe.")
        return redirect("/")

    tarefas = Tarefa.objects.filter(projeto=p_id)
    return render (request, "tarefa/index.html", {'projeto': projeto, "tarefas": tarefas})

@login_required
@Desenvolvedor_helper.must_work_at
def ler (request, p_id, t_id):
    try:
        tarefa = Tarefa.objects.get(id=t_id)
    except Tarefa.DoesNotExist:
        messages.error (request, "Esta tarefa não existe.")
        return redirect("/")
    #Neste ponto, o projeto com certeza existe (não é necessário checar)
    projeto = Projeto.objects.get(id=p_id)
    responsavel = tarefa.user.username
    return render(request, "tarefa/ler.html", {'tarefa': tarefa, 'projeto': projeto, 'username_responsavel': responsavel})

@login_required
@Desenvolvedor_helper.must_work_at
def editar (request, p_id, t_id):
    if request.method == 'POST':
        return editar_post(request, p_id, t_id)
    else:
        try:
            tarefa = Tarefa.objects.get(id=t_id)
        except Tarefa.DoesNotExist:
            messages.error (request, "Esta tarefa não existe.")
            return redirect("/")
        return render(request, "tarefa/editar.html", {'tarefa': tarefa})


@login_required
@Desenvolvedor_helper.must_work_at
def criar (request,p_id):
    if request.method == 'POST':
        return criar_post(request, p_id)
    else:
        projeto = Projeto.objects.get(id=p_id)
        return render(request, "tarefa/criar.html", {'projeto': projeto})

@login_required
@Desenvolvedor_helper.must_work_at
def remover (request, p_id, t_id):
    try:
        tarefa = Tarefa.objects.get(id=t_id)
    except Tarefa.DoesNotExist:
        messages.error (request, "Esta tarefa não existe.")
        return redirect("/")
    n_del = tarefa.delete()[0]
    if n_del != 1:
        messages.error (request, "Falha ao remover essa tarefa.")
        return redirect("/projeto/{0}/tarefa/{1}".format(p_id,t_id))
    messages.info (request, "Tarefa removida!")
    return redirect("/projeto/{0}/tarefa/".format(p_id))


def editar_post(request,p_id,t_id):
    try:
        tarefa = Tarefa.objects.get(id=t_id)
    except Tarefa.DoesNotExist:
        messages.error (request, "Esta tarefa não existe.")
        return redirect("/")
    form = request.POST
    projeto = Projeto.objects.get(id=p_id)
    try:
        tarefa.nome=form.get("nome")
        tarefa.descricao=form.get("descricao")
        tarefa.deadline=form.get('deadline')
        tarefa.estado=form.get('estado')
        tarefa.save()
        messages.info(request, "Tarefa editada!")
        return redirect ("/projeto/{0}/tarefa/{1}".format(p_id,t_id))
    except:
        messages.error (request, "Preencha todos os campos corretamente. (obs: O nome deve ter no máximo 30 caracteres.)")
        return render(request, "/projeto/{0}/tarefa/{1}/editar".format(p_id,t_id), {'tarefa': tarefa})


def criar_post(request, p_id):
    form = request.POST
    projeto = Projeto.objects.get(id=p_id)
    try:
        tarefa = Tarefa.objects.create (nome=form.get("nome"),descricao=form.get("descricao"),
                               deadline=form.get('deadline'),estado=False,user=request.user,
                               projeto=projeto)
        messages.info(request, "Tarefa criada!")
        return redirect ("/projeto/{0}/tarefa/{1}".format(p_id,tarefa.id))
    except:
        # tarefa = {'nome'=form.get("nome"),'descricao'=form.get("descricao"),
        #                        'deadline'=form.get('deadline'),'estado'=False,'user'=request.user,
        #                        'projeto'=projeto} passar tarefa para formulario preenchido
        messages.error (request, "Preencha todos os campos corretamente. (obs: O nome deve ter no máximo 30 caracteres.)")
        return render(request, "tarefa/criar.html", {'projeto': projeto})
