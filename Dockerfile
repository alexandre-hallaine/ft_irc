FROM alpine:latest

RUN apk add --no-cache make g++ clang

COPY . /irc

WORKDIR /irc

RUN make debug

ENV PORT 6667
ENV PASSWORD password

EXPOSE 6667

ENTRYPOINT [ "/bin/sh", "-c", "/irc/ircserv $PORT $PASSWORD" ]
