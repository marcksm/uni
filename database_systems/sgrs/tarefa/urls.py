from  django.conf.urls  import  url
from django.contrib.auth import views as auth_views
from  .  import  views

urlpatterns = [
    url (r'^$',  views.index,  name='index'),
    url(r'^criar$', views.criar, name='criar'),
    url(r'^(?P<t_id>[0-9]+)$', views.ler, name='ler'),
    url(r'^(?P<t_id>[0-9]+)/editar/$', views.editar, name='editar'),
    url(r'^(?P<t_id>[0-9]+)/remover/$', views.remover, name='remover')
]
