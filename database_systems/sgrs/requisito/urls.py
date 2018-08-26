from  django.conf.urls  import  url
from django.contrib.auth import views as auth_views
from  .  import  views

urlpatterns = [
	# listar requitos do projeto
   	url(r'^$', views.requisitos, name='requisitos'),
   	# deletar requisito
   	url(r'(?P<requisito_id>\d+)/excluir/$', views.requisito_deletar, name='requisito_deletar'),
   	# listar funcionalidades
   	url(r'(?P<requisito_id>\d+)/excluir/(?P<funcionalidade_id>\d+)$', views.funcionalidades_deletar, name='deletar_funcionalidade'),
    url(r'(?P<requisito_id>\d+)$', views.funcionalidades, name='funcionalidades'),
]
