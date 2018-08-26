FROM ruby:2.4.0

RUN apt-get update -qq && apt-get install -y -qq sqlite3 libsqlite3-dev nodejs cron
ENV INSTALL_PATH /seminarioime

RUN mkdir -p $INSTALL_PATH

WORKDIR $INSTALL_PATH

COPY seminarioime/Gemfile ./
COPY seminarioime/Gemfile.lock ./

RUN gem install bundler --no-ri --no-rdoc

RUN bundle install --jobs 1

COPY seminarioime/ .

EXPOSE 80

ARG MYSQL_USER=root
ARG MYSQL_PWD=root
ARG MYSQL_HOST=localhost
ARG SECRET_KEY_BASE=aaf1b874cd04bafb045fbe2de715fcb7d05205336b8b434d773595793c1b6426bed029a1a0979b8950b9c1268494706b42bfad22607063edba0d7ca19f45b72d

ENV MYSQL_USER ${MYSQL_USER}
ENV MYSQL_PWD ${MYSQL_PWD}
ENV MYSQL_HOST ${MYSQL_HOST}
ENV SECRET_KEY_BASE ${SECRET_KEY_BASE}

RUN whenever --update-crontab

CMD ["rails", "server", "-b", "0.0.0.0", "-p", "80", "-e", "production"]