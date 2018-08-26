from  django.conf.urls  import  include, url
from django.contrib.auth import views as auth_views

from  .  import  views

urlpatterns = [
    url (r'^$',  views.index,  name='index'),
    url (r'^todos$',  views.all,  name='all'),    
    url(r'^criar$', views.criar, name='criar'),
    url(r'^(?P<p_id>\d+)$', views.id, name='id'),
    url(r'^(?P<p_id>\d+)/editar/$', views.editar, name='editar'),
    url(r'^(?P<p_id>\d+)/remover$', views.remover, name='remover'),
    url(r'(?P<p_id>\d+)/requisitos/', include('requisito.urls')),
    url(r'(?P<p_id>[0-9]+)/tarefa/', include('tarefa.urls')),
]
