#!/bin/bash

echo Configurar e popular o banco de dados
echo Deseja usar o nosso servidor padrão ou configurar um novo?[Y = padrao/n = novo]
read -r temp_ans
if  [ "$temp_ans" = "Y" ]; then
	sed -i "/'USER':/s/.*/\t'USER':'',/" sgrs/settings.py
	sed -i "/'PASSWORD':/s/.*/\t'PASSWORD':'',/" sgrs/settings.py
	sed -i "/'NAME':'/s/.*/\t'NAME':'',/" sgrs/settings.py
	sed -i "/'HOST':/s/.*/\t'HOST':'',/" sgrs/settings.py
	echo Aplicando as migrações ...
	python2 manage.py migrate

	echo Populando as tabelas ...

	python2 manage.py loaddata db.json
	python2 manage.py loaddata db2.json
	python2 manage.py loaddata db3.json
	echo acesse o banco de dados remoto através do comando:
	echo psql -h 35.197.109.194 -U postgres -d jef
	echo senha: 
	exit 1
elif [ "$temp_ans" = "n" ]; then
	echo Configure:
else
	echo resposta invalida rode novamente

fi
echo Insira um usuario valido para acessar psql:
read -r temp_user
echo Digite a senha do usuario:
read -r temp_pass
echo Insira um nome para criar o banco de dados:
read -r temp_db
echo Insira o host do banco de dados, deixar em branco = localhost:
read -r temp_host

if [ -z "$temp_host" ]; then
	temp_host='localhost'
else
	sed -i "/'HOST':/s/.*/\t'HOST':'$temp_host',/" sgrs/settings.py
fi

echo Criando banco de dados ...
echo Digite novamente a senha do usuario
if createdb $temp_db -h $temp_host -U $temp_user -W ; then
	echo $temp_db banco de dados criado.
else
	echo banco existente, rode o comando \'dropdb $temp_db\'
	exit 1
fi
sed -i "/'USER':/s/.*/\t'USER': '$temp_user',/" sgrs/settings.py
sed -i "/'PASSWORD':/s/.*/\t'PASSWORD': '$temp_pass',/" sgrs/settings.py
sed -i "/'NAME':'/s/.*/\t'NAME':'$temp_db',/" sgrs/settings.py
sed -i "/'HOST':/s/.*/\t'HOST': '$temp_host',/" sgrs/settings.py

echo Aplicando as migrações ...
python2 manage.py migrate

echo Populando as tabelas ...

python2 manage.py loaddata db.json
python2 manage.py loaddata db2.json
python2 manage.py loaddata db3.json
