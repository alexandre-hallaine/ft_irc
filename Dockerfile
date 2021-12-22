FROM alpine:latest

RUN apk add --no-cache make g++ clang

COPY . /irc

WORKDIR /irc

RUN make debug

EXPOSE 6667

ENTRYPOINT [ "/irc/ircserv", "$PORT", "$PASSWORD" ]
