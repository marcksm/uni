# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.http import HttpResponse
from django.shortcuts import render
from django.contrib.auth import authenticate, login
from projeto.models import Projeto
from desenvolvedor.models import Trabalha_em
from django.contrib.auth.models import User
from django.contrib.auth.decorators import login_required
from desenvolvedor.helper import Desenvolvedor_helper as helper
from django.contrib import messages
from django.shortcuts import redirect


# Create your views here.

@login_required
def index(request):
    projetos = Projeto.objects.all().order_by('-id')[:10]
    return render(request, "projeto/index.html", {'projetos' : projetos})

@login_required
def all(request):
    projetos = Projeto.objects.all()
    return render(request, "projeto/all.html", {'projetos' : projetos})

@login_required
def criar(request):
    if (request.method == 'POST'):
        return _novo(request)
    else:
        return render(request, "projeto/criar.html")


@login_required
@helper.must_work_at
def editar(request, p_id):
    if (request.method == 'POST'):
        return _edicao(request)
    else:
        projeto = Projeto.objects.get(id=p_id)
        users = helper.get_users_project(p_id)
        s = ""
        for user in users:
            s += user.username + ','
        s = s[:len(s)-1]
        return render(request, "projeto/editar.html", {'projeto' : projeto, 'users' : s})


@login_required
@helper.must_work_at
def id(request, p_id):
    projeto = Projeto.objects.get(id=p_id)
    users = helper.get_users_project(p_id)
    usernames = map(lambda u: u.username, users)
    return render(request, "projeto/id.html", {'projeto' : projeto, 'users' : usernames})

@login_required
@helper.must_work_at
def remover(request, p_id):
    _excluir_projeto(p_id)
    messages.info(request, "Projeto excluido com sucesso!")
    return redirect("/desenvolvedor")


def _edicao(request):
    post = _extrair_post(request.POST)
    _fatorar_dic(post)
    e_id = post.get("id")

    if (_checar_entrada_edicao(post) == False):
        messages.error(request, "Formulário incompleto")
        return redirect("/projeto/{0}/editar".format(e_id))

    n_devs = post['devs'].split(',')

    if (_ha_usuario_valido(n_devs) == False):
        messages.error(request, "Não é possível deixar o projeto com nenhum desenvolvedor")
        return redirect("/projeto/{0}/editar".format(e_id))


    p = Projeto.objects.get(id=e_id)
    p = _editar_projeto(p, post['nome'], post['estado'], post['descricao'])
    not_found = _cadastrar_users(n_devs, p)
    messages.info(request, "Projeto editado com sucesso!")

    if (len(not_found) > 0):
        nfs = ""
        for nf_user in not_found:
            nfs += nf_user + " "
        messages.error(request, "Os seguintes desenvolvedores não foram vinculados ao projeto por não existirem ou por já estarem no projeto: {0}".format(nfs))

    return redirect("/projeto/{0}".format(e_id))


def _number_dev(p):
    l = Trabalha_em.objects.filter(projeto=p)
    return len(l)

def _ha_usuario_valido(devs):
    for dev in devs:
        if (User.objects.filter(username=dev).exists()):
            return True

    return False

def _cadastrar_user(dev, p):
    try:
        q_user = User.objects.get(username=dev)
    except User.DoesNotExist:
        return False

    if (not Trabalha_em.objects.filter(user=q_user, projeto=p).exists()):
        n_te = Trabalha_em(user=q_user, projeto=p)
        n_te.save()
        return True, n_te
    return False


def _editar_projeto(p, e_nome, e_estado, e_descricao):
    p.nome = e_nome

    if e_estado == 'True': p.estado = True
    else: p.estado = False

    p.descricao = e_descricao
    p.save()
    return p

def _cadastrar_projeto(n_nome, n_descricao,):
    p = Projeto(nome=n_nome, descricao=n_descricao)
    p.save()
    return p

def _extrair_post(post):
    dic = {}
    for key, value in post.items():
        dic[key] = value

    return dic

def _cadastrar_users(devs, p):
    Trabalha_em.objects.filter(projeto=p).delete()
    not_found = []
    for dev in devs:
        if (dev == ""): continue
        if (not _cadastrar_user(dev, p)):
            not_found.append(dev)
    return not_found

def _checar_entrada_novo(dic):
    if not 'descricao' in dic or dic['descricao'].strip() == "" : return False
    if not 'nome' in dic or dic['nome'].strip() == "": return False
    if not 'devs' in dic: return False

    return True

def _checar_entrada_edicao(dic):
    if not 'estado' in dic or dic['estado'].strip() == "": return False
    if not 'descricao' in dic or dic['descricao'].strip() == "" : return False
    if not 'nome' in dic or dic['nome'].strip() == "": return False
    if not 'devs' in dic: return False

    return True

def _excluir_projeto(p_id):
    Projeto.objects.filter(id=p_id).delete()


def _fatorar_dic(dic):
    for key in dic.keys():
        dic[key] = dic[key].strip()

def _novo(request):
    post = _extrair_post (request.POST)
    _fatorar_dic(post)

    if (_checar_entrada_novo(post) == False):
        messages.error(request, "Formulário com campos vazios")
        return redirect("/projeto/criar")

    n_devs = post['devs'].split(",")
    n_devs.append(request.user.username)
    p = _cadastrar_projeto (post['nome'], post['descricao'])
    not_found = _cadastrar_users(n_devs, p)
    messages.info(request, "Projeto criado com sucesso!")

    if (len(not_found) > 0):
        nfs = ""
        for u in not_found:
            nfs += u + ' '
        messages.error(request, "Os seguintes desenvolvedores não foram vinculados ao projeto por já estarem no projeto ou por não existirem: {0}".format(nfs))

    return redirect("/projeto/{0}".format(p.id))
