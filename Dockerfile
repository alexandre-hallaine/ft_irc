FROM alpine:latest

RUN apk add --no-cache make g++ clang

COPY . /irc

WORKDIR /irc

RUN make

EXPOSE 6667

ENTRYPOINT [ "/irc/ircserv", "6667", "password" ]