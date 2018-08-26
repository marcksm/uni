# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.contrib.auth.decorators import login_required
from requisito.models import Requisito, Funcionalidades
from projeto.models import Projeto
from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.contrib import messages
from django.http import HttpResponseRedirect
from django.core.exceptions import ObjectDoesNotExist
from desenvolvedor.helper import Desenvolvedor_helper

@login_required
@Desenvolvedor_helper.must_work_at
def requisitos(request, p_id):
    projeto = Projeto.objects.get(id=p_id)

    titulo = request.POST.get('titulo')
    descricao = request.POST.get('descricao')
    pk = request.POST.get('pk')
    if titulo and descricao:
        requisito = Requisito(titulo=titulo, descricao=descricao, projeto_id=projeto.id)
        if pk:
            requisito = Requisito.objects.get(id=pk)
        requisito.titulo = titulo
        requisito.descricao = descricao
        requisito.save()
        return HttpResponseRedirect(request.path_info)

    requisitos = Requisito.objects.filter(projeto=projeto.id)
    # funcionalidades = Funcionalidades.objects.filter(pub_date__year=2006)
    return render(request, "requisito/visualizar.html", {'projeto': projeto, 'requisitos': requisitos})

@login_required
@Desenvolvedor_helper.must_work_at
def funcionalidades(request, p_id, requisito_id):
    projeto = Projeto.objects.get(id=p_id)
    requisito = Requisito.objects.get(projeto=projeto.id, id=requisito_id)

    descricao = request.POST.get('descricao')
    pk = request.POST.get('pk')
    if descricao:
        funcionalidade = Funcionalidades(descricao=descricao, requisito_id=requisito.id)
        if pk:
            funcionalidade = Funcionalidades.objects.get(id=pk)
        funcionalidade.descricao = descricao
        funcionalidade.save()
        return HttpResponseRedirect(request.path_info)

    funcionalidades = Funcionalidades.objects.filter(requisito=requisito.id)
    data = {
        'projeto': projeto,
        'requisito': requisito,
        'funcionalidades': funcionalidades
    }
    return render(request, "requisito/funcionalidades.html", data)

@login_required
@Desenvolvedor_helper.must_work_at
def funcionalidades_deletar(request, p_id, requisito_id, funcionalidade_id):
    projeto = Projeto.objects.get(id=p_id)
    requisito = Requisito.objects.get(projeto=projeto.id, id=requisito_id)
    try:
        funcionalidade = Funcionalidades.objects.get(requisito=requisito.id, id=funcionalidade_id)
        funcionalidade.delete()
    except ObjectDoesNotExist:
        pass
    return redirect('funcionalidades', p_id, requisito_id)

@login_required
@Desenvolvedor_helper.must_work_at
def requisito_deletar(request, p_id, requisito_id):
    projeto = Projeto.objects.get(id=p_id)
    try:
        requisito = Requisito.objects.get(projeto=projeto.id, id=requisito_id)
        requisito.delete()
    except ObjectDoesNotExist:
        pass
    return redirect('requisitos', p_id)
