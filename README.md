<p align="center">
  <image alt="shiba" src="files/shibaicon.jpg">
</p>

# ShibRC

Simple IRC Server based on the RFC (mainly 2812) written in C++.

ShibRC does not support server-server communication and is best used with **irssi** (or any client that send packets terminated with `\r\n`).

# Connect

### :warning: Our URL to connect has changed, it's now: shibrc.fr :warning:

If you'd like to try our server without having to build it you can connect to our public server `shibrc.fr` using the password `password` with the following commands :

- First install a client, here we'll use **irssi** since it is the one we chose to do the project with :

```bash
sudo apt install irssi
```

- Or install with brew if you are at 42 :

```bash
brew install irssi
```

- Then simply connect to the server using this command :

```bash
irssi -c shibrc.fr -w password
```

> For less typing you could do `/SERVER ADD -network shibrc shibrc.fr 6667 password` inside of **irssi** and then you can simply connect to our server by doing `irssi -c shibrc`.

> As you may have noticed the `oper_password` specified in the config file doesn't work on our server `shibrc.fr` in order to avoid abuse, if you'd like to try our operator commands and permissions you can simply build the server locally.

# Run

Do `make` and then run :

```bash
./ircserv <port> <password>
```

Or you could also do `make run` which directly starts the server on the port 6667 and with the password password.

![makerun](/files/makerun.PNG)

You can modify the config file `default.config` to your convinience as well as the files.

If you'd like to see what packets we received and send you can use `make debug` *make sure that you did a `make clean` before.*

![makedebug](/files/makedebug.PNG)

Finally we added a bot, to run it go inside the bot folder and do `make` and then provide the needed arguments or simply do `make run`, the bot will create / join the #bot channel and you will be able to use the commands from there by using the prefix `!`. The bot handles a few commands such as :
```
help
flip
roll
nick
quit
```

## Handled commands

This following list of commands are handled on our server, since most of them were not asked by the subject there is certain masks and parameters we may have ommited for our convinience, some commands might not be perfect aswell so if you find any issues feel free to let us know  :

```
- INVITE
- JOIN
- KICK
- LIST
- NAMES
- PART
- TOPIC
- MODE
- NICK
- OPER
- QUIT
- USER
- KILL
- PING
- PONG
- AWAY
- ISON
- USERHOST
- USERS (handled but disabled)
- WALLOPS
- NOTICE
- PRIVMSG
- ADMIN
- INFO
- LUSERS
- MOTD
- TIME
- VERSION
- WHO
- WHOIS
- WHOWAS
```

## Handled modes :

The following list of modes are handled by the server, yet again there may be omitted functionnality or errors :

```
USER MODES :
- a : away
- i : invisible
- w : wallops
- r : restricted
- o : operator

CHANNEL MODES :
for users :
    - O : channel creator
    - o : channel operator
    - v : voice
for channels :
    - i : invite only
    - m : moderated
    - n : outside privmsg disabled
    - p : private
    - t : topic locked
    - k : key locked
    - l : user limit
```

if you need a detailed description of each mode click [HERE](https://www.alien.net.au/irc/chanmodes.html)

# DOCS

*we recommend following the 281x versions instead as they not experimental*
- [RFC1459](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC2810](https://datatracker.ietf.org/doc/html/rfc2810)
- [RFC2811](https://datatracker.ietf.org/doc/html/rfc2811)
- [RFC2812](https://datatracker.ietf.org/doc/html/rfc2812)
- [RFC2813](https://datatracker.ietf.org/doc/html/rfc2813)

## MADE WITH LOVE BY :

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/alexandre-hallaine/"><img src="https://avatars.githubusercontent.com/u/52411215?v=4" width="100px;" alt=""/><br /><sub><b>Alexandre Hallaine (ahallain)</b></sub></a><br /><a href="https://profile.intra.42.fr/users/ahallain" title="Intra 42"><img src="https://img.shields.io/badge/Paris-FFFFFF?style=plastic&logo=42&logoColor=000000" alt="Intra 42"/></a></td>
    <td align="center"><a href="https://github.com/assxios/"><img src="https://avatars.githubusercontent.com/u/53396610?v=4" width="100px;" alt=""/><br /><sub><b>Assxios (droge)</b></sub></a><br /><a href="https://profile.intra.42.fr/users/droge" title="Intra 42"><img src="https://img.shields.io/badge/Paris-FFFFFF?style=plastic&logo=42&logoColor=000000" alt="Intra 42"/></a></td>
    <td align="center"><a href="https://github.com/Nimon77/"><img src="https://avatars.githubusercontent.com/u/11821952?v=4" width="100px;" alt=""/><br /><sub><b>Nimon77 (nsimon)</b></sub></a><br /><a href="https://profile.intra.42.fr/users/nsimon" title="Intra 42"><img src="https://img.shields.io/badge/Paris-FFFFFF?style=plastic&logo=42&logoColor=000000" alt="Intra 42"/></a></td>
  </tr>
</table>
<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->
