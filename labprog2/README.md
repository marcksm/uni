# Seminarioime

[![build status](https://gitlab.com/tecprog2-01-2017/seminarioime/badges/master/build.svg)](https://gitlab.com/tecprog2-01-2017/seminarioime/commits/master)

## Para montar

Entar na pasta seminarioimes e:

```
rvm install 2.4.0
gem install bundler
bundle install
```

```
Para o banco de dados:
rake db:migrate
rake db:seed
```

```
rails server
```

## Para executar testes
```
rails db:environment:set RAILS_ENV=test
rspec
```